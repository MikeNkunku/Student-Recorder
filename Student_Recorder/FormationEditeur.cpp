/**
  * \file FormationEditeur.cpp
  * \brief Définition des caractéristiques de la fenêtre d'édition des formations et de ses méthodes.
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 11 juin 2014
  */


#include "FormationEditeur.h"
#include <QDebug>

/**
 * @brief Constructeur de la classe objet FormationEditeur, avec définition des différents éléments permettant l'édition des formations.
 * @param FormationToEdit La formation à éditer.
 * @param parent Fentêtre principale.
 */
FormationEditeur::FormationEditeur(Formation& FormationToEdit,QMainWindow *parent):fo(FormationToEdit){

    codeLabel= new QLabel("code",this);
    titreLabel= new QLabel("titre", this);
    creditsCSLabel= new QLabel("CS",this);
    creditsTMLabel= new QLabel("TM",this);
    creditsTSHLabel= new QLabel("TSH",this);
    creditsSPLabel= new QLabel("SP",this);

    code = new QLineEdit(fo.getCode(),this);
    titre = new QTextEdit(fo.getTitre(),this);
    CS = new QSpinBox(this);
    TM = new QSpinBox(this);
    TSH = new QSpinBox(this);
    SP = new QSpinBox(this);
    CS->setRange(0,50);
    TM->setRange(0,50);
    TSH->setRange(0,50);
    SP->setRange(0,50);

    CS->setValue(fo.getCS());
    TM->setValue(fo.getTM());
    TSH->setValue(fo.getTSH());
    SP->setValue(fo.getSP());

    addUV=new QPushButton("Ajouter une UV",this);
    deleteUV=new QPushButton("Supprimer une UV",this);
    addUVCons= new QPushButton("Ajouter UV conseillée");
    deleteUVCons= new QPushButton("Supprimer UV conseillée");
    addFiliere=new QPushButton("Ajouter une Filiere",this);
    deleteFiliere=new QPushButton("Supprimer une Filiere",this);

    QObject::connect(addUV,SIGNAL(clicked()),this,SLOT(ajouterUV()));
    QObject::connect(deleteUV,SIGNAL(clicked()),this,SLOT(supprimerUV()));
    QObject::connect(addUVCons,SIGNAL(clicked()),this,SLOT(ajouterUVCons()));
    QObject::connect(deleteUVCons,SIGNAL(clicked()),this,SLOT(supprimerUVCons()));
    QObject::connect(addFiliere,SIGNAL(clicked()),this,SLOT(ajouterFiliere()));
    QObject::connect(deleteFiliere,SIGNAL(clicked()),this,SLOT(supprimerFiliere()));

    QObject::connect(code, SIGNAL(textChanged(QString)),this,SLOT(activSave(QString)));
    QObject::connect(titre, SIGNAL(textEdited()),this,SLOT(activSave()));
    QObject::connect(SP, SIGNAL(valueChanged(QString)),this,SLOT(activSave(QString)));
    QObject::connect(TSH, SIGNAL(valueChanged(QString)),this,SLOT(activSave(QString)));
    QObject::connect(CS, SIGNAL(valueChanged(QString)),this,SLOT(activSave(QString)));
    QObject::connect(TM, SIGNAL(valueChanged(QString)),this,SLOT(activSave(QString)));
    QObject::connect(addUV, SIGNAL(clicked()),this,SLOT(activSave()));
    QObject::connect(addFiliere, SIGNAL(clicked()),this,SLOT(activSave()));
    QObject::connect(deleteUV, SIGNAL(clicked()),this,SLOT(activSave()));
    QObject::connect(deleteFiliere, SIGNAL(clicked()),this,SLOT(activSave()));

    cancel=new QPushButton("Annuler",this);
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancelChanges()));

    save = new QPushButton("sauver",this);
    save->setEnabled(false); //desactive le bouton
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(sauverFormation()));

    coucheH1= new QHBoxLayout;
    coucheH2= new QHBoxLayout;
    coucheH3= new QHBoxLayout;
    coucheH4 = new QHBoxLayout;
    coucheH5= new QHBoxLayout;
    couche = new QVBoxLayout;

    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(creditsCSLabel);
    coucheH1->addWidget(CS);
    coucheH1->addWidget(creditsTMLabel);
    coucheH1->addWidget(TM);
    coucheH1->addWidget(creditsTSHLabel);
    coucheH1->addWidget(TSH);
    coucheH1->addWidget(creditsSPLabel);
    coucheH1->addWidget(SP);

    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);

    coucheH4->addWidget(addFiliere);
    coucheH4->addWidget(deleteFiliere);
    coucheH3->addWidget(addUV);
    coucheH3->addWidget(deleteUV);
    coucheH3->addWidget(addUVCons);
    coucheH3->addWidget(deleteUVCons);

    coucheH5->addWidget(cancel);
    coucheH5->addWidget(save);

    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH5);

    this->setLayout(couche);
    parent->setCentralWidget(this);
}

