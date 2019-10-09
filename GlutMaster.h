// GlutMaster.h: interface for the CGlutMaster class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GLUTMASTER_
#define _GLUTMASTER_

#include "GlutWindow.h"

// Le nombre maximal de fen�tres glut qui peuvent �tre cr�es
#define MAX_NUMBER_OF_WINDOWS 32 
#define ESCAPE							(27)

/**
 * @class CGlutMaster
 * @brief Definition d'une classe qui s'occupe de la fenetre windows
 *
 * Classe abstraite qui regit les interactions avec le clavier, souris, etc.
 *
 */


class CGlutMaster  
{
public:

	//Fonctions de rappel
	//-------------------

	static void CallBackKeyboard(unsigned char key, int x, int y);
	static void CallBackSpecialKeyboard(int key, int x, int y);
	static void CallBackMenu(int NumMenu);
	static void CallBackReshape(int width, int height);
	static void CallBackMouseMove(int x, int y);
	static void CallBackMouse(int button, int state, int x, int y);
	static void CallBackDisplay();
	static void CallBackGLUI( int ID );  //MODIF GLUI
	static void timerCallback( int ptr );  //MODIF GLUI

	//Fonctions d'Initialisations
	//---------------------------
	static void InitGlut();
	static void StartDisplay();

	//Fonctions pour l'enregistrement de fen�tres
	//-------------------------------------------
	static void RegisterWindow(CGlutWindow& GlutWindow);
	static void UnregisterWindow(CGlutWindow& GlutWindow) {ms_arpGlutWnd[GlutWindow.GetNumeroFen()] = NULL;}
	
private:

	// Le constructeur est priv� puisqu'on ne veut pas que des objets de cette
	// classe soient cr��s.  Tout dans cette classe est statique, donc il n'est pas
	// n�cessaire de ce cr�er des objets de ce type.
	CGlutMaster(){;}
	virtual ~CGlutMaster(){;}


	// Ce tableau contiendra un pointeur � toutes les fen�tres GLUT (CGlutWindow)
	// qui auront �t� enregistr�es au pr�s de Glut Master
	static CGlutWindow* ms_arpGlutWnd[MAX_NUMBER_OF_WINDOWS];
};

#endif