
#include "AdvGlutWnd.h"
#include "TransformationGL.h"
#include <GL/glut.h>
#include "Plan3D.h"
#include "Droite3D.h"


/*---------------------------------------------------------------------------
 * FONCTION: CTransformationGL
 * CLASSE  : CTransformationGL
 *
 * Constructeur d'une transformation GL
 * 
 * ENTREES : fen : la fenetre opengl sur laquelle il effectuera des transformations
 *           xmin, xmax, ymin, ymax : les bornes initiale de la fenetre virtuelle
 *           incr_zoom : l'increment qui sera utilise lors des zoom-in, zoom-out
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
CTransformationGL::CTransformationGL( CAdvGlutWnd& Parent, 
                                    double xmin, double xmax, double ymin, double ymax, 
									double zNear, double zFar,
                                    double incr_zoom)
   : m_xMinFen(xmin), m_xMaxFen(xmax), m_yMinFen(ymin), m_yMaxFen(ymax),
     m_IncrementZoom( incr_zoom ),
	 m_FenParent(Parent)
{
	m_zNear = zNear;
	m_zFar = zFar;
	m_Projection = Orthogonale;
}

/*---------------------------------------------------------------------------
 * FONCTION: changerCloture
 * CLASSE  : CTransformationGL
 *
 * Permet de changer la cloture de la transformation
 * 
 * ENTREES : imin, imax, jmin, jmax : les nouvelles limites de la cloture
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
void CTransformationGL::SetCloture( int imin, int imax, int jmin, int jmax )
{
   m_xMinCloture = imin;
   m_xMaxCloture = imax;
   m_yMinCloture = jmin;
   m_yMaxCloture = jmax;
}

/*---------------------------------------------------------------------------
 * FONCTION: changerFenetreVirtuelle
 * CLASSE  : CTransformationGL
 *
 * Permet de changer la fenetre virtuelle
 * 
 * ENTREES : xmin, xmax, ymin, ymax : les nouvelles bornes de la fenetre virtuelle
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
void CTransformationGL::SetFenetreVirtuelle( double xmin, double xmax, double ymin, double ymax )
{
   m_xMinFen = xmin;
   m_xMaxFen = xmax;
   m_yMinFen = ymin;
   m_yMaxFen = ymax;
}

/*---------------------------------------------------------------------------
 * FONCTION: zoomIn
 * CLASSE  : CTransformationGL
 *
 * Permet de faire un zoom in selon l'increment de zoom
 * 
 * ENTREES : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
void CTransformationGL::ZoomIn()
{
	double changementx;
	double changementy;

	changementx=0.1*(m_xMaxFen-m_xMinFen);
	changementy=0.1*(m_yMaxFen-m_yMinFen);

	m_xMinFen = m_xMinFen+changementx;
	m_xMaxFen = m_xMaxFen-changementx;
	m_yMinFen = m_yMinFen+changementy;
	m_yMaxFen = m_yMaxFen-changementy;

		AjusterFenetre();
		MettreAJourFenetre();
}



/*---------------------------------------------------------------------------
 * FONCTION: zoomOut
 * CLASSE  : CTransformationGL
 *
 * Permet de faire un zoom out selon l'increment de zoom
 * 
 * ENTREES : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
void CTransformationGL::ZoomOut()
{
	double changementx;
	double changementy;

	changementx=0.1*(m_xMaxFen-m_xMinFen);
	changementy=0.1*(m_yMaxFen-m_yMinFen);

	m_xMinFen = m_xMinFen-changementx;
	m_xMaxFen = m_xMaxFen+changementx;
	m_yMinFen = m_yMinFen-changementy;
	m_yMaxFen = m_yMaxFen+changementy;

		AjusterFenetre();

		MettreAJourFenetre();
}

/*---------------------------------------------------------------------------
 * FONCTION: mettreAJourFenetre
 * CLASSE  : CTransformationGL
 *
 * Cette fonction dit a la fenetre OpenGL quelle est la fenetre virtuelle qu'elle
 * doit afficher.  Dans cette fonction, on se mets en mode de projection, on charge
 * la matrice identité, on applique la matrice et on se remets en model view.
 * 
 * ENTREES : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
void CTransformationGL::MettreAJourFenetre()
{      
   glMatrixMode( GL_PROJECTION );
 
   glLoadIdentity();

   AppliquerFenetre();

   glMatrixMode( GL_MODELVIEW );

}

/*---------------------------------------------------------------------------
 * FONCTION: mettreAJourCloture
 * CLASSE  : CTransformationGL
 *
 * Fonction qui dit a la fenetre OpenGL dans quelle cloture il devra faire 
 * afficher la fenetre virtuelle
 * 
 * ENTREES : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUNE
 *---------------------------------------------------------------------------*/ 