/**
 * @brief Méthode qui permet de sauvegarder une formation qui a eu un changement dans la base de données.
 * Un message de confirmation est affiché après réalisation.
 */
void FormationEditeur::sauverFormation(){

    fo.setCode(code->text());
    fo.setTitre(titre->toPlainText());

    fo.setcredCS(CS->value());
    fo.setcredTM(TM->value());
    fo.setcredTSH(TSH->value());
    fo.setcredTSH(SP->value());


    QMessageBox::information(this,"Sauvegarde","Formation sauvegardée...");


}

/**
 * @brief Un signal est envoyé pour permettre à l'utilisateur d'activer le bouton Sauvegarder de l'interface.
 */
void FormationEditeur::activSave(QString){
    save->setEnabled(true);
}

/**
 * @brief Cette méthode permet d'annuler les changements en bloquant l'accès au bouton Sauvegarder, et en réattribuant les valeurs d'origine
 * de la formation contenues dans la base de données.
 */
void FormationEditeur::cancelChanges(){

    save->setEnabled(false);
    code->setText(fo.getCode());
    titre->setPlainText(fo.getTitre());

}

/**
 * @brief Cette méthode permet de supprimer une UV à une formation.
 */
void FormationEditeur::supprimerUV(){

    QStringList items;
    QList<UV*> uvs = fo.getUVList();

    for (QList<UV*>::const_iterator it = uvs.begin() ; it != uvs.end(); ++it)
           items << (*it)->getCode();



    bool ok;
    QString item = QInputDialog::getItem(this, "Suppression d'UV","UV : ", items, 0, true, &ok);
    if (ok && !item.isEmpty())
    {
        UV* f1 = fo.getUV(item);
        if(f1)
        {
            int reponse = QMessageBox::question(this,"Suppression UV",QString("Etes-vous sûr de vouloir supprimer l'UV "+item+" de la formation?"));
            if(reponse == QMessageBox::No)
                QMessageBox::information(this,"Suppression UV","UV conservée!");
            else if(reponse == QMessageBox::Yes)
            {
                fo.supprimerUV(item);
                QMessageBox::information(this,"Suppression UV",QString("L'UV' "+item+" a bien été supprimée!"));
            }
        }
        for(QList<Formation*>::iterator it=fo.getParentList().begin();it!=fo.getParentList().end();++it){
            if((*it)->getUVList().contains(f1)){
                int reponse = QMessageBox::question(this,"Suppression UV",QString("L'UV est aussi presente dans la formation parente"+((*it)->getCode())+" de la formation?"));
                if(reponse == QMessageBox::No)
                    QMessageBox::information(this,"Suppression UV","UV conservée!");
                else if(reponse == QMessageBox::Yes)
                {
                    (*it)->supprimerUV(item);
                    QMessageBox::information(this,"Suppression UV",QString("L'UV' "+item+" a bien été supprimée!"));
                }
            }

        }

    }
}

/**
 * @brief Cette méthode permet d'ajouter une UV à une formation.
 */
void FormationEditeur::ajouterUV(){

    QStringList items;
    QList<UV*> uvs;

    UVManager& um = UVManager::getInstance();
    for(UVManager::iterator it=um.begin();it!=um.end();++it)
    {
        if(!fo.getUVList().contains(&(*it)))
            uvs<<&(*it);
    }

    for (QList<UV*>::const_iterator it = uvs.begin() ; it != uvs.end(); ++it)
           items << (*it)->getCode();

    bool ok;
    QString item = QInputDialog::getItem(this, "Ajout d'UV","UV : ", items, 0, true, &ok);

    if (ok && !item.isEmpty())
    {

        UV& f1 = um.getUV(item);
        if(&f1)
        {
            int reponse = QMessageBox::question(this,"Ajout d'UV",QString("Etes-vous sûr de vouloir ajouter l'UV "+item+" à la formation?"));
            if(reponse == QMessageBox::No)
                QMessageBox::information(this,"Ajout d'UV","UV non ajoutée!");
            else if(reponse == QMessageBox::Yes)
            {
                fo.ajouterUV(&f1);
                QMessageBox::information(this,"Ajout d'UV",QString("L'UV' "+item+" a bien été ajoutée!"));
            }

            for(QList<Formation*>::iterator it=fo.getParentList().begin();it!=fo.getParentList().end();++it){
                if((*it)->getUVList().contains(&f1)){
                    int reponse = QMessageBox::question(this,"Ajout d'UV",QString("Voulez-vous également ajouter l'UV à la formation parente "+((*it)->getCode())+" ?"));
                    if(reponse == QMessageBox::No)
                        QMessageBox::information(this,"Ajout d'UV","UV non ajoutée!");
                    else if(reponse == QMessageBox::Yes)
                    {
                        (*it)->ajouterUV(&f1);
                        QMessageBox::information(this,"Ajout d'UV",QString("L'UV' "+item+" a bien été ajoutée!"));
                    }
                }

            }
        }
    }
}

