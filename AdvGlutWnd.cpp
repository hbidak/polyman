// AdvGlutWnd.cpp: implementation of the CAdvGlutWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "AdvGlutWnd.h"
#include "TransformationGL.h"
#include "GlutMaster.h"
#include <stdlib.h>

#define DISTANCE_OBS_DEFAUT 20
#define Z_NEAR_DEFAUT 3
#define Z_FAR_DEFAUT 100


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::CAdvGlutWnd

  Description :	Constructeur d'un objet de type CAdvGlutWnd

  Param�tres :
	 const CPoint2D& PosFenetre : La position de la fen�tre.
	 const CRectangle& DimFenetre : La dimension de la fen�tre.
	 const CCouleurGL CouleurFond : La couleur de fond.
	 const char Titre[] : Le titre
	 unsigned int Mode : Le mode de la fen�tre.

  Valeur retourn�e :	Aucune (constructeur) : 
------------------------------------------------------------------*/
CAdvGlutWnd::CAdvGlutWnd(const CPoint2D& PosFenetre, const CRectangle& DimFenetre, 
						 const CCouleurGL CouleurFond, const char Titre[], 
						 unsigned int Mode)
						 :CGlutWindow(PosFenetre, DimFenetre, CouleurFond, Titre, Mode)
{
	//On pr�pare la cam�ra
	//--------------------

	m_pCamera = new CCameraGL(DISTANCE_OBS_DEFAUT, CPoint3D(0,0,0), 0, 90);

	//On pr�pare la tranformation
	//---------------------------

	m_pTransformation = new CTransformationGL(*this, -2,2,-2,2, Z_NEAR_DEFAUT, Z_FAR_DEFAUT, 2);
	m_pTransformation->SetCloture(0, GetDimension().GetLargeur(), 0, GetDimension().GetHauteur());
	m_pTransformation->AjusterFenetre();
	m_pTransformation->SetProjection(CTransformationGL::Orthogonale);
	m_pTransformation->MettreAJourCloture();
	m_pTransformation->MettreAJourFenetre();

	//On initialise le mode de la souris
	m_iModeSouris = MODE_AUCUN;

	//Initialisation des indicateurs de zoom rectangle
	m_bDoitActiverDepthTest = false;
	m_bDoitActiverLumiere = false;
	m_bEnTraceRectangle = false;
}


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::CAdvGlutWnd

  Description :	Constructeur d'une SOUS-FEN�TRE Glut.  Celle-ci sera 
				� l'int�rieur d'une fen�tre Glut (parent) pr�alablement 
				construite.

  Param�tres :
	 const CGlutWindow& Parent : La fen�tre Parent.
	 const CPoint2D& Position : La position de la fen�tre � l'int�rieur du parent.
	 const CRectangle& Dimension : La dimension de la fen�tre.
	 const CCouleurGL& CouleurFond : La couleur de fond.
	 int Mode : Le mode de cr�ation de la fen�tre.

  Valeur retourn�e :	Aucune (constructeur) 
------------------------------------------------------------------*/
CAdvGlutWnd::CAdvGlutWnd(CGlutWindow& Parent, const CPoint2D& Position, const CRectangle& Dimension, const CCouleurGL& CouleurFond, int Mode)
:CGlutWindow(Parent, Position, Dimension, CouleurFond, Mode)
{
	//On pr�pare la cam�ra
	//--------------------

	m_pCamera = new CCameraGL(DISTANCE_OBS_DEFAUT, CPoint3D(0,0,0), 0, 90);

	//On pr�pare la tranformation
	//---------------------------

	m_pTransformation = new CTransformationGL(*this, -2,2,-2,2, Z_NEAR_DEFAUT, Z_FAR_DEFAUT, 2);
	m_pTransformation->SetCloture(0, GetDimension().GetLargeur(), 0, GetDimension().GetHauteur());
	m_pTransformation->AjusterFenetre();
	m_pTransformation->SetProjection(CTransformationGL::Orthogonale);
	m_pTransformation->MettreAJourCloture();
	m_pTransformation->MettreAJourFenetre();

	//On initialise le mode de la souris
	//sp�cial mb
	m_iModeSouris = MODE_AUCUN;

	//Initialisation des indicateurs de zoom rectangle
	m_bDoitActiverDepthTest = false;
	m_bDoitActiverLumiere = false;
	m_bEnTraceRectangle = false;
}


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::~CAdvGlutWnd

  Description :	Destructeur
