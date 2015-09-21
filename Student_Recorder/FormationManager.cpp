/**
  * \file FormationManager.cpp
  * \brief Définition des méthodes non-inline de la classe FormationManager.
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 11 juin 2014
  */


#include "FormationManager.h"
#include "DBManager.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <iostream>
#include <QSqlQuery>

/****************** FORMATION MANAGER *************************/

/**
 * @brief Constructeur de l'Handler unique de la classe FormationManager.
 */
FormationManager::Handler FormationManager::handler=Handler();

/**
 * @return L'instance unique de la classe FormationManager après création si elle n'existait pas avant.
 */
FormationManager& FormationManager::getInstance(){
    if (!handler.instance) handler.instance = new FormationManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

/**
 * @brief Suppression de l'instance unique de la mémoire, puis réinitialisation de l'instance au pointeur NULL.
 */
void FormationManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

/**
 * @brief Destructeur de la classe qui lance la sauvegarde dans la base de données.
 */
FormationManager::~FormationManager(){
    this->save();
}

/**
 * @brief Permet d'ajouter une formation à la liste des formations, si elle n'est pas déjà présente dans la liste.
 * Si c'est le cas, une exception est déclenchée avec un message d'erreur.
 * @param c Code de la formation.
 * @param t Titre de la formation.
 * @param CS Nombre de crédits CS à valider.
 * @param TM Nombre de crédits TM à valider.
 * @param TSH Nombre de crédits TSH à valider.
 * @param SP Nombre de crédits SP à valider.
 * @param B 1 si la formation est une Branche, 0 sinon.
 */
void FormationManager::addFormation(const QString& c, const QString& t, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP, bool B)
{
    Formation* F=0;

    if((!fmts.empty()) && fmts.contains(&getFormation(c)))
        throw UTProfilerException("La formation est déjà présente !");

    if(B){
        F=new Branche(c,t,CS,TM,TSH,SP,B);
    }
    else {F = new Filiere(c,t,CS,TM,TSH,SP,B);}

    fmts.append(F);
}

/**
 * @brief Méthode qui permet de charger en mémoire les différentes formations présentes dans la base de données.
 */
void FormationManager::load(){
    QString c;
    QString t;
    unsigned int CS;
    unsigned int TM;
    unsigned int TSH;
    unsigned int SP;
    QList<UV*> UVCons;
    bool B;
    QSqlQuery* query;
    QSqlQuery* query1,*query2,*query3;
    unsigned int nombre_select=0;
    UVManager& m=UVManager::getInstance();
    DatabaseManager& db=DatabaseManager::getInstanceDB();

    query = new QSqlQuery("SELECT * FROM Formations",db.getMyDB());


    if(db.getMyDB().isOpen()){

        while(query->next())
        {
            nbFormations++;
            c = query->value(0).toString();
            t = query->value(1).toString();

            CS = query->value(2).toInt();
            TM = query->value(3).toInt();
            TSH = query->value(4).toInt();
            SP = query->value(5).toInt();
            B = query->value(6).toBool();
            addFormation(c,t,CS,TM,TSH,SP,B);

        }
        for(QList<Formation*>::iterator it= fmts.begin();it!=fmts.end();++it){

            query1 = new QSqlQuery(QString("SELECT code, uv FROM Formation_UV_table WHERE code='%1'" ).arg((*it)->getCode()),db.getMyDB());

            while(query1->next())
            {
                (*it)->ajouterUV(&m.getUV(query1->value(1).toString()));
            }
            query2 = new QSqlQuery(QString("SELECT code, uv FROM Formation_UVCons_table WHERE code='%1'" ).arg((*it)->getCode()),db.getMyDB());
            while(query2->next())
            {
                (*it)->ajouterUVCons(&m.getUV(query2->value(1).toString()));
            }
            query3 = new QSqlQuery(QString("SELECT branche, filiere FROM Formation_Branche_Filiere WHERE branche='%1'" ).arg((*it)->getCode()),db.getMyDB());
            while(query3->next())
            {
                (*it)->ajouterFiliere(&getFormation(query3->value(1).toString()));
                getFormation(query3->value(1).toString()).ajouterParent((*it));
            }
        }
    }

    if(nbFormations == 0)
    {
        throw UTProfilerException("Aucune formation dans la base");
    }
}

/**
 * @brief Méthode qui sauvegarde les formations dans la base de données.
 */
void FormationManager::save()
{
    DatabaseManager& db=DatabaseManager::getInstanceDB();
    if(db.getMyDB().isOpen()){
        QSqlQuery* query2 = new QSqlQuery(QString("DELETE FROM Formation_UV_table"),db.getMyDB());
        query2->exec();
        query2=new QSqlQuery(QString("DELETE FROM Formation_UVCons_table"),db.getMyDB());
        query2->exec();
        query2=new QSqlQuery(QString("DELETE FROM Formation_Branche_Filiere"),db.getMyDB());
        query2->exec();
        query2=new QSqlQuery(QString("DELETE FROM Formations"),db.getMyDB());
        query2->exec();
    }



    for(unsigned int i = 0; i<nbFormations; i++)
    {

            db.updateTablesFormations(
                      fmts[i]->getCode(),
                      fmts[i]->getTitre(),
                      fmts[i]->getCS(),
                      fmts[i]->getTM(),
                      fmts[i]->getTSH(),
                      fmts[i]->getSP(),
                      fmts[i]->estComposite(),
                      fmts[i]->getUVList(),
                      fmts[i]->getUVConsList(),
                      fmts[i]->getFiliereList()
                      );
    }

}

/**
 * @param c Code de la formation recherchée.
 * @return Un pointeur sur la formation si elle existe, sinon le pointeur NULL.
 */
Formation* FormationManager::trouverFormation(const QString c) const{
    for(QList<Formation*>::const_iterator it= fmts.begin();it!=fmts.end();++it){
        if((*it)->getCode()==c)
            return (*it);
    }

}

/**
 * @param code Code de la formation recherchée.
 * @return Une référence sur la formation recherchée si existante, sinon une exception est déclenchée.
 */
Formation& FormationManager::getFormation(const QString code){
    Formation* f=trouverFormation(code);
    if (!f) throw UTProfilerException("erreur, FormationManager, Formation inexistante");
    return *f;
}

/**
 * @brief Constructeur de la classe FormationManager initialisant le nombre de Formations à 0, modification à faux et créant une liste vide
 * de pointeurs de Formations.
 */
FormationManager::FormationManager():nbFormations(0),fmts(QList<Formation*>()),modification(0){

}
