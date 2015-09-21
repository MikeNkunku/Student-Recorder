/**
  * \file UVEditeur.cpp
  * \brief Définition des méthodes de la classe UVEditeur non-inline
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "UVEditeur.h"
#include "DBManager.h"


//on aura pas besoin de destructeur car le destructeur par défaut fera appel à tous les destructeurs.

/**
 * @brief Constructeur de la classe UVEditeur qui ouvre une fenêtre avec les différentes caractéristiques de l'UV à éditer.
 * @param uvToEdit L'UV à modifier.
 * @param parent Un pointeur sur la fenêtre principale.
 */
UVEditeur::UVEditeur(UV& uvToEdit, QMainWindow* parent):uv(uvToEdit){

    codeLabel= new QLabel("Code",this);
    titreLabel= new QLabel("Titre", this);
    creditsLabel= new QLabel("Crédits",this);
    creditsCSLabel= new QLabel("CS",this);
    creditsTMLabel= new QLabel("TM",this);
    creditsTSHLabel= new QLabel("TSH",this);
    creditsSPLabel= new QLabel("SP",this);
    ouvertureLabel= new QLabel("Ouverture",this);
    //brancheLabel= new QLabel("Branche",this);



    creditsCS= new QSpinBox(this);
    creditsCS->setRange(0,8);


    creditsTM= new QSpinBox(this);
    creditsTM->setRange(0,8);


    creditsTSH= new QSpinBox(this);
    creditsTSH->setRange(0,8);


    creditsSP= new QSpinBox(this);
    creditsSP->setRange(0,8);


    automne = new QCheckBox("Automne",this);


    printemps = new QCheckBox("Printemps",this);


    save = new QPushButton("Sauvegarder",this);
    save->setEnabled(false); //desactive le bouton

    code = new QLineEdit(uv.getCode(),this);
    titre = new QTextEdit(uv.getTitre(),this);
    //branche = new QLineEdit(uv.getBranche(),this);
    parent->setWindowTitle(QString("Edition de l'UV ")+uv.getCode());
    creditsCS->setValue(uv.getNbCreditsCS());
    creditsTM->setValue(uv.getNbCreditsTM());
    creditsTSH->setValue(uv.getNbCreditsTSH());
    creditsSP->setValue(uv.getNbCreditsTSH());
    automne->setChecked(uv.ouvertureAutomne());
    printemps->setChecked(uv.ouverturePrintemps());

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(sauverUV()));

    QObject::connect(code, SIGNAL(textChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(titre, SIGNAL(textChanged(/*QString*/)),this,SLOT(activSave(/*QString*/)));
    //QObject::connect(branche, SIGNAL(textChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(creditsSP, SIGNAL(valueChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(creditsTSH, SIGNAL(valueChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(creditsTM, SIGNAL(valueChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(creditsCS, SIGNAL(valueChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(automne, SIGNAL(stateChanged(/*QString*/int)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(printemps, SIGNAL(stateChanged(/*QString*/int)),this,SLOT(activSave(/*QString*/)));





    cancel=new QPushButton("Annuler",this);
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancelChanges()));

    coucheH1 = new QHBoxLayout;
    coucheH2 = new QHBoxLayout;
    coucheH3 = new QHBoxLayout;
    coucheH4 = new QHBoxLayout;
    couche = new QVBoxLayout;


    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(creditsCSLabel);
    coucheH1->addWidget(creditsCS);
    coucheH1->addWidget(creditsTMLabel);
    coucheH1->addWidget(creditsTM);
    coucheH1->addWidget(creditsTSHLabel);
    coucheH1->addWidget(creditsTSH);
    coucheH1->addWidget(creditsSPLabel);
    coucheH1->addWidget(creditsSP);

    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);

    coucheH3->addWidget(ouvertureLabel);
    coucheH3->addWidget(automne);
    coucheH3->addWidget(printemps);

    coucheH4->addWidget(cancel);
    coucheH4->addWidget(save);


    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    this->setLayout(couche);
    parent->setCentralWidget(this);
}

/**
 * @brief Constructeur de la classe UVCreateur qui ouvre une fenêtre avec les caractéristiques de la nouvelle UV à remplir.
 * @param parent Un pointeur vers la fenêtre principale.
 */
