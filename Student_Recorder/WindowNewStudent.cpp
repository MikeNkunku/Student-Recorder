/**
  * \file WindowNewStudent.cpp
  * \brief Définition des méthodes non-inline de la classe WindowNewStudent
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "WindowNewStudent.h"

/**
 * @brief Constructeur de la classe WindowNewStudent qui affiche la fenêtre permettant l'enregistrement des informations d'une nouvelle
 * personne dans la base de données.
 */
WindowNewStudent::WindowNewStudent() : QWidget()
{
    setFixedSize(500,400);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    /**Création des champs du formulaire*/

    m_login = new QLineEdit();
    m_login->setPlaceholderText("Login");

    m_name = new QLineEdit();
    m_name->setPlaceholderText("Nom");

    m_surname = new QLineEdit();
    m_surname->setPlaceholderText("Prénom");


    m_cursusCurrentSemester = new QComboBox;
    QList<Formation*>* listCursus = FormationManager::getInstance().getFormationList();
    QList<Formation*>::iterator it;
    it = listCursus->begin();
    while (it != listCursus->end()){
        m_cursusCurrentSemester->addItem((*it)->getCode());
        it++;
    }

    m_nbCurrentSemester = new QSpinBox;
    m_nbCurrentSemester->setRange(1, 10);

    m_nbInitialCredits = new QSpinBox;
    m_nbInitialCredits->setRange(0, 200);

    /**Création du formulaire*/

    formLayout = new QFormLayout();
    formLayout->addRow(tr("Login CAS :"), m_login);
    formLayout->addRow(tr("Nom :"), m_name);
    formLayout->addRow(tr("Prénom :"), m_surname);
    formLayout->addRow(tr("Cursus du semestre en cours:"), m_cursusCurrentSemester);
    formLayout->addRow(tr("# semestre"), m_nbCurrentSemester);
    formLayout->addRow(tr("Nombre d'ECTS en entrant à l'UTC :"), m_nbInitialCredits);
    widgetFormLayout = new QWidget;
    widgetFormLayout->setLayout(formLayout);
    mainLayout->addWidget(widgetFormLayout);

    /**Création des boutons**/
    buttonCreateNewStudent = new QPushButton("Valider", this);
    QObject::connect(buttonCreateNewStudent, SIGNAL(clicked()), this, SLOT(createNewStudent()));
    buttonCancel = new QPushButton("Annuler",this);
    QObject::connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));

    /**Layout des boutons*/
    QHBoxLayout* layerHButtons = new QHBoxLayout();
    layerHButtons->addWidget(buttonCancel);
    layerHButtons->addWidget(buttonCreateNewStudent);


    mainLayout->addLayout(layerHButtons);
    setLayout(mainLayout);

}

/**
 * @brief Cette méthode permet d'enregistrer une nouvelle personne dans la base de données.
 */
void WindowNewStudent::createNewStudent(){
    if (m_login->isModified()){
    RecordManager::giveInstance().addRecord(m_login->text(), m_name->text(), m_surname->text(), 5/*À REMPLACER*/);
    close();
    }
    else{
        QMessageBox::information(this, tr("Veuillez entrer un login !"), "Veuillez entrer un login !");
    }
}
