#ifndef STATION_H
#define STATION_H

#include <list>
#include "Module.h"
#include "ObjetGL.h"
#include "Constantes.h"
#include "GlutMaster.h"
#include "GlutWindow.h"
#include "AdvGlutWnd.h"
#include "Macros.h"
//#include "Propulsion.h"
//#include "Jonction.h"
//#include "Scene.h"
#include <fstream>
using namespace std;
#include <ctime>


class Station: public CObjetGL
{
private:
	Module* pere;
	list<CObjetGL*> mStations;

	CPoint3D centre;
	double hauteur_s;
	double largeur_s;
	float angle;

	CVecteur vitesse;
	float vitesse_angulaire;


public:

	Station();
	~Station();

	void Afficher() const;
	void animer(double dt);

	bool SelectionModule(CPoint3D Point,CObjetGL* &ptr) const;

	void Centre_gravite();
	void AjouterStation( CObjetGL* obj);
	void eliminerDernierStations( void );
    void eliminerTousStations( void );
	void destruction(CObjetGL* obj);
	void RetourPremierModule(CObjetGL* &ptr);
	bool Station_incluse(CObjetGL* obj);
	bool Station_Copie(CObjetGL* &obj);
	bool retour_module_station(CObjetGL* &obj, int compteur);
	bool grosseur_liste();
	int nb_module_inclus();
	bool Eval_collision_2_station(CObjetGL* ptr,CObjetGL* &objet_qui_touche) const;
	void Modif_position_station(double x,double y);
	bool Verification_station_avant(CObjetGL* &pointeur);
	void Imprimer( ostream& out = cout ) const;
	friend ostream& operator <<( ostream& out, const Station& s )
   { s.Imprimer(out); return out; }

	void Eval_collision_2_station(list<CObjetGL*> mStations2);

	bool Verif_station(CObjetGL* ptr) const;

	Station( const Station& b ) { *this = b; }
    const Station& operator=( const Station& b );

	double GetAngle() const{return angle;}
	void SetAngle (double Angle) {angle=Angle;}

	CPoint3D GetPosition() const {return centre;}  
	void SetPosition(CPoint3D point) {centre = point;} 

	CVecteur GetVitesse() const {return vitesse;}
	void SetVitesse(CVecteur Vitesse) {vitesse=Vitesse;}

	float GetVitesse_Angulaire() const{return vitesse_angulaire;}
	void SetVitesse_Angulaire (float Vitesse_Angulaire) {vitesse_angulaire=Vitesse_Angulaire;}

	double GetLargeur() const {return largeur_s;}
	void SetLargeur (double Largeur) {largeur_s=Largeur;}

	double GetHauteur() const {return hauteur_s;}
	void SetHauteur (double Hauteur) {hauteur_s=Hauteur;}

};


#endif