#ifndef _POINT2D_
#define _POINT2D_

#include <iostream>

class CPoint2D  
{
public:

	//Construction / Destruction
	//--------------------------

	CPoint2D(double _x = 0, double _y = 0);
	virtual ~CPoint2D(){;}


	//Fonctions d'accès
	//------------------

	int GetX() const {return x;}
	int GetY() const {return y;}

	void SetX(const double _x) {x = _x;}
	void SetY(const double _y) {y = _y;}

	//Fonction pour afficher le point dans la console
	//-----------------------------------------------

	void imprimer() const;

private:

	//Les attributs du point
	//----------------------
	int x, y;
};

#endif