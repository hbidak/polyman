// Rectangle.cpp: implementation of the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "Rectangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*------------------------------------------------------------------
  Fonction :	CRectangle::CRectangle

  Description :	Constructeur d'un objet de type CRectangle

  Paramètres :

	 int Largeur : Largeur de l'objet
	 int Hauteur : Hauteur de l'objet

  Valeur retournée :	Aucune (constructeur) : 

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CRectangle::CRectangle(int Largeur, int Hauteur)
{
	m_iLargeur = Largeur;
	m_iHauteur = Hauteur;
}



/*------------------------------------------------------------------
  Fonction :	imprimer

  Description :	Impression sur std
------------------------------------------------------------------*/
void CRectangle::imprimer() const
{
	std::cout << "Largeur : " << m_iLargeur << endl;
	std::cout << "Hauteur : " << m_iHauteur << endl;
}
