// Vecteur.cpp: implementation of the CVecteur class.
//
//////////////////////////////////////////////////////////////////////
#include "vecteur.h"
#include "Point3D.h"
#include "Macros.h"


/*---------------------------------------------------------------------------
 * FONCTION: CVecteur
 * CLASSE  : CVecteur
 *
 * Constructeur d'un CVecteur
 * 
 * ENTREES : _x, _y, _z : les composantes du CVecteur selon ces axes.
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
CVecteur::CVecteur(double _x, double _y, double _z)
{
   x = _x;
   y = _y;
   z = _z;
}
 
/*---------------------------------------------------------------------------
 * FONCTION: CVecteur
 * CLASSE  : CVecteur
 *
 * Constructeur d'un CVecteur a partir de deux points dans l'espace
 * 
 * ENTREES : Origine et Fin : les deux points qui délimitent le CVecteur
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
CVecteur::CVecteur(const CPoint3D & Origine, const CPoint3D & Fin)
{
   x = Fin.GetX() - Origine.GetX();
   y = Fin.GetY() - Origine.GetY();
   z = Fin.GetZ() - Origine.GetZ();
}
 
/*---------------------------------------------------------------------------
 * FONCTION: getModule()
 * CLASSE  : CVecteur
 *
 * Permet d'obtenir le module du CVecteur
 * 
 * ENTREES : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : Le module du CVecteur
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
double CVecteur::GetModule() const
{
   return sqrt( x*x + y*y + z*z );
}
 
/*---------------------------------------------------------------------------
 * FONCTION: Scalar
 * CLASSE  : CVecteur
 *
 * Fait le produit scalaire entre *this et un autre CVecteur (b)
 * 
 * ENTREES : b : L'autre CVecteur du produit scalaire
 * SORTIES : AUCUNES
 * RETOUR  : Le résultat du produit scalaire
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
double CVecteur::Scalar(const CVecteur& b)
{
   return (x*b.x + y*b.y + z*b.z);
}

/*---------------------------------------------------------------------------
 * FONCTION: operator = 
 * CLASSE  : CVecteur
 *
 * Permet de faire des assignations sur les CVecteurs
 * 
 * ENTREES : Droite : le CVecteur a droite du terme d'égalité
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
const CVecteur & CVecteur::operator = (const CVecteur & Droite)
{
  x = Droite.x;
  y = Droite.y;
  z = Droite.z;

  return *this;
}

/*---------------------------------------------------------------------------
 * FONCTION: getFin
 * CLASSE  : CVecteur
 *
 * Permet d'obtenir le ou se terminerait le CVecteur si son origine était au 
 * point "Debut"
 * 
 * ENTREES : Debut : le point de départ du CVecteur
 * SORTIES : AUCUNES
 * RETOUR  : Le point de fin
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
CPoint3D CVecteur::GetFin(const CPoint3D& Debut) const
{
  CPoint3D Fin;
  
  Fin.SetX(x + Debut.GetX());
  Fin.SetY(y + Debut.GetY());
  Fin.SetZ(z + Debut.GetZ());
  
  return Fin;
}

/*---------------------------------------------------------------------------
 * FONCTION: operator+
 * CLASSE  : CVecteur
 *
 * Permet de faire l'addition de CVecteurs
 * 
 * ENTREES : Droite : le CVecteur a droite du "+"
 * SORTIES : AUCUNES
 * RETOUR  : Le CVecteur résultant
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
CVecteur CVecteur::operator+(const CVecteur& Droite) const
{
  CVecteur VRetour;
  
  VRetour.x = x + Droite.x;
  VRetour.y = y + Droite.y;
  VRetour.z = z + Droite.z;
  
  return VRetour;
}


/*---------------------------------------------------------------------------
 * FONCTION: operator-
 * CLASSE  : CVecteur
 *
 * Permet de faire la soustraction de CVecteurs
 * 
 * ENTREES : Droite : le CVecteur a droite du "-"
 * SORTIES : AUCUNES
 * RETOUR  : Le CVecteur résultant
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
CVecteur CVecteur::operator-(const CVecteur& Droite) const
{
  CVecteur VRetour;
  
  VRetour.x = x - Droite.x;
  VRetour.y = y - Droite.y;
  VRetour.z = z - Droite.z;
  
  return VRetour;
}

/*---------------------------------------------------------------------------
 * FONCTION: operator*
 * CLASSE  : CVecteur
 *
 * Permet de multiplier un CVecteur par une constante
 * 
 * ENTREES : Multiplication : la constante par laquelle on multiplie le CVecteur
 * SORTIES : AUCUNES
 * RETOUR  : Le CVecteur résultat
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
CVecteur CVecteur::operator*(const double Multiplication) const
{
  CVecteur VRetour;
  
  VRetour.x = x * Multiplication;
  VRetour.y = y * Multiplication;
  VRetour.z = z * Multiplication;

  return VRetour;
}

/*---------------------------------------------------------------------------
 * FONCTION: Vectorial
 * CLASSE  : CVecteur
 *
 * Permet de faire le produit vectoriel entre le CVecteur courant et un autre
 * 
 * ENTREES : b : le deuxieme CVecteur (*this x b)
 * SORTIES : AUCUNES
 * RETOUR  : Le CVecteur résultat
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
CVecteur CVecteur::Vectorial(const CVecteur& b) const
{
  CVecteur VRetour;

  VRetour.x = y * b.z - b.y * z;
  VRetour.y = -(x * b.z - b.x * z);
  VRetour.z = x * b.y - b.x * y;

  return VRetour;
}


/*------------------------------------------------------------------
  Fonction :	CVecteur::IsNull

  Description :	Permet de savoir si le vecteur est le vecteur null (0,0,0).

  Paramètres :

  Valeur retournée :	bool : true => le vecteur est null

  Par : 2000-4-15 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
bool CVecteur::IsNull() const
{
	return (EGAL_ZERO(x) && EGAL_ZERO(y) && EGAL_ZERO(z));
}


/*------------------------------------------------------------------
  Fonction :	CVecteur::Noralize

  Description :	Permet de normaliser le vecteur.

  Paramètres :

  Valeur retournée :	bool : true => l'opération a été effectuée (le vecteur n'est pas null).

  Par : 2000-4-15 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
bool CVecteur::Normalize()
{
	bool Null = IsNull();

	if (!Null)
		*this = *this / GetModule();

	return !Null;
}

/*------------------------------------------------------------------
  Fonction :	CVecteur::CartesianToSpheric

  Description :	Calcule les coordonnées spheriques du vecteur

  Paramètres : r, phi et theta qui seront modifiées par référence
				phi et theta sont retournés en degrés

  Valeur retournée :	aucune

  Par : 2002-11-03 Carlos Valcarcel
------------------------------------------------------------------*/
void CVecteur::CartesianToSpheric(double& r, double& phi, double& theta) const
{
	r = GetModule();
	phi = acos(z/r);
	
	if (x!=0)
		theta = atan(y/x);
	else
		theta = 0.0;

    if (x<0.0) 
		 theta = theta + PI;

	phi = RAD_TO_DEG(phi);
	theta = RAD_TO_DEG(theta);

}

