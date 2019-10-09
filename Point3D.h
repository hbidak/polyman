// Point3D.h: interface for the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _POINT3D_
#define _POINT3D_

#include <iostream>
#include "Vecteur.h"

using namespace std;

/**
 * @class CPoint3D
 * @brief Definition de la classe qui cree un point en 3 dimensions 
 *
 * Classe qui permet d'avoir un point en 3D
 */

class CPoint3D  
{
public:

	//Construction / Destruction
	//--------------------------

	CPoint3D(const double& x = 0.0, const double& y = 0.0, const double& z = 0.0);
	CPoint3D(CVecteur pV){ x = pV.GetX(); y = pV.GetY(); z = pV.GetZ();}
	virtual ~CPoint3D(){;}


	//Fonctions d'accès
	//-----------------

    double* GetPtr() {return &x;}
    const double* GetPtr() const {return &x;}
        
	double GetX() const {return x;}
	double GetY() const {return y;}
	double GetZ() const {return z;}

	void SetX(const double& _x) {x = _x;}
	void SetY(const double& _y) {y = _y;}
	void SetZ(const double& _z) {z = _z;}

	// on peut obtenir un point par l'addition d'un point et d'un vecteur
	CPoint3D operator + (CVecteur & v)
	{ return CPoint3D(x+v.GetX(), y+v.GetY(), z+v.GetZ()); }
	void operator+=(const CVecteur& pV){x+=pV.GetX();y+=pV.GetY();z+=pV.GetZ();}

	//Fonction pour afficher le point dans la console
	//-----------------------------------------------
	void imprimer() const;

private:

	//Les attributs de la classe
	double x, y, z;
};

#endif