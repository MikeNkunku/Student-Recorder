/**
  * \file WindowsLoadStudent.cpp
  * \brief Définition des méthodes de la classe WindowLoadStudent non-inline
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "windowloadstudent.h"

/**
 * @brief Constructeur de la classe WindowLoadStudent qui permet de charger le parcours universitaire d'un étudiant donné.
 */
WindowLoadStudent::WindowLoadStudent()
{
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    buttonOpenWindowNewStudent = new QPushButton(tr("Ajouter un étudiant"));
    connect(buttonOpenWindowNewStudent, SIGNAL(clicked()), this, SLOT(openWindowNewStudent()));
    mainLayout->addWidget(buttonOpenWindowNewStudent);
    listStudent = new QListWidget(this);
    for (int i = 0; i<RecordManager::giveInstance().getListRecords()->size();i++){
        labelLogin = new QListWidgetItem(RecordManager::giveInstance().getListRecords()->at(i)->getLogin(), listStudent);
        //labelLogin->setText(RecordManager::giveInstance().getListRecords().at(i).getSurname());
    }
    connect(listStudent, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(selectStudent(QListWidgetItem*)));
    //connect(listStudent, SIGNAL(itemDoubleClicked(QListWidgetItem*)), qApp, SLOT(MainWindow::setStudent(QListWidgetItem*)));
    mainLayout->addWidget(listStudent);
    setLayout(mainLayout);
}

/**
 * @brief Cette méthode permet de choisir un étudiant parmi tous ceux dont le dossier est présent dans la base de données.
 * @param Pointeur vers un objet.
 */
void WindowLoadStudent::selectStudent(QListWidgetItem* item)
{
    qDebug() << item->text();
    QList<Record*>::iterator it;
    it = RecordManager::giveInstance().getListRecords()->begin();
    while ((*it)->getLogin() != item->text() /*it!=RecordManager::getListRecords()->end()*/){
        it++;
    }
    Record* selectedStudent = (*it);
    QSqlQuery *query1;
    query1 = new QSqlQuery(QString("SELECT nom, semestre FROM Semestre_table WHERE identifiant='%1';" ).arg(selectedStudent->getLogin()));
    DatabaseManager& db=DatabaseManager::getInstanceDB();
    if(db.getMyDB().isOpen()){
        while(query1->next())
        {
            selectedStudent->addSemester(query1->value(0).toString(), query1->value(1).toString());
            qDebug()<<query1->value(0).toString()<<query1->value(1).toString();
        }
        //selectedStudent->getListSemesters().at(3)->addUVFollowedThisSemester("LO21", "C");
    }
    qDebug()<<"Suppression de query1";
    delete query1;
    if(db.getMyDB().isOpen()){
        qDebug()<<"BDD ouverte 2";
    QList<Semester*> studentSemesterList=selectedStudent->getListSemesters();
    QList<Semester*>::iterator itSemester;
        for(itSemester = studentSemesterList.begin(); itSemester != studentSemesterList.end() ; ++itSemester){
            QString nameSemester = (*itSemester)->getNameSemester();
            qDebug()<< "Nom du semestre : "<<nameSemester;
            Semester* selectedSemester = (*itSemester);
            QSqlQuery *query2;
            query2 = new QSqlQuery(QString("SELECT uv, resultat FROM INSCRIPTIONS_table WHERE id='%1' AND semestre='%2';").arg(selectedStudent->getLogin(), nameSemester));
            while(query2->next()) {
                (*itSemester)->addUVFollowedThisSemester(query2->value(0).toString(), query2->value(1).toString());
//               (*itSemester)->addUVFollowedThisSemester(tr("%1").arg(query2->value(0).toString()), tr("%1").arg(query2->value(1).toString()));
                QString tmpCode = query2->value(0).toString();
                QString tmpResult = query2->value(1).toString();
                qDebug()<<"UV : "<<tmpCode<< "Note :"<<tmpResult;
            }
            delete query2;
        }
    }
    qDebug()<<"Login de l'étudiant : "<<selectedStudent->getLogin();
    newWindowRecordConsultation = new WindowRecordConsultation(selectedStudent->getLogin());
    close();
    newWindowRecordConsultation->show();
}

void WindowLoadStudent::openWindowNewStudent()
{
    windowNewStudent = new WindowNewStudent;
    windowNewStudent->show();
}



