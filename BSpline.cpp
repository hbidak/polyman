// BSpline.cpp : Defines the class methods.
//

#include "BSpline.h"

/**
 * Constructeur copie
 */
BSpline::BSpline( const BSpline& autre )
{
	nettoyer();

	_noeuds = new double[ autre._nbNoeuds ];
	_nbNoeuds = autre._nbNoeuds;

	unsigned int i;
	for( i=0; i<_nbNoeuds; ++i )
		_noeuds[i] = autre._noeuds[i];
}

/**
 * Destructeur
 */
BSpline::~BSpline()
{
	nettoyer();
}

/**
 * Charger un vecteur de valeurs nodales
 * Retourne FALSE si le vecteur est invalide
 */
bool
BSpline::setVecteurNodal( double* noeuds, unsigned int nbNoeuds )
{
	nettoyer();

	if( noeuds == NULL || nbNoeuds == 0 )
		return false;

	unsigned int i;
	for( i=0; i<nbNoeuds-1; ++i )
		if( noeuds[i] > noeuds[i+1] ) 
			return false;

	_nbNoeuds = nbNoeuds;
	_noeuds = new double[_nbNoeuds];

	for( i=0; i<nbNoeuds; ++i )
		_noeuds[i] = noeuds[i];

	return true;
}


/**
 * Évaluation d'une fonction de pondération avec Cox-deBoor
 * Retourne une valeur négative lorsqu'une erreur se produit
 */
double
BSpline::evalN( int i, int k, double t )
{
	// Verifier que l'ordre est bien superieur a 0
	if( k <= 0 )
		return -1;

	// S'assurer que i a une valeur adéquate
	if( i < 0 || _nbNoeuds <= (unsigned int)i+k )
		return -1;

	// Condition de sortie de la recursion: ordre = 1 (degré = 0)
	if( k == 1 )
	{
		// Si on est dans le bon intervalle (ouvert a droite), on retourne 1
		if( _noeuds[i] <= t && t < _noeuds[i+1] )
			return 1;

		// Cas particulier, le dernier intervalle est ferme a droite
		if( i+1 == _nbNoeuds-1 && t == _noeuds[_nbNoeuds-1] )
			return 1;

		// Dans tous les autres cas, on est hors de l'intervalle
		return 0;
	}

	// L'ordre est supérieur à 1, récursion
	double Aa = ( t - _noeuds[i]   );
	double Ab = ( _noeuds[i+k] - t );

	double Ba = _noeuds[i+k-1] - _noeuds[i];
	double Bb = _noeuds[i+k] -   _noeuds[i+1];
	if( Ba < 0 || Bb < 0 ) return -1;

	double Ca = 0;
	double Cb = 0;
	if( Ba != 0 )
		Ca = Aa / Ba;
	if( Bb != 0 )
		Cb = Ab / Bb;

	double Na = evalN( i, k-1, t );
	double Nb = evalN( i+1, k-1, t );
	if( Na < 0 || Nb < 0 ) return -1;

	return Ca * Na + Cb * Nb;
}


/**
 * Méthodes privées
 */
void 
BSpline::nettoyer()
{
	if( _noeuds != NULL )
		delete[] _noeuds;
	
	_noeuds = NULL;
	_nbNoeuds = 0;
}


