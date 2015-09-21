/**
  * \file Category.h
  * \brief Définition de la classe Category
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <QString>

/**
 *      Cette classe implémente les différentes catégories possible pour les UV (Unités de Valeur).
 */
class Category{
public:
    /**
     *      Constructeur de la classe Category.
     * @param code Abbréviation de la catégorie.
     * @param name Nom complet de la categorie.
     */
    inline Category(QString code, QString name):m_code(code), m_name(name){}
    /**
     * @return L'abbréviation de la catégorie.
     */
    inline QString getCode() const {return m_code;}
    /**
     *      Permet de modifier l'abbréviation d'une catégorie.
     * @param code Nouvelle abbréviation de la catégorie.
     */
    inline void setCode(QString code){m_code = code;}
    /**
     * @return Le nom complet de la catégorie.
     */
    inline QString getName() const {return m_name;}
    /**
     *      Permet de modifier le nom complet d'une catégorie.
     * @param name Le nouveau nom de la catégorie.
     */
    inline void setName(QString name){m_name = name;}
protected:
    /**
     * @brief m_code
     *      L'abbréviation de la catégorie.
     */
    QString m_code; //CS, TM, TSH, SP
    /**
     * @brief m_name
     *      Le nom complet de la catégorie.
     */

     /** m_name Le nom complet de la catégorie.
     */
    QString m_name; //Connaissances scientifiques, Techniques et méthodes, Technologies et Sciences de l'Homme,…
};

#endif // CATEGORY_H