/**
 * @brief Suppression d'une UV des UV conseillées pour une Formation.
 */
void FormationEditeur::supprimerUVCons(){

    QStringList items;
    QList<UV*> uvs = fo.getUVConsList();

    for (QList<UV*>::const_iterator it = uvs.begin() ; it != uvs.end(); ++it)
           items << (*it)->getCode();



    bool ok;
    QString item = QInputDialog::getItem(this, "Suppression d'UV","UV : ", items, 0, true, &ok);
    if (ok && !item.isEmpty())
    {
        UV* f1 = fo.getUV(item);
        if(f1)
        {
            int reponse = QMessageBox::question(this,"Suppression UV",QString("Etes-vous sûr de vouloir supprimer l'UV "+item+" de la formation?"));
            if(reponse == QMessageBox::No)
                QMessageBox::information(this,"Suppression UV","UV conservée!");
            else if(reponse == QMessageBox::Yes)
            {
                fo.supprimerUVCons(item);
                QMessageBox::information(this,"Suppression UV",QString("L'UV' "+item+" a bien été supprimée!"));
            }
        }

    }
}

/**
 * @brief Ajout d'une UV aux UV conseillées pour une formation donnée.
 */
void FormationEditeur::ajouterUVCons(){

    QStringList items;
    QList<UV*> uvs=fo.getUVList();

    UVManager& um = UVManager::getInstance();

    for (QList<UV*>::const_iterator it = uvs.begin() ; it != uvs.end(); ++it)
           items << (*it)->getCode();

    bool ok;
    QString item = QInputDialog::getItem(this, "Ajout d'UV","UV : ", items, 0, true, &ok);

    if (ok && !item.isEmpty())
    {

        UV& f1 = um.getUV(item);
        if(&f1)
        {
            int reponse = QMessageBox::question(this,"Ajout d'UV",QString("Etes-vous sûr de vouloir ajouter l'UV "+item+" à la formation?"));
            if(reponse == QMessageBox::No)
                QMessageBox::information(this,"Ajout d'UV","UV non ajoutée!");
            else if(reponse == QMessageBox::Yes)
            {
                fo.ajouterUVCons(&f1);
                QMessageBox::information(this,"Ajout d'UV",QString("L'UV' "+item+" a bien été ajoutée!"));
            }
        }
    }
}

/**
 * @brief Cette méthode permet d'ajouter une Filiere à la liste des formations, avant de l'ajouter définitivement dans la base de données.
 */
void FormationEditeur::ajouterFiliere(){

    QStringList items;
    QList<Formation*> fmts;

    FormationManager& fm = FormationManager::getInstance();
    for(QList<Formation*>::iterator it=fm.getFormationList()->begin();it!=fm.getFormationList()->end();++it)
    {
        if(!fo.getFiliereList().contains((*it)))
            fmts<<(*it);
    }


    for (QList<Formation*>::const_iterator it = fmts.begin() ; it != fmts.end(); ++it)
           items << (*it)->getCode();

    bool ok;
    QString item = QInputDialog::getItem(this, "Ajout de Filiere","Formation : ", items, 0, true, &ok);

    if (ok && !item.isEmpty())
    {

        Formation& f1 = fm.getFormation(item);
        if(&f1)
        {
            int reponse = QMessageBox::question(this,"Ajout de Filiere",QString("Etes-vous sûr de vouloir ajouter la formation "+item+" comme filiere de la formation?"));
            if(reponse == QMessageBox::No)
                QMessageBox::information(this,"Ajout de Filiere","Filiere non ajoutée!");
            else if(reponse == QMessageBox::Yes)
            {
                fo.ajouterFiliere(&f1);
                QMessageBox::information(this,"Ajout de Filiere",QString("La Filiere "+item+" a bien été ajoutée!"));
            }
        }
    }
}

/**
 * @brief Suppression d'une Filiere dans la liste des formations après leur chargement, puis suppression dans la base de données par son
 * absence dans la liste des formations.
 */
