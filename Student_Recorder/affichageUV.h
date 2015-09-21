/**
  * \file affichageUV.h
  * \brief Fenêtre affichant les différentes UV dans la base de données actuelle
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#ifndef AFFICHAGEUV_H
#define AFFICHAGEUV_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include <iostream>
#include <QSpinBox>

/**
 * Cette classe permet de définit un objet dont le rôle est d'afficher les UV (Unités de Valeur).
 *
 */
class AfficheurUV : public QWidget {
    Q_OBJECT

    QMainWindow* parent;
    QWidget *zoneCentrale;

    /*Création des boutons pour pouvoir filtrer */
    QCheckBox* printemps;
    QCheckBox* automne;

    QRadioButton* All;
    QRadioButton* CS;
    QRadioButton* TM;
    QRadioButton* TSH;
    QRadioButton* SP;

    QRadioButton* AllBr;
    QRadioButton* TC;
    QRadioButton* GI;
    QRadioButton* GB;
    QRadioButton* GSU;
    QRadioButton* GM_GSM;
    QRadioButton* GP;

    QSpinBox semestre;
    QSpinBox categorie;

    //Boxes auxquelles appartiennent les critères de filtre
    QGroupBox* typUV;
    QGroupBox* typForm;

    /*tableau d'affichage des UVs */
    QTableWidget* tab;
    QTableWidgetItem* newItem;
    QStringList* Labels,cat;
    QMap<QString,int> map;

    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QVBoxLayout* couche;

public:
    AfficheurUV (QMainWindow& FM);
public slots:
    void filtre();

};
#endif // AFFICHAGEUV_H
