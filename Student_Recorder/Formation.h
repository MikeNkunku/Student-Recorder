#ifndef FORMATION_H
#define FORMATION_H

/**
  * \file Formation.h
  * \brief Classes gérant les formations de l'UTC
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "UV.h"
#include <QList>

/**
 * @brief Formation
 *
 * La classe Formation est une classe abstraite qui définie les attributs communs aux deux classes filles, ainsi que 4
 * méthodes abstraites pures. On a décidé d'appliquer le design pattern composite car les branches sont composés de filières, mais peuvent aussi
 * etre composé de branche. Ce design pattern nous paraissait adapté à la situation
 *
 * Pour les attributs communs nous utilisons des QList afin de stocker les UV présentes dans la Formation, mais aussi les UV "conseille" pour la formation (par exemple pour
 * le GI il est conseille de faire nf16, lo21... )
 * On stocke aussi la formation parente si il y en a une (ou plusieurs), et les Filieres dans des QList
 *   virtual void supprimerUV(const QString& c)=0;
 *   virtual void ajouterUV(UV *u)=0;
 *
 *      En effet, si on ajoute une uv dans une filiere, il faut aussi l'ajouter dans la branche à laquelle elle apartient, mais la réciproque n'est pas vrai.
 *
 *   virtual void ajouterFiliere(Formation* f)=0;
 *      Si on ajoute une filière à une filière, il faut la transformer en branche.
 *
 *   virtual void supprimerFiliere(const QString& c)=0;
 *          Une filiere n'est pas censé avoir de filiere donc la méthode est différente pour les deux classes.
 *
 */

class Formation{
protected:
    /**
     * @brief Code de la formation.
     */
    QString code;
    /**
     * @brief Titre de la formation.
     */
    QString titre;
    /**
     * @brief Liste de pointeurs sur les UV de la formation.
     */
    QList<UV *> uvs;
    /**
     * @brief Liste de pointeurs sur les UV conseillées pour la formation.
     */
    QList<UV *> UVConseille;
    /**
     * @brief Liste regroupant des pointeurs sur les Formations ascendantes pour une Filiere donnée.
     */
    QList<Formation*> Parents;
    /**
     * @brief Liste regroupant des pointeurs sur les filières pour une Branche donnée.
     */
    QList<Formation*> Filiere;
    /**
     * @brief Nombre de crédits CS à valider.
     */
    unsigned int credCS;
    /**
     * @brief Nombre de crédits TM à valider.
     */
    unsigned int credTM;
    /**
     * @brief Nombre de crédits TSH à valider.
     */
    unsigned int credTSH;
    /**
     * @brief Nombre de crédits SP à valider.
     */
    unsigned int credSP;
    /**
     * @brief Booléen.
     */
    bool composite;
    Formation(const QString& c,const QString& t,unsigned int CS,unsigned int TM,unsigned int TSH,unsigned int SP,bool B):code(c),titre(t),credCS(CS),credTM(TM),credTSH(TSH),credSP(SP),composite(B)
    {uvs=QList<UV*>();UVConseille=QList<UV*>();}
    Formation& operator=(Formation& F);
    Formation(const Formation& F);
    ~Formation();
    friend class FormationManager;
public:
    /**
     * @return Le code de la formation.
     */
    QString getCode()const { return code; }
    /**
     * @return Le titre de la formation.
     */
    QString getTitre()const { return titre; }
    /**
     * @return Le nombre de crédits CS à valider.
     */
    int getCS()const {return credCS;}
    /**
     * @return Le nombre de crédits TM à valider.
     */
    int getTM() const {return credTM;}
    /**
     * @return Le nombre de crédits TSH à valider.
     */
    int getTSH() const {return credTSH;}
    /**
     * @return Le nombre de crédits SP à valider.
     */
    int getSP() const {return credSP;}
    /**
     * @brief Permet de modifier le code correspondant à une formation.
     * @param c Nouveau code de la formation.
     */
    void setCode(const QString& c){code=c;}
    /**
     * @brief Permet de modifier le titre de la formation.
     * @param t Nouveau titre.
     */
    void setTitre(const QString& t){titre=t;}
    /**
     * @brief Permet de modifier le nombre de crédits CS à valider.
     * @param cr Nouveau nombre de crédits.
     */
    void setcredCS(unsigned int cr){credCS=cr;}
    /**
     * @brief Permet de modifier le nombre de crédits TM à valider
     * @param cr Nouveau nombre de crédits.
     */
    void setcredTM(unsigned int cr){credTM=cr;}
    /**
     * @brief Permet de modifier le nombre de crédits TSH à valider.
     * @param cr Nouveau nombre de crédits.
     */
    void setcredTSH(unsigned int cr){credTSH=cr;}
    void setcredSP(unsigned int cr){credSP=cr;}
    void setUV (QList<UV*> uv){uvs=uv;}
    void setUVCons(QList<UV*> uv){UVConseille=uv;}

