/**
  * \file Record.cpp
  * \brief Définition des méthodes de la classe Record non-inline
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "Record.h"

/**
 * @brief Constructeur de la classe Record.
 * @param login Login de l'étudiant.
 * @param name Nom de famille de l'étudiant.
 * @param surname Prénom de l'étudiant.
 * @param nbSemesters Nombre de semestres effectués par l'étudiant.
 */
Record::Record(QString login, QString name, QString surname, unsigned int nbSemesters):
    m_login(login),
    m_name(name),
    m_surname(surname),
    m_nbSemesters(nbSemesters)
{}
