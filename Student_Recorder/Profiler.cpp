/**
  * \file Profiler.cpp
  * \brief Définition des méthodes de la classe Profiler non-inline
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "Profiler.h"

/**
 * @brief Définition des caractéristiques de la fenêtre principale, des menus accessibles et des actions possibles.
 */
Profiler::Profiler(){

    menuFichier = menuBar()->addMenu("&Fichier");

    menuChargement = menuFichier->addMenu("&Charger...");
    actionChargerUV = new QAction("&Chargement des UV", this);
    menuChargement->addAction(actionChargerUV);
    QObject::connect(actionChargerUV, SIGNAL(triggered()), this, SLOT(chargementUV()));

    loadStudent = new QAction(this);
    loadStudent = menuChargement->addAction(tr("Charger un étudiant…"));
    QObject::connect(loadStudent, SIGNAL(triggered()), this, SLOT(openWindowLoadStudent()));

    actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    menuEdition = menuBar()->addMenu("&Édition");

    menuEditionUV = menuEdition->addMenu("&Édition d'UV");
    actionCreerUV = new QAction("&Créer une UV",this);
    actionEditerUV = new QAction("&Modifier une UV", this);
    menuEditionUV->addAction(actionCreerUV);
    menuEditionUV->addAction(actionEditerUV);

    QObject::connect(actionCreerUV,SIGNAL(triggered()),this,SLOT(creerUV()));
    QObject::connect(actionEditerUV, SIGNAL(triggered()), this, SLOT(editeurUV()));

    menuEditionFormation = menuEdition->addMenu("&Édition de Formation");
    actionCreerFormation = new QAction("&Créer une Formation",this);
    actionEditerFormation = new QAction("&Modifier une Formation", this);
    menuEditionFormation->addAction(actionCreerFormation);
    menuEditionFormation->addAction(actionEditerFormation);

    QObject::connect(actionCreerFormation,SIGNAL(triggered()),this,SLOT(creerFormation()));
    QObject::connect(actionEditerFormation, SIGNAL(triggered()), this, SLOT(editeurFormation()));

    actionEditerDossier = new QAction("&Édition de dossier", this);
    menuEdition->addAction(actionEditerDossier);



    menuRecherche = menuBar()->addMenu("&Recherche");

    actionRechercheUV = new QAction("&D'UV", this);
    menuRecherche->addAction(actionRechercheUV);

    QObject::connect(actionRechercheUV, SIGNAL(triggered()), this, SLOT(affichageUV()));

    zoneCentrale = new QWidget;

    setCentralWidget(zoneCentrale);
}

void Profiler::affichageUV(){
    AfficheurUV* afficheur = new AfficheurUV(*this);
}

void Profiler::editeurUV(){
    try{
        UVManager& m= UVManager::getInstance();

        QString uv = QInputDialog::getText(this, "Recherche d'uv","Entrer le code de l'uv que vous recherchez");

        UV& u = m.getUV(uv);
        UVEditeur* edit = new UVEditeur(u,this);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this,"UV introuvable", "Veillez à respectez les majuscules.");
    }
}

void Profiler::creerUV(){
//    UVManager& m = UVManager::getInstance();

    try{
        UVCreateur* createur = new UVCreateur(this);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this,"Création d'UV","Erreur lors de la création de la fenêtre");
    }
}

void Profiler::chargementUV(){

    try {
        UVManager::getInstance().load();
        FormationManager::getInstance().load();
        QMessageBox::information(this, "Chargement Catalogue", "La base de donnée à correctement été chargé.");
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Chargement Catalogue", "Erreur lors du chargement"+e.getInfo());
    }


}

void Profiler::editeurFormation(){
    try{
        FormationManager& fm= FormationManager::getInstance();

        QString fo = QInputDialog::getText(this, "Recherche de formation","Entrer le code de la formation que vous recherchez");

        Formation& f = fm.getFormation(fo);
        FormationEditeur* edit = new FormationEditeur(f,this);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this,"Formation introuvable", "Veillez à respectez les majuscules.");
    }

}

void Profiler::creerFormation(){
    try{
        FormationCreateur* create = new FormationCreateur(this);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this,"Erreur lors de la création de la formation", "Vérifiez que la formation n'est pas déjà présente.");
    }
}

void Profiler::openWindowLoadStudent(){
    windowLoadStudent = new WindowLoadStudent;
    windowLoadStudent->show();
}

Profiler::~Profiler(){
    RecordManager::freeInstance();
    FormationManager::libererInstance();
    UVManager::libererInstance();
}
