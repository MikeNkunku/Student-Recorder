#ifndef UVRESULT_H
#define UVRESULT_H
#include <QString>

/**
  * \file UVResult.h
  * \brief Définition de la classe implémentant les résultats d'UV
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

/**
 * @brief Cette classe implémente les résultats obtenus dans les UV.
 */
class UVResult
{
public:
    /**
     * @brief Constructeur de la classe UVResult.
     * @param nameUV Code de l'UV.
     * @param result Résultat obtenu.
     */
    UVResult(QString nameUV, QString result);
    /**
     * @return Le code de l'UV.
     */
    QString getNameUV(){return m_nameUV;}
    /**
     * @return Le résultat obtenu.
     */
    QString getResultUV(){return m_result;}
private:
    /**
     * @brief Code de l'UV.
     */
    QString m_nameUV;
    /**
     * @brief Résultat obtenu à l'UV.
     */
    QString m_result;
};

#endif // UVRESULT_H