void FormationEditeur::supprimerFiliere(){
    QStringList items;
    QList<Formation*> fmts = fo.getFiliereList();

    for (QList<Formation*>::const_iterator it = fmts.begin() ; it != fmts.end(); ++it)
           items << (*it)->getCode();

    bool ok;
    QString item = QInputDialog::getItem(this, "Suppression de Filiere","Formation : ", items, 0, true, &ok);

    if (ok && !item.isEmpty())
    {
        Formation* f1 = fo.trouverFiliere(item);
        if(f1)
        {
            int reponse = QMessageBox::question(this,"Suppression de Filiere",QString("Etes-vous sûr de vouloir supprimer la Filiere "+item+" de la formation?"));
            if(reponse == QMessageBox::No)
                QMessageBox::information(this,"Suppression de Filiere","Filiere non supprimée!");
            else if(reponse == QMessageBox::Yes)
            {
                fo.supprimerFiliere(item);
                QMessageBox::information(this,"Suppression de Filiere",QString("La Filiere "+item+" a bien été supprimée!"));
            }
        }
    }
}

/**
 * @brief Constructeur de la classe FormationCreateur qui permet de créer et ajouter une Formation aux formations déjà existantes.
 * @param parent Pointeur vers la fenêtre principale.
 */
FormationCreateur::FormationCreateur(QMainWindow *parent){

    codeLabel= new QLabel("code",this);
    titreLabel= new QLabel("titre", this);
    creditsCSLabel= new QLabel("CS",this);
    creditsTMLabel= new QLabel("TM",this);
    creditsTSHLabel= new QLabel("TSH",this);
    creditsSPLabel= new QLabel("SP",this);

    code = new QLineEdit(this);
    titre = new QTextEdit(this);
    CS = new QSpinBox(this);
    TM = new QSpinBox(this);
    TSH = new QSpinBox(this);
    SP = new QSpinBox(this);
    CS->setRange(0,50);
    TM->setRange(0,50);
    TSH->setRange(0,50);
    SP->setRange(0,50);

    QObject::connect(code, SIGNAL(textChanged(QString)),this,SLOT(activSave(QString)));
    QObject::connect(titre, SIGNAL(textEdited(QString)),this,SLOT(activSave(QString)));
    QObject::connect(SP, SIGNAL(valueChanged(QString)),this,SLOT(activSave(QString)));
    QObject::connect(TSH, SIGNAL(valueChanged(QString)),this,SLOT(activSave(QString)));
    QObject::connect(CS, SIGNAL(valueChanged(QString)),this,SLOT(activSave(QString)));
    QObject::connect(TM, SIGNAL(valueChanged(QString)),this,SLOT(activSave(QString)));

    cancel=new QPushButton("Annuler",this);
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancelChanges()));

    save = new QPushButton("sauver",this);
    save->setEnabled(false); //desactive le bouton
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(sauverFormation()));

    coucheH1= new QHBoxLayout;
    coucheH2= new QHBoxLayout;
    coucheH4 = new QHBoxLayout;
    couche = new QVBoxLayout;

    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(creditsCSLabel);
    coucheH1->addWidget(CS);
    coucheH1->addWidget(creditsTMLabel);
    coucheH1->addWidget(TM);
    coucheH1->addWidget(creditsTSHLabel);
    coucheH1->addWidget(TSH);
    coucheH1->addWidget(creditsSPLabel);
    coucheH1->addWidget(SP);

    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);

    coucheH4->addWidget(cancel);
    coucheH4->addWidget(save);

    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH4);

    this->setLayout(couche);
    parent->setCentralWidget(this);
}

/**
 * @brief Cette méthode permet de sauvegarder une formation dans la liste des formations de FormationManager, avant sauvegarde dans la base
 * de données.
 */
void FormationCreateur::sauverFormation(){
    FormationManager& fm = FormationManager::getInstance();

    fm.addFormation(code->text(),titre->toPlainText(),CS->value(),TM->value(),TSH->value(),SP->value(),0);


    QMessageBox::information(this,"Sauvegarde","Formation sauvegardée...");


}

/**
 * @brief Permet d'activer le bouton Sauvegarder de la fenêtre.
 */
void FormationCreateur::activSave(QString){
    save->setEnabled(true);
}

/**
 * @brief Cette méthode permet d'annuler les changements en bloquant l'accès au bouton Sauvegarder de la fenêtre, et en remplaçant
 * le code et le titre par la chaine vide. De cette manière, lors de la sauvegarde des formations dans la base de données, si le code
 * correspond à la chaine vide, aucune modification ne sera apportée à la base de donnée pour la formation concernée.
 */
void FormationCreateur::cancelChanges(){

    save->setEnabled(false);
    code->setText("");
    titre->setPlainText("");

}
