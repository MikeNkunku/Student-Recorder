/**
  * \file WindowNewSemester.cpp
  * \brief Définition des méthodes de la classe WindowNewSemester non-inline
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "WindowNewSemester.h"

/**
 * @brief Cette classe permet de définir la fenêtre apparaissant dans le cas d'enregistrement d'un nouveau semestre pour une personne déjà
 * dans la base de données.
 * @param login Login de la personne.
 */
WindowNewSemester::WindowNewSemester(QString login)
{
    m_login = login;
    setFixedSize(400,500);
    QVBoxLayout* mainLayout = new QVBoxLayout();


    /**Création des champs du formulaire*/

    m_cursusSemester = new QComboBox;
    QList<Formation*>* listCursus = FormationManager::getInstance().getFormationList();
    QList<Formation*>::iterator it;
    it = listCursus->begin();
    while (it != listCursus->end()){
        m_cursusSemester->addItem((*it)->getCode());
        it++;
    }
    m_nbCurrentSemester = new QSpinBox;
    m_nbCurrentSemester->setRange(1, 9);

    m_currentSemester = new QComboBox;
    m_currentSemester->addItem("P2014");
    m_currentSemester->addItem("A2013");
    m_currentSemester->addItem("P2013");
    m_currentSemester->addItem("A2012");
    m_currentSemester->addItem("P2012");
    m_currentSemester->addItem("A2011");
    m_currentSemester->addItem("P2011");
    m_currentSemester->addItem("A2010");
    m_currentSemester->addItem("P2010");
    m_currentSemester->addItem("A2009");
    m_currentSemester->addItem("P2009");
    m_currentSemester->addItem("A2008");


    /**Création du formulaire*/

    formLayout = new QFormLayout();

    formLayout->addRow(tr("Cursus du semestre :"), m_cursusSemester);
    formLayout->addRow(tr("# semestre"), m_nbCurrentSemester);
    formLayout->addRow(tr("Semestre :"), m_currentSemester);
    mainLayout->addLayout(formLayout);

    //m_iteratorGradeUV = m_gradeUV.begin();
    for (unsigned int i = 0; i<7; i++){
        m_HBoxes.push_back(new QHBoxLayout);
        m_titleUV.push_back(new QLineEdit);
        m_titleUV[i]->setFixedWidth(50);
        m_HBoxes[i]->addWidget(m_titleUV[i]);
        m_gradeUV.push_back(new QComboBox);
        m_gradeUV[i]->addItem("A");
        m_gradeUV[i]->addItem("B");
        m_gradeUV[i]->addItem("C");
        m_gradeUV[i]->addItem("D");
        m_gradeUV[i]->addItem("E");
        m_gradeUV[i]->addItem("FX");
        m_gradeUV[i]->addItem("F");
        m_gradeUV[i]->addItem(tr("RES"));
        m_gradeUV[i]->addItem(tr("ABS"));
        m_gradeUV[i]->addItem("EC");
        m_gradeUV[i]->setFixedWidth(120);
        m_HBoxes[i]->addWidget(m_gradeUV[i]);
        mainLayout->addLayout(m_HBoxes[i]);
        //m_gradeUV.insert(m_iteratorGradeUV, )
        //if (m_titleUV[i]->isModified());
        //m_iteratorGradeUV++;
    }



    /**Création du formulaire*/

   // widgetFormLayout = new QWidget;
    //widgetFormLayout->setLayout(formLayout);
    //mainLayout->addWidget(widgetFormLayout);

    /**Création des boutons**/
    buttonCreateNewSemester = new QPushButton("Valider", this);
    QObject::connect(buttonCreateNewSemester, SIGNAL(clicked()), this, SLOT(createNewSemester()));
    buttonCancel = new QPushButton("Annuler",this);
    QObject::connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));

    /**Layout des boutons*/
    QHBoxLayout* layerHButtons = new QHBoxLayout();
    layerHButtons->addWidget(buttonCancel);
    layerHButtons->addWidget(buttonCreateNewSemester);


    mainLayout->addLayout(layerHButtons);
    setLayout(mainLayout);
}

/**
 * @brief Cette méthode permet d'entrer l'inscription d'une personne pour un nouveau semestre dans la base de données.
 */
void WindowNewSemester::createNewSemester(){
    QString Errors;
    bool allUVareOK(1);
    for (unsigned int i = 0; i<7;i++){
        if (m_titleUV[i]->isModified() /*&& UVManager::getInstance().getUV(m_titleUV[i]->text()==0)*/) {
        Errors.append("L'UV " + m_titleUV[i]->text() + " n'existe pas.\n");
        allUVareOK = 0;
        }
    }
    if (!allUVareOK)
    {
        QMessageBox::information(this, "UV introuvable", Errors);
    }
    else
    {
        QString nameCursus = m_cursusSemester->currentText();
        nameCursus.append(QString::number(m_nbCurrentSemester->value()));
        qDebug() << nameCursus;
        RecordManager::giveInstance().findRecordByLogin(m_login)->addSemester(nameCursus, m_currentSemester->currentText());
        for (unsigned int i = 0; i<7; i++){
            if(m_titleUV[i]->isModified()){
                m_mapUVGrade[m_titleUV[i]->text()]=m_gradeUV[i]->currentText();
            }
        }
    }
    //RecordManager::giveInstance().addRecord(m_name->text(), m_surname->text(), m_age->value(), 5/*À REMPLACER*/, m_seasonFirstSemester->currentText(), 2011/*atoi(m_yearFirstSemester->currentText())*/);
    //close();
}
