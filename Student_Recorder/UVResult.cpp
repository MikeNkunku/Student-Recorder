/**
  * \file UVResult.cpp
  * \brief Fichier source associé à UVResult.h
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "UVResult.h"

/**
 * @brief Constructeur de la classe UVResult.
 * @param nameUV Code de l'UV.
 * @param result Résultat obtenu à l'UV.
 */
UVResult::UVResult(QString nameUV, QString result):m_nameUV(nameUV), m_result(result){}
