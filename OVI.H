#ifndef OVI_H
#define OVI_H

#include "ObjetGL.h"
#include "Trajectoire.h"
#include "Constantes.h"
#include <list>
#include <vector>

class OVI:public CObjetGL
{
private:
	CTrajectoire* traj;
	//	CTrajectoire* trajS;

	bool Mode_Jeu;
	//ajout
	
	double pourcentage;
	int pcourant ;
	int Nlight;

public:
	OVI(CPoint3D pos, double hauteur, double largeur, int NbrOvi);
	~OVI();

	void Afficher() const;
	void animer(double);
	void AjouterPtsTrajectoire(double x0,double y0,double z0); //ajout
	void AjouterPtsTrajectoireSplines(double x0,double y0,double z0);
	void modifierCouleur(double ,double , double );
	void Imprimer( ostream& out = cout ) const;
	friend ostream& operator <<( ostream& out, const OVI& s )
   { s.Imprimer(out); return out; }


	CPoint3D GetPosition() const {return m_Position;}  
	void SetPosition(CPoint3D point) {m_Position = point;}

	CTrajectoire* GetTrajectoire();
	
};

#endif