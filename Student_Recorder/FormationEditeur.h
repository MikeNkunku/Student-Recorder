#ifndef FORMATIONEDITEUR_H
#define FORMATIONEDITEUR_H

/**
  * \file FormationEditeur.h
  * \brief Définition de la fenêtre permettant l'édition d'UV.
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "FormationManager.h"

#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidget>
#include <QMainWindow>
#include <QInputDialog>

/**
 * @brief Cette classe objet permet de visualiser les différentes caractéristiques des UV, et via la gestion de ses signaux, va permettre de
 * modifier les UV à l'utilisateur.
 */
class FormationEditeur:public QWidget{
    Q_OBJECT //deploie les instructions pour gérer les signaux et les slots

    Formation& fo;
    QLabel* codeLabel;
    QLabel* titreLabel;
    QLabel* creditsCSLabel;
    QLabel* creditsTMLabel;
    QLabel* creditsTSHLabel;
    QLabel* creditsSPLabel;

    QLineEdit* code;
    QTextEdit* titre;
    QSpinBox* CS;
    QSpinBox* TM;
    QSpinBox* TSH;
    QSpinBox* SP;

    QPushButton* addUV;
    QPushButton* deleteUV;
    QPushButton* addUVCons;
    QPushButton* deleteUVCons;
    QPushButton* addFiliere;
    QPushButton* deleteFiliere;

    QPushButton* save;
    QPushButton* cancel;

    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;

    QVBoxLayout* couche;

public:
    FormationEditeur(Formation& FormationToEdit, QMainWindow *parent=0);

public slots:
    void activSave(QString="");
    void cancelChanges();
    void supprimerUV();
    void ajouterUV();
    void supprimerUVCons();
    void ajouterUVCons();
    void ajouterFiliere();
    void supprimerFiliere();
    void sauverFormation();
};

/**
 * @brief Cette classe objet permet de créer des UV.
 */
class FormationCreateur:public QWidget{
    Q_OBJECT //deploie les instructions pour gérer les signaux et les slots

    QLabel* codeLabel;
    QLabel* titreLabel;
    QLabel* creditsCSLabel;
    QLabel* creditsTMLabel;
    QLabel* creditsTSHLabel;
    QLabel* creditsSPLabel;

    QLineEdit* code;
    QTextEdit* titre;
    QSpinBox* CS;
    QSpinBox* TM;
    QSpinBox* TSH;
    QSpinBox* SP;

    QPushButton* save;
    QPushButton* cancel;

    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH4;

    QVBoxLayout* couche;

public:
    FormationCreateur(QMainWindow *parent=0);

public slots:
    void activSave(QString="");
    void cancelChanges();
    void sauverFormation();
};

#endif // FORMATIONEDITEUR_H
