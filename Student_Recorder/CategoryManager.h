/**
  * \file CategoryManager.h
  * \brief Définition de la classe CategoryManager, de ses attributs et méthodes
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include <iostream>
#include <QString>
#include <QList>
#include <algorithm>
#include "Category.h"

/**
 Classe qui permet de gérer les différentes catégories (cs,tsh, tm, sp...)  : en ajouter, en supprimer,…
 */
class CategoryManager{
public:
    /**Gestion du singleton*/
    static CategoryManager& giveInstance();
    static void freeInstance();

    /**Gestion des catégories*/
    void addCategory(QString code, QString name);
    void deleteCategory(QString code);
    Category getCategory(QString code);
    /**
     * @return QList des différentes catégories existantes pour les UV.
     */
    QList<Category> getListCategory(){return l_category;}
protected:
    /**
     *  @brief
     *      Pointeur sur l'instance unique de CategoryManager.
     */
    static CategoryManager* singleInstance;
    CategoryManager();
    CategoryManager(const CategoryManager&);
    virtual ~CategoryManager();
    void operator= (const CategoryManager);
    /**
     * @brief
     *      QList regroupant les différentes catégories existantes.
     */
    QList<Category> l_category;
};

#endif // CATEGORYMANAGER_H
