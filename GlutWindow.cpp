// GlutWindow.cpp: implementation of the CGlutWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "GlutWindow.h"
#include "GlutMaster.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <iostream>

int CGlutWindow::ms_iNbGlutWindow = 0;

/*------------------------------------------------------------------
  Fonction :	CGlutWindow::CGlutWindow

  Description :	Constructeur d'un objet de type CGlutWindow.
				Lorsque celui-ci est appel�, une fen�tre glut est 
				pr�te � �tre utilis�e.

  Param�tres :

	 const CPoint2D& PosFenetre : La position de la fenetre sur l'�cran.
	 const CRectangle& DimFenetre : La dimension de la fenetre.
	 const CCouleurGL CouleurFond : La couleur de fond.
	 const char Titre[] : Le titre de la fen�tre
	 unsigned int Mode : Les modes de l'�cran (voir glutInitDisplayMode)

  Valeur retourn�e :	Aucune (constructeur)
------------------------------------------------------------------*/
CGlutWindow::CGlutWindow(const CPoint2D& PosFenetre, const CRectangle& DimFenetre, 
						 const CCouleurGL CouleurFond, const char Titre[], 
						 unsigned int Mode)
{
	//Il n'y a pas de parent
	m_pParent = NULL;

	m_bBtnGaucheEnfonce = false;
	m_bBtnCentreEnfonce = false;
	m_bBtnDroitEnfonce = false;

	// On initialise le type d'affichage
	glutInitDisplayMode(Mode);

	//On fixe la dimension
	//--------------------

	if ( (DimFenetre.GetLargeur() > 0) && (DimFenetre.GetHauteur() > 0))
		glutInitWindowSize(DimFenetre.GetLargeur(), DimFenetre.GetHauteur());
	else
	{
		std::cout << "La dimension de fenetre est invalide.\n" << endl;
		DimFenetre.imprimer();
		std::cout << "Elle sera initialis�e � (150,150)." << endl;
		glutInitWindowSize( 150, 150 );
	}
	
	//On fixe la position de la fentre
	//--------------------------------
	if ((PosFenetre.GetX() >= 0) && (PosFenetre.GetY() >= 0))
		glutInitWindowPosition(PosFenetre.GetX(), PosFenetre.GetY());
	else
	{
		std::cout << "La position de fentre est invalide." << endl;
		PosFenetre.imprimer();
		cout << "Elle sera initialis�e � (150,150)." << endl;
		glutInitWindowPosition( 150, 150);
	}

	//On cr�e la fen�tre
	m_iNumeroFen = glutCreateWindow(Titre);

	//On enregistre la fenetre aupr�s de Glut Master
	CGlutMaster::RegisterWindow(*this);

	//Appliquer la couleur de fond
	SetCouleurFond(CouleurFond);
	
	//On active le test de profondeur.
	glEnable( GL_DEPTH_TEST );

	ms_iNbGlutWindow++;
}


/*------------------------------------------------------------------
  Fonction :	CGlutWindow::CGlutWindow

  Description :	Constructeur d'une fen�tre GLUT.  

				******************************************
				APPELEZ CE CONSTRUCTEUR QUE POUR CR�ER UNE 
				SOUS-FEN�TRE D'UNE FEN�TRE D�J� EXISTANTE.
				******************************************

  Param�tres :

	 const CGlutWindow& Parent : La fen�tre � l'int�rieur de laquelle se trouvera la fen�tre cr��e
	 const CPoint2D& Position : La position de la fen�tre dans le parent.
	 const CRectangle& Dimension : La dimension de la nouvelle fen�tre.
	 const CCouleurGL& CouleurFond : La couleur de fond.
	 int Mode : Le mode de cr�ation.

  Valeur retourn�e :	Aucune (constructeur) : 
------------------------------------------------------------------*/
CGlutWindow::CGlutWindow(CGlutWindow& Parent, const CPoint2D& Position, const CRectangle& Dimension, const CCouleurGL& CouleurFond, int Mode)
	:m_pParent(&Parent)
{

	// On ajoute la fen�tre qu'on vient de cr�er dans la 
	// liste chain�e de son parent.
	Parent.m_SousFenetres.push_back(this);	
	
	m_bBtnGaucheEnfonce = false;
	m_bBtnCentreEnfonce = false;
	m_bBtnDroitEnfonce = false;

	// On initialise le type d'affichage
	glutInitDisplayMode(Mode);

	//On cr�e la fen�tre
	m_iNumeroFen = glutCreateSubWindow(Parent.GetNumeroFen(), Position.GetX(), Position.GetY(), Dimension.GetLargeur(), Dimension.GetHauteur());

	//On enregistre la fenetre aupr�s de Glut Master
	CGlutMaster::RegisterWindow(*this);

	//Appliquer la couleur de fond
	SetCouleurFond(CouleurFond);
	
	//On active le test de profondeur.
	glEnable( GL_DEPTH_TEST );

	ms_iNbGlutWindow++;
}


