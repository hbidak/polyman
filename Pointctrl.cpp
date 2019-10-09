#include "Pointctrl.h"

/**
 *
 * Constructeur de base
 *
 */
CPointCtrl::CPointCtrl()
{
}

/**
 *
 * Constructeur détaillé
 *
 */
CPointCtrl::CPointCtrl(const CVecteur &pos)
{
}

/**
 *
 * Destructeur
 *
 */
CPointCtrl::~CPointCtrl()
{
}

/**
 *
 * Affichage du point de contrôle (à compléter) 
 *
 */
void CPointCtrl::Afficher() const
{
	glPushMatrix(); 		
 	glColor3f(0.9, 0.5, 0.0); glPointSize( 8.f );
	glBegin(GL_POINTS);
	glVertex3d(m_Position.GetX(), m_Position.GetY(), m_Position.GetZ());
	glEnd(); glPointSize( 1.f );
	glPopMatrix();
}


void CPointCtrl::modifierCouleur(double ,double , double )
{
	//TODO
}