------------------------------------------------------------------*/
CAdvGlutWnd::~CAdvGlutWnd()
{
	//On d�salloue la m�moire
	delete m_pCamera;
	delete m_pTransformation;
	m_pCamera = NULL;
	m_pTransformation = NULL;
}

/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::ClicSouris

  Description :	Fonction appel�e par Glut Master lorsqu'on clic avec 
				la souris � l'int�rieur de la fen�tre.

  Param�tres :
	 int button : Le boutton sur lequel il y a un �v�nement.
	 int state : L'�tat du bouton (enfonc�...)
	 int x : La position X de la souris.
	 int y : La position Y de la souris.

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CAdvGlutWnd::ClicSouris(int button, int state, int x, int y) 
{
	CGlutWindow::ClicSouris(button, state, x, y);

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
		}
		else //on relache le bouton
		{
		}
	}

	m_DernierPtSouris = CPoint2D(x,y);
}


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::MouseMove

  Description :	Fonction appel�e par Glut Master lorsque la souris se d�place.

  Param�tres :
	 int x : La position X de la souris.
	 int y : La position Y de la souris.

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CAdvGlutWnd::MouseMove(int x, int y)
{
	/*if (BtnGaucheEnfonce())
	{
		switch (m_iModeSouris)
		{
		default:
			break;
		}
	}*/

	m_DernierPtSouris = CPoint2D(x,y);
}


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::InitRectangleElastique

  Description :	Fonctions pour initialiser l'affichage d'un rectangle 
				�lastique en mode XOR.

  Param�tres :
	 const CPoint2D &PtAncrage : Le point fixe du rectangle.

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CAdvGlutWnd::InitRectangleElastique(const CPoint2D &PtAncrage)
{
	
	//cout<<"ici"<<endl;
	//PtAncrage.imprimer();
	m_bEnTraceRectangle = true;

	//On d�sactive l'�clairage et le test de profondeur
	
	m_bDoitActiverDepthTest = (glIsEnabled(GL_DEPTH_TEST) == GL_TRUE);
	glDisable(GL_DEPTH_TEST);

	m_bDoitActiverLumiere = (glIsEnabled(GL_LIGHTING) == GL_TRUE);
	glDisable(GL_LIGHTING);


	GLint Cloture [4];
	m_PtAncrage = PtAncrage; // position du coin fixe du rectangle
	m_DernierPtSouris = m_PtAncrage;   // position du coin mobile du rectangle

	
	// Sauver les attributs de tracage
	glPushAttrib (GL_LINE_BIT | GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT);

	// Sauver la transformation virtuelle->affichage
	glMatrixMode ( GL_MODELVIEW );
	glPushMatrix ();
	glLoadIdentity ();
	glMatrixMode ( GL_PROJECTION );
	glPushMatrix ();

	// Initialiser la matrice 1 pixel = 1 unite virtuelle
	glLoadIdentity () ;
	glGetIntegerv ( GL_VIEWPORT, Cloture);
	gluOrtho2D ( 0.0, (GLdouble) Cloture[2] , (GLdouble) Cloture[3], 0.0 );

	// On trace le rectangle en pointill�s
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0x3333);

	// Changer le mode de tracage des rectangle, initialiser la couleur et le mode XOR
	glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
	glColor3f ( 1.0, 1.0, 1.0 );
	glEnable ( GL_COLOR_LOGIC_OP );
	glLogicOp ( GL_XOR );

	// Tracer un premier rectanble (un seul point...)
	glRecti ( m_PtAncrage.GetX(), m_PtAncrage.GetY(), m_DernierPtSouris.GetX(), m_DernierPtSouris.GetY());

	// S'arranger pour que le rectangle soit immediatement visible
	glFlush();
	glutSwapBuffers();
}


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::MAJRectangleElastique

  Description :	Cette fonction permet de mettre � jour le rectangle 
				�lastique pr�alablement initialis�.  Celle-ci efface 
				l'ancien rectangle et en trace un nouveau.

  Param�tres :
	 const CPoint2D &NouveauCoin : Le nouveau coin du rectangle.

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CAdvGlutWnd::MAJRectangleElastique(const CPoint2D &NouveauCoin)
{
	//cout<<"ici2"<<endl;
	//NouveauCoin.imprimer();
	//m_DernierPtSouris.imprimer();
	//m_PtAncrage.imprimer();
	//m_DernierPtSouris.imprimer();
	//cout<<endl;

	// Changer le buffer de tracage pour retracer dans le buffer
	// ou a ete trace le rectangle precedent
	glutSwapBuffers();

	// Tracer l'ancien rectangle (ca efface l'ancien rectangle a cause du XOR)
	glRecti ( m_PtAncrage.GetX(), m_PtAncrage.GetY(), m_DernierPtSouris.GetX(), m_DernierPtSouris.GetY());

	// Recuperer la nouvelle position et tracer le nouveau rectangle
	m_DernierPtSouris = NouveauCoin;
	glRecti ( m_PtAncrage.GetX(), m_PtAncrage.GetY(), m_DernierPtSouris.GetX(), m_DernierPtSouris.GetY());

	// S'arranger pour que le nouveau rectangle soit immediatement visible
	glFlush();
	glutSwapBuffers();

}


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::TermineRectangleElastique

  Description :	Cette fonction permet de terminer le tracage du 
				rectangle �lastique.

  Param�tres :
	 const CPoint2D &CoinFinal : Le coin final du rectangle.

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CAdvGlutWnd::TermineRectangleElastique(const CPoint2D &CoinFinal)
{
//	CoinFinal.imprimer();
	glDisable ( GL_COLOR_LOGIC_OP );     /* D�sactiver les op�rations bitblt */

	// Reetablir les attributs initiaux
	glPopAttrib();

	// Reatblir la transformation initiale
	glMatrixMode ( GL_PROJECTION );
	glPopMatrix ();
	glMatrixMode ( GL_MODELVIEW );       /* Remettre l'ancienne transformation de mod�le */
	glPopMatrix ();


	// On ne trace plus en pointill�s
	glDisable(GL_LINE_STIPPLE);
	
	// R�tablissement du depth test et de l'�clairage
	if (m_bDoitActiverDepthTest)
		glEnable(GL_DEPTH_TEST);
	if (m_bDoitActiverLumiere)
		glEnable(GL_LIGHTING);	

	m_bEnTraceRectangle = false;

}


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::Reshape

  Description :	Fonction appel�e par Glut Master lorsque la fen�tre 
				est redimensionn�e.

  Param�tres :
	 int Width : La nouvelle largeur.
	 int Height : La nouvelle hauteur.

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CAdvGlutWnd::Reshape(int Width, int Height)
{
	
	int xmin,xmax,ymin,ymax;	
	int hauteur,largeur;
	double rapportx,rapporty;
	double xmin_virt,xmax_virt,ymin_virt,ymax_virt;

	CGlutWindow::Reshape(Width, Height);
		
	m_pTransformation->GetCloture(xmin,xmax,ymin,ymax);

	largeur=xmax-xmin;
	hauteur=ymax-ymin;

	rapportx=double(Width)/double(largeur);
	rapporty=double(Height)/double(hauteur);

	

	if(rapportx>1 )
	{
		m_pTransformation->GetFenetreVirtuelle(xmin_virt,xmax_virt,ymin_virt,ymax_virt);
		
		m_pTransformation->SetFenetreVirtuelle(xmin_virt,xmax_virt,ymin_virt*(1/rapportx),ymax_virt*(1/rapportx));

	}

	if(rapporty>1)
	{
		m_pTransformation->GetFenetreVirtuelle(xmin_virt,xmax_virt,ymin_virt,ymax_virt);
		
		m_pTransformation->SetFenetreVirtuelle(xmin_virt*(1/rapporty),xmax_virt*(1/rapporty),ymin_virt,ymax_virt);
	}

	m_pTransformation->SetCloture(0, Width, 0, Height);

	m_pTransformation->AjusterFenetre();

	m_pTransformation->MettreAJourCloture();
	
	m_pTransformation->MettreAJourFenetre();


}


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::Menu

  Description :	Fonction appel�e par Glut Master lorsqu'un item d'un 
				menu est s�lectionn�.

  Param�tres :
	 int NumMenu : Le num�ro de l'item s�lectionn� � l'int�rieur du menu.

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CAdvGlutWnd::Menu(int NumMenu)
{

}


/*------------------------------------------------------------------
  Fonction :	CAdvGlutWnd::Clavier

  Description :	Fonction appel�e par Glut Master lorsque un touche 
				du clavier est appuy�e.

  Param�tres :
	 unsigned char Key : La touche sur laquelle on a appuy�.
	 int x : La position X de la souris � ce moment.
	 int y : La position Y de la souris � ce moment.

  Valeur retourn�e :	void : 
------------------------------------------------------------------*/
void CAdvGlutWnd::Clavier(unsigned char Key, int x, int y)
{

}
