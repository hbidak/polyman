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
 * @param argc : nombre de paramètres passés au programme
 * @param argv : chaînes de caractères contenant chaque paramètre.
 * @return 0: application terminée normalement; != 0: erreur
 * @exception
 *
 */
int main( int argc, char **argv )
{
	//Initialisation de la librairie glut
	//-----------------------------------
	CGlutMaster::InitGlut();

	//On crée la fenêtre de la scène
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

	//On démarre la boucle de glut
	//----------------------------
	CGlutMaster::StartDisplay();

	return 0;

}
