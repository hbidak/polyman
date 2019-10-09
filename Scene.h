#ifndef _CSCENE_H_
#define _CSCENE_H_


#include <list>
#include "ObjetGL.h"
#include "Vecteur.h"
#include "OVI.h"
#include "Propulsion.h"
#include "Jonction.h"
#include "GlutMaster.h"
#include "GlutWindow.h"
#include "AdvGlutWnd.h"
#include "Station.h"
//#include "TransformationGL.h"
#include <fstream>
using namespace std;


//

/**
 * La classe principale: elle contient et gère tous les éléments de la scène
 *
 */
class CScene
{
public:
   CScene();
   ~CScene();
   CScene( const CScene& b ) { *this = b; }
   const CScene& operator=( const CScene& b );

   // Methodes pour la gestion des objets
   void initialiser();
   void ajouterObjet( CObjetGL* obj ); 
   void eliminerDernierObjet( void );
   void eliminerTousObjets( void );
   void vitesse_initiale_station(double x,double y, double z);
   bool Selection_de_station(CPoint3D point_clique,CObjetGL* &ptr);
   void mise_a_jour_collision(CObjetGL* ptr);
   bool	jonction_de_station(CObjetGL* objet1,CObjetGL* objet2);
   void incrementerTemps(double dt) { mTemps += dt;}
   void evalrebonds(double xmin,double xmax,double ymin,double ymax);
   void evalcollisions();
   void dupliquer_station(CObjetGL* premier_objet_liste, CPoint3D point_clique, int NbrOvi);
   bool Selection_de_station3d(int numero_station,CObjetGL* &ptr);

   bool SelectionModule(CPoint3D Point,CObjetGL* &ptr) const;
//   bool Verif_station(CObjetGL* ptr) const;

   void Modifier_Vecteur_vitesse(CObjetGL* station_selectionne,double vitesse,double angle);

   void afficher() const;
   void animer(double dt,double xmin,double xmax,double ymin,double ymax) ;

 //  void charger();
   void imprimer( ostream& out = cout ) const;
   friend ostream& operator <<( ostream& out, const CScene& s )
   { s.imprimer(out); return out; }
   void destruction(CObjetGL* obj);
 //  void enregistrer();
   void imprime() const;
   void mise_jour_station(CObjetGL* ptr);
  // void Copier_station_liste_a_autre(list<CObjetGL*>::const_iterator premiere_liste,list<CObjetGL*>::const_iterator deuxieme_liste);
 
	
private:

/**
 * La liste des objets 
 * Vous pouvez en créer plusieurs différentes si vous le voulez
 *
 */
   list<CObjetGL*> mObjets;  // liste chainee (STL) des elements du jeu

 /**
 * Temps écoulé
 *
 */
   Station * mStation;
   CTransformationGL* mTransformation;
   double mTemps;

};

#endif /* _CSCENE_H_ */
