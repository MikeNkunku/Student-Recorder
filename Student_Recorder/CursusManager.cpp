/**
  * \file CursusManager.cpp
  * \brief Définition des méthodes non-inline de la classe CursusManager
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "CursusManager.h"
#include "UTProfiler.h"

/**
 * @brief Constructeur de la classe.
 */
CursusManager::CursusManager(){}

/**
 * @brief Initialisation de l'instance unique à 0 (Pointeur NULL).
 */
CursusManager* CursusManager::singleInstance = 0;

/**
 * @return Une référence sur l'instance unique, après création si elle n'existait pas au préalable.
 */
CursusManager& CursusManager::giveInstance(){
    if (!singleInstance) {
        singleInstance = new CursusManager;
    }
    return *singleInstance;
}

/**
 * @brief Suppression de l'instance unique de la classe CursusManager, qui pointe alors comme initialement sur le pointeur NULL.
 */
void CursusManager::freeInstance(){
    if (singleInstance) {
        delete singleInstance;
    }
    singleInstance = 0;
}

/**
 * @brief Destructeur de la classe.
 */
CursusManager::~CursusManager(){}

/**
 * @brief Ajout d'un cursus à la liste des cursus déjà suivis.
 * @param code Code du cursus (ex : Génie Informatique -> GI).
 * @param name Nom complet du cursus (ex : GI -> Génie Informatique).
 */
void CursusManager::addCursus(QString code, QString name){
    CursusManager::l_cursus.push_back(Cursus(code, name));
}

/**
 * @param code Code du cursus
 * @return Le cursus s'il existe, sinon déclenche une exception.
 */
Cursus CursusManager::getCursus(QString code){
    QList<Cursus>::iterator it;
    for (it = l_cursus.begin(); it != l_cursus.end() && (*it).getCode() != code; ++it);
    if (it != l_cursus.end()){
        return *it;
    }
    throw UTProfilerException("Le cursus recherché n'existe pas !\n");
    // À modifier IMPÉRATIVEMENT (faire un try catch)
}

/**
 * @brief Suppression d'un cursus.
 * @param code Code du cursus.
 */
void CursusManager::deleteCursus(QString code){
    QList<Cursus>::iterator it;
    for (it = l_cursus.begin(); it != l_cursus.end() && (*it).getCode() != code; ++it);
    if (it != l_cursus.end()){
        l_cursus.erase(it);
    }
}
