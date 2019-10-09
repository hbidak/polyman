#ifndef _FENETREPRINCIPALE_
#define _FENETREPRINCIPALE_

#include "Constantes.h"
#include "AdvGlutWnd.h"

/**
 * @class CFenetrePrincipale
 * @brief Definition de la classe qui gere la fenetre principale 
 *
 * Classe qui possede les differents objets qui s'occupe des differentes
 * interractions avec le clavier et la souris
 */


class CFenetrePrincipale : public CAdvGlutWnd  
{
public:

	// Construction / Destruction
	//---------------------------
	CFenetrePrincipale::CFenetrePrincipale(  const CPoint2D& PosFenetre,
											 const CRectangle& DimFenetre, 
											 const CCouleurGL CouleurFond );

	CFenetrePrincipale::CFenetrePrincipale( CGlutWindow& Parent, 
								const CPoint2D& PosFenetre,
								const CRectangle& DimFenetre, 
								const CCouleurGL CouleurFond );

	virtual ~CFenetrePrincipale();

	// Fonctions virtuelles surchargées.
	//----------------------------------

	void Afficher();
	void Menu(int NumMenu);
	void ClicSouris(int button, int state, int x, int y);
	void Clavier(unsigned char Key, int x, int y);
	void Reshape(int Width, int Height);
	
private:
};

#endif  //_FENETREPRINCIPALE_
