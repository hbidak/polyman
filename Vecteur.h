// Vecteur.h: interface for the CVector class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <math.h>
#include "macros.h"

#define PI 3.14159265
class CPoint3D;


/**
 * @class CVecteur
 * @brief Definition de la classe qui cree un vecteur en 3 dimensions 
 *
 * Classe qui permet d'avoir un vecteur en 3D et d'effectuer des operations dessus.
 */


class CVecteur  
{
public:

	//Construction / destruction
	//--------------------------
	CVecteur(double _x = 0.0, double _y = 0.0, double _z = 0.0);
	CVecteur(const CPoint3D & Origine, const CPoint3D & Fin);
	CVecteur(const CVecteur& V) {*this = V;}
	virtual ~CVecteur(){;}

	//Surcharge d'opérateurs
	//----------------------
	CVecteur operator / (const double Diviseur) const;
	const CVecteur & operator = (const CVecteur & Droite);
	CVecteur operator+(const CVecteur& Droite) const;
	CVecteur operator-(const CVecteur& Droite) const;
	CVecteur operator*(const double Multiplication) const;
	void operator+=(const CVecteur& Droite);

	//Produits de vecteurs
	//--------------------
	double Scalar(const CVecteur& b);
	CVecteur Vectorial(const CVecteur& b) const;

	//Fonctions utilitaires
	//---------------------
	bool Normalize();
	bool IsNull() const;
	
	//Fonctions d'accès	
	//-----------------
	CPoint3D GetFin(const CPoint3D& Debut) const;
	double GetModule()	const;
	double GetX()const {return x;}
	double GetY()const {return y;}
	double GetZ()const {return z;}
	bool GetPhiNegative()const {return PhiNegative;}

	void SetX(const double& _x) {x = _x;}
	void SetY(const double& _y) {y = _y;}
	void SetZ(const double& _z) {z = _z;}
	void SetXYZ(const double& _x, const double& _y, const double& _z){x = _x; y = _y; z = _z;}
	void SetPhiNegative(const bool& PhiNegative_Init) {PhiNegative = PhiNegative_Init;}

	//Coordonnées sphériques
	double GetR() const {return GetModule();}
	double GetPhi() const {return acos(z/GetModule());}
	double GetTheta() const {double theta = atan(y/x); if (x>0.0) return theta; else return (3.141592654+theta);} //theta +

	void CartesianToSpheric(double& r, double& phi, double& theta) const;
	void SphericToCartesian(const double& r, const double& _phi, const double& _theta);

private:
	//Les composantes x,y,z du Vecteur
	//--------------------------------
	double x, y, z ;
	bool PhiNegative;
};


