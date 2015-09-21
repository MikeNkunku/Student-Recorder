/**
  * \file UV.h
  * \brief Déclaration de la classe UV, de ses attributs et méthodes ainsi que de la classe permettant la gestion des exceptions.
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#ifndef UV_H
#define UV_H

#include <QString>
#include <QMap>

/**
 * @brief The UTProfilerException class
 *      La classe UTProfilerException permet de gérer les différentes exceptions pouvant survenir en affichant un message,
 * en indiquant une ligne donnée, et cela pour un fichier spécifique.
 */
class UTProfilerException{
public:
    UTProfilerException(const QString& message, const QString &f="na", unsigned int l=0):
        info(message),file(f),line(l){}
    QString getInfo() const { return info; }
#ifndef NDEBUG
    // retourne le fichier dans lequel cettte exception a été levée.
    QString getFile() const { return file; }
    // retourne la ligne du fichier à laquelle cette exception a été levée.
    unsigned int getLine() const { return line; }
#endif
private:
    QString info;
    QString file;
    unsigned int line;

};

/**
 * @brief The UV class
 *
 */
class UV {
    /**
     * @brief Code de l'UV.
     */
    QString code;
    /**
     * @brief Titre, intitulé de l'UV.
     */
    QString titre;
    /**
     * @brief L'attribut categorie est de type QMap et permet d'attribuer à chaque type d'UV le nombre de crédits correspondant.
     */
    QMap<QString,int> categorie;
    /**
     * @brief Booléen correspondant à la disponibilité de l'UV aux semestres d'automne.
     */
    bool automne;
    /**
     * @brief Booléen correspondant à la disponibilité de l'UV aux semestres de printemps.
     */
    bool printemps;
    UV(const UV& u);
    UV& operator=(const UV& u);
    /**
     * @brief UV
     *
     * Constructeur de l'UV.
     * @param c Code de l'UV.
     * @param t Titre de l'UV.
     * @param cat QMap permettant d'accéder aux nombres de crédits correspondants pour chaque type pour cette UV.
     * @param a Booléen correspondant à la disponibilité de l'UV aux semestres d'automne.
     * @param p Booléen correspondant à la disponibilité de l'UV aux semestres de printemps.
     */
    UV(const QString& c, const QString& t, QMap<QString,int> cat,bool a, bool p):
      code(c),titre(t),categorie(cat),automne(a),printemps(p){}
    friend class UVManager;
public:
    /**
     * @brief getCode
     * @return Le code de l'UV.
     */
    QString getCode() const { return code; }
    /**
     * @brief getTitre
     * @return Le titre de l'UV.
     */
    QString getTitre() const { return titre; }
    /**
     * @brief getNbCreditsCS
     * @return Le nombre de crédits CS obtenus par validation de l'enseignement.
     */
    unsigned int getNbCreditsCS() const { return categorie.value("CS"); }
    /**
     * @brief getNbCreditsTM
     * @return Le nombre de crédits TM obtenus par validation de l'enseignement.
     */
    unsigned int getNbCreditsTM() const { return categorie.value("TM"); }
    /**
     * @brief getNbCreditsTSH
     * @return Le nombre de crédits TSH obtenus par validation de l'enseignement.
     */
    unsigned int getNbCreditsTSH() const { return categorie.value("TSH"); }
    /**
     * @brief getNbCreditsSP
     * @return Le nombre de crédits SP obtenus par validation de l'enseignement.
     */
    unsigned int getNbCreditsSP() const { return categorie.value("SP"); }

    /**
     * @brief getCat
     * @return QMap de l'UV.
     */
    QMap<QString,int> getCat()const{return categorie;}
    QStringList getCategorie() const;
    /**
     * @brief ouvertureAutomne
     * @return Vrai si l'UV est disponible aux semestres d'automne, faux sinon.
     */
    bool ouvertureAutomne() const { return automne; }
    /**
     * @brief ouverturePrintemps
     * @return Vrai si l'UV est disponible aux semestres de printemps, faux sinon.
     */
    bool ouverturePrintemps() const { return printemps; }

    /**
     * @brief setCode
     *      Permet la modification du code d'une UV.
     * @param c Nouveau code de l'UV.
     */
    void setCode(const QString& c) { code=c; }
    /**
     * @brief setTitre
     *      Permet la modification du titre d'une UV.
     * @param t Nouveau titre de l'UV.
     */
    void setTitre(const QString& t) { titre=t; }
    /**
     * @brief setOuvertureAutomne
     *      Permet la modification de l'ouverture d'une UV aux semestres d'automne.
     * @param b Nouvelle valeur booléenne.
     */
    void setOuvertureAutomne(bool b) { automne=b; }
    /**
     * @brief setOuverturePrintemps
     *      Permet la modification de l'ouverture d'une UV aux semestres de printemps.
     * @param b Nouvelle valeur booléenne.
     */
    void setOuverturePrintemps(bool b) { printemps=b; }
    /**
     * @brief setCreditsCS
     *      Permet de modifier le nombre de crédits CS gagnés par validation d'une UV.
     * @param c Nouveau nombre de crédits CS.
     */
    void setCreditsCS(unsigned int c){categorie.insert("CS",c);}
    /**
     * @brief setCreditsTM
     *      Permet de modifier le nombre de crédits TM gagnés par validation d'une UV.
     * @param c Nouveau nombre de crédits TM.
     */
    void setCreditsTM(unsigned int c){categorie.insert("TM",c);}
    /**
     * @brief setCreditsTSH
     *      Permet de modifier le nombre de crédits TSH gagnés par validation d'une UV.
     * @param c Nouveau nombre de crédits TSH.
     */
    void setCreditsTSH(unsigned int c){categorie.insert("TSH",c);}
    /**
     * @brief setCreditsSP
     *      Permet de modifier le nombre de crédits SP gagnés par validation d'une UV.
     * @param c Nouveau nombre de crédits SP.
     */
    void setCreditsSP(unsigned int c){categorie.insert("SP",c);}
};

#endif // UV_H
