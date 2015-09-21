#ifndef UT_PROFILER_h
#define UT_PROFILER_h

/**
  * \file UTProfiler.h
  * \brief Définition du gestionnaire d'UV, de ses attributs et de ses méthodes
  * \author Hugo ROBINE-LANGLOIS
  * \author Olympio BARTHELEMY
  * \author Mickaël NKUNKU
  * \version 1.0
  * \date 10 juin 2014
  */

#include <QTextStream>
#include <QStringList>
#include "DBManager.h"
#include "UV.h"



using namespace std;

/**
 * @brief Enumération des catégories
 */
enum Categorie {
    /* Connaissances Scientifiques */ CS,  /* Techniques et Méthodes */ TM,
    /* Technologies et Sciences de l'Homme */ TSH, /* Stage et Projet */ SP
};

QTextStream& operator<<(QTextStream& f, const Categorie& s);
Categorie StringToCategorie(const QString& s);
QString CategorieToString(Categorie c);
QTextStream& operator>>(QTextStream& f, Categorie& cat);

/**
 * @brief Les différentes notes possibles.
 */
enum Note { A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC  };
/**
 * @brief Les différents types de semestres existants.
 */
enum Saison { Automne, Printemps };
inline QTextStream& operator<<(QTextStream& f, const Saison& s) { if (s==Automne) f<<"A"; else f<<"P"; return f;}

class Semestre {
    /**
     * @brief Un semestre.
     */
    Saison saison;
    /**
     * @brief Une année.
     */
    unsigned int annee;
public:
    /**
     * @brief Constructeur de la classe Semestre.
     * @param s Le type de semestre.
     * @param a L'année.
     */
    Semestre(Saison s, unsigned int a):saison(s),annee(a){ if (annee<1972||annee>2099) throw UTProfilerException("annee non valide"); }
    /**
     * @return Le type de semestre.
     */
    Saison getSaison() const { return saison; }
    /**
     * @return L'année.
     */
    unsigned int getAnnee() const { return annee; }
};

inline QTextStream& operator<<(QTextStream& f, const Semestre& s) { return f<<s.getSaison()<<s.getAnnee()%100; }

/**
 * @brief Permet de gérer les UV.
 */
