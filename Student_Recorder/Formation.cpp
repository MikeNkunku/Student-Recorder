/**
  * \file Formation.cpp
  * \brief Fichier définissant les méthodes non-inline de la classe Formation.
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include "Formation.h"
#include <QDebug>



/**
 * @brief Permet de trouver l'UV souhaitée parmi celles de la formation.
 * @param c Code de l'UV recherchée.
 * @return Pointeur sur l'UV si existante dans la formation, 0 sinon.
 */
UV* Formation::trouverUV(const QString& c)const{
    for(QList<UV*>::const_iterator it=uvs.begin();it!=uvs.end();++it){
        if (c==(*it)->getCode()) return (*it);
    }

    return 0;
}

/**
 * @brief Permet de trouver l'UV souhaitée parmi celles de la formation.
 * @param c Code de l'UV recherchée.
 * @return Un pointeur sur l'UV si existante, sinon affiche un message d'erreur.
 */
UV* Formation::getUV(const QString& c){
    UV* uv=trouverUV(c);
    if (!uv) throw UTProfilerException("erreur, ForamtionManager, UV inexistante dans les uvs de la formation");
    return uv;
}

/**
 * @param c Code de l'UV recherchée.
 * @return Un pointeur sur l'UV si elle est effectivement conseillée, le pointeur NULL sinon.
 */
UV* Formation::trouverUVCons(const QString& c)const{
    for(QList<UV*>::const_iterator it=UVConseille.begin();it!=UVConseille.end();++it){
        if (c==(*it)->getCode()) return (*it);
    }

    return 0;
}

/**
 * @param c Code de l'UV recherchée.
 * @return Un pointeur sur l'UV si conseillée, sinon un message d'erreur est affiché.
 */
UV* Formation::getUVCons(const QString& c){
    UV* uv=trouverUVCons(c);
    if (!uv) throw UTProfilerException("erreur, FormationManager, UV inexistante dans les uvs conseilles de la formation");
    return uv;
}

/**
 * @brief Destructeur de la classe Formation.
 * Suppression du tableau d'UV et du tableau d'UV conseillées.
 */
Formation::~Formation(){
    for(QList<UV*>::iterator it=uvs.begin();it!=uvs.end();++it)
        delete *it;
    for(QList<UV*>::iterator it=UVConseille.begin();it!=UVConseille.end();++it)
        delete *it;
}

/**
 * @brief Cette fonction permet de vérifier l'existence d'une formation dans la base de données.
 *
 * @param c Abbréviation de la filière recherchée.
 * @return Un pointeur vers la filière correspondante si existante, 0 sinon.
 */
Formation* Formation::trouverFiliere(const QString& c) const{
    for(unsigned int i=0; i<Filiere.length();i++)
        if (c==Filiere[i]->getCode()) return Filiere[i];
    throw UTProfilerException("Formation non trouvable");
    return 0;
}

/**
 * @brief Cette méthode permet la suppression d'une UV, d'abord dans dans toutes les formations dans lesquelles elle est présente,
 *  puis dans le tableau d'UV de l'instance unique de la classe UVManager.
 *
 * @param c Code de l'UV recherchée.
 */
void Branche::supprimerUV(const QString& c){
    if(uvs.contains(getUV(c))){

        for(QList<Formation*>::iterator it=Filiere.begin();it!=Filiere.end();++it)
            (*it)->supprimerUV(c);

        uvs.removeOne(getUV(c));
    }
}

/**
 * @brief Ajout d'une UV à une formation si non présente. Si elle l'est déjà, une exception est déclenchée.
 *
 * @param u Pointeur vers l'UV correspondante.
 */
void Branche::ajouterUV(UV* u){
    ///
    /// On passe un pointeur en paramètre afin de ne pas avoir utiliser l'UVManager dans la méthode, limitant ainsi les dépendances entre classes
    ///
    if(!uvs.contains(u))
        uvs.append(u);
    else throw UTProfilerException("L'uv est déjà présente dans la formation");


}
/**
 * @brief Suppression d'une UV de la liste des UV de Filiere.
 * @param c Code de l'UV à supprimer.
 */
void Filiere::supprimerUV(const QString& c){
    UV* u=getUV(c);

    if(uvs.contains(u))
        uvs.removeOne(u);
    else throw UTProfilerException("L'uv n'est pas présente dans la formation");
}

/**
 * @brief Permet d'ajouter une UV à une Filiere.
 * @param u Pointeur sur l'UV à ajouter.
 */
void Filiere::ajouterUV(UV* u){
    if(!uvs.contains(u)){
        uvs.append(u);
        for(QList<Formation*>::iterator it=Parents.begin();it!=Parents.end();++it)
            if (!(*it)->getUVList().contains(u))
                    (*it)->ajouterUV(u);
    }
    else throw UTProfilerException("L'uv est déjà présente dans la formation");
}

/**
 * @brief Ajout d'une UV à la liste des UV conseillées pour la dite Formation.
 * @param u Un pointeur d'UV.
 */
void Formation::ajouterUVCons(UV* u){
    if((!UVConseille.contains(u)) && (uvs.contains(u)))
        UVConseille.append(u);
    else throw UTProfilerException("L'uv est deja présente dans les uvs conseille de la formation, ou n'est pas présente dans la liste d'uv de la formation");
}

/**
 * @brief Suppression de l'UV dont le code est transmis en argument de la liste des UV conseillées.
 * @param c Code de l'UV conseillée à supprimer.
 */
void Formation::supprimerUVCons(const QString& c){
    UV* u=getUVCons(c);
    if(UVConseille.contains(u))
        UVConseille.removeOne(u);
    else throw UTProfilerException("L'UV n'est pas présente dans la liste des UV conseillées");
}

void Branche::ajouterFiliere(Formation* f){
    Filiere.append(f);
}

/**
 * @brief Permet d'ajouter une filière à une Formation.
 * @param f Un pointeur sur une formation.
 */
void Filiere::ajouterFiliere(Formation* f){
    Branche* b=new Branche(this->getCode(),this->getTitre(),this->getCS(),this->getTM(),this->getTSH(),this->getSP(),1);

    QList<Formation*> pa = getParentList();
    QList<Formation*> fi = getFiliereList();

    for(QList<Formation*>::iterator it=pa.begin();it!=pa.end();++it){
        (*it)->supprimerFiliere(f->getCode());
        (*it)->ajouterFiliere(f);
        b->ajouterParent(*it);
    }

    for(QList<Formation*>::iterator it=fi.begin();it!=fi.end();++it){
        (*it)->supprimerParent(f->getCode());
        (*it)->ajouterParent(f);
        b->ajouterFiliere(*it);
    }

    b->ajouterFiliere(f);
}

