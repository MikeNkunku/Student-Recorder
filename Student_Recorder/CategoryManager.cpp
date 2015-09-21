/**
  * \file CategoryManager.h
  * \brief Définition des méthodes non-inline du gestionnaire des catégories d'UV
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "CategoryManager.h"
#include "UTProfiler.h"
#include <QString>
#include <QMessageBox>


/**
 * @brief CategoryManager::CategoryManager
 *
 *      Constructeur de la classe CategoryManager;
 */
CategoryManager::CategoryManager(){}

/**
 * @brief CategoryManager::singleInstance
 *
 *      L'unique instance de classe CategoryManager pointe initialement sur NULL (0);
 */
CategoryManager* CategoryManager::singleInstance = 0;

/**
 * @brief CategoryManager::giveInstance
 *
 *      Création de l'unique instance si non existante.
 * @return L'instance unique de CategoryManager.
 */
CategoryManager& CategoryManager::giveInstance(){
    if (!singleInstance) {
        singleInstance = new CategoryManager;
    }
    return *singleInstance;
}

/**
 * @brief CategoryManager::freeInstance
 *
 *      Si l'instance unique de CategoryManager existe, alors cette dernière est supprimée et elle est pointe à nouveau sur NULL (0).
 */
void CategoryManager::freeInstance(){
    if (singleInstance) {
        delete singleInstance;
    }
    singleInstance = 0;
}

/**
 * @brief CategoryManager::~CategoryManager
 *
 *      Destructeur de la classe CategoryManager.
 */
CategoryManager::~CategoryManager(){}

/**
 * @brief CategoryManager::addCategory
 *
 *      Permet d'ajouter une catégorie.
 * @param code Abbréviation de la catégorie à ajouter.
 * @param name Nom complet de la catégorie à ajouter.
 */
void CategoryManager::addCategory(QString code, QString name){
    CategoryManager::l_category.push_back(Category(code, name));
}

/**
 * @brief CategoryManager::getCategory
 * @param code Abbréviation de la catégorie recherchée
 * @return La catégorie recherchée si existante, sinon un message d'erreur est affiché.
 */
Category CategoryManager::getCategory(QString code){
    QList<Category>::iterator it=l_category.begin();
    while(it != l_category.end() && (*it).getCode() != code)
        it++;
    if (it != l_category.end()) return *it;
    throw UTProfilerException("Catégorie introuvable !\nVeuillez respecter les majuscules.");
    /*for (it = l_category.begin(); it != l_category.end() && (*it).getCode() != code; ++it);
    if (it != l_category.end()){
            return *it;
    }
    return *l_category.begin(); // À modifier IMPÉRATIVEMENT (faire un try catch)
            */
}

/*unsigned int CategoryManager::findIndexCategory(QString code) const{
    for (unsigned int i = 0; i < l_category.size(); i++) {
        if (code == l_category[i].getCode()) return i;
    }
    return 0;
}

Category* CategoryManager::findCategory(QString& code) const{
    unsigned int index = findIndexCategory(code);
    if (index) return m_category[index];
    return 0;
}*/

/*Category& CategoryManager::getCategory(QString& code) const{
    Category* category = findCategory(code);
    return *category;
}
*/
/**
 * @brief CategoryManager::deleteCategory
 *
 *      Permet la suppression d'une catégorie dans la liste des catégories des UV.
 * @param code Abbréviation de la catégorie à supprimer.
 */
void CategoryManager::deleteCategory(QString code){
    QList<Category>::iterator it;
    for (it = l_category.begin(); it != l_category.end() && (*it).getCode() != code; ++it);
    if (it != l_category.end()){
        l_category.erase(it);
    }
}