/*------------------------------------------------------------------
  Fonction :	CVecteur::SphericToCartesian

  Description :	Calcule les coordonnées cartésiennes du vecteur à partir de données sphériques

  Paramètres : r, phi et theta en degrés

  Valeur retournée :	aucune

  Par : 2002-11-03 Carlos Valcarcel
------------------------------------------------------------------*/
void CVecteur::SphericToCartesian(const double& r, const double& _phi, const double& _theta)
{
	double phi = DEG_TO_RAD(_phi);
	double theta = DEG_TO_RAD(_theta);

	x = r*sin(phi)*cos(theta);
	y = r*sin(phi)*sin(theta);
	z = r*cos(phi);
}


/*------------------------------------------------------------------
  Fonction :	operator /

  Description :	Permet de faire des divisions par un scalaire.

  Paramètres :
	 const double Diviseur : Le diviseur (doit être différent de 0)

  Valeur retournée :	CVecteur CVecteur::operator : Le résulat de l'opération.

  Par : 2000-4-15 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CVecteur CVecteur::operator/(const double Diviseur) const
{
	CVecteur Retour(*this);

	bool DiviseurValide = !(EGAL_ZERO(Diviseur));

	if (DiviseurValide)
		Retour = *this * (1/Diviseur);

	return Retour;
}


void CVecteur::operator+=(const CVecteur& Droite)
{
	x += Droite.GetX();
	y += Droite.GetY();
	z += Droite.GetZ();
}