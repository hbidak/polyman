#ifndef BSPLINE_H
#define BSPLINE_H

#include <stdio.h>

/**
 * @class BSpline
 * @brief Definition de la classe qui fait une BSpline
 *
 * Classe qui permet de sp�cifier une vecteur de valeur nodales et des 
 * points de contr�le en 3D
 */

class BSpline
{
public:
	
	//Construction / destruction
	//--------------------------
	BSpline() : _noeuds(NULL), _nbNoeuds(0) {}
	BSpline( const BSpline& autre );
	virtual ~BSpline();

	//Contr�le du vecteur de valeurs nodales
	//Retourne FALSE si le vecteur est invalide
	//-----------------------------------------
	bool setVecteurNodal( double* noeuds, unsigned int nbNoeuds );

	//�valuation de la fonction B-Spline par Cox-deBoor
  // i : indice de la fonction � �valuer (ou encore, indice du point de contr�le)
  // k : ordre de la fonction ( = degr� + 1 )
	// t : valeur du param�tre
	//Retourne N i,k (t)
  //Retourne une valeur n�gative lorsqu'une erreur se produit
	//---------------------------------------------------------
	double evalN( int i, int k, double t );

private:

  void    nettoyer();

	double*      _noeuds;
	unsigned int _nbNoeuds;

};






#endif