// ObjetGL.cpp: implementation of the CObjetGL class.
//
//////////////////////////////////////////////////////////////////////

#include "ObjetGL.h"
#include <math.h>


/*------------------------------------------------------------------
  Fonction :	CObjetGL::CObjetGL

  Description :	Constructeur paramétré (et aussi par défaut) d'un objet 
				de type CObjetGL

  Paramètres :
	 CPoint3D Pos : La position de l'objet.
	 double AngleX : Son angle de rotation en X.
	 double AngleY : Son angle de rotation en Y
	 double AngleZ : Son angle de rotation en Z
	 double EchelleX : Son échelle en X
	 double EchelleY : Son échelle en Y
	 double EchelleZ : Son échelle en Z

  Valeur retournée :	Aucune (constructeur)

  Par : 2000-3-27 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CObjetGL::CObjetGL(CPoint3D Pos, CVecteur Direction, CVecteur Up,
				   double EchelleX, double EchelleY, double EchelleZ)
{
	m_Position = Pos;
	m_Direction = Direction;
	m_Up = Up;

	m_EchelleX = EchelleX;
	m_EchelleY = EchelleY;
	m_EchelleZ = EchelleZ;

	m_DisplayList = 0;
}


/*------------------------------------------------------------------
  Fonction :	CObjetGL::~CObjetGL

  Description :	Destructeur

  Par : 2001-1-5 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CObjetGL::~CObjetGL()
{

}

/*------------------------------------------------------------------
  Fonction :	CObjetGL::CObjetGL

  Description :	Constructeur copie d'un objet de type CObjetGL.

  Paramètres :
	 const CObjetGL & Source : L'objet à copier (la source)

  Valeur retournée :	Aucune (constructeur)

  Par : 2000-3-27 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CObjetGL::CObjetGL(const CObjetGL & Source)
{
	m_DisplayList = 0;
	*this = Source;
}


/*------------------------------------------------------------------
  Fonction :	CObjetGL::operator=

  Description :	Sucharge de l'opérateur d'égalité pour la classe CObjetGL.

  Paramètres :
	 const CObjetGL & Droite : L'objet à droite de l'égalité.

  Valeur retournée :	const CObjetGL& : Le résultat de l'égalité.

  Par : 2000-3-27 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
const CObjetGL& CObjetGL::operator=(const CObjetGL & Droite)
{
	if (&Droite != this)
	{
		m_Position = Droite.m_Position;
		m_Direction = Droite.m_Direction;
		m_Up = Droite.m_Up;

		m_EchelleX = Droite.m_EchelleX;
		m_EchelleY = Droite.m_EchelleY;
		m_EchelleZ = Droite.m_EchelleZ;

	}

	return *this;
}



/*------------------------------------------------------------------
  Fonction :	CObjetGL::PrepareModelViewMatrix

  Description :	Cette fonction prepare la matrice de transformation 
				en fonction des paramètres de position, de rotation 
				et d'échelle.  Elle fait donc une série de glTranslate,
				glRotate, et glScale.

  Valeur retournée :	void : 

  Par : 2001-1-5 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CObjetGL::PrepareModelViewMatrix() const
{
	//Orientation de l'objet
	double		Matrice[4][4];
	CVecteur	Dir, Left, Up;

	Dir = m_Direction;
	Dir.Normalize();
    
	Left = m_Up.Vectorial(m_Direction);
	Left.Normalize();

    Up = Dir.Vectorial(Left);

	Matrice[0][0] = Dir.GetX();
	Matrice[0][1] = Dir.GetY();
	Matrice[0][2] = Dir.GetZ();
	Matrice[0][3] = 0;

	Matrice[1][0] = Left.GetX();
	Matrice[1][1] = Left.GetY();
	Matrice[1][2] = Left.GetZ();
	Matrice[1][3] = 0;

	Matrice[2][0] = Up.GetX();
	Matrice[2][1] = Up.GetY();
	Matrice[2][2] = Up.GetZ();
	Matrice[2][3] = 0;

	
	Matrice[3][0] = m_Position.GetX();
	Matrice[3][1] = m_Position.GetY();
	Matrice[3][2] = m_Position.GetZ();
	Matrice[3][3] = 1;

	glMultMatrixd((double *) Matrice);

	//Mise à l'échelle
	glScaled(m_EchelleX, m_EchelleY, m_EchelleZ);
	///------------------------------
}


/*------------------------------------------------------------------
  Fonction :	CObjetGL::CreateDisplayList

  Description :	Fonction pour créer le display list de l'objet.  Vous 
				aurez à la coder dans des classes dérivées si vous 
				voulez utiliser des display list. Par défaut, ils ne 
				sont pas utilisés, donc la fonction ne fait rien.

  Valeur retournée :	void : 

  Par : 2001-1-5 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CObjetGL::CreateDisplayList()
{
	
}

void CObjetGL::afficher_propriete() 
{
	cout<<endl;
	cout<<"Type: ";
	
	switch (type)
		{
			case (TYPE_SPHERE):
				cout<<"Sphere";
			break;
	
			case (TYPE_CUBE):
				cout<<"Cube";
			break;

			case (TYPE_CYLINDRE):
				cout<<"Cylindre";
			break;

			case (TYPE_PRISME):
				cout<<"Prisme rectangulaire";
			break;

			case (TYPE_PROPULSION):
				cout<<"Cone";
			break;

			case (TYPE_OVI):
				cout<<"Ovi";
			break;
		}	

	cout<<endl;
	cout<<"POSITION: ("<<m_Position.GetX()<<","<<m_Position.GetY()<<","<<m_Position.GetZ()<<")";
	cout<<endl;
	cout<<"DIMENSION DE L'AIRE DE SELECTION: ("<<m_Largeur*2<<","<<m_Hauteur*2<<")";
	cout<<endl;
}


/*
void CObjetGL::SetCouleur (double coulr,double coulg, double coulb)
{
	switch (type)
		{
			case (1):
				cout<<"Sphere";
			break;
	
			case (2):
				cout<<"Cube";
			break;

			case (3):
				cout<<"Cylindre";
			break;

			case (4):
				cout<<"Prisme rectangulaire";
			break;

			case (5):
				cout<<"Cone";
			break;

			case (6):
				cout<<"Ovi";
			break;
		}	

}
*/

/*
void CObjetGL::imprimer_objet() 
{
	FicSortie.open("enregistrement.txt");
	if(FicSortie.fail())
		cout<<"Probleme d'ouverture du fichier d'enregistrement";


	FicSortie<<endl;
	FicSortie<<"Type: ";
	
	switch (type)
		{
			case (TYPE_SPHERE):
				FicSortie<<"Sphere";
			break;
	
			case (TYPE_CUBE):
				FicSortie<<"Cube";
			break;

			case (TYPE_CYLINDRE):
				FicSortie<<"Cylindre";
			break;

			case (TYPE_PRISME):
				FicSortie<<"Prisme rectangulaire";
			break;

			case (TYPE_PROPULSION):
				FicSortie<<"Cone";
			break;

			case (TYPE_OVI):
				FicSortie<<"Ovi";
			break;
		}	

	FicSortie<<endl;
	FicSortie<<"POSITION: ("<<m_Position.GetX()<<","<<m_Position.GetY()<<","<<m_Position.GetZ()<<")";
	FicSortie<<endl;
	FicSortie<<"DIMENSION DE L'AIRE DE SELECTION: ("<<m_Largeur*2<<","<<m_Hauteur*2<<")";
	FicSortie<<endl;
}
*/