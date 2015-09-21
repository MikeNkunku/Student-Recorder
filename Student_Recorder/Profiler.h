/**
  * \file Profiler.h
  * \brief Déclaration de l'objet permettant les premières actions dans l'application et de ses composantes.
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#ifndef PROFILER_H
#define PROFILER_H


#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QLineEdit>
#include <QFormLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QAction>
#include <QInputDialog>


#include "UVEditeur.h"
#include "affichageUV.h"
#include "UTProfiler.h"
#include "FormationManager.h"
#include "FormationEditeur.h"
#include "WindowLoadStudent.h"

/**
 * @brief The Profiler class
 *
 *  Cette classe permet de définir la fenêtre d'ouverture de l'application et les différentes actions possibles telles que le chargement
 * nécessaire des UVs pour pouvoir les consulter ou les modifier ou encore le chargement du dossier d'un étudiant.
 */
class Profiler : public QMainWindow {
    Q_OBJECT
private:
    QMenu *menuFichier;
    QAction *actionQuitter;
    QMenu *menuChargement;
    QAction *actionChargerUV;
    QMenu *menuEdition;
    QAction *actionEditerUV;
    QAction *actionCreerUV;
    QAction *actionEditerDossier;
    QMenu *menuRecherche;
    QAction *actionRechercheUV;
    QWidget *zoneCentrale;
    QMenu *menuEditionUV;
    WindowLoadStudent* windowLoadStudent;

    QMenu* menuEditionFormation;
    QAction* actionCreerFormation;
    QAction* actionEditerFormation;
    QAction* loadStudent;

public:
    Profiler();
    ~Profiler();

public slots:
    void affichageUV();
    void editeurUV();
    void creerUV();
    void chargementUV();
    void editeurFormation();
    void creerFormation();
    void openWindowLoadStudent();
};

#endif // PROFILER_H
