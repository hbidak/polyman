// Point2D.cpp: implementation of the CPoint2D class.
//
//////////////////////////////////////////////////////////////////////

#include "Point2D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/*------------------------------------------------------------------
  Fonction :	CPoint2D::CPoint2D

  Description :	Constructeur d'un objet de type CPoint2D

  Paramètres :

	 int _x : la coordonnée X du point
	 int _y : la coordonnée Y du point

  Valeur retournée :	Aucune (constructeur)

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CPoint2D::CPoint2D(double _x, double _y):x(_x),y(_y)
{
	
}


/*------------------------------------------------------------------
  Fonction :	Imprimer

  Description :	Impression sur STD
------------------------------------------------------------------*/
void CPoint2D::imprimer( void ) const
{
	std::cout <<"("<< x << "," << y << ")";
}
