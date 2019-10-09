#ifndef _DROITE3D_
#define _DROITE3D_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vecteur.h"
#include "Point3D.h"
#include "Plan3D.h"

/**
 * @class CDroite3D
 * @brief Definition de la classe qui cree une droite en 3 dimensions 
 *
 * Classe qui permet d'avoir une droite en 3D
 */


class CDroite3D  
{
public:
	//Construction / destruction
	//--------------------------

	CDroite3D(const CPoint3D& Pt1, const CPoint3D& Pt2);
	CDroite3D(const CVecteur& Direction, const CPoint3D& PtSurDroite);
	virtual ~CDroite3D(){;}

	// Fonction pour trouver l'intersection entre une droite et un plan.
	bool Intersection(const CPlan3D& PlanCoupe, CPoint3D& Intersection) const;

private:

	// Un droite dans l'espace 3d est définit par 
	//
	// x - x0   y - y0   z - z0
	// ------ = ------ = ------
	//   a        b        c
	//
	// où le point (x0, y0, z0) est un point de la droite
	// et le vecteur (a, b, c) est un vecteur parallele
	// à la droite.

	CPoint3D m_PtDroite;	// (x0, y0, z0)
	CVecteur m_Direction;	// (a, b, c)
};

#endif