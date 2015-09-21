/**
  * \file DBManager.h
  * \brief Définition du gestionnaire de la base de données, de sest attributs et méthodes
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlQuery>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include "Formation.h"

/**
 * @brief Cette classe permet de gérer la base de données utilisées pour la gestion des UV, des branches, des formations ainsi que des
 * inscriptions des étudiants.
 */
class DatabaseManager : public QObject{
private:
    /**
     * @brief La base de données.
     */
    QSqlDatabase db;
    friend struct Handler;
    /**
     * @brief Permet de gérer l'instance unique.
     */
    struct Handler{
        /**
         * @brief L'instance unique de la classe DatabaseManager.
         */
        DatabaseManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;
    DatabaseManager();
    ~DatabaseManager();
public:
    bool openDB();
    bool closeDB();
    QSqlError lastError();
    static DatabaseManager& getInstanceDB();
    static void libererInstance();
    /**
     * @brief
     * @return La base de données utilisée.
     */
    QSqlDatabase getMyDB(){return db;}
    void updateTableUV( bool a, bool p, QString c, QString t, unsigned int cs, unsigned int tm, unsigned int tsh, unsigned int sp);
    void updateTablesFormations(const QString c, const QString t, unsigned int CS, unsigned int TM, unsigned int TSH,unsigned int SP,bool B,QList<UV*> uv,QList<UV*> uvcons,QList<Formation*> filiere);
    void updateTableStudent(QString idStudent, QString n, QString p);
    void updateTableInscriptions(QString uv, QString s, QString r, QString id);
};

#endif // DBMANAGER_H
