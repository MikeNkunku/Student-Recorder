#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

/**
  * \file RecordManager.h
  * \brief Définition du gestionnaire d'enregistrements, de ses attributs et méthodes
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "Record.h"
#include "Semester.h"
#include "DBManager.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QString>
#include <QList>

/**
 * @brief Cette classe permet de gérer les différents enregistrements possibles dans la base de données, notamment les données entrées par
 * un étudiant ainsi que ses inscriptions.
 */
class RecordManager
{
public:
    static RecordManager& giveInstance();
    static void freeInstance();
    /**
     * @return Une liste de pointeurs sur des enregistrements.
     */
    QList<Record*>* getListRecords(){return &l_record;}
    void addRecord(QString login, QString name, QString surname, unsigned int nbSemesters=0);
    void load();
    void save();
    Record* findRecordByLogin(QString login);
protected:
    /**
     * @brief Instance unique de la classe RecordManager.
     */
    static RecordManager* uniqueInstance;
    RecordManager();
    RecordManager(const RecordManager&);
    virtual ~RecordManager();
    void operator= (const RecordManager&);
    /**
     * @brief Liste de pointeurs sur des enregistrements.
     */
    QList<Record*> l_record;

};

#endif // RECORDMANAGER_H
