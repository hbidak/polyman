
#include <math.h>
#include "CameraGL.h"
#include "Macros.h"
#include <GL/glut.h>


/*------------------------------------------------------------------
  Fonction :	CCameraGL::CCameraGL

  Description :	Constructeur d'une caméra OpenGL

  Paramètres :
	 const double& DisObs : La distance entre la caméra et le point de vise.
	 const CPoint3D& PtVise : Le point de vise.
	 const double& AngElev : L'angle d'élévation.
	 const double& AngleRot : L'angle de rotation.

  Valeur retournée :	Aucune (constructeur)

  Par : 2001-1-5 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CCameraGL::CCameraGL(const double& DisObs, const CPoint3D& PtVise, const double& AngElev, const double& AngleRot)
{
    m_DistanceObservateur = DisObs;
    m_PointVise = PtVise;
    m_AngleElevation = AngElev;
    m_AngleRotation = AngleRot;
	m_EstAJour = false;
}


/*------------------------------------------------------------------
  Fonction :	CCameraGL::CCameraGL

  Description :	Constructeur copie.

  Paramètres :
	 const CCameraGL& Source : L'objet source.

  Valeur retournée :	Aucune (constructeur) : 

  Par : 2001-1-5 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CCameraGL::CCameraGL(const CCameraGL& Source)
{
    *this = Source;
}



/*------------------------------------------------------------------
  Fonction :	CCameraGL::operator = 

  Description :	Surcharge de l'opérateur d'égalité.

  Paramètres :
	 const CCameraGL& Droite : L'objet source.

  Valeur retournée :	const CCameraGL& : Le résultat.

  Par : 2001-1-5 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
const CCameraGL& CCameraGL::operator = (const CCameraGL& Droite)
{
    if (&Droite != this)
    {
		m_DistanceObservateur = Droite.m_DistanceObservateur;
		m_PointVise = Droite.m_PointVise;
		m_AngleElevation = Droite.m_AngleElevation;
		m_AngleRotation = Droite.m_AngleRotation;
		m_PositionCamera = Droite.m_PositionCamera;
		m_EstAJour = Droite.m_EstAJour;
		m_Up = Droite.m_Up;
    }

    return *this;
}

/*------------------------------------------------------------------
  Fonction :	CCameraGL::PositionnerCamera

  Description :	Permet de positionner la camera en fonction de ses 
				parametres (c'est un gluLookAt deguise)

  Paramètres :

  Valeur retournée :	void : 

  Par : 2001-1-5 Maxime Beaudry
  MAJ: 
  Modifié par:	Céline Haché	2002-01-18
------------------------------------------------------------------*/
/*void CCameraGL::PositionnerCamera()
{
	// Lorsque les paramètres ne sont pas à jour,
	// on doit les recalculer
	//--------------------------------------------

	if (!m_EstAJour)
	{
		// ici on doit utiliser les angles et la distance
		// pour calculer les 3 vecteurs du LookAt

		m_EstAJour = true;
	}

	gluLookAt(0, 0, m_DistanceObservateur, 0, 0, 0, 0, 1, 0);
	//gluLookAt(0,0 , 5, 0, 0, 0, 0, 1, 0);
}*/
void CCameraGL::PositionnerCamera()
{
	// Lorsque les paramètres ne sont pas à jour,
	// on doit les recalculer
	//--------------------------------------------
		
		double doubrote = DEG_TO_RAD(m_AngleRotation);
		double doubeleve= DEG_TO_RAD(m_AngleElevation);
	
	if (!m_EstAJour)
	{
		// ici on doit utiliser les angles et la distance
		// pour calculer les 3 vecteurs du LookAt
		
		//mise a jour du point vise
		//CVecteur Vise(m_PointVise.GetX(),m_PointVise.GetY(),m_PointVise.GetZ());
		//m_PointVise = Vise;
		
		
	
		//mise a jour de la position de la camera
		CPoint3D posvect (m_PointVise.GetX()+m_DistanceObservateur*cos(doubeleve)*cos(doubrote), 
							m_PointVise.GetY()	+ m_DistanceObservateur*cos(doubeleve)*sin(doubrote),
							m_PointVise.GetZ()+ m_DistanceObservateur*sin(doubeleve));
	
		//cout<<"x "<<posvect.GetX()<<" y  "<<posvect.GetY()<<" z "<<posvect.GetZ()<<endl;
		//cout<<"x "<<m_PointVise.GetX()<<" y  "<<m_PointVise.GetY()<<" z "<<m_PointVise.GetZ()<<endl;
		
		m_PositionCamera=posvect;
		cout<<"x "<<m_PositionCamera.GetX()<<" y  "<<m_PositionCamera.GetY()<<" z "<<m_PositionCamera.GetZ()<<endl;
				
		//mise a jour du vecteur m_up
		/*CVecteur Ve  (0,sin(doubeleve),cos(doubeleve));
		m_Up = Ve;*/
	
		CVecteur Ve  (-cos (doubrote),-sin(doubrote),0.0);
		
		CVecteur Nord (0,0,1);
		
		CVecteur Vec_z = Ve.Vectorial(Nord);
		
		CVecteur Regard(m_PositionCamera,m_PointVise);
		
		CVecteur Vec = Vec_z.Vectorial(Regard);

		Vec.Normalize();
		
		m_Up = Vec;

		cout<<"x "<<m_Up.GetX()<<" y  "<<m_Up.GetY()<<" z "<<m_Up.GetZ()<<endl;
	
		m_EstAJour = true;
	}

	gluLookAt(m_PositionCamera.GetX(),m_PositionCamera.GetZ(),m_PositionCamera.GetY(),
					m_PointVise.GetX(),m_PointVise.GetY(),m_PointVise.GetZ(),
					m_Up.GetX(),m_Up.GetZ(),m_Up.GetY());
	

	//gluLookAt(0, 0, m_DistanceObservateur, 0, 0, 0, 0, 1, 0);
}



/*------------------------------------------------------------------
  Fonction :	CCameraGL::SetAngleElevation

  Description :	Permet de modifier l'angle d'élévation.

  Paramètres :
	 double Angle : Le nouvel angle d'élévation.

  Valeur retournée :	void : 

  Par : 2001-1-5 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CCameraGL::SetAngleElevation(double Angle)
{
	m_AngleElevation = Angle;
	m_EstAJour = false;
}


/*------------------------------------------------------------------
  Fonction :	CCameraGL::SetAngleRotation

  Description :	Permet de modifier l'angle de rotation.

  Paramètres :
	 double Angle : Le nouvel angle de rotation.

  Valeur retournée :	void : 

  Par : 2001-1-5 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CCameraGL::SetAngleRotation(double Angle)
{
	m_AngleRotation = Angle;
	m_EstAJour = false;
}


/*------------------------------------------------------------------
  Fonction :	CCameraGL::IncrementerAngleElevation

  Description :	Permet d'incrémenter l'angle d'élévation

  Paramètres :
	 const double Increment : L'incrément de l'angle.

  Valeur retournée :	void : 

  Par : 2000-3-19 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CCameraGL::IncrementerAngleElevation(const double Increment)
{
	SetAngleElevation(m_AngleElevation + Increment);
}

/*------------------------------------------------------------------
  Fonction :	CCameraGL::IncrementerAngleRotation

  Description :	Permet d'incrémenter l'angle de rotation

  Paramètres :
	 const double Increment : L'incrément de l'angle.

  Valeur retournée :	void : 

  Par : 2000-3-19 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CCameraGL::IncrementerAngleRotation(const double Increment)
{
	SetAngleRotation(m_AngleRotation + Increment);
}
