#ifndef WINDOWLOADSTUDENT_H
#define WINDOWLOADSTUDENT_H

/**
  * \file WindowLoadStudent.h
  * \brief Fenêtre affichant les différentes caractéristiques d'un étudiant présentes dans la base de données.
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include <QtWidgets>
#include <QList>
#include "WindowRecordConsultation.h"
#include "WindowNewStudent.h"
#include "RecordManager.h"
#include "Record.h"
#include "Semester.h"
#include "RecordManager.h"
#include "UVResult.h"
#include "DBManager.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QString>
#include <QList>

/**
 * @brief Cette classe objet permet de visualiser les différentes inscriptions d'un étudiant ainsi que son parcours universitaire au
 * sein de l'établissement.
 */
class WindowLoadStudent : public QWidget
{
    Q_OBJECT
public:
    WindowLoadStudent();
protected:
    QVBoxLayout* mainLayout;
    QListWidget* listStudent;
    QListWidgetItem* labelLogin;
    WindowRecordConsultation* newWindowRecordConsultation;
    QPushButton* buttonOpenWindowNewStudent;
    WindowNewStudent* windowNewStudent;

signals:
    //void studentLoaded(QString login);
    void itemDoubleClicked(QListWidgetItem *item);
private slots:
    void selectStudent(QListWidgetItem* item);
    void openWindowNewStudent();
};

#endif // WINDOWLOADSTUDENT_H
