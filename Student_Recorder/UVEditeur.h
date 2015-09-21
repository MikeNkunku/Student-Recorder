#ifndef UVEDITEUR_H
#define UVEDITEUR_H

/**
  * \file UVEditeur.h
  * \brief Fenêtre dans laquelle les UV sont éditées
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */


#include "UTProfiler.h"
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

/**
 * @brief Cette classe objet permet d'éditer les UV, via les signaux récupérés et les slots associés.
 */
class UVEditeur : public QWidget{
    Q_OBJECT //deploie les instructions pour gérer les signaux et les slots

    UV& uv;
    QLineEdit* code;
    QLabel* codeLabel;

    QTextEdit* titre;
    QLabel* titreLabel;

    QLabel* creditsLabel;

    QSpinBox* creditsCS;
    QLabel* creditsCSLabel;

    QSpinBox* creditsTM;
    QLabel* creditsTMLabel;

    QSpinBox* creditsTSH;
    QLabel* creditsTSHLabel;

    QSpinBox* creditsSP;
    QLabel* creditsSPLabel;

    QLabel* ouvertureLabel;

    QCheckBox* printemps;
    QCheckBox* automne;
    QPushButton* save;
    QPushButton* cancel;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;


public:
    UVEditeur(UV& u, QMainWindow *parent=0); //on peut éventuellement avoir une classe parente

public slots:
    void sauverUV();
    void activSave(QString str="");
    void cancelChanges();
};

/**
 * @brief Cette classe objet permet de créer des UV.
 */
class UVCreateur : public QWidget {
    Q_OBJECT //deploie les instructions pour gérer les signaux et les slots

    QLineEdit* code;
    QLabel* codeLabel;

    QTextEdit* titre;
    QLabel* titreLabel;

    QLabel* creditsLabel;

    QSpinBox* creditsCS;
    QLabel* creditsCSLabel;

    QSpinBox* creditsTM;
    QLabel* creditsTMLabel;

    QSpinBox* creditsTSH;
    QLabel* creditsTSHLabel;

    QSpinBox* creditsSP;
    QLabel* creditsSPLabel;

    QLabel* ouvertureLabel;

    QCheckBox* printemps;
    QCheckBox* automne;
    QPushButton* save;
    QPushButton* cancel;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;


public:
    UVCreateur(QMainWindow *parent=0);

public slots:
    void creerUV();
    void activSave(QString str="");
    void cancelChanges();
};

#endif // UVEDITEUR_H
