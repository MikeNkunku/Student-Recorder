#ifndef WINDOWNEWSEMESTER_H
#define WINDOWNEWSEMESTER_H

/**
  * \file WindowNewSemester.h
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
#include <QMap>
#include "recordmanager.h"
#include "record.h"
#include "FormationManager.h"
#include "UTProfiler.h"

/**
 * @brief Cette classe permet à l'utilisateur de s'inscrire pour un nouveau semestre à des UV.
 */
class WindowNewSemester : public QWidget
{
    Q_OBJECT
public:
    WindowNewSemester(QString login);


private:
    /**Éléments*/
    QPushButton* buttonCreateNewSemester;
    QPushButton* buttonCancel;
    WindowNewSemester* windowNewSemester;
    QComboBox* m_cursusSemester;
    QSpinBox* m_nbCurrentSemester;
    QComboBox* m_currentSemester;
    QVector <QLineEdit*> m_titleUV;
    QVector <QComboBox*> m_gradeUV;
    QVector <QHBoxLayout*> m_HBoxes;
    QString m_login;

    QMap <QString, QString> m_mapUVGrade;
    //QMap <QString, QString>::iterator m_iteratorGradeUV;
    /*QLineEdit* m_titleUV1;
    QLineEdit* m_titleUV2;
    QLineEdit* m_titleUV3;
    QLineEdit* m_titleUV4;
    QLineEdit* m_titleUV5;
    QLineEdit* m_titleUV6;
    QLineEdit* m_titleUV7;
    QComboBox* m_gradeUV1;
    QComboBox* m_gradeUV2;
    QComboBox* m_gradeUV3;
    QComboBox* m_gradeUV4;
    QComboBox* m_gradeUV5;
    QComboBox* m_gradeUV6;
    QComboBox* m_gradeUV7;*/

    /**Layout*/
    QFormLayout* formLayout;
    QWidget* widgetFormLayout;
    QVBoxLayout* mainLayout;
    QHBoxLayout* layerHButtons;

    //QList<Cursus> listCursus;

signals:
public slots:
    void createNewSemester();
private slots:
};
#endif // WINDOWNEWSEMESTER_H
