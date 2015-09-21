#include "UTProfiler.h"
#include "DBManager.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <iostream>

QStringList CategorieToStringList(QMap<QString,int> c){
    QStringList cat;
    QString CS,TM,TSH,SP;

    if(c.value("CS")!=0)
        CS="CS";
    else CS="";
    if(c.value("TM")!=0)
        TM="TM";
    else TM="";
    if(c.value("TSH")!=0)
        TSH="TSH";
    else TSH="";
    if(c.value("SP")!=0)
        SP="SP";
    else SP="";
    cat<<CS<<TM<<TSH<<SP;
    return cat;
}

QStringList UV::getCategorie() const{
    return CategorieToStringList(this->categorie);
}


UVManager::UVManager():uvs(0),nbUV(0),nbMaxUV(0),modification(false){
}


//Chargement de toutes les uvs en mémoire si aucun paramètre, sinon juste l'UV dont le code est envoyé
void UVManager::load()
{

    bool automne;
    bool printemps;
    QString code;
    QString titre;
    //Categorie categorie
    QMap<QString,int> cat;
    int nombre_select = 0;
    QSqlQuery* query;
    DatabaseManager& dbu=DatabaseManager::getInstanceDB();


    query = new QSqlQuery("SELECT * FROM UV_table",dbu.getMyDB());

    while(query->next())
    {

        nombre_select++;
        automne = query->value(0).toBool();
        printemps = query->value(1).toBool();

        code = query->value(2).toString();
        titre = query->value(3).toString();

        cat.insert("CS",query->value(4).toInt());
        cat.insert("TM",query->value(5).toInt());
        cat.insert("TSH",query->value(6).toInt());
        cat.insert("SP",query->value(7).toInt());

        ajouterUV(code,titre,cat,automne,printemps);

    }
    std::cout<<nombre_select<<"\n";
    if(nombre_select == 0)
    {
        throw UTProfilerException("Erreur au chargement, l'UV n'existe pas");
    }



}



//Sauvegarder des uvs dans la BDD

void UVManager::save()
{
    qDebug()<<"nbUv = "<<nbUV;
    DatabaseManager& db=DatabaseManager::getInstanceDB();

    for(unsigned int i = 0; i<nbUV; i++)
    {
        db.updateTableUV(uvs[i]->ouvertureAutomne(),
                      uvs[i]->ouverturePrintemps(),
                      uvs[i]->getCode(),
                      uvs[i]->getTitre(),
                      uvs[i]->getNbCreditsCS(),
                      uvs[i]->getNbCreditsTM(),
                      uvs[i]->getNbCreditsTSH(),
                      uvs[i]->getNbCreditsSP()
//                      CategorieToStringList(uvs[i]->getCategorie())
                      );
    }

}

UVManager::~UVManager(){
    DatabaseManager& db=DatabaseManager::getInstanceDB();

    if(getModification())
        save();

    for(unsigned int i=0; i<nbUV; i++) delete uvs[i];
    delete[] uvs;
}

void UVManager::addItem(UV* uv){
    if (nbUV==nbMaxUV){
        UV** newtab=new UV*[nbMaxUV+10];
        for(unsigned int i=0; i<nbUV; i++) newtab[i]=uvs[i];
        nbMaxUV+=10;
        UV** old=uvs;
        uvs=newtab;
        delete[] old;
    }
    uvs[nbUV++]=uv;
}

void UVManager::ajouterUV(const QString& c, const QString& t, QMap<QString,int> cat, bool a, bool p){
    if (trouverUV(c)) {
        throw UTProfilerException(QString("erreur, UVManager, UV ")+c+QString("déja existante"));
    }else{
        UV* newuv=new UV(c,t,cat,a,p);
        addItem(newuv);
        setModification();
    }
}

UV* UVManager::trouverUV(const QString& c)const{
    for(unsigned int i=0; i<nbUV; i++)
        if (c==uvs[i]->getCode()) return uvs[i];
    return 0;
}

UV& UVManager::getUV(const QString& code){
    UV* uv=trouverUV(code);
    if (!uv) throw UTProfilerException("erreur, UVManager, UV inexistante",__FILE__,__LINE__);
    return *uv;
}


const UV& UVManager::getUV(const QString& code)const{
    return const_cast<UVManager*>(this)->getUV(code);
        // on peut aussi dupliquer le code de la méthode non-const
}

UVManager::Handler UVManager::handler=Handler();

UVManager& UVManager::getInstance(){
    if (!handler.instance) handler.instance = new UVManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

void UVManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}


void UVManager::insertUV(QString code, QString titre, QMap<QString,int> cat,bool a, bool p){
    DatabaseManager& db = DatabaseManager::getInstanceDB();


    db.updateTableUV(a,p,code,titre,cat.value("CS"),cat.value("TM"),cat.value("TSH"),cat.value("SP"));
}