/*------------------------------------------------------------------
  Fonction :	CGlutWindow::~CGlutWindow

  Description :	Destructeur d'une fen�tre GLUT.  Tout les enfants
		de cette fen�tre seront d�truits.
------------------------------------------------------------------*/
CGlutWindow::~CGlutWindow()
{
	// On detruit les enfants de cette fen�tre
	int iNbSousFenetre = (int) m_SousFenetres.size();

	for (int iSousFenetre = 0; iSousFenetre < iNbSousFenetre; iSousFenetre++)
	{
		CGlutWindow* pWnd = m_SousFenetres.front();
		delete pWnd;
	}

	// S'il y a un parent, on enleve cette fen�tre de la liste d'enfants du parent
	if (m_pParent != NULL)
		m_pParent->m_SousFenetres.remove(this);

	// On detruit l'objet courant.
	glutDestroyWindow(m_iNumeroFen);
	CGlutMaster::UnregisterWindow(*this);

	ms_iNbGlutWindow--;

	std::cout << "Destruction de la fenetre #" << m_iNumeroFen << endl;
}


/*------------------------------------------------------------------
  Fonction :	CGlutWindow::SetDimension

  Description :	Cette fonction permet de modifier la dimension de la fen�tre.

	sp�cial mb: tester

  Param�tres :
	 const CRectangle& NouvelleDim : La nouvelle dimension

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CGlutWindow::SetDimension(const CRectangle& NouvelleDim)
{
	// On fixe la dimension de la fenetre
	//-----------------------------------

	if ( (NouvelleDim.GetLargeur() > 0) && (NouvelleDim.GetHauteur() > 0))
		glutReshapeWindow(NouvelleDim.GetLargeur(), NouvelleDim.GetHauteur());
	else
	{
		std::cout << "La dimension de fenetre est invalide.\n";
		NouvelleDim.imprimer();
		std::cout << "  Elle sera initialis�e � (150,150)." << endl;
		glutReshapeWindow(150, 150);
	}
}


/*------------------------------------------------------------------
  Fonction :	CGlutWindow::SetCouleurFond

  Description :	Cette fonction permet de modifier la couleur de fond de la fen�tre.

  Param�tres :
	 const CCouleurGL& CouleurFond : La nouvelle couleur de fond.

  Valeur retourn�e :	void : 

  Par : 2000-12-9 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CGlutWindow::SetCouleurFond(const CCouleurGL& CouleurFond)
{
	glClearColor(CouleurFond.GetRed() / 255.0, CouleurFond.GetGreen() / 255.0, CouleurFond.GetBlue() / 255.0, 1.0);
}


/*------------------------------------------------------------------
  Fonction :	CGlutWindow::Redraw

  Description :	Cette fonction permet de r�afficher la fen�tre de 
				laquelle on app�le cette fonction.

  Param�tres :

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CGlutWindow::Redraw() const
{
	glutSetWindow(m_iNumeroFen);
	glutPostRedisplay();
}


/*------------------------------------------------------------------
  Fonction :	CGlutWindow::Reshape

  Description :	Fonction appel�e par Glut Master lorsque cette fen�tre 
				est redimensionn�e.

  Param�tres :
	 int Width : La nouvelle largeur. 
	 int Height : La nouvelle hauteur.

  Valeur retourn�e :	void
------------------------------------------------------------------*/
void CGlutWindow::Reshape(int Width, int Height)
{
	//On ne fait rien dans cette classe
}
 
/*------------------------------------------------------------------
  Fonction :	CGlutWindow::ClicSouris

  Description :	Fonction appel�e par Glut Master lorsqu'on enfonce 
				ou on relache un bouton de la souris.

  Param�tres :
	 int button : Le boutton 
	 int state : L'�tat du bouton (enfonc�,...)
	 int x : La position X de la souris.
	 int y : La position Y de la souris.

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CGlutWindow::ClicSouris(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)		
		m_bBtnGaucheEnfonce = (state == GLUT_DOWN);
	if (button == GLUT_MIDDLE_BUTTON)		
		m_bBtnCentreEnfonce = (state == GLUT_DOWN);
	if (button == GLUT_RIGHT_BUTTON)		
		m_bBtnDroitEnfonce = (state == GLUT_DOWN);
}

/*------------------------------------------------------------------
  Fonction :	CGlutWindow::GetDimension

  Description :	Cette fonction retourne la dimension de la fen�tre.

  Param�tres :

  Valeur retourn�e :	CRectangle : La dimension de la fen�tre.
------------------------------------------------------------------*/
CRectangle CGlutWindow::GetDimension() const
{
	return CRectangle(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


/*------------------------------------------------------------------
  Fonction :	CGlutWindow::RedrawAll

  Description :	Cette fonction permet de r�afficher la fen�tre pour 
				laquelle on app�le cette fonction ainsi que toutes 
				ses sous-fen�tres.

  Param�tres :

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CGlutWindow::RedrawAll() const
{
	//On r�affiche la fen�tre
	Redraw();

	//On r�affiche les enfants
	std::list<CGlutWindow*>::const_iterator DernierFils = m_SousFenetres.end();
	
	for (std::list<CGlutWindow*>::const_iterator FilsCourant = m_SousFenetres.begin(); FilsCourant != DernierFils; FilsCourant++)
		(*FilsCourant)->Redraw();

	//On remets l'objet courant comme fen�tre courante
	glutSetWindow(m_iNumeroFen);
}