    /**
     * @return Vrai si la Formation est composite, faux sinon.
     */
    bool estComposite(){return composite;}
    QList<UV*> getUVList(){return uvs;}
    QList<UV*> getUVConsList(){return UVConseille;}
    UV* trouverUV(const QString& c)const;
    UV* getUV(const QString& c);
    UV* trouverUVCons(const QString& c)const;
    UV* getUVCons(const QString& c);

    QList<Formation*> getParentList(){return Parents;}
    Formation* trouverFiliere(const QString& c)const;

    Formation* getParent(const QString& c){
        for(int i=0; i<Parents.length();i++)
            if (c==Parents[i]->getCode()) return Parents[i];
        throw UTProfilerException("Formation introuvable");
    }

    void ajouterUVCons(UV *u);
    void supprimerUVCons(const QString& c);


    virtual void supprimerUV(const QString& c)=0;
    virtual void ajouterUV(UV *u)=0;
    virtual void ajouterFiliere(Formation* f)=0;
    virtual void supprimerFiliere(const QString& c)=0;

    void ajouterParent(Formation* f){if (!f->estComposite()) throw("On ne peut pas ajouter une filiere en parent"); if(!Parents.contains(f))Parents.append(f);}
    void supprimerParent(const QString& c){Formation* f =getParent(c); f->supprimerFiliere(getCode()); Parents.removeOne(f);}

    QList<Formation*> getFiliereList(){return Filiere;}
    Formation* getFiliere(const QString& c){
        for(int i=0; i<Filiere.length();i++)
            if (c==Filiere[i]->getCode()) return Filiere[i];
        throw UTProfilerException("Filiere introuvable");
                           }
};


class Branche:public Formation {
    friend class FormationManager;
public:
    Branche(const QString& c,const QString& t,unsigned int CS,unsigned int TM,unsigned int TSH,unsigned int SP,bool B):Formation(c,t,CS,TM,TSH,SP,B){Filiere=QList<Formation*>();}
    void ajouterFiliere(Formation* f);
    void supprimerFiliere(const QString& c){Filiere.removeOne(getFiliere(c));}

    void ajouterUV(UV* u);
    void supprimerUV(const QString& c);

    int getNbFiliere(){return Filiere.length();}
};

class Filiere:public Formation{

public:
    Filiere(const QString& c,const QString& t,unsigned int CS,unsigned int TM,unsigned int TSH,unsigned int SP,bool B):Formation(c,t,CS,TM,TSH,SP,B){Parents=QList<Formation*>();}
    QList<Formation*> getFiliere(){return QList<Formation*>();}

    void ajouterUV(UV* u);
    void supprimerUV(const QString& c);
    void ajouterParent(Formation* f){Parents.append(f);}
    void supprimerParent(const QString& c);

    void ajouterFiliere(Formation* f);
    void supprimerFiliere(const QString& c){throw UTProfilerException("Filiere : pas de suppression de filiere possible");}
};

#endif // FORMATION_H
