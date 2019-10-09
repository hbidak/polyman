// GlutMaster.cpp: implementation of the CGlutMaster class.
//
//////////////////////////////////////////////////////////////////////

#include "GlutMaster.h"
#include <GL/Glut.h>
#include <stdlib.h>
#include "FenetreGL.h"

//Cr�ation des attributs statiques
//-----------------------------------

CGlutWindow* CGlutMaster::ms_arpGlutWnd[MAX_NUMBER_OF_WINDOWS];


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::RegisterWindow

  Description :	Cette fonction enregistre une fen�tre GLUT aupr�s de 
				Glut Master.  Apr�s l'appel de cette fonction, les 
				fonction d'affichage, de clavier, etc. de la fen�tre 
				glut seront appel�es par Glut Master.

  Param�tres :

	 CGlutWindow &GlutWindow : Une r�f�rence � la fen�tre qu'on veut enregistrer.

  Valeur retourn�e :	void 

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::RegisterWindow(CGlutWindow &GlutWindow)
{

	//On garde on pointeur � cette fen�tre
	//------------------------------------------

	ms_arpGlutWnd[GlutWindow.GetNumeroFen()] = &GlutWindow;



	// On enregistre les fonction de rappel
	//-------------------------------------------

	glutDisplayFunc(*CallBackDisplay);
	glutMotionFunc(*CallBackMouseMove);

	// Callbacks GLUT
	glutMouseFunc(*CallBackMouse);
	glutReshapeFunc(*CallBackReshape); 
	glutKeyboardFunc(*CallBackKeyboard);
	glutSpecialFunc(*CallBackSpecialKeyboard);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::StartDisplay

  Description :	Cette fonction permet de "d�marrer" les fen�tres Glut.  
				Appelez cette fonction � la fin de votre main lorsque 
				toutes vos fen�tres ont �t� cr��es et que vous voulez 
				d�marrer leur affichage.

  Valeur retourn�e :	Aucune

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::StartDisplay()
{
	glutMainLoop();
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackDisplay

  Description :	Cette fonction sera appel� par GLUT lorsqu'une fen�tre 
				a besoin d'�tre r�affich�e.  � ce moment, Glut Master 
				d�termine quelle est la fen�tre qui doit �tre r�affich� 
				et il app�le la fonction "Afficher" de la fen�tre appropri�e.

  Valeur retourn�e :	Aucune

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackDisplay()
{
	ms_arpGlutWnd[glutGetWindow()]->Afficher();
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackMouse

  Description :	Cette fonction sera appel�e par GLUT lorsqu'un 
				�v�n�ment de souris (clic) se produit dans une fen�tre.

  Param�tres :

	 int button : Le bouton de la souris.
	 int state : Son �tat (up/down)
	 int x : la position x de l'�v�nement
	 int y : La position y de l'�v�nement

  Valeur retourn�e :	void : 

  Par : 2000-12-9 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackMouse(int button, int state, int x, int y)
{
	ms_arpGlutWnd[glutGetWindow()]->ClicSouris(button, state, x, y);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::InitGlut

  Description :	Cette fonction permet d'initialiser la librairie GLUT.  
				Celle-ci devrait �tre appel�e pr�alablement � tout 
				appel GLUT.

  Valeur retourn�e :	void : 

  Par : 2000-12-9 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::InitGlut()
{

	// Param�tres bidons
	char * dummy_argv[1];
	dummy_argv[0] = "run";
	int dummy_argc = 1;

	// Initialisation de GLUT

	glutInit(&dummy_argc, dummy_argv);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackMouseMove

  Description :	Cette fontion sera appel�e par GLUT lorsque la souris 
				bouge dans une fen�tre GLUT et qu'un des boutons de 
				la souris est enfonc�.

  Param�tres :
	 int x : La position X de la souris.
	 int y : La position Y de la souris.

  Valeur retourn�e :	Aucune

  Par : 2000-12-10 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackMouseMove(int x, int y)
{
	ms_arpGlutWnd[glutGetWindow()]->MouseMove(x, y);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackReshape

  Description :	Fonction qui sera appel�e par GLUT lorsqu'une 
				fen�tre est redimensionn�e.

  Param�tres :
	 int width : La nouvelle largeur
	 int height : La nouvelle hauteur.

  Valeur retourn�e :	void : 

  Par : 2000-12-11 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackReshape(int width, int height)
{
	ms_arpGlutWnd[glutGetWindow()]->Reshape(width, height);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackMenu

  Description :	Fonction qui sera appel�e par GLUT lorsqu'un �l�ment 
				est s�lectionn� � l'int�rieur d'un menu.

  Param�tres :
	 int NumMenu : Le num�ro du menu qui a �t� s�lectionn�.

  Valeur retourn�e :	void : 

  Par : 2000-12-11 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackMenu(int NumMenu)
{
	ms_arpGlutWnd[glutGetWindow()]->Menu(NumMenu);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackKeyboard

  Description :	Fonction qui sera appel�e par GLUT lorsque une 
				touche normale est appuy�e sur le clavier.

  Param�tres :
	 unsigned char key : La touche appuy�e.
	 int x : La position X de la souris.
	 int y : La position Y de la souris.

  Valeur retourn�e :	void : 

  Par : 2000-12-11 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackKeyboard(unsigned char key, int x, int y)
{
	if (key == ESCAPE)
	{
		// On termine le programme
			for (int iFen = 0; iFen < MAX_NUMBER_OF_WINDOWS; iFen++)
			{
				if (ms_arpGlutWnd[iFen] != NULL)
					delete ms_arpGlutWnd[iFen];
			}
			exit(0);
	}
	else
		ms_arpGlutWnd[glutGetWindow()]->Clavier(key, x, y);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackSpecialKeyboard

  Description :	Fonction qui sera appel�e par GLUT lorsqu'une touche 
				sp�ciale du clavier sera enfonc�e (ex : F1)

  Param�tres :
	 int key : La touche 
	 int x : La position X de la souris
	 int y : La position Y de la souris

  Valeur retourn�e :	void : 

  Par : 2001-1-4 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackSpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F4:
		{
			// On termine le programme
			for (int iFen = 0; iFen < MAX_NUMBER_OF_WINDOWS; iFen++)
			{
				if (ms_arpGlutWnd[iFen] != NULL)
					delete ms_arpGlutWnd[iFen];
			}
			exit(0);
		}
		break;
		
	default:
		ms_arpGlutWnd[glutGetWindow()]->ClavierSpecial(key, x, y);
	}
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackGLUI

  Description :	MODIF GLUI

  Valeur retourn�e :	Aucune

  Par : 2002-03-04 Jean-No� Morissette
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackGLUI( int ID )
{
	ms_arpGlutWnd[glutGetWindow()]->GLUI_event( ID );
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::timerCallback

  Description :	JNM ANIM

  Valeur retourn�e :	Aucune

  Par : 2002-03-04 Jean-No� Morissette
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::timerCallback( int ptr )
{
	CFenetreGL *pDemoWnd;
	pDemoWnd = (CFenetreGL*) ptr;
	pDemoWnd->AvancerTemps();   //JNM ANIM
	glutTimerFunc(30, CGlutMaster::timerCallback, (int)pDemoWnd);

 //CGlutMaster::timerCallback((int)this); // A mettre dans FenetreGL
}
