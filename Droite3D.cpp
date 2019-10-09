// Droite3D.cpp: implementation of the CDroite3D class.
//
//////////////////////////////////////////////////////////////////////

#include "Droite3D.h"
#include "Macros.h"



/*------------------------------------------------------------------
  Fonction :	CDroite3D::CDroite3D

  Description :	Constructeur d'une droite 3D

  Paramètres :
	 const CVecteur& Direction : Un vecteur parallèle à la droite 
								 (ne doit pas être nul sinon il y 
								 a un throw)
	 const CPoint3D& PtSurDroite : Un point par lequel passe la droite.

  Valeur retournée :	Aucune (constructeur) : 

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

  Paramètres :
	 const CPoint3D &Pt1 : Un point sur la droite
	 const CPoint3D &Pt2 : Un autre point sur la droite (différent 
						   de Pt1 sinon il y a un throw)

  Valeur retournée :	Aucune (constructeur) : 

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

  Paramètres :

	 const CPlan3D &PlanCoupe : Le plan avec lequel on veut trouver l'intersection.
	 CPoint3D &Intersection : Le résultat de l'intersection.

  Valeur retournée :	bool : false => la droite est parallèle au plan, 
							   donc l'intersection ne peut être trouvée.

  Par : 2001-1-9 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
bool CDroite3D::Intersection(const CPlan3D &PlanCoupe, CPoint3D &Intersection) const
{
	
	return false;
}
