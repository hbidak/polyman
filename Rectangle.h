#ifndef _RECTANGLE_H__
#define _RECTANGLE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>

using namespace std;

/**
 * @class CRectangle
 * @brief Definition de la classe qui fait un rectangle 
 *
 * Classe qui gere les differents parametres d'un rectangle
 *
 */


class CRectangle  
{
public:
	//Construction / destruction
	//--------------------------
	CRectangle(int Largeur = 0, int Hauteur = 0);
	virtual ~CRectangle(){;}

	//Fonction d'accès
	//----------------
	int GetLargeur() const {return m_iLargeur;}
	int GetHauteur() const {return m_iHauteur;}
	void SetLargeur(int Largeur) {m_iLargeur = Largeur;}
	void SetHauteur(int Hauteur) {m_iHauteur = Hauteur;}

	void imprimer( void ) const;

private:

	// La dimension en X = largeur
	int m_iLargeur;

	// La dimension en Y = hauteur
	int m_iHauteur;
};

#endif 