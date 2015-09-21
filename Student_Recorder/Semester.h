#ifndef SEMESTER_H
#define SEMESTER_H

/**
  * \file Semester.h
  * \brief Définition d'un semestre, de ses caractéristiques et de ses méthodes
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include <QList>
#include <QString>
#include <QStringList>
#include "UVResult.h"


/**
 * @brief Cette classe permet d'implémenter les
 */
class Semester
{
public:
    /**
     * @brief Constructeur de la classe Semester.
     * @param nameCursus Nom de code du cursus.
     * @param nameSemester Nom de code du semestre.
     */
    Semester(QString nameCursus, QString nameSemester):m_codeCursus(nameCursus), m_codeSemester(nameSemester){}
    /**
     * @brief Permet d'ajouter le résultat d'une UV à la liste de note déjà existante.
     * @param codeUV Code de l'UV.
     * @param resultUV Résultat obtenu à l'UV.
     */
    void addUVFollowedThisSemester(QString codeUV, QString resultUV){
        UVResult* newUVResult = new UVResult(codeUV, resultUV);
        m_listUVAndResult.append(newUVResult);
    }
    /**
     * @return La liste de pointeurs sur des données UVResult.
     */
    QList< UVResult* > getListUVAndResult(){return m_listUVAndResult;}
    /**
     * @return Nom de code du cursus (ex : TC01).
     */
    QString getNameCursus(){return m_codeCursus;} //TC01
    /**
     * @return Nom de code du semestre (ex : P2011).
     */
    QString getNameSemester(){return m_codeSemester;} //P2011

private:
    /**
     * @brief Concaténation du code du cursus avec le numéro du semestre.
     */
    QString m_codeCursus; //TC01
    /**
     * @brief Concaténation de l'initiale du type de semestre avec l'année.
     */
    QString m_codeSemester; //P2011
    /**
     * @brief Liste de pointeurs sur des données UVResult.
     */
    QList<UVResult*> m_listUVAndResult;
};

#endif // SEMESTER_H
