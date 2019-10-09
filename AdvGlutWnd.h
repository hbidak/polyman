#ifndef _ADVGLUTWND_
#define _ADVGLUTWND_


#include "Constantes.h"
#include "GlutWindow.h"
#include "CameraGL.h"
#include "TransformationGL.h"
#include "Sphere.h"
#include "CRU.h"
#include "propulsion.h"
#include "jonction.h"




// MODIF GLUI:  Les controles GLUI de l'interface
#define BUTTON_NEWGAME	1002
#define BUTTON_ORTHO	1003

// Constantes pour le mode de la souris
#define MODE_AUCUN 0
#define MODE_TRANSLATION 1
#define MODE_ELASTIQUE_ZOOM_IN 2
#define MODE_ELASTIQUE_ZOOM_OUT 3
#define AJOUTER_SPHERE 4
#define AJOUTER_CUBE 5
#define AJOUTER_CYLINDRE 6
#define AJOUTER_PRISME_RECTANGULAIRE 7
#define AJOUTER_PROPULSION 8
#define AJOUTER_OVI 9
#define DESTRUCTION_OBJET 10
#define TRANSLATION_OBJET 11
#define ROTATION_OBJET 12
#define PROPRIETE_OBJET 13
#define REINITIALISER 14
#define TRAJECTOIRE_OVI 15
#define ZOOM_IN 16
#define ZOOM_OUT 17
#define SELECTION_OBJET 18
#define CHARGER 19
#define	ENREGISTRER 20
#define MODE_JEU 21
#define ARRETER_MODE_JEU 22
#define STOPPER_JEU 23
#define RECOMMENCER_JEU 24
#define DUPLIQUER_STATION 25

#define MODE_CAM    26

/**
 * @class CAdvGlutWnd
 * @brief Definition d'une classe qui s'occupe de la fenetre OpenGL
 *
 * Classe abstraite qui regit l'affichage avec Glut et OpenGL.
 */


class CAdvGlutWnd : public CGlutWindow  
{
public:

	// Construction / destruction
	//---------------------------
	CAdvGlutWnd(const CPoint2D& PosFenetre, const CRectangle& DimFenetre, 
						 const CCouleurGL CouleurFond, const char Titre[], 
						 unsigned int Mode = DEFAULT_MODE);
	CAdvGlutWnd(CGlutWindow& Parent, const CPoint2D& Position, const CRectangle& Dimension, const CCouleurGL& CouleurFond, int Mode = DEFAULT_MODE);
	virtual ~CAdvGlutWnd();

	// Fonctions virtuelles de CGlutWindow qui sont red�finies
	//--------------------------------------------------------

	virtual void Clavier(unsigned char Key, int x, int y);
	virtual void Menu(int NumMenu);
	virtual void Reshape(int Width, int Height);
	virtual void MouseMove(int x, int y);
	virtual void ClicSouris(int button, int state, int x, int y);
	virtual void ClavierSpecial(int Key, int x, int y){;}

	//Fonctions d'acc�s
	//-----------------
	CTransformationGL* GetTransformation() {return m_pTransformation;}
	CCameraGL* GetCamera() {return m_pCamera;}


protected:

	// Fonctions et attributs reli�s au tracage
	// d'un rectangle �lastique en mode XOR
	//-------------------------------------------
	
	void TermineRectangleElastique(const CPoint2D& CoinFinal);
	void MAJRectangleElastique(const CPoint2D& NouveauCoin);
	void InitRectangleElastique(const CPoint2D& PtAncrage);

	//Indique si on est en train de tracer un
	//rectangle �lastique
	bool m_bEnTraceRectangle;

	//les autres variables utilis�es lors du 
	//tracage du rectangle �lastique
	bool m_bDoitActiverDepthTest;
	bool m_bDoitActiverLumiere;

	//Le point fixe du rectangle �lastique
	CPoint2D m_PtAncrage;


	//Les outils qu'utilisent la fen�tre
	//pour �tre plus "�volu�e"
	//----------------------------------


	CCameraGL* m_pCamera;
	CTransformationGL* m_pTransformation;

	//L'�tat de la souris.  Ceci signifie le type
	//d'action que prendra la fen�tre lorsqu'il y 
	//a un �v�nement de souris.  Par exemple, faire
	//un zoom-in lorsqu'on clic dans la fen�tre
	int m_iModeSouris;

	//La position o� �tait le curseur de la souris
	//lors du dern�er �v�nement 
	//ex : d�placement (avec bouton enfonc�), clic, ...)
	CPoint2D m_DernierPtSouris;
	

};

#endif