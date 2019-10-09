/*=======================================================================
 * Programme principal
 *=====================================================================*/

#include "GlutMaster.h"
#include "CouleurGL.h"
#include "Principale.h"
#include "FenetreGL.h"


#pragma warning (disable:4995)
#pragma warning (disable:4311)
#pragma warning (disable:4312)

/**
 * @fn  int main( int argc, char **argv )
 *
 * Programme principal pour le tp1.
 *
 * @param argc : nombre de param�tres pass�s au programme
 * @param argv : cha�nes de caract�res contenant chaque param�tre.
 * @return 0: application termin�e normalement; != 0: erreur
 * @exception
 *
 */
int main( int argc, char **argv )
{
	//Initialisation de la librairie glut
	//-----------------------------------
	CGlutMaster::InitGlut();

	//On cr�e la fen�tre de la sc�ne
	//------------------------------
	CRectangle	DimFenetre(500,500);
	CPoint2D	PosFenetre(100,100);
	CCouleurGL	CouleurFond;

	CouleurFond.LoadStdColor(STD_NavyBlue);
	CFenetrePrincipale* pFenPrin = new CFenetrePrincipale(PosFenetre, DimFenetre, CouleurFond);

	CouleurFond.LoadStdColor(STD_Black);
	CFenetreGL* pFenetreGL = new CFenetreGL(*pFenPrin, PosFenetre, DimFenetre, CouleurFond);


	CScene* lScene;
	lScene = new CScene();

	pFenetreGL->SetScene(lScene);

	//On d�marre la boucle de glut
	//----------------------------
	CGlutMaster::StartDisplay();

	return 0;

}
