#ifndef _HEADER_Transformation_GL_H_
#define _HEADER_Transformation_GL_H_

class CPoint2D;
class CAdvGlutWnd;
class CPlan3D;
class CPoint3D;

/**
 * @class CTransformationGL
 * @brief Definition d'une classe controler la fenetre virtuelle
 *
 * Définition de la classe TransformationGL qui s'occupe des modifications
 * de la fenetre virtuelle (zoom, pan, rotation
 */

class CTransformationGL
{
public:

	// Construction / destruction
	//---------------------------

	CTransformationGL(	CAdvGlutWnd & Parent, double xmin, double xmax,
						double ymin, double ymax, double zNear, double zFar,
						double incr_zoom = 2);
	virtual ~CTransformationGL(){;}


	//Fonctions pour faire des zooms
	//------------------------------

	void ZoomOut(const CPoint2D& Coin1, const CPoint2D& Coin2);
	void ZoomIn(const CPoint2D& Coin1, const CPoint2D & Coin2);
	void ZoomOut(const CPoint2D& PtClic);
	void ZoomIn(const CPoint2D& PtClic);
	void ZoomIn( void );
	void ZoomOut( void );


	//Fonctions de manipulation de la fenêtre virtuelle
	//-------------------------------------------------

	void CentrerSurPt(const CPoint2D& PtCentre, const bool MAJFenetre = true);
	void TranslateFenetre(const CPoint2D& PtPrecedent, const CPoint2D& PtCourant);
	void DeplacerFenetre(const double & DeplEnX, const double & DeplEnY);
	void MettreAJourFenetre();
	void MettreAJourCloture();
	void AjusterFenetre();
	void AppliquerFenetre() const;
	

	//Fonctions de transformations (calcul)
	//-------------------------------------

	void TransformerEnAffichage( double x, double y, int& i, int& j ) const;
	void TransformerEnVirtuel( int i, int j, double& x_virt, double& y_virt ) const;
	bool TransformerEnVirtuel(int x, int y, const CPlan3D& PlanCoupe, CPoint3D &PtVirt) const;


	//Type enum représentant les types de projection possibles.
	//---------------------------------------------------------
	enum TypeProjection {Orthogonale, Perspective};

	//Fonctions d'accès
	//-----------------


	void GetFenetreVirtuelle( double& xmin, double& xmax, double& ymin, double& ymax ) const {xmin = m_xMinFen; xmax = m_xMaxFen; ymin = m_yMinFen; ymax = m_yMaxFen;}
	void GetCloture( int& imin, int& imax, int& jmin, int& jmax ) const {imin = m_xMinCloture; imax = m_xMaxCloture; jmin = m_yMinCloture; jmax = m_yMaxCloture;}
	void SetFenetreVirtuelle( double xmin, double xmax, double ymin, double ymax );
	void SetCloture( int imin, int imax, int jmin, int jmax );
	void SetIncrementZoom( double n_incr ) {m_IncrementZoom = n_incr;}
	double GetIncrementZoom() const {return m_IncrementZoom;}
	TypeProjection GetProjection() const {return m_Projection;}
	void SetProjection(TypeProjection Proj) {m_Projection = Proj;}
	void SetZNear(const double zNear) {m_zNear = zNear;}
	double GetZNear() const {return m_zNear;}
	void SetZFar(const double zFar) {m_zFar = zFar;}
	double GetZFar() const {return m_zFar;}

private:

	//Délimite l'avant et l'arrière du volume de visualisation
	double m_zFar, m_zNear;
	
	//La fenêtre GL auquelle la transformation est associée
	CAdvGlutWnd& m_FenParent;

	//Les bornes de la fenêtre virtuelle
	double m_xMinFen, m_xMaxFen, m_yMinFen, m_yMaxFen;

	//Les bornes de la cloture d'affichage
	int m_xMinCloture, m_xMaxCloture, m_yMinCloture, m_yMaxCloture;

	//L'increment de zoom
	double m_IncrementZoom;

	//Le type de projection actuellement employé
	TypeProjection m_Projection;

protected:

	//Fonction utilitaire interne
	void GetMinMaxRectangle(const CPoint2D& Coin1, const CPoint2D& Coin2, double& xMin, double &xMax, double &yMin, double &yMax, int &xMinAff, int &xMaxAff, int & yMinAff, int & yMaxAff);
};

#endif
