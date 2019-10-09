// Droite3D.cpp: implementation of the CDroite3D class.
//
//////////////////////////////////////////////////////////////////////

#include "Droite3D.h"
#include "Macros.h"



/*------------------------------------------------------------------
  Fonction :	CDroite3D::CDroite3D

  Description :	Constructeur d'une droite 3D

  Param�tres :
	 const CVecteur& Direction : Un vecteur parall�le � la droite 
								 (ne doit pas �tre nul sinon il y 
								 a un throw)
	 const CPoint3D& PtSurDroite : Un point par lequel passe la droite.

  Valeur retourn�e :	Aucune (constructeur) : 

  Par : 2001-1-10 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CDroite3D::CDroite3D(const CVecteur& Direction, const CPoint3D& PtSurDroite)
{
	if (Direction.IsNull())
		throw("Impossible de construire une droite 3d puisque le vecteur de direction est null.");

	m_Direction = Direction;
	m_PtDroite = PtSurDroite;
}


/*------------------------------------------------------------------
  Fonction :	CDroite3D::CDroite3D

  Description :	Constructeur d'une droite 3D

  Param�tres :
	 const CPoint3D &Pt1 : Un point sur la droite
	 const CPoint3D &Pt2 : Un autre point sur la droite (diff�rent 
						   de Pt1 sinon il y a un throw)

  Valeur retourn�e :	Aucune (constructeur) : 

  Par : 2001-1-10 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CDroite3D::CDroite3D(const CPoint3D &Pt1, const CPoint3D &Pt2)
	:m_Direction(Pt1, Pt2)
{
	if (m_Direction.IsNull())
		throw("Impossible de construire une droite 3d puisque le vecteur de direction est null.");

	m_PtDroite = Pt1;
}

/*------------------------------------------------------------------
  Fonction :	CDroite3D::Intersection

  Description :	Cette fonction permet de trouver l'intersection 
				entre une droite et un plan dans l'espace 3D.

  Param�tres :

	 const CPlan3D &PlanCoupe : Le plan avec lequel on veut trouver l'intersection.
	 CPoint3D &Intersection : Le r�sultat de l'intersection.

  Valeur retourn�e :	bool : false => la droite est parall�le au plan, 
							   donc l'intersection ne peut �tre trouv�e.

  Par : 2001-1-9 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
bool CDroite3D::Intersection(const CPlan3D &PlanCoupe, CPoint3D &Intersection) const
{
	
	return false;
}
