#include "RecordManager.h"

RecordManager::RecordManager(){}

RecordManager* RecordManager::uniqueInstance=0;

RecordManager& RecordManager::giveInstance(){
    if (uniqueInstance==0){
        uniqueInstance= new RecordManager;
        uniqueInstance->load();
    }
    return *uniqueInstance;
}

void RecordManager::addRecord(QString login, QString name, QString surname, unsigned int nbSemesters){
    l_record.push_back(new Record(login, name, surname, nbSemesters));
}

void RecordManager::freeInstance(){
    if (uniqueInstance!=0)
        delete uniqueInstance;
    uniqueInstance = 0;
}

Record* RecordManager::findRecordByLogin(QString login){
    QList<Record*>::iterator it;
    for (it = l_record.begin(); it!=l_record.end();it++){
        if ((*it)->getLogin()==login) return *it;
    }
}

void RecordManager::load(){
    QString login;
    QString name;
    QString surname;
    QList<Record*> list_record;
    QSqlQuery* query;
    unsigned int nombre_select=0;
    //RecordManager& m=RecordManager::getInstance();

    query = new QSqlQuery("SELECT identifiant, nom, prenom FROM ETU_table;");

    DatabaseManager& db=DatabaseManager::getInstanceDB();
    if(db.getMyDB().isOpen()){

        while(query->next())
        {

            nombre_select++;
            login = query->value(0).toString();
            name = query->value(1).toString();
            surname = query->value(2).toString();
            addRecord(login, name, surname);
            qDebug()<<"Étudiant"<<login;

        }
    }
/*
    if(nombre_select == 0)
    {
        throw UTProfilerException("Erreur au chargement, la formation n'existe pas");
    }
*/
}

void RecordManager::save(){
    DatabaseManager& db=DatabaseManager::getInstanceDB();
    qDebug()<<"Test de l'ouverture de la BDD";
    if(db.getMyDB().isOpen()){
        qDebug()<<"Début des query";
        QSqlQuery* query2 = new QSqlQuery(QString("DELETE FROM ETU_table"),db.getMyDB());
        query2->exec();
    }

    for(unsigned int i = 0; i<l_record.size(); i++)
    {

            db.updateTableStudent(
                      l_record.at(i)->getLogin(),
                      l_record.at(i)->getName(),
                      l_record.at(i)->getSurname()
                      );
    }

}

RecordManager::~RecordManager(){
    save();
}