void CTransformationGL::MettreAJourCloture()
{
	glViewport( m_xMinCloture, m_yMinCloture,
				(GLint)(m_xMaxCloture-m_xMinCloture), (GLint)(m_yMaxCloture-m_yMinCloture) );
}

/*---------------------------------------------------------------------------
 * FONCTION: transformerEnAffichage
 * CLASSE  : CTransformationGL
 *
 * Fonction servant a calculer les coordonnees dans l'espace d'affichage
 * d'un point specifie en coordonnees virtuelles.
 *
 * ENTREES : x : coordonnee x du point dans l'espace virtuel
 *           y : coordonnee y du point dans l'espace virtuel
 * SORTIES : i et j : coordonnees du point dans l'espace d'affichage
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
 void CTransformationGL::TransformerEnAffichage( double x, double y, int& i, int& j ) const
{
	double resultatx;
	double resultaty;

	resultatx=double(x-m_xMinFen)/double(m_xMaxFen - m_xMinFen);
	i=resultatx*(m_xMaxCloture-m_xMinCloture);


	resultaty=double(y-m_yMinFen)/double(m_yMaxFen - m_yMinFen);
	j=-(resultaty-1)*(m_yMaxCloture-m_yMinCloture);

}

/*---------------------------------------------------------------------------
 * FONCTION: transformerEnVirtuel
 * CLASSE  : CTransformationGL
 *
 * Fonction servant a calculer les coordonnees dans l'espace virtuelles
 * d'un point specifie en coordonnees d'affichage.
 *
 * ENTREES : i : coordonnee i du point dans l'espace d'affichage
 *           j : coordonnee j du point dans l'espace d'affichage
 * SORTIES : x_virt :coordonnee x du point dans l'espace virtuel
 *           y_virt :coordonnee y du point dans l'espace virtuel
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void CTransformationGL::TransformerEnVirtuel( int i, int j, double& x_virt, double& y_virt ) const
{
	double resultatx;
	double resultaty;

	resultatx=double(i)/double(m_xMaxCloture-m_xMinCloture);
	x_virt=resultatx*(m_xMaxFen - m_xMinFen)+m_xMinFen;

	resultaty=1-(double(j)/double(m_yMaxCloture-m_yMinCloture));
	y_virt =resultaty*(m_yMaxFen - m_yMinFen)+m_yMinFen;

}

/*---------------------------------------------------------------------------
 * FONCTION: ajusterFenetre
 * CLASSE  : CTransformationGL
 *
 * Fonction servant a ajuster les coordonnees d'une fenetre virtuelle en
 * fonction de la cloture de facon a ce que le rapport d'aspect soit
 * respecter.
 *
 * ENTREES : AUCUNES
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. :
 *---------------------------------------------------------------------------*/
