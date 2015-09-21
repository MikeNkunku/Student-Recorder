#ifndef WINDOWNEWSTUDENT_H
#define WINDOWNEWSTUDENT_H

/**
  * \file WindowNewStudent.h
  * \brief Fenêtre affichant les différentes UV dans la base de données actuelle
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include <QtWidgets>
#include <QWidget>
#include <QDate>
#include <QList>
#include "FormationManager.h"
#include "recordmanager.h"
#include "record.h"

/**
 * @brief Cette classe objet sert d'interface pour entrer un nouvel étudiant dans la base de données, et gérer ses inscriptions.
 */
class WindowNewStudent : public QWidget
{
    Q_OBJECT
public:
    WindowNewStudent();


private:
    /**Éléments*/
    QPushButton* buttonCreateNewStudent;
    QPushButton* buttonCancel;
    WindowNewStudent* windowNewStudent;
    QLineEdit* m_login;
    QLineEdit* m_name;
    QLineEdit* m_surname;
    QComboBox* m_cursusCurrentSemester;
    QSpinBox* m_nbCurrentSemester;
    QSpinBox* m_nbInitialCredits;


    /**Layout*/
    QFormLayout* formLayout;
    QWidget* widgetFormLayout;
    QVBoxLayout* mainLayout;
    QHBoxLayout* layerHButtons;

    QList<Formation*>* listCursus;

signals:
public slots:
    void createNewStudent();
private slots:
};

#endif // WINDOWNEWSTUDENT_H
