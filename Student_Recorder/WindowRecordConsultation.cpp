/**
  * \file WindowRecordConsultation.cpp
  * \brief Définition des méthodes non-inline de la classe WindowRecordConsultation
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "WindowRecordConsultation.h"

/**
 * @brief Constructeur de la classe WindowRecordConsultation qui permet de consulter le parcours d'une personne dont le login est déjà
 * connu car présent dans la base de données.
 * @param login Login de la personne.
 */
WindowRecordConsultation::WindowRecordConsultation(QString login)
{
    centralView = new QWidget();
    centralView->setFixedWidth(488);
    //QLayout* mainLayout  = new QLayout;
    //QToolBar* toolbar = addToolBar(tr("Étudiant"));
    //mainLayout->addWidget(toolbar);

    m_currentStudent = RecordManager::giveInstance().findRecordByLogin(login);

    //toolbar->addWidget(buttonOpenWindowNewStudent);

    buttonOpenWindowNewSemester = new QPushButton(tr("Ajouter un semestre"));
    connect(buttonOpenWindowNewSemester, SIGNAL(clicked()), this, SLOT(openWindowNewSemester()));

    //toolbar->addWidget(buttonOpenWindowNewSemester);

    m_identityStudent = new QWidget();
    m_identityStudentBox = new QVBoxLayout();
    m_identityStudentBox->addWidget(buttonOpenWindowNewSemester);
    m_nameStudent = new QLabel();
    m_surnameStudent = new QLabel();
    m_nameStudent->setText("Nom : "+ m_currentStudent->getName());
    m_surnameStudent->setText("Prénom : " + m_currentStudent->getSurname());
    m_identityStudentBox->addWidget(m_nameStudent);
    m_identityStudentBox->addWidget(m_surnameStudent);
    m_tableUV = new QTableWidget(m_identityStudent);
    m_tableUV->setColumnCount(5);
    m_tableUV->setRowCount(100);
    m_tableUV->setHorizontalHeaderLabels(QStringList() << "Semestre" <<"UV" << "Résultat" << "Catégorie" << "Crédits" );
    unsigned int i = 0;
    QList<Semester*> currStudentList=m_currentStudent->getListSemesters();

    for(QList<Semester*>::iterator itSemesters = currStudentList.begin(); itSemesters != currStudentList.end(); ++itSemesters){
        QList<UVResult*> studentUVResultList=(*itSemesters)->getListUVAndResult();
        for(QList<UVResult*>::iterator itUVResults = studentUVResultList.begin(); itUVResults != studentUVResultList.end(); ++itUVResults){
             m_tableUV->setItem(i,0, new QTableWidgetItem(tr("%1").arg((*itSemesters)->getNameCursus())));
             QString nameUV = (*itUVResults)->getNameUV();
             qDebug() << nameUV;
             m_tableUV->setItem(i,1, new QTableWidgetItem(tr("%1").arg(nameUV)));
             m_tableUV->setItem(i,2, new QTableWidgetItem(tr("%1").arg((*itUVResults)->getResultUV())));
             qDebug() << i;
             i++;
        }

    }

    m_identityStudentBox->addWidget(m_tableUV);
    //m_identityStudent->setLayout(m_identityStudentBox);
    //layout->addWidget(buttonOpenWindowNewStudent);
    setLayout(m_identityStudentBox);
    //setCentralWidget(centralView);
}


/*void WindowNewStudent::openWindowNewStudent()
{
    windowNewStudent = new WindowNewStudent;
    windowNewStudent->show();
}*/

void WindowRecordConsultation::openWindowNewSemester()
{
    windowNewSemester = new WindowNewSemester(m_currentStudent->getLogin());
    windowNewSemester->show();
}

/*void WindowRecordConsultation::openWindowLoadStudent(){
    windowLoadStudent = new WindowLoadStudent;
    windowLoadStudent->show();
}*/



void WindowRecordConsultation::setStudent(Record* newCurrentStudent){
    m_currentStudent=newCurrentStudent;
}