class UVManager {
private:
    /**
     * @brief Tableau de pointeurs sur les UV.
     */
    UV** uvs;
    /**
     * @brief Nombre réel d'UV dans le tableau uvs .
     */
    unsigned int nbUV;
    /**
     * @brief Nombre maximal d'UV stockable dans le tableau uvs .
     */
    unsigned int nbMaxUV;
    void addItem(UV* uv);
    /**
     * @brief Permet de déterminer s'il y a eu un changement.
     */
    bool modification;
    UV* trouverUV(const QString& c) const;
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);
    UVManager();
    ~UVManager();
    friend struct Handler;
    /**
     * @brief Permet la gestion de l'instance unique de la classe UVManager.
     */
    struct Handler{
        /**
         * @brief Instance unique de UVManager.
         */
        UVManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:

    void load();
    void save();
    void updateTableUV(bool a, bool p, QString c, QString t, unsigned int cs, unsigned int tm, unsigned int tsh, unsigned int sp);
    static UVManager& getInstance();
    static void libererInstance();
    void ajouterUV(const QString& c, const QString& t, QMap<QString,int> cat, bool a, bool p);
    const UV& getUV(const QString& code) const;
    UV& getUV(const QString& code);
    /**
     * @brief S'il y a eu au moins une modification, l'attribut passe à vrai.
     */
    void setModification(){ if (!modification) modification=true;}
    /**
     * @return Vrai s'il y a eu au moins une modification, faux sinon.
     */
    bool getModification(){return modification;}

    void insertUV(QString code, QString titre, QMap<QString,int> cat, bool a, bool p);
    /**
     * @return Le nombre d'UV dans le tableau uvs .
     */
    unsigned int getNbUV(){return nbUV;}

    /**
     * @brief Classe qui permet de boucler sur les UV du tableau uvs.
     */
    class Iterator {
        friend class UVManager;
        /**
         * @brief Tableau de pointeurs sur les UV.
         */
        UV** currentUV;
        /**
         * @brief Nombre d'UV restantes sur lesquelles boucler.
         */
        unsigned int nbRemain;
        /**
         * @brief Constructeur défini de manière privée de la classe Iterator.
         * @param u Tableau de pointeurs de pointeurs d'UV.
         * @param nb Nombre d'UV dans le tableau u.
         */
        Iterator(UV** u, unsigned int nb):currentUV(u),nbRemain(nb){}
    public:
        /**
         * @brief Constructeur défini publiquement de la classe Iterator, en initialisant le tableau currentUV à NULL, et le nombre d'UV du
         * tableau à 0.
         */
        Iterator():nbRemain(0),currentUV(0){}
        /**
         * @return Vrai s'il n'y a plus d'UV sur lesquelles boucler, faux sinon.
         */
        bool isDone() const { return nbRemain==0; }
        /**
         * @brief Affiche une erreur s'il n'est plus possible d'itérer, sinon décrémente de 1 le nombre d'UV restantes et passe à l'UV suivante.
         */
        void next() {
            if (isDone())
                throw UTProfilerException("error, next on an iterator which is done");
            nbRemain--;
            currentUV++;
        }
        /**
         * @return Une référence sur l'UV pointée s'il en reste encore. Sinon, un message d'erreur est affiché.
         */
        UV& current() const {
            if (isDone())
                throw UTProfilerException("error, indirection on an iterator which is done");
            return **currentUV;
        }
    };
    Iterator getIterator() {
        return Iterator(uvs,nbUV);
    }

    class iterator {
        UV** current;
        unsigned int nbRemain;
        iterator(UV** u, unsigned int nb):current(u),nbRemain(nb){}
        friend class UVManager;
    public:
        iterator():current(0){};
        UV& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current;--nbRemain; return *this; }
    };
    /**
     * @return Un itérateur pointant sur la toute première UV dans le tableau.
     */
    iterator begin() { return iterator(uvs,nbUV); }
    /**
     * @return Un itérateur pointant sur la dernière UV dans le tableau.
     */
    iterator end() { return iterator(uvs+nbUV,0); }
    /**
     * @brief Cette classe permet d'itérer sur les UV en ajoutant des critères de filtre.
     */
    class FilterIterator {
        friend class UVManager;
        /**
         * @brief Tableau de pointeurs
         */
        UV** currentUV;
        /**
         * @brief Nombre d'UV restantes sur lesquelles itérer.
         */
        unsigned int nbRemain;
        /**
         * @brief Une catégorie d'UV donnée.
         */
        QString categorie;
        /*FilterIterator(UV** u, unsigned nb, QString c=""):currentUV(u),nbRemain(nb),categorie(c){
            while(nbRemain>0 && (!(*currentUV)->getCategorie().contains(categorie))){
                nbRemain--; currentUV++;
            }
        }*/
        /**
         * @brief Constructeur privé de la classe FilterIterator.
         * @param u Tableau de pointeurs d'UV.
         * @param nb Nombre d'UV contenues dans le tableau.
         * @param c Catégorie donnée d'UV.
         */
        FilterIterator(UV** u, unsigned nb, QString c=""):currentUV(u),nbRemain(nb),categorie(c){
            while(nbRemain>0 && (!(*currentUV)->getCat().value(categorie))){
                nbRemain--; currentUV++;
            }
        }
    public:
        /**
         * @brief Constructeur public de la classe FilterIterator initialisant le tableau à NULL, et le nombre d'UV restantes à 0.
         */
        FilterIterator():nbRemain(0),currentUV(0){}
        /**
         * @return Vrai s'il n'y a plus d'UV à traiter, faux sinon.
         */
        bool isDone() const { return nbRemain==0; }
        /**
         * @return Un itérateur pointant sur la prochaine UV de type catégorie.
         */
        FilterIterator& operator++(){
            ++currentUV; nbRemain--;
            //qDebug()<<"nbRemain avant while : "<<nbRemain;
            while(nbRemain>0 && (!(*currentUV)->getCat().value(categorie))){
                nbRemain--; currentUV++;
                //qDebug()<<"nbRemain dans while : "<<nbRemain;
            }
            //qDebug()<<"Retour de ++it";
            return *this;
        }
        /**
         * @param fi Un autre FilterIterator.
         * @return Vrai si l'UV courante pointée est différente, faux sinon.
         */
        bool operator!=(FilterIterator fi) const{return currentUV!=fi.currentUV;}
        /**
         * @return Une référence sur l'UV pointée.
         */
        UV& operator*() const {return **currentUV;}
        /**
         * @brief Passe à la prochaine UV si possible, sinon un message d'erreur apparaît.
         */
        void next() {
            if (isDone())
                throw UTProfilerException("error, next on an iterator which is done");
            do {
                nbRemain--;currentUV++;
            }while(nbRemain>0 && (!(*currentUV)->getCategorie().contains(categorie)));
        }

        UV& current() const {
            if (isDone())
                throw UTProfilerException("error, indirection on an iterator which is done");
            return **currentUV;
        }
    };
    FilterIterator getFilterIterator(QString c) {
        return FilterIterator(uvs,nbUV,c);
    }
    /**
     * @param c Catégorie d'UV (CS, TM, TSH, SP,...)
     * @return Un pointeur sur un pointeur de la première UV de type c dans le tableau uvs .
     */
    FilterIterator FIbegin(QString c) { return FilterIterator(uvs,nbUV,c); }
    /**
     * @param c Catégorie d'UV (CS, TM, TSH, SP, ...)
     * @return Un pointeur sur un pointeur de la dernière UV de type c dans le tableau uvs .
     */
    FilterIterator FIend(QString c) { return FilterIterator(uvs+nbUV,0,c);}
};



#endif

