#ifndef RECORD_H
#define RECORD_H

/**
  * \file Record.h
  * \brief Définition des enregistrements, de leurs attributs et méthodes
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include <QString>
#include <QVector>
#include <QList>
#include "Semester.h"
#include "UVResult.h"

/**
 * @brief Cette classe implémente les différentes inscriptions possibles dans la base de données.
 */
class Record {
public:
    Record(QString m_login, QString name, QString surname, unsigned int nbSemesters);
    /**
     * @return Le login de la personne.
     */
    QString getLogin() const{return m_login;}
    /**
     * @return Le nom de famille de la personne.
     */
    QString getName() const{return m_name;}
    /**
     * @return Le prénom de la personne.
     */
    QString getSurname() const {return m_surname;}
    /**
     * @return La liste de pointeurs sur les semestres effectués.
     */
    QList<Semester*> getListSemesters(){return l_semesters;}
    /**
     * @brief Permet d'ajouter un semestre à la liste des semestres déjà passés ou en cours.
     * @param nameCursus Code du cursus (ex : TC01).
     * @param nameSemester Code du semestre (ex : P2014).
     */
    void addSemester(QString nameCursus, QString nameSemester) {
        Semester* newSemester = new Semester(nameCursus, nameSemester);
        l_semesters.append(newSemester);
    }
    /**
     * @brief Ajout d'un résultat à la liste des résultats.
     * @param nameCursus Code du cursus.
     * @param nameUV Code de l'UV.
     * @param result Résultat obtenu.
     */
    void addResultSemester(QString nameCursus, QString nameUV, QString result){
        QList<Semester*>::iterator it = l_semesters.begin();
        while((*it)->getNameCursus()!=nameCursus && it != l_semesters.end()){
            if ((*it)->getNameCursus()==nameCursus){
                (*it)->addUVFollowedThisSemester(nameUV, result);
            }
        }
    }


    //unsigned int nbCreditValidated() const;
private:
    /**
     * @brief Nom de famille.
     */
    QString m_name;
    /**
     * @brief Prénom.
     */
    QString m_surname;
    /**
     * @brief Login UTC.
     */
    QString m_login;
    /**
     * @brief Age.
     */
    unsigned int m_age;
    /**
     * @brief Nombre de semestres déjà effectués.
     */
    unsigned int m_nbSemesters;
    /**
     * @brief Code du premier semestre suivi.
     */
    QString m_firstSemester;
    /**
     * @brief Année du premier semestre suivi.
     */
    unsigned int m_firstYear;
    /**
     * @brief Liste de pointeurs sur les semestres déjà effectués ou en cours.
     */
    QList<Semester*> l_semesters;

    //QVector<QVector<QString> > v_UVFollowedBySemesters;
};

#endif // RECORD_H
