#include "Principale.h"
#include "Constantes.h"


CFenetrePrincipale::CFenetrePrincipale( const CPoint2D& PosFenetre,
									    const CRectangle& DimFenetre,
										const CCouleurGL CouleurFond )
				   :CAdvGlutWnd( PosFenetre, DimFenetre,
								 CouleurFond, TITRE_FENETRE_PRINCIPALE )
{
}

CFenetrePrincipale::CFenetrePrincipale( CGlutWindow& Parent, const CPoint2D& PosFenetre,
						    const CRectangle& DimFenetre, const CCouleurGL CouleurFond )
			 :CAdvGlutWnd( Parent, PosFenetre, DimFenetre, CouleurFond )
{

	// Se donner une fenêtre virtuelle par défaut de dimension commode.
	m_pTransformation->SetFenetreVirtuelle( 0.0, 10.0, 0.0, 10.0 );

}


CFenetrePrincipale::~CFenetrePrincipale()
{
}

void CFenetrePrincipale::Afficher()
{
	const char charTitre[] = CHARTITRE;
	
	// On efface l'ancienne vue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//On prépare la matrice de modélisation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m_pCamera->PositionnerCamera();
	
	// Écrire le nom des fenêtres
	double xmin,xmax,ymin,ymax,x,y,len;
	int i;
	int xmin1,xmax1,ymin1,ymax1;

	// Pas très élégant...
	m_pTransformation->GetFenetreVirtuelle( xmin, xmax, ymin, ymax );
	m_pTransformation->GetCloture( xmin1, xmax1, ymin1, ymax1 );

	y = -(ymin + (ESPACEMENT_FENETRE-3)*(ymax-ymin)/(double)(ymax1-ymin1));
	len = ((double)glutBitmapLength (GLUT_BITMAP_HELVETICA_12, (unsigned char*)charTitre ))*(xmax-xmin)/(double)(xmax1-xmin1);
	
	x = xmin + ((xmax-xmin)/2.0) - (len / 2.0);
	
	glRasterPos2f(x, y);
	for ( i=0; i < (int)strlen(charTitre) ; i++ )
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, charTitre[i]);

	//On permute le front et le back buffer.
	glutSwapBuffers();
}

void CFenetrePrincipale::ClicSouris(int button, int state, int x, int y)
{
}

void CFenetrePrincipale::Menu(int NumMenu)
{

}


void CFenetrePrincipale::Clavier(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'j':
	case 'J':
			//MessageBox( NULL, "Impossible de passer au mode jeu", "Erreur", MB_ICONEXCLAMATION|MB_OK|MB_TASKMODAL );
		break;
	case '-':
		break;
	}
}

void CFenetrePrincipale::Reshape(int Width, int Height)
{
	CAdvGlutWnd::Reshape( Width, Height );

	//On réaffiche les enfants
	std::list<CGlutWindow*>::const_iterator FilsCourant = m_SousFenetres.begin();

	int iSubWidth = Width-ESPACEMENT_FENETRE*2;
	int iSubHeight = Height-ESPACEMENT_FENETRE*2;
		
	glutSetWindow( (*FilsCourant)->GetNumeroFen() );
	glutPositionWindow(ESPACEMENT_FENETRE, ESPACEMENT_FENETRE);
	glutReshapeWindow(iSubWidth, iSubHeight);

	//On remets l'objet courant comme fenêtre courante
	glutSetWindow(GetNumeroFen());
}