UVCreateur::UVCreateur(QMainWindow* parent){

    codeLabel= new QLabel("Code",this);
    titreLabel= new QLabel("Titre", this);
    creditsLabel= new QLabel("Crédits",this);
    creditsCSLabel= new QLabel("CS",this);
    creditsTMLabel= new QLabel("TM",this);
    creditsTSHLabel= new QLabel("TSH",this);
    creditsSPLabel= new QLabel("SP",this);
    ouvertureLabel= new QLabel("Ouverture",this);



    creditsCS= new QSpinBox(this);
    creditsCS->setRange(0,8);


    creditsTM= new QSpinBox(this);
    creditsTM->setRange(0,8);


    creditsTSH= new QSpinBox(this);
    creditsTSH->setRange(0,8);


    creditsSP= new QSpinBox(this);
    creditsSP->setRange(0,8);


    automne = new QCheckBox("Automne",this);


    printemps = new QCheckBox("Printemps",this);


    save = new QPushButton("Sauvegarder",this);
    save->setEnabled(false); //desactive le bouton

    code = new QLineEdit(this);
    titre = new QTextEdit(this);

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(creerUV()));

    QObject::connect(code, SIGNAL(textChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(titre, SIGNAL(textChanged(/*QString*/)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(creditsSP, SIGNAL(valueChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(creditsTSH, SIGNAL(valueChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(creditsTM, SIGNAL(valueChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(creditsCS, SIGNAL(valueChanged(QString)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(automne, SIGNAL(stateChanged(/*QString*/int)),this,SLOT(activSave(/*QString*/)));
    QObject::connect(printemps, SIGNAL(stateChanged(/*QString*/int)),this,SLOT(activSave(/*QString*/)));





    cancel=new QPushButton("Annuler",this);
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancelChanges()));

    coucheH1 = new QHBoxLayout;
    coucheH2 = new QHBoxLayout;
    coucheH3 = new QHBoxLayout;
    coucheH4 = new QHBoxLayout;
    couche = new QVBoxLayout;


    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(creditsCSLabel);
    coucheH1->addWidget(creditsCS);
    coucheH1->addWidget(creditsTMLabel);
    coucheH1->addWidget(creditsTM);
    coucheH1->addWidget(creditsTSHLabel);
    coucheH1->addWidget(creditsTSH);
    coucheH1->addWidget(creditsSPLabel);
    coucheH1->addWidget(creditsSP);

    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);

    coucheH3->addWidget(ouvertureLabel);
    coucheH3->addWidget(automne);
    coucheH3->addWidget(printemps);

    coucheH4->addWidget(cancel);
    coucheH4->addWidget(save);


    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    this->setLayout(couche);
    parent->setCentralWidget(this);
}

/**
 * @brief Cette méthode permet de sauvegarder une UV après création ou modification.
 */
void UVEditeur::sauverUV(){

    UVManager& m = UVManager::getInstance();
    m.setModification();
    uv.setCode(code->text());
    uv.setCreditsCS(creditsCS->value());
    uv.setCreditsTM(creditsTM->value());
    uv.setCreditsTSH(creditsTSH->value());
    uv.setCreditsSP(creditsSP->value());
    //uv.setBranche(branche->text());
    //uv.setCategorie(Categorie(categorie->currentIndex()));
    uv.setOuverturePrintemps(printemps->isChecked());
    uv.setOuvertureAutomne(automne->isChecked());
    //uv.setNbCreditsCS(credits->value());
    uv.setTitre(titre->toPlainText());
    //m.updateTableUV(automne->isChecked(),printemps->isChecked(),code->text(),titre->toPlainText(),creditsCS->value(),creditsTM->value(),creditsTSH->value(),creditsSP->value());
    QMessageBox::information(this,"Sauvegarde","UV sauvegardée...");


}
/**
 * @brief UVEditeur::activSave
 * Permet d'appuyer sur le bouton Sauvegarder.
 */
void UVEditeur::activSave(QString str){
    save->setEnabled(true);
}

/**
 * @brief UVEditeur::cancelChanges
 * Permet d'annuler les changements.
 */
void UVEditeur::cancelChanges(){
/*    categorie->setCurrentIndex(int(uv.getCategorie()));
    credits->setValue(uv.getNbCredits());*/
    save->setEnabled(false);
    code->setText(uv.getCode());
    titre->setPlainText(uv.getTitre());
    //branche->setText(uv.getBranche());
    printemps->setChecked(uv.ouverturePrintemps());
    automne->setChecked(uv.ouvertureAutomne());
}

/**
 * @brief Cette méthode permet de créer une UV si non existante. Si c'est le cas, un message d'erreur apparaît.
 */
void UVCreateur::creerUV(){
    try{

    UVManager& m = UVManager::getInstance();

    QMap<QString,int>* cat = new QMap<QString,int>;

    cat->insert("CS",creditsCS->value());
    cat->insert("TM",creditsTM->value());
    cat->insert("TSH",creditsTSH->value());
    cat->insert("SP",creditsCS->value());

    m.ajouterUV(code->text(),titre->toPlainText(),*cat,
                //branche->text(),
                automne->isChecked(),printemps->isChecked());
    m.setModification();
    QMessageBox::information(this,"Création d'UV","L'UV a bien été créée.");

    }
    catch(UTProfilerException& e){
        QMessageBox::warning(this,"Création d'UV","Erreur lors de la création de l'UV !");
    }
}

/**
 * @brief UVCreateur::activSave
 * Permet d'appuyer sur le bouton Sauvegarder après avoir repéré un changement.
 */
void UVCreateur::activSave(QString str){
    save->setEnabled(true);
}


/**
 * @brief Cette méthode permet d'annuler les changements apportés en bloquant l'accès au bouton Sauvegarder, et en remplaçant le titre et le
 * code de l'UV par la chaîne vide. De cette façon, lors de la sauvegarde, si le code de l'UV est égal à la chaîne vide, il n'y aura pas
 * modification de l'UV.
 */
void UVCreateur::cancelChanges(){
/*   categorie->setCurrentIndex(int(uv.getCategorie()));
    credits->setValue(uv.getNbCredits());*/
    save->setEnabled(false);
    code->setText("");
    titre->setPlainText("");
    printemps->setChecked(false);
    automne->setChecked(false);
}
