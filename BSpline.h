#ifndef BSPLINE_H
#define BSPLINE_H

#include <stdio.h>

/**
 * @class BSpline
 * @brief Definition de la classe qui fait une BSpline
 *
 * Classe qui permet de spécifier une vecteur de valeur nodales et des 
 * points de contrôle en 3D
 */

class BSpline
{
public:
	
	//Construction / destruction
	//--------------------------
	BSpline() : _noeuds(NULL), _nbNoeuds(0) {}
	BSpline( const BSpline& autre );
	virtual ~BSpline();

	//Contrôle du vecteur de valeurs nodales
	//Retourne FALSE si le vecteur est invalide
	//-----------------------------------------
	bool setVecteurNodal( double* noeuds, unsigned int nbNoeuds );

	//Évaluation de la fonction B-Spline par Cox-deBoor
  // i : indice de la fonction à évaluer (ou encore, indice du point de contrôle)
  // k : ordre de la fonction ( = degré + 1 )
	// t : valeur du paramètre
	//Retourne N i,k (t)
  //Retourne une valeur négative lorsqu'une erreur se produit
	//---------------------------------------------------------
	double evalN( int i, int k, double t );

private:

  void    nettoyer();

	double*      _noeuds;
	unsigned int _nbNoeuds;

};






#endif