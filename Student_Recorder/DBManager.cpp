/**
  * \file DBManager.cpp
  * \brief Objet permettant de gérer la base de données : définition de ses méthodes non-inline
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 11 juin 2014
  */

#include "DBManager.h"
#include <QList>
#include <QVariant>
#include <QDebug>

/**
 * @brief Ouverture de la base de données.
 *
 * @return Valeur booléenne (vrai si la base de données a bien été ouverte, sinon faux).
 */
bool DatabaseManager::openDB(){
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    //db.setDatabaseName("C:/Users/Hugo/Dropbox/UTC/LO21_projet/Hugo/Projet_lo21/BDD_projet_LO21.db");
    db.setDatabaseName("C:/Users/Hugo/Dropbox/UTC/LO21_projet/Projet_final/Projet_lo21/BDD_projet_LO21.db");
    //db.setDatabaseName("/Users/Olympio/Dropbox/LO21_projet/Hugo/Projet_lo21/BDD_projet_LO21.db");
    // Open database

    return db.open();
}

/**
 * @brief Permet de connaître la dernière erreur rencontrée par la classe DatabaseManager.
 *
 * @return Erreur SQL.
 */
QSqlError DatabaseManager::lastError(){
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

/**
 * @brief Ferme la base de données.
 *
 * @return Vrai.
 */
bool DatabaseManager::closeDB(){
    // Close database
    db.close();

    return true;
}
/**
 * @brief Constructeur de la classe.
 */

DatabaseManager::DatabaseManager(){
    openDB();

}

/**
 * @brief Destructeur de la classe DatabaseManager.
 */
DatabaseManager::~DatabaseManager(){
    closeDB();
}

/**
 * @brief Création de l'Handler.
 */
DatabaseManager::Handler DatabaseManager::handler=Handler();

/**
 * @return Une référence sur l'instance unique de la classe DatabaseManager, après création si non existante auparavant.
 */
DatabaseManager& DatabaseManager::getInstanceDB(){
    if (!handler.instance) handler.instance = new DatabaseManager;
    return *handler.instance;
}

/**
 * @brief Si l'instance unique existe, elle est supprimée avant de la réinitialiser au pointeur NULL.
 */
void DatabaseManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

//Insertion dans la table des uvs dans la BDD
/**
 * @brief Cette méthode est appelée à la fermeture de l'application.
 * Elle permet de mettre à jour de la table contenant toutes les UV et leurs caractéristiques dans la base de données de manière définitive.
 *
 * @param a Ouverture de l'UV aux semestres d'automne (Oui|Non).
 * @param p Ouverture de l'UV aux semestres de printemps (Oui|Non).
 * @param c Code correspondant à l'UV.
 * @param t Titre, intitulé de l'UV.
 * @param cs Nombre de Crédits CS en ECTS octroyés par validation de l'UV.
 * @param tm Nombre de Crédits TM en ECTS octroyés par validation de l'UV.
 * @param tsh Nombre de Crédits TSH en ECTS octroyés par validation de l'UV.
 * @param sp Nombre de Crédits SP en ECTS octroyés par validation de l'UV.
 */
void DatabaseManager::updateTableUV( bool a, bool p, QString c,QString t, unsigned int cs, unsigned int tm, unsigned int tsh, unsigned int sp)
{
    DatabaseManager& db=DatabaseManager::getInstanceDB();

    if(db.getMyDB().isOpen() && c!="")
    {
        QSqlQuery query;
        QSqlQuery* query1;

        query1 = new QSqlQuery(QString("SELECT * from UV_table where code = '%1'").arg(c));

        if(query1->next())
        {
            query.prepare("UPDATE UV_table SET automne=:a, printemps=:pr, code=:co, titre=:ti, CS=:cs, TM=:tm, TSH=:tsh, SP=:sp WHERE code = :co");
        }
        else
        {
            query.prepare("INSERT INTO UV_table (automne, printemps, code, titre, CS, TM, TSH, SP ) VALUES (:a, :pr, :co, :ti, :cs, :tm, :tsh, :sp)");
        }

        query.bindValue(":a",a);
        query.bindValue(":pr",p);
        query.bindValue(":co",c);
        query.bindValue(":ti",t);
        query.bindValue(":cs",cs);
        query.bindValue(":tm",tm);
        query.bindValue(":tsh",tsh);
        query.bindValue(":sp",sp);


        query.exec();

    }

}

/**
 * @brief Permet la mise à jour des tables liées aux formations dans la base de données.
 * @param c Code correspondant à la formation.
 * @param t Intitulé de la formation.
 * @param CS Nombre de crédits CS à valider.
 * @param TM Nombre de crédits TM à valider.
 * @param TSH Nombre de crédits TSH à valider.
 * @param SP Nombre de crédits SP à valider.
 * @param B 1 si c'est une Branche, 0 sinon.
 * @param uv Liste de pointeurs d'UV.
 * @param uvcons Liste de pointeurs sur les UV conseillées.
 * @param filiere Liste de pointeurs sur les filières possibles d'une Branche donnée.
 */
void DatabaseManager::updateTablesFormations(const QString c, const QString t, unsigned int CS, unsigned int TM, unsigned int TSH,unsigned int SP,bool B,QList<UV*> uv,QList<UV*> uvcons,QList<Formation*> filiere){
    DatabaseManager& db=DatabaseManager::getInstanceDB();
    if(db.getMyDB().isOpen() && c!="")
    {
        QSqlQuery* query;
        QSqlQuery query3;

        db.getMyDB().transaction();

        if(uv.length()>0){
            for(int i=0;i<uv.length();i++){
                QSqlQuery query1;
                query1.prepare("INSERT INTO Formation_UV_table (code, uv) VALUES (:a,:u)");
                query1.bindValue(":a",c);
                query1.bindValue(":u",uv[i]->getCode());
                query1.exec();
            }
        }
        if(uvcons.length()>0){
            for(int i=0;i<uvcons.length();i++){
                query = new QSqlQuery(QString("INSERT INTO Formation_UVCons_table (code,uv) VALUES ('%1','%2')").arg(c).arg(uvcons[i]->getCode()));
                query->exec();
            }
        }

        if(filiere.length()>0){
            QSqlQuery query1;
            for(int i=0;i<filiere.length();i++){
                query1.prepare("INSERT INTO Formation_Branche_Filiere (branche,filiere) VALUES (:c,:f)");
                query1.bindValue(":c",c);
                query1.bindValue(":f",filiere[i]->getCode());
                query1.exec();
            }
        }

        query3.prepare("INSERT INTO Formations (code, nom, CS, TM, TSH, SP, branche ) VALUES (:co, :ti, :cs, :tm, :tsh, :sp, :b)");


        query3.bindValue(":co",c);
        query3.bindValue(":ti",t);
        query3.bindValue(":cs",CS);
        query3.bindValue(":tm",TM);
        query3.bindValue(":tsh",TSH);
        query3.bindValue(":sp",SP);
        query3.bindValue(":b",B);


        query3.exec();

        db.getMyDB().commit();
    }
}

void DatabaseManager::updateTableStudent(QString idStudent, QString n, QString p)
{
    DatabaseManager& db=DatabaseManager::getInstanceDB();

    if(db.getMyDB().isOpen())
    {
        QSqlQuery query;
        QSqlQuery* query1;

        query1 = new QSqlQuery(QString("SELECT * from ETU_table where identifiant = '%1'").arg(idStudent));

        if(query1->next())
        {
            query.prepare("UPDATE ETU_table SET identifiant=:id, nom=:n, prenom=:p WHERE identifiant=:id;");
        }
        else
        {
            query.prepare("INSERT INTO ETU_table (identifiant, nom, prenom) VALUES (:id, :n, :p);");
        }

        query.bindValue(":id",idStudent);
        query.bindValue(":n",n);
        query.bindValue(":p",p);
        query.exec();

    }

}

 void DatabaseManager::updateTableInscriptions(QString uv, QString s, QString r, QString id){
     DatabaseManager& db=DatabaseManager::getInstanceDB();
    if(db.getMyDB().isOpen())
    {
        QSqlQuery query;
        QSqlQuery* query1;

        query1 = new QSqlQuery(QString("SELECT * from INSCRIPTIONS_table where identifiant = '%1';").arg(id));

        if(query1->next())
        {
            query.prepare("UPDATE INSCRIPTIONS_table SET uv=:uv, semestre=:s, resultat=:r, id=:id WHERE identifiant=:id;");
        }
        else
        {
            query.prepare("INSERT INTO INSCRIPTIONS_table (uv, semestre, resultat, id) VALUES (:uv, :s, :r, :id);");
        }

        query.bindValue(":uv",uv);
        query.bindValue(":s",s);
        query.bindValue(":r",r);
        query.bindValue(":id",id);


        query.exec();
        qDebug() << "Record sauvegardés";
    }
}
//return QFile::remove("../LO21_project.db");


