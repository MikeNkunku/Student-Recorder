#ifndef FORMATIONMANAGER_H
#define FORMATIONMANAGER_H

/**
  * \file FormationManager.h
  * \brief Définition du gestionnaire de formations, de ses attributs et de ses méthodes
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "UTProfiler.h"
#include "Formation.h"
#include <QList>



/**
 * @brief Cette classe permet la gestion des formations dans la base de données (ajout, suppression, modification, ...).
 */
class FormationManager{
    /**
     * @brief Liste de pointeurs sur les différentes formations existantes (branches et filières).
     */
    QList<Formation*> fmts;
    /**
     * @brief Nombre de formations existantes.
     */
    unsigned int nbFormations;
    /**
     * @brief modification Vrai s'il y a modification, faux sinon.
     */
    bool modification;
    void addItem(Formation* f);
    FormationManager(const FormationManager& fm);               //On bloque le constructeur de recopie et l'opérateur d'affectation
    FormationManager& operator=(const FormationManager& fm);
    FormationManager();
    ~FormationManager();

    friend struct Handler;
    /**
     * @brief Permet de gérer l'unique instance de la classe FormationManager.
     */
    struct Handler{
        /**
         * @brief Instance unique de FormationManager.
         */
        FormationManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;
public:
    static FormationManager& getInstance();
    static void libererInstance();
    void addFormation(const QString& c, const QString& t, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP, bool B);
    /**
     * @return Pointeur sur la liste de pointeurs de formation.
     */
    QList<Formation*>* getFormationList() {return &fmts;}
    Formation& getFormation(const QString code);
    const Formation& getFormation(const QString code) const;
    Formation* trouverFormation(const QString code) const;

    void load();
    void save();
};

#endif // FORMATIONMANAGER_H