void CTransformationGL::AjusterFenetre()
{
  // Les rapports sont sous la forme (largeur / hauteur)
	double RapportCloture = (double)(m_xMaxCloture - m_xMinCloture) / (double)(m_yMaxCloture - m_yMinCloture);
	double RapportFenetre = (m_xMaxFen - m_xMinFen) / (m_yMaxFen - m_yMinFen);


	//Si notre cloture est plus large que notre fenetre
	if (RapportCloture > RapportFenetre)
	{

		//On redimensionne notre fenetre en la faisant plus large
		double NouvelleLargeurFenetre = RapportCloture * (m_yMinFen - m_yMaxFen);

		double PointCentralX = (m_xMaxFen + m_xMinFen)/2;

		m_xMaxFen = PointCentralX + NouvelleLargeurFenetre / 2;
		m_xMinFen = PointCentralX - NouvelleLargeurFenetre / 2;

		//Lorsque la fenetre OpenGL est en creation, cette fonction est appelée avec des valeur
		//aléatoires.  On doit donc faire attention que nos m_xMinFen et m_xMaxFen ne s'inversent pas
		if (m_xMinFen > m_xMaxFen)
		{		
			double temp = m_xMaxFen;
			m_xMaxFen = m_xMinFen;
			m_xMinFen = temp;
		}
	}

	//Si notre fenetre est plus large que notre cloture
	else if (RapportCloture < RapportFenetre)
    {
		//On redimensionne notre fenetre en la faisant plus haute
		double NouvelleHauteurFenetre = (m_xMaxFen - m_xMinFen) / RapportCloture;

		double PointCentralY = (m_yMaxFen + m_yMinFen)/2;
		m_yMaxFen = PointCentralY + NouvelleHauteurFenetre / 2;
		m_yMinFen = PointCentralY - NouvelleHauteurFenetre / 2;

		if (m_yMinFen > m_yMaxFen)
		{
			double temp = m_yMaxFen;
			m_yMaxFen = m_yMinFen;
			m_yMinFen = temp;
		}
	}
}

/*---------------------------------------------------------------------------
 * FONCTION: DeplacerFenetre
 * CLASSE  : CTransformationGL
 *
 * Permet de déplacer la fenetre virtuelle en x et en y
 * 
 * ENTREES : DeplEnX, DeplEnY : les déplacements en x et en y.  Ces valeurs 
 *                              doivent être exprimées en proportion de la 
 *			        fenetre.  Ex : (0.25, 0.0) On se déplace de 
 *			        25% de la fenetre vers la droite.
 * SORTIES : AUCUNES
 * RETOUR  : AUCUN
 * EXCEPT. : AUCUN
 *---------------------------------------------------------------------------*/ 
void CTransformationGL::DeplacerFenetre(const double & DeplEnX, const double & DeplEnY)
{
	double deplacementx;
	double deplacementy;

	deplacementx=(m_xMaxFen-m_xMinFen)*DeplEnX;
	deplacementy=(m_yMaxFen-m_yMinFen)*DeplEnY;

	m_xMaxFen=m_xMaxFen+deplacementx;
	m_xMinFen=m_xMinFen+deplacementx;
	m_yMaxFen=m_yMaxFen+deplacementy;
	m_yMinFen=m_yMinFen+deplacementy;

	MettreAJourFenetre();
}


