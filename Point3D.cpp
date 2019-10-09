// Point3D.cpp: implementation of the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "Point3D.h"


/*------------------------------------------------------------------
  Fonction :	CPoint3D::CPoint3D

  Description :	Constructeur d'un objet de type CPoint3D

  Paramètres :

	 const double& _x : La composante X du point.
	 const double& _y : La composante Y du point.
	 const double& _z : La composante Z du point.

  Valeur retournée :	Aucune (constructeur)

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CPoint3D::CPoint3D(const double& _x, const double& _y, const double& _z)
{
	x = _x;
	y = _y;
	z = _z;
}


/*------------------------------------------------------------------
  Fonction :	imprimer

  Description :	Impression sur std
------------------------------------------------------------------*/
void CPoint3D::imprimer( void ) const
{
	std::cout << "(" << x << "," << y << "," << z << ")";
}
