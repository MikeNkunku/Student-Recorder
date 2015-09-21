/**
  * \file main.cpp
  * \brief Fichier permettant de lancer l'application.
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 11 juin 2014
  */


#include "UTProfiler.h"
#include "UVEditeur.h"

#include "Profiler.h"
#include "DBManager.h"
#include <QApplication>
#include <QObject>
#include <QFileDialog>
#include <iostream>


using namespace std;

//remplacer exercice1 par main pour executer
int exercice1(int argc, char *argv[]){
    QApplication app(argc, argv);
    QPushButton b("Quitter",0); //quitter est un type Qstring qui est un type string prenant en compte les caractères spéciaux
    //Prototype de la fonction : QObject::connect(pointeur, SIGNAL, qApp, SLOT)
    QObject::connect(&b, SIGNAL(clicked()), qApp, SLOT(quit()));
    b.show(); //dire a un composant graphique de se montrer

    QPushButton bcou("Coucou",0);   //ouvre une seconde fenêtre, si on clique sur "Quitter" on ferme les deux fenêtres.
    bcou.show();

    return app.exec();
}


int exercice2(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget fenetre;
    fenetre.setFixedSize(200, 200);
    //...
    QLineEdit code(&fenetre);
    code.setFixedWidth(180);

    QTextEdit titre(&fenetre);
    //titre.setGeometry(10,45,180,110);
    titre.setFixedSize(180,110);


    QPushButton save("Sauver",&fenetre);
    save.setFixedWidth(80);
/*
    titre.move(10,45);
    code.move(10,10);
    save.move(10,170);
*/
    /*
    QPushButton exit("Quitter",&fenetre);
    QObject::connect(&exit, SIGNAL(clicked()), qApp, SLOT(quit()));*/

    /*QHBoxLayout coucheH;
    coucheH.addWidget(&save);
    coucheH.addWidget(&exit);
    */

    QVBoxLayout couche;
    /* L'ordre définit l'ordre d'affichage des widgets */
    couche.addWidget(&code);
    couche.addWidget(&titre);
    //couche.addLayout(&coucheH);
    couche.addWidget(&save);

    fenetre.setLayout(&couche); //Indique a fenetre d'utiliser couche pour positionner les objets


    //UVManager m=UVManager::getInstance(); //singleton, constructeur de recopie dans la partie privée, impossible à compiler. Attention médian
    UVManager& m=UVManager::getInstance();

    QString chemin = QFileDialog::getOpenFileName();
   // m.load(chemin);

    UV& lo21=m.getUV("LO21");
    code.setText(lo21.getCode());
    titre.setText(lo21.getTitre());


    fenetre.show();   //appel du show de tous les widgets enfants

    return app.exec();
}

int exercice3(int argc, char *argv[]) {
    QApplication app(argc, argv);
    UVManager& m=UVManager::getInstance();
//    QString chemin = QFileDialog::getOpenFileName();
    m.load();
    cout<<"test";
    UV& uv=m.getUV("LO21");
    UVEditeur fenetre(uv);
    fenetre.show();
    return app.exec();
}

int menu(int argc, char* argv[]){

    QApplication app(argc,argv);

    Profiler fenetre;
    fenetre.show();
    return app.exec();


}

int main (int argc, char* argv[]) {
    //return menu(argc, argv);
    DatabaseManager& m=DatabaseManager::getInstanceDB();

    menu(argc,argv);
    return 0;

}

