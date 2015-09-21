/**
  * \file affichageUV.cpp
  * \brief Fenêtre affichant les différentes UV dans la base de données actuelle
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "affichageUV.h"
#include "UTProfiler.h"
#include <QtXml>
#include "FormationManager.h"
#include "Formation.h"

/**
 * @brief AfficheurUV::AfficheurUV
 *
 *  Cette fenêtre présente les différentes UV existantes dans la base de données.
 *  Y sont affichés le code, le titre, la catégorie, le nombre de crédits (en ECTS) CS, TM, TSH et SP.
 *
 * @param FM Fenêtre principale de l'application.
 */
AfficheurUV::AfficheurUV(QMainWindow &FM){

    parent=&FM;

    zoneCentrale = new QWidget;

    coucheH1 = new QHBoxLayout;
    coucheH2 = new QHBoxLayout;
    coucheH3 = new QHBoxLayout;

    UVManager& m=UVManager::getInstance();
    unsigned int i=0;

    automne = new QCheckBox("Automne",this);
    automne->setChecked(true);
    QObject::connect(automne, SIGNAL(stateChanged(int)),this,SLOT(filtre()));

    printemps = new QCheckBox("Printemps",this);
    printemps->setChecked(true);
    QObject::connect(printemps, SIGNAL(stateChanged(int)),this,SLOT(filtre()));

    All = new QRadioButton("Tout",this);
    All->setChecked(true);
    QObject::connect(All, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    CS = new QRadioButton("CS",this);
    QObject::connect(CS, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    TM = new QRadioButton("TM",this);
    QObject::connect(TM, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    TSH = new QRadioButton("TSH",this);
    QObject::connect(TSH, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    SP = new QRadioButton("SP",this);
    QObject::connect(SP, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    coucheH1->addWidget(All);
    coucheH1->addWidget(CS);
    coucheH1->addWidget(TM);
    coucheH1->addWidget(TSH);
    coucheH1->addWidget(SP);
    coucheH1->addWidget(printemps);
    coucheH1->addWidget(automne);
    typUV=new QGroupBox("Types d'UV et Ouverture",this);
    typUV->setLayout(coucheH1);

    AllBr = new QRadioButton("Pour tous",this);
    AllBr->setChecked(true);
    QObject::connect(AllBr, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    TC = new QRadioButton("TC",this);
    QObject::connect(TC, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    GI = new QRadioButton("GI",this);
    QObject::connect(GI, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    GB = new QRadioButton("GB",this);
    QObject::connect(GB, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    GP = new QRadioButton("GP",this);
    QObject::connect(GP, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    GSU = new QRadioButton("GSU",this);
    QObject::connect(GSU, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    GM_GSM = new QRadioButton("GM/GSM",this);
    QObject::connect(GM_GSM, SIGNAL(clicked(bool)),this,SLOT(filtre()));

    coucheH2->addWidget(AllBr);
    coucheH2->addWidget(TC);
    coucheH2->addWidget(GI);
    coucheH2->addWidget(GB);
    coucheH2->addWidget(GM_GSM);
    coucheH2->addWidget(GP);
    coucheH2->addWidget(GSU);
    //coucheH2->addStretch(1);

    typForm = new QGroupBox("Niveaux de formation",this);
    typForm->setLayout(coucheH2);

    tab = new QTableWidget(this);
    tab->setRowCount(m.getNbUV());
    tab->setColumnCount(7);
    QMap<QString,int> map;

    Labels=new QStringList;

    *Labels<<"Code"<<"Titre"<<"Categorie"<<"Credits CS"<<"Credits TM"<<"Credits TSH"<<"Credits SP";
    tab->setHorizontalHeaderLabels(*Labels);

    for(UVManager::iterator it=m.begin();it!=m.end();++it){

        UV& u=*it;

        newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
        tab->setItem(i, 0, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
        tab->setItem(i, 1, newItem);

        cat=u.getCategorie();
        newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
        tab->setItem(i,2, newItem);

        map=u.getCat();
        newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
        tab->setItem(i,3, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
        tab->setItem(i,4, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
        tab->setItem(i,5, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
        tab->setItem(i,6, newItem);

        i++;
    }

    tab->verticalHeader()->hide();
    tab->resizeColumnsToContents ();
    tab->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    coucheH3->addWidget(tab);

    couche = new QVBoxLayout;

    couche->addWidget(typUV);
    couche->addWidget(typForm);
    couche->addLayout(coucheH3);
    zoneCentrale = new QWidget;
    zoneCentrale->setLayout(couche);

    parent->setCentralWidget(zoneCentrale);
}

/**
 * @brief AfficheurUV::filtre
 *
 *  Cette fonction se déclenche dès lors que les critères de filtrage par défaut sont modifiés.
 * Il est possible de filtrer selon trois critères :
 *  - la disponibilité de l'UV selon les semestres : Automne ou Printemps ;
 *  - la catégorie de l'UV : toutes catégories confondues, CS, TM, TSH ou SP ;
 *  - le niveau de formation : Tous niveaux, TC, GI, GP, GM/GSM, GSU ou GB.
 *
 */
void AfficheurUV::filtre(){
    UVManager& m=UVManager::getInstance();
    FormationManager& fm=FormationManager::getInstance();
    QTableWidget* oldtab=tab;
    QTableWidget* newtab=new QTableWidget(this);
    newtab->setRowCount(m.getNbUV());
    newtab->setColumnCount(7);
    unsigned int i(0);

    Labels=new QStringList;
    *Labels<<"Code"<<"Titre"<<"Categorie"<<"CS"<<"Credits TM"<<"Credits TSH"<<"Credits SP";
    newtab->setHorizontalHeaderLabels(*Labels);
    newtab->verticalHeader()->hide();
    newtab->resizeColumnsToContents ();
    newtab->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    if(All->isChecked()){
            if(AllBr->isChecked()){
            for(UVManager::iterator it=m.begin();it!=m.end();++it){
                UV& u=*it;
                if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
                newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                newtab->setItem(i, 0, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                newtab->setItem(i, 1, newItem);

                cat=u.getCategorie();
                newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                newtab->setItem(i,2, newItem);

                map=u.getCat();
                newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                newtab->setItem(i,3, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                newtab->setItem(i,4, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                newtab->setItem(i,5, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                newtab->setItem(i,6, newItem);

                i++;
            }
            }
            }
        else if(GI->isChecked()) {
                QList<UV*> uvsGI = fm.getFormation(QString("GI")).getUVList();
                for(QList<UV*>::iterator it=uvsGI.begin();it!=uvsGI.end();++it) {
                    UV& u= (**it);
                    if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GB->isChecked()){
                QList<UV*> uvsGB = fm.getFormation(QString("GB")).getUVList();
                for(QList<UV*>::iterator it=uvsGB.begin();it!=uvsGB.end();++it) {
                    UV& u= (**it);
                    if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GM_GSM->isChecked()){
                QList<UV*> uvsGM = fm.getFormation(QString("GM")).getUVList();
                for(QList<UV*>::iterator it=uvsGM.begin();it!=uvsGM.end();++it) {
                    UV& u= (**it);
                    if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
            else if (GP->isChecked()){
                QList<UV*> uvsGP = fm.getFormation(QString("GP")).getUVList();
                for(QList<UV*>::iterator it=uvsGP.begin();it!=uvsGP.end();++it) {
                    UV& u= (**it);
                    if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
            else if (GSU->isChecked()){
                QList<UV*> uvsGSU = fm.getFormation(QString("GSU")).getUVList();
                for(QList<UV*>::iterator it=uvsGSU.begin();it!=uvsGSU.end();++it) {
                    UV& u= (**it);
                    if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
            else if (TC->isChecked()){
                QList<UV*> uvsTC = fm.getFormation(QString("TC")).getUVList();
                for(QList<UV*>::iterator it=uvsTC.begin();it!=uvsTC.end();++it) {
                    UV& u= (**it);
                    if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
    }

    else if(CS->isChecked()){
        if(AllBr->isChecked()){
            qDebug()<<"Cs - AllBr checked";
        for(UVManager::FilterIterator it=m.FIbegin("CS");it!=m.FIend("CS");++it){

            UV& u=*it;
            if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
            newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
            newtab->setItem(i, 0, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
            newtab->setItem(i, 1, newItem);

            cat=u.getCategorie();
            newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
            newtab->setItem(i,2, newItem);

            map=u.getCat();
            newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
            newtab->setItem(i,3, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
            newtab->setItem(i,4, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
            newtab->setItem(i,5, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
            newtab->setItem(i,6, newItem);

            i++;
        }
        }
        }
        else if(GI->isChecked()) {
                QList<UV*> uvsGI = fm.getFormation(QString("GI")).getUVList();
                for(QList<UV*>::iterator it=uvsGI.begin();it!=uvsGI.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("CS")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GB->isChecked()){
                QList<UV*> uvsGB = fm.getFormation(QString("GB")).getUVList();
                for(QList<UV*>::iterator it=uvsGB.begin();it!=uvsGB.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("CS")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GM_GSM->isChecked()){
                QList<UV*> uvsGM = fm.getFormation(QString("GM")).getUVList();
                for(QList<UV*>::iterator it=uvsGM.begin();it!=uvsGM.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("CS")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GP->isChecked()){
                QList<UV*> uvsGP = fm.getFormation(QString("GP")).getUVList();
                for(QList<UV*>::iterator it=uvsGP.begin();it!=uvsGP.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("CS")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GSU->isChecked()){
                QList<UV*> uvsGSU = fm.getFormation(QString("GSU")).getUVList();
                for(QList<UV*>::iterator it=uvsGSU.begin();it!=uvsGSU.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("CS")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (TC->isChecked()){
                QList<UV*> uvsTC = fm.getFormation(QString("TC")).getUVList();
                for(QList<UV*>::iterator it=uvsTC.begin();it!=uvsTC.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("CS")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
    }

    else if(TM->isChecked()){
        if (AllBr->isChecked()){
        for(UVManager::FilterIterator it=m.FIbegin("TM");it!=m.FIend("TM");++it){

            UV& u=*it;
            if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
            newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
            newtab->setItem(i, 0, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
            newtab->setItem(i, 1, newItem);

            cat=u.getCategorie();
            newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
            newtab->setItem(i,2, newItem);

            map=u.getCat();
            newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
            newtab->setItem(i,3, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
            newtab->setItem(i,4, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
            newtab->setItem(i,5, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
            newtab->setItem(i,6, newItem);

            i++;}
        }
        }
        else if(GI->isChecked()) {
                QList<UV*> uvsGI = fm.getFormation(QString("GI")).getUVList();
                for(QList<UV*>::iterator it=uvsGI.begin();it!=uvsGI.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("TM")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GB->isChecked()){
                QList<UV*> uvsGB = fm.getFormation(QString("GB")).getUVList();
                for(QList<UV*>::iterator it=uvsGB.begin();it!=uvsGB.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("TM")>0) &&((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GM_GSM->isChecked()){
                QList<UV*> uvsGM = fm.getFormation(QString("GM")).getUVList();
                for(QList<UV*>::iterator it=uvsGM.begin();it!=uvsGM.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("TM")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
                QList<UV*> uvsGSM = fm.getFormation(QString("GSM")).getUVList();
                for(QList<UV*>::iterator it=uvsGSM.begin();it!=uvsGSM.end();++it) {
                    UV& u= (**it);
                    if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GP->isChecked()){
                QList<UV*> uvsGP = fm.getFormation(QString("GP")).getUVList();
                for(QList<UV*>::iterator it=uvsGP.begin();it!=uvsGP.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("TM")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GSU->isChecked()){
                QList<UV*> uvsGSU = fm.getFormation(QString("GSU")).getUVList();
                for(QList<UV*>::iterator it=uvsGSU.begin();it!=uvsGSU.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("TM")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (TC->isChecked()){
            QList<UV*> uvsTC = fm.getFormation(QString("TC")).getUVList();
            for(QList<UV*>::iterator it=uvsTC.begin();it!=uvsTC.end();++it) {
                UV& u= (**it);
                if ((u.getCat().value("TM")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                newtab->setItem(i, 0, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                newtab->setItem(i, 1, newItem);

                cat=u.getCategorie();
                newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                newtab->setItem(i,2, newItem);

                map=u.getCat();
                newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                newtab->setItem(i,3, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                newtab->setItem(i,4, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                newtab->setItem(i,5, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                newtab->setItem(i,6, newItem);
                i++;
                }
            }
        }
    }

    else if(TSH->isChecked()){
        if(AllBr->isChecked()){
        for(UVManager::FilterIterator it=m.FIbegin("TSH");it!=m.FIend("TSH");++it){

            UV& u=*it;
            if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
            newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
            newtab->setItem(i, 0, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
            newtab->setItem(i, 1, newItem);

            cat=u.getCategorie();
            newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
            newtab->setItem(i,2, newItem);

            map=u.getCat();
            newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
            newtab->setItem(i,3, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
            newtab->setItem(i,4, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
            newtab->setItem(i,5, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
            newtab->setItem(i,6, newItem);

            i++;}
        }
        }
        else if(GI->isChecked()) {
                QList<UV*> uvsGI = fm.getFormation(QString("GI")).getUVList();
                for(QList<UV*>::iterator it=uvsGI.begin();it!=uvsGI.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("TSH")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GB->isChecked()){
                QList<UV*> uvsGB = fm.getFormation(QString("GB")).getUVList();
                for(QList<UV*>::iterator it=uvsGB.begin();it!=uvsGB.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("TSH")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GM_GSM->isChecked()){
                QList<UV*> uvsGM = fm.getFormation(QString("GM")).getUVList();
                for(QList<UV*>::iterator it=uvsGM.begin();it!=uvsGM.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("TSH")>0) && (automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
        }
        else if (GP->isChecked()){
            QList<UV*> uvsGP = fm.getFormation(QString("GP")).getUVList();
            for(QList<UV*>::iterator it=uvsGP.begin();it!=uvsGP.end();++it) {
                UV& u= (**it);
                if ((u.getCat().value("TSH")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                newtab->setItem(i, 0, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                newtab->setItem(i, 1, newItem);

                cat=u.getCategorie();
                newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                newtab->setItem(i,2, newItem);

                map=u.getCat();
                newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                newtab->setItem(i,3, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                newtab->setItem(i,4, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                newtab->setItem(i,5, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                newtab->setItem(i,6, newItem);
                i++;
                }
            }
        }
        else if (GSU->isChecked()){
                QList<UV*> uvsGSU = fm.getFormation(QString("GSU")).getUVList();
                for(QList<UV*>::iterator it=uvsGSU.begin();it!=uvsGSU.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("TSH")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (TC->isChecked()){
            QList<UV*> uvsTC = fm.getFormation(QString("TC")).getUVList();
            for(QList<UV*>::iterator it=uvsTC.begin();it!=uvsTC.end();++it) {
                UV& u= (**it);
                if ((u.getCat().value("TSH")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                newtab->setItem(i, 0, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                newtab->setItem(i, 1, newItem);

                cat=u.getCategorie();
                newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                newtab->setItem(i,2, newItem);

                map=u.getCat();
                newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                newtab->setItem(i,3, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                newtab->setItem(i,4, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                newtab->setItem(i,5, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                newtab->setItem(i,6, newItem);
                i++;
                }
            }
        }
    }

    else if(SP->isChecked()){
        if(AllBr->isChecked()){
        for(UVManager::FilterIterator it=m.FIbegin("SP");it!=m.FIend("SP");++it){

            UV& u=*it;
            if ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps())){
            newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
            newtab->setItem(i, 0, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
            newtab->setItem(i, 1, newItem);

            cat=u.getCategorie();
            newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
            newtab->setItem(i,2, newItem);

            map=u.getCat();
            newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
            newtab->setItem(i,3, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
            newtab->setItem(i,4, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
            newtab->setItem(i,5, newItem);

            newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
            newtab->setItem(i,6, newItem);

            i++;}
        }
        }
        else if(GI->isChecked()) {
                QList<UV*> uvsGI = fm.getFormation(QString("GI")).getUVList();
                for(QList<UV*>::iterator it=uvsGI.begin();it!=uvsGI.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("SP")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GB->isChecked()){
                QList<UV*> uvsGB = fm.getFormation(QString("GB")).getUVList();
                for(QList<UV*>::iterator it=uvsGB.begin();it!=uvsGB.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("SP")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GM_GSM->isChecked()){
                QList<UV*> uvsGM = fm.getFormation(QString("GM")).getUVList();
                for(QList<UV*>::iterator it=uvsGM.begin();it!=uvsGM.end();++it) {
                    UV& u= (**it);
                    if ((u.getCat().value("SP")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                    newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                    newtab->setItem(i, 0, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                    newtab->setItem(i, 1, newItem);

                    cat=u.getCategorie();
                    newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                    newtab->setItem(i,2, newItem);

                    map=u.getCat();
                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                    newtab->setItem(i,3, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                    newtab->setItem(i,4, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                    newtab->setItem(i,5, newItem);

                    newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                    newtab->setItem(i,6, newItem);
                    i++;
                    }
                }
            }
        else if (GP->isChecked()){
            QList<UV*> uvsGP = fm.getFormation(QString("GP")).getUVList();
            for(QList<UV*>::iterator it=uvsGP.begin();it!=uvsGP.end();++it) {
                UV& u= (**it);
                if ((u.getCat().value("SP")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                newtab->setItem(i, 0, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                newtab->setItem(i, 1, newItem);

                cat=u.getCategorie();
                newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                newtab->setItem(i,2, newItem);

                map=u.getCat();
                newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                newtab->setItem(i,3, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                newtab->setItem(i,4, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                newtab->setItem(i,5, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                newtab->setItem(i,6, newItem);
                i++;
                }
            }
        }
        else if (GSU->isChecked()){
            QList<UV*> uvsGSU = fm.getFormation(QString("GSU")).getUVList();
            for(QList<UV*>::iterator it=uvsGSU.begin();it!=uvsGSU.end();++it) {
                UV& u= (**it);
                if ((u.getCat().value("SP")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                newtab->setItem(i, 0, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                newtab->setItem(i, 1, newItem);

                cat=u.getCategorie();
                newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                newtab->setItem(i,2, newItem);

                map=u.getCat();
                newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                newtab->setItem(i,3, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                newtab->setItem(i,4, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                newtab->setItem(i,5, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                newtab->setItem(i,6, newItem);
                i++;
                }
            }
        }
        else if (TC->isChecked()){
            QList<UV*> uvsTC = fm.getFormation(QString("TC")).getUVList();
            for(QList<UV*>::iterator it=uvsTC.begin();it!=uvsTC.end();++it) {
                UV& u= (**it);
                if ((u.getCat().value("SP")>0) && ((automne->isChecked() && printemps->isChecked() && (u.ouvertureAutomne() || u.ouverturePrintemps())) || (automne->isChecked() && !(printemps->isChecked()) && u.ouvertureAutomne()) || (printemps->isChecked() && !(automne->isChecked()) && u.ouverturePrintemps()))){
                newItem = new QTableWidgetItem(tr("%1").arg(u.getCode()));
                newtab->setItem(i, 0, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(u.getTitre()));
                newtab->setItem(i, 1, newItem);

                cat=u.getCategorie();
                newItem = new QTableWidgetItem(tr("%1").arg(cat.value(0)+cat.value(1)+cat.value(2)+cat.value(3)));
                newtab->setItem(i,2, newItem);

                map=u.getCat();
                newItem = new QTableWidgetItem(tr("%1").arg(map.value("CS")));
                newtab->setItem(i,3, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TM")));
                newtab->setItem(i,4, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("TSH")));
                newtab->setItem(i,5, newItem);

                newItem = new QTableWidgetItem(tr("%1").arg(map.value("SP")));
                newtab->setItem(i,6, newItem);
                i++;
                }
            }
        }
    }

    coucheH3->removeWidget(tab);
    delete oldtab;
    tab=newtab;
    for(unsigned int j(i);j<=m.getNbUV();j++){
        tab->hideRow(j);
    }

    coucheH3->addWidget(tab);

}
