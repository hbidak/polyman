#ifndef _GLUTWINDOW_
#define _GLUTWINDOW_


#include <GL/glut.h>
#include "Point2D.h"
#include "Rectangle.h"
#include "CouleurGL.h"
#include <list>

/**
 * @class CGlutWindow
 * @brief Definition d'une classe qui s'occupe de la fenetre OpenGL
 *
 * Classe abstraite qui regit l'affichage avec Glut et OpenGL.
 *
 */


//Le mode par d�faut dans lequel sont construites les fen�tres.
//-------------------------------------------------------------
#define DEFAULT_MODE GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH

class CGlutWindow  
{
public:
	
	//Construction / destruction
	//--------------------------
	CGlutWindow(const CPoint2D& PosFenetre, const CRectangle& DimFenetre, const CCouleurGL CouleurFond = CCouleurGL(), const char Titre[] = "Fenetre GLUT", unsigned int Mode = DEFAULT_MODE);
	CGlutWindow(CGlutWindow& Parent, const CPoint2D& Position, const CRectangle& Dimension, const CCouleurGL& CouleurFond, int Mode = DEFAULT_MODE);
	virtual ~CGlutWindow();


	//Fonctions virtuelles � surcharger dans les classes d�riv�es
	//pour avoir des fen�tres plus sp�cialis�es.
	//-----------------------------------------------------------

	virtual void Afficher() = 0;
	virtual void ClicSouris(int button, int state, int x, int y);
	virtual void MouseMove(int x, int y) {;}
	virtual void Menu(int NumMenu){;}
	virtual void Clavier(unsigned char Key, int x, int y){;}
	virtual void ClavierSpecial(int Key, int x, int y){;}
	virtual void Reshape(int Width, int Height);

	virtual void GLUI_event( int ID ){;}  // MODIF GLUI

	// Fonctions de r�affichage
	//-------------------------
	void Redraw() const;
	void RedrawAll() const;

	//Fonctions d'acc�s
	//-----------------

	int GetNumeroFen() const {return m_iNumeroFen;}

	void SetDimension(const CRectangle& NouvelleDim);
	void SetCouleurFond(const CCouleurGL& CouleurFond);

	bool BtnGaucheEnfonce() const {return m_bBtnGaucheEnfonce;}
	bool BtnCentreEnfonce() const {return m_bBtnCentreEnfonce;}
	bool BtnDroitEnfonce() const {return m_bBtnDroitEnfonce;}

	static int GetNbGlutWindow() {return ms_iNbGlutWindow;}

	CRectangle GetDimension() const;

protected:
	// La liste des sous-fen�tres qui sont � l'int�rieur de cette fen�tre
	std::list<CGlutWindow*> m_SousFenetres;

	//Le pointeur � la fen�tre parent
	CGlutWindow* m_pParent;
private:

	//Le num�ro de la fen�tre
	int m_iNumeroFen;

	// Pour savoir si le bouton gauche de la souris est enfonc�
	bool m_bBtnGaucheEnfonce;
	bool m_bBtnCentreEnfonce;
	bool m_bBtnDroitEnfonce;

	// Cet variable statique indique le nombre de fen�tres glut 
	// pr�sentement "vivantes"
	static int ms_iNbGlutWindow;
};

#endif