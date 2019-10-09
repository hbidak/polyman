#ifndef _OBJETGL_H__
#define _OBJETGL_H__

#include "Point3D.h"
#include "Point2D.h"
#include "Vecteur.h"
#include <assert.h>
#include <GL/glut.h>
//#include <fstream>
//using namespace std;
//ofstream FicSortie;


/**
 * @class CObjetGL
 * @brief Definition de la classe de base de tous les objets 
 *
 * Classe qui possede les differentes methodes et variables communs
 * a tous les objets
 */
enum TYPE_OBJET { TYPE_SPHERE, TYPE_CUBE, TYPE_CYLINDRE, TYPE_PRISME, TYPE_PROPULSION, TYPE_CONE, TYPE_OVI };

class CObjetGL  
{
public:

	// Construction / destruction
	//----------------------------
	CObjetGL(CPoint3D Pos = CPoint3D(0,0,0),
			CVecteur Direction = CVecteur(1,0,0), CVecteur Up = CVecteur(0,0,1),
			double EchelleX = 1.0, double EchelleY = 1.0, double EchelleZ = 1.0);
	CObjetGL(const CObjetGL& Source);
	virtual ~CObjetGL();

	const CObjetGL& operator=(const CObjetGL& Droite);


	//Pour créer ou mettre à jour la liste d'affichage de l'objet
	//-----------------------------------------------------------
	virtual void CreateDisplayList();
	

	//Pour afficher l'objet
	//---------------------
	virtual void Afficher() const =0;
	virtual void animer( double ) = 0; 
//	virtual void imprimer() const=0;
	void afficher_propriete();
	void imprimer_objet();
//	virtual void modifierCouleur(double ,double , double )=0; 

	//Fonctions d'accès
	//-----------------

	//void SetCouleur (double coulr,double coulg, double coulb);

	bool GetSelectionne() const {return selectionne;}
	void SetSelectionne(bool Selectionne) {selectionne=Selectionne;}

	bool GetSi_Station() const {return station;}
	void SetSi_Station(bool Station) {station=Station;}

	double GetAngle() const{return angle;}
	void SetAngle (double Angle) {angle=Angle;}
	
	TYPE_OBJET GetType() const {return type;}
	void SetType (TYPE_OBJET Type) {type=Type;}

	void Setm_UP (double x,double y,double z){m_Up.SetXYZ(x,y,z);}

	double GetLargeur() const {return m_Largeur;}
	void SetLargeur (double largeur) {m_Largeur=largeur;}

	double Gethauteur() const {return m_Hauteur;}
	void Sethauteur (double hauteur) {m_Hauteur=hauteur;}

	CPoint3D GetPosition() const {return m_Position;}  
	void SetPosition(CPoint3D point) {m_Position = point;}  

	double GetEchelleX() const {return m_EchelleX;}
	void   SetEchelleX(double Echelle) {assert(Echelle>0); m_EchelleX = (Echelle>0) ? Echelle: 1.0;}

	double GetEchelleY() const {return m_EchelleY;}
	void   SetEchelleY(double Echelle) {assert(Echelle>0); m_EchelleY = (Echelle>0) ? Echelle: 1.0;}

	double GetEchelleZ() const {return m_EchelleZ;}
	void   SetEchelleZ(double Echelle) {assert(Echelle>0); m_EchelleZ = (Echelle>0) ? Echelle: 1.0;}

protected:
	//Pour préparer la matrice de modélisaton
	void PrepareModelViewMatrix() const;

	//La position de l'objet
	CPoint2D m_carre;
	CPoint3D m_Position;
	CVecteur m_Direction; // (Vitesse)
	CVecteur m_Up;
	CObjetGL::TYPE_OBJET type;

	//Ses facteurs d'échelle
	double m_EchelleX;
	double m_EchelleY;
	double m_EchelleZ;

	// Largeur et hauteur
	double	m_Largeur;
	double	m_Hauteur;

	//angle
	double angle;

	//si une station
	bool station;

	//selectionnée
	bool selectionne;

	// Couleur
	double r;
	double g;
	double b;

	//Son numéro de displayList
	GLuint		 m_DisplayList;
};

#endif