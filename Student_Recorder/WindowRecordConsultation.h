#ifndef WINDOWRECORDCONSULTATION_H
#define WINDOWRECORDCONSULTATION_H

/**
  * \file WindowRecordConsultation.h
  * \brief Fenêtre affichant les différentes UV dans la base de données actuelle
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include <QtWidgets>
#include <QString>
#include "windownewstudent.h"
#include "WindowNewSemester.h"
#include "RecordManager.h"
#include "UVResult.h"
#include "Semester.h"
#include "UTProfiler.h"

/**
 * @brief Cette classe permet de visualiser les différentes inscriptions et les différents enregistrements présents dans la base de données.
 */
class WindowRecordConsultation: public QWidget //:public QMainWindow
{
    Q_OBJECT
public:
    WindowRecordConsultation(QString login);
    void setStudent(Record* newCurrentStudent);

protected:
    QPushButton* buttonOpenWindowNewStudent;
    QPushButton* buttonOpenWindowNewSemester;
    QWidget* centralView;
    QWidget* m_identityStudent;
    QToolBar* toolbar;
    //WindowNewStudent* windowNewStudent;
    WindowNewSemester* windowNewSemester;
    QVBoxLayout* m_identityStudentBox;
    QLabel* m_nameStudent;
    QLabel* m_surnameStudent;
    QMenu* menuFile;
    QAction* loadStudent;
    Record* m_currentStudent;
    QTableWidget* m_tableUV;
signals:

public slots:

    void openWindowNewSemester();
    //void setStudent(QListWidgetItem* item);
private slots:
};


#endif // WINDOWRECORDCONSULTATION_H