/*------------------------------------------------------------------
  Fonction :	CTransformationGL::TranslateFenetre

  Description :	Permet de translater la fenêtre virtuelle en fonction de la 
				position de la souris.  

  Paramètres :
	 const CPoint2D & PtPrecedent : La position de la souris correspondant à l'ancienne fenêtre virtuelle.
	 const CPoint2D & PtCourant : La position de la souris correspond à la nouvelle fenêtre.

	=>En fait les deux points définissent un vecteur de déplacement

  Valeur retournée :	void : 

  Par : 2000-3-20 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CTransformationGL::TranslateFenetre(const CPoint2D & PtPrecedent, const CPoint2D & PtCourant)
{
	double deplacementx;
	double deplacementy;
	double x_virt_precedent;
	double y_virt_precedent;
	double x_virt_courant;
	double y_virt_courant;

	//PtPrecedent.imprimer();
	TransformerEnVirtuel( PtPrecedent.GetX(), PtPrecedent.GetY(), x_virt_precedent, y_virt_precedent);
	TransformerEnVirtuel( PtCourant.GetX(), PtCourant.GetY(),x_virt_courant, y_virt_courant);

	deplacementx=(x_virt_precedent-x_virt_courant)/(m_xMaxFen-m_xMinFen);
	deplacementy=(y_virt_precedent-y_virt_courant)/(m_yMaxFen-m_yMinFen);
	//cout<<"precedent"<<x_virt_precedent<<" " <<y_virt_precedent;
	//cout<<"courant"<<x_virt_courant<<" " << y_virt_courant;
	//cout<<"deplacement"<<deplacementx<<","<<deplacementy;

	DeplacerFenetre(deplacementx, deplacementy);

}


/*------------------------------------------------------------------
  Fonction :	CTransformationGL::ZoomIn et ZoomOut

  Description :	Permet de zoomer sur un point de l'écran 

  Paramètres :
	 const CPoint2D & PtClic : Le point sur lequel on veut zoomer (en coordonnées d'affichage)

  Valeur retournée :	void : 

  Par : 2000-3-20 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CTransformationGL::ZoomIn(const CPoint2D & PtClic)
{
	CentrerSurPt(PtClic, false);
	ZoomIn();
}

void CTransformationGL::ZoomOut(const CPoint2D & PtClic)
{
	CentrerSurPt(PtClic, false);
	ZoomOut();
}

/*------------------------------------------------------------------
  Fonction :	CTransformationGL::CentrerSurPt

  Description :	Permet de centrer la fenêtre virtuelle sur un point de l'écran.

  Paramètres :
	 const CPoint2D & PtCentre : Le point sur lequel on doit centrer (en coord d'affichage)
	 const bool MAJFenetre : true-> on met à jour la fenêtre virtuelle.

  Valeur retournée :	void : 

  Par : 2000-3-20 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CTransformationGL::CentrerSurPt(const CPoint2D & PtCentre, const bool MAJFenetre)
{

}

/*------------------------------------------------------------------
  Fonction :	CTransformationGL::ZoomIn

  Description :	Permet de faire un zoom in sur un rectangle déterminé 
				par deux coins.  La fenêtre résultante est ajustée.

  Paramètres :
	 const CPoint2D & Coin1 : Le premier coin.
	 const CPoint2D & Coin2 : Le deuxième coin.

  Valeur retournée :	void : 

  Par : 2000-3-20 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CTransformationGL::ZoomIn(const CPoint2D & Coin1, const CPoint2D & Coin2)
{
	double Coin1_x;
	double Coin1_y;
	double Coin2_x;
	double Coin2_y;


	TransformerEnVirtuel( Coin1.GetX(), Coin1.GetY(), Coin1_x, Coin1_y );
	TransformerEnVirtuel( Coin2.GetX(), Coin2.GetY(), Coin2_x, Coin2_y );

	if (Coin1_x < Coin2_x && Coin1_y < Coin2_y)
	{
		SetFenetreVirtuelle( Coin1_x, Coin2_x, Coin1_y, Coin2_y );
	}

	if (Coin1_x > Coin2_x && Coin1_y > Coin2_y)
	{
		SetFenetreVirtuelle( Coin2_x, Coin1_x, Coin2_y, Coin1_y );
	}

	if (Coin1_x < Coin2_x && Coin1_y > Coin2_y)
	{
		SetFenetreVirtuelle( Coin1_x, Coin2_x, Coin2_y, Coin1_y );
	}

	if (Coin1_x > Coin2_x && Coin1_y < Coin2_y)
	{
		SetFenetreVirtuelle( Coin2_x, Coin1_x, Coin1_y, Coin2_y );
	}
	
	//cout<<m_xMaxFen<<" "<<m_xMinFen<<" "<<m_yMaxFen<<" "<<m_yMinFen<<endl;

	AjusterFenetre();
	MettreAJourFenetre();

}


/*------------------------------------------------------------------
  Fonction :	CTransformationGL::ZoomOut

  Description :	Permet de faire un zoom out sur un rectangle délimité par deux points.

  Paramètres :
	 const CPoint2D & Coin1 : Le premier coin du rectangle
	 const CPoint2D & Coin2 : Le deuxième coin.

  Valeur retournée :	void : 

  Par : 2000-3-22 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CTransformationGL::ZoomOut(const CPoint2D & Coin1, const CPoint2D & Coin2)
{
	double longueur1;
	double longueur2;
	double longueur3;
	double longueurtotal;
	double hauteur1;
	double hauteur2;
	double hauteur3;
	double hauteurtotal;
	double augmentationx;
	double augmentationy;
	double milieucarre_x;
	double milieucarre_y;
	double deplacement_x;
	double deplacement_y;

	longueur1=abs(Coin1.GetX()-Coin2.GetX());
	longueur2=m_xMaxCloture - m_xMinCloture;
	longueur3=longueur2/longueur1;
	
	hauteur1=abs(Coin1.GetY()-Coin2.GetY());
	hauteur2=m_yMaxCloture - m_yMinCloture;
	hauteur3=hauteur2/hauteur1;

	longueurtotal=longueur3*(m_xMaxFen - m_xMinFen);
	hauteurtotal=hauteur3*(m_yMaxFen - m_yMinFen);

	augmentationx=(longueurtotal-(m_xMaxFen - m_xMinFen))/2;
	augmentationy=(hauteurtotal-(m_yMaxFen - m_yMinFen))/2;

	SetFenetreVirtuelle( m_xMinFen-augmentationx, m_xMaxFen+augmentationx, m_yMinFen-augmentationy, m_yMaxFen+augmentationy );

	if (Coin1.GetX() < Coin2.GetX())
	{
		milieucarre_x=Coin2.GetX()-longueur1/2;
	}

	if (Coin1.GetX() > Coin2.GetX() )
	{
		milieucarre_x=Coin1.GetX()-longueur1/2;
	}

	if (Coin1.GetY() > Coin2.GetY())
	{
		milieucarre_y=Coin1.GetY()-hauteur1/2;
	}

	if (Coin1.GetY() < Coin2.GetY())
	{
		milieucarre_y=Coin2.GetY()-hauteur1/2;
	}

	deplacement_x=-(longueurtotal*((milieucarre_x-longueur2/2)/longueur2))/(m_xMaxFen-m_xMinFen);
	deplacement_y=(hauteurtotal*((milieucarre_y-hauteur2/2)/hauteur2))/(m_yMaxFen-m_yMinFen);

	MettreAJourFenetre();
	AjusterFenetre();

	DeplacerFenetre(deplacement_x, deplacement_y);

	MettreAJourFenetre();

}


/*------------------------------------------------------------------
  Fonction :	CTransformationGL::GetMinMaxRectangle

  Description :	Permet d'obtenir les minimums et les maximums (en virtuel 
				et en affichage) d'un rectangle délimité par deux coins.

  Paramètres :
	 const CPoint2D & Coin1 : Un coin du rectangle.
	 const CPoint2D & Coin2 : Un deuxième coin.
	 double & xMin : Le x minimal, en virtuel, du rectangle.
	 double & xMax : Le x maximal, en virtuel, du rectangle.
	 double & yMin : Le y minimal, en virtuel, du rectangle.
	 double & yMax : Le y maximal, en virtuel, du rectangle.
	 int &xMinAff : La borne gauche du rectangle (en affichage).
	 int &xMaxAff : La borne doite du rectangle (en affichage).
	 int & yMinAff : Le y minmal du rectangle (en affichage).
	 int & yMaxAff : Le y maximal du rectangle (en affichage).

  Valeur retournée :	void : 

  Par : 2000-3-22 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CTransformationGL::GetMinMaxRectangle(const CPoint2D & Coin1, const CPoint2D & Coin2, double & xMin, double & xMax, double & yMin, double & yMax, int &xMinAff, int &xMaxAff, int & yMinAff, int & yMaxAff)
{
	//On prends comme standard que "Lache" = Coin1 et "Clic" = Coin2
	//Ou on a lache la souris
	double xLacheVirt, yLacheVirt;
	double xClicVirt, yClicVirt;
	TransformerEnVirtuel(Coin1.GetX(), Coin1.GetY(), xLacheVirt, yLacheVirt);
	TransformerEnVirtuel(Coin2.GetX(), Coin2.GetY(), xClicVirt, yClicVirt);


	//Déterminer les bornes min et max en x et en y
	//---------------------------------------------

	if (xClicVirt < xLacheVirt)
	{
		xMin = xClicVirt;
		xMinAff = Coin2.GetX();
		xMax = xLacheVirt;
		xMaxAff = Coin1.GetX();
	}
	else
	{
		xMin = xLacheVirt;
		xMinAff = Coin1.GetX();
		xMax = xClicVirt;
		xMaxAff = Coin2.GetX();
	}
	if (yClicVirt < yLacheVirt)
	{
		yMin = yClicVirt;
		yMinAff = Coin2.GetY();
		yMax = yLacheVirt;
		yMaxAff = Coin1.GetY();
	}
	else
	{
		yMin = yLacheVirt;
		yMinAff = Coin1.GetY();
		yMax = yClicVirt;
		yMaxAff = Coin2.GetY();
	}
}


/*------------------------------------------------------------------
  Fonction :	CTransformationGL::AppliquerFenetre

  Description :	Cette fonction permet d'appliquer la fenêtre virtuelle 
				selon le type de projection et les propriétés de la fenêtre.

  Paramètres :

  Valeur retournée :	void : 

  Par : 2001-1-4 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CTransformationGL::AppliquerFenetre() const
{
	//cout<<"dans appliquer fenetre"<<endl;
	if (m_Projection == Orthogonale)
	{
		cout << "gl ortho" << m_zNear<<" "<<m_zFar<<endl;  
		glOrtho( m_xMinFen, m_xMaxFen, m_yMinFen, m_yMaxFen,m_zNear, m_zFar);
	}

	else
	{
		cout << "gl frustum" << m_zNear<<" "<<m_zFar<<endl;  
	//	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
		glFrustum(m_xMinFen, m_xMaxFen, m_yMinFen, m_yMaxFen,m_zNear, m_zFar);
		//glFrustum(m_xMinFen, m_xMaxFen, m_yMinFen, m_yMaxFen,1, 100);
	}
}

/*------------------------------------------------------------------
  Fonction :	CTransformationGL::TransformerEnVirtuel

  Description :	Cette fonction permet de transformer un point (donné en coordonnée 
				d'affichage) en coordonnées virtuelles étant donné un certain 
				plan sur lequel doit se trouver le point.

  Paramètres :
	 int x : La position X du point en coorodnnée d'affichage.
	 int y : La position Y du point en coorodnnée d'affichage.
	 const CPlan3D& PlanCoupe : Le plan sur lequel on veut trouver 
								la position correspondante en virtuel.
	 CPoint3D &PtVirt : Le point virtuel résultant.

  Valeur retournée :	bool : false => il est impossible de convertir le point en virtuel puisque le plan est parallèle à la direction de la caméra.

  Par : 2001-1-9 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
bool CTransformationGL::TransformerEnVirtuel(int x, int y, const CPlan3D& PlanCoupe, CPoint3D &PtVirt) const
{

	return false;   

}


/*------------------------------------------------------------------
  Fonction :	CTransformationGL::Proportion_Rotation

  Description :	Cette fonction permet de transformer un point (donné en coordonnée 
				d'affichage) en coordonnées virtuelles étant donné un certain 
				plan sur lequel doit se trouver le point.

  Paramètres :
	 int x : La position X du point en coorodnnée d'affichage.
	 int y : La position Y du point en coorodnnée d'affichage.
	 const CPlan3D& PlanCoupe : Le plan sur lequel on veut trouver 
								la position correspondante en virtuel.
	 CPoint3D &PtVirt : Le point virtuel résultant.

  Valeur retournée :	bool : false => il est impossible de convertir le point en virtuel puisque le plan est parallèle à la direction de la caméra.

  Par : 2001-1-9 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
