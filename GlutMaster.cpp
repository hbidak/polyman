// GlutMaster.cpp: implementation of the CGlutMaster class.
//
//////////////////////////////////////////////////////////////////////

#include "GlutMaster.h"
#include <GL/Glut.h>
#include <stdlib.h>
#include "FenetreGL.h"

//Création des attributs statiques
//-----------------------------------

CGlutWindow* CGlutMaster::ms_arpGlutWnd[MAX_NUMBER_OF_WINDOWS];


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::RegisterWindow

  Description :	Cette fonction enregistre une fenêtre GLUT auprès de 
				Glut Master.  Après l'appel de cette fonction, les 
				fonction d'affichage, de clavier, etc. de la fenêtre 
				glut seront appelées par Glut Master.

  Paramètres :

	 CGlutWindow &GlutWindow : Une référence à la fenêtre qu'on veut enregistrer.

  Valeur retournée :	void 

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::RegisterWindow(CGlutWindow &GlutWindow)
{

	//On garde on pointeur à cette fenêtre
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

  Description :	Cette fonction permet de "démarrer" les fenêtres Glut.  
				Appelez cette fonction à la fin de votre main lorsque 
				toutes vos fenêtres ont été créées et que vous voulez 
				démarrer leur affichage.

  Valeur retournée :	Aucune

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::StartDisplay()
{
	glutMainLoop();
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackDisplay

  Description :	Cette fonction sera appelé par GLUT lorsqu'une fenêtre 
				a besoin d'être réaffichée.  À ce moment, Glut Master 
				détermine quelle est la fenêtre qui doit être réaffiché 
				et il appèle la fonction "Afficher" de la fenêtre appropriée.

  Valeur retournée :	Aucune

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackDisplay()
{
	ms_arpGlutWnd[glutGetWindow()]->Afficher();
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackMouse

  Description :	Cette fonction sera appelée par GLUT lorsqu'un 
				événément de souris (clic) se produit dans une fenêtre.

  Paramètres :

	 int button : Le bouton de la souris.
	 int state : Son état (up/down)
	 int x : la position x de l'événement
	 int y : La position y de l'événement

  Valeur retournée :	void : 

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
				Celle-ci devrait être appelée préalablement à tout 
				appel GLUT.

  Valeur retournée :	void : 

  Par : 2000-12-9 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::InitGlut()
{

	// Paramêtres bidons
	char * dummy_argv[1];
	dummy_argv[0] = "run";
	int dummy_argc = 1;

	// Initialisation de GLUT

	glutInit(&dummy_argc, dummy_argv);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackMouseMove

  Description :	Cette fontion sera appelée par GLUT lorsque la souris 
				bouge dans une fenêtre GLUT et qu'un des boutons de 
				la souris est enfoncé.

  Paramètres :
	 int x : La position X de la souris.
	 int y : La position Y de la souris.

  Valeur retournée :	Aucune

  Par : 2000-12-10 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackMouseMove(int x, int y)
{
	ms_arpGlutWnd[glutGetWindow()]->MouseMove(x, y);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackReshape

  Description :	Fonction qui sera appelée par GLUT lorsqu'une 
				fenêtre est redimensionnée.

  Paramètres :
	 int width : La nouvelle largeur
	 int height : La nouvelle hauteur.

  Valeur retournée :	void : 

  Par : 2000-12-11 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackReshape(int width, int height)
{
	ms_arpGlutWnd[glutGetWindow()]->Reshape(width, height);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackMenu

  Description :	Fonction qui sera appelée par GLUT lorsqu'un élément 
				est sélectionné à l'intérieur d'un menu.

  Paramètres :
	 int NumMenu : Le numéro du menu qui a été sélectionné.

  Valeur retournée :	void : 

  Par : 2000-12-11 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackMenu(int NumMenu)
{
	ms_arpGlutWnd[glutGetWindow()]->Menu(NumMenu);
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::CallBackKeyboard

  Description :	Fonction qui sera appelée par GLUT lorsque une 
				touche normale est appuyée sur le clavier.

  Paramètres :
	 unsigned char key : La touche appuyée.
	 int x : La position X de la souris.
	 int y : La position Y de la souris.

  Valeur retournée :	void : 

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

  Description :	Fonction qui sera appelée par GLUT lorsqu'une touche 
				spéciale du clavier sera enfoncée (ex : F1)

  Paramètres :
	 int key : La touche 
	 int x : La position X de la souris
	 int y : La position Y de la souris

  Valeur retournée :	void : 

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

  Valeur retournée :	Aucune

  Par : 2002-03-04 Jean-Noé Morissette
  MAJ: 
------------------------------------------------------------------*/
void CGlutMaster::CallBackGLUI( int ID )
{
	ms_arpGlutWnd[glutGetWindow()]->GLUI_event( ID );
}


/*------------------------------------------------------------------
  Fonction :	CGlutMaster::timerCallback

  Description :	JNM ANIM

  Valeur retournée :	Aucune

  Par : 2002-03-04 Jean-Noé Morissette
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
