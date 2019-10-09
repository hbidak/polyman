#include "Jonction.h"



Jonction::Jonction(double longueur ,
					   double hauteur,
					   double profondeur,
						double r , 
						double g , 
						double b ): l( longueur ), h (hauteur),p (profondeur),coulr( r ), coulg( g ), coulb( b )
{
	b_connecte=false;
}

Jonction::~Jonction()
{

}

static void dessJonction( GLdouble x, GLdouble y, GLdouble z,
                         GLdouble longueur, GLdouble hauteur , GLdouble profondeur)
{
  // définition d'un objet quadric
   static GLUquadricObj *quadric = NULL;
   // si c'est la première fois alors ...
   if ( quadric == NULL ) quadric = gluNewQuadric( );
   // initialiser l'apparence
   gluQuadricNormals( quadric, GLU_SMOOTH );
   // choisir le style
   glPushMatrix( );
   // le centre de la sphère est à ...
   //glTranslated( x, y, z );

   //glRotated(m_Up.GetTheta()*(180/3.14159265),0,0,1);
   // et hop!
   glBegin (GL_POLYGON);
		glVertex3d (longueur/2,hauteur/2,-profondeur/2);
		glVertex3d (longueur/2,hauteur/2,profondeur/2);
		glVertex3d (longueur/2,-hauteur/2,profondeur/2);
		glVertex3d (longueur/2,-hauteur/2,-profondeur/2);
	glEnd();

	glBegin (GL_POLYGON);
		glVertex3d (-longueur/2,hauteur/2,-profondeur/2);
		glVertex3d (-longueur/2,hauteur/2,profondeur/2);
		glVertex3d (-longueur/2,-hauteur/2,profondeur/2);
		glVertex3d (-longueur/2,-hauteur/2,-profondeur/2);
	glEnd();

	glBegin (GL_POLYGON);
		glVertex3d (longueur/2,hauteur/2,-profondeur/2);
		glVertex3d (longueur/2,hauteur/2,profondeur/2);
		glVertex3d (-longueur/2,hauteur/2,profondeur/2);
		glVertex3d (-longueur/2,hauteur/2,-profondeur/2);
	glEnd();

	glBegin (GL_POLYGON);
		glVertex3d (longueur/2,-hauteur/2,-profondeur/2);
		glVertex3d (longueur/2,-hauteur/2,profondeur/2);
		glVertex3d (-longueur/2,-hauteur/2,profondeur/2);
		glVertex3d (-longueur/2,-hauteur/2,-profondeur/2);
	glEnd();

	glBegin (GL_POLYGON);
		glVertex3d (longueur/2,-hauteur/2,profondeur/2);
		glVertex3d (longueur/2,hauteur/2,profondeur/2);
		glVertex3d (-longueur/2,hauteur/2,profondeur/2);
		glVertex3d (-longueur/2,-hauteur/2,profondeur/2);
	glEnd();

	glBegin (GL_POLYGON);
		glVertex3d (longueur/2,-hauteur/2,-profondeur/2);
		glVertex3d (longueur/2,hauteur/2,-profondeur/2);
		glVertex3d (-longueur/2,hauteur/2,-profondeur/2);
		glVertex3d (-longueur/2,-hauteur/2,-profondeur/2);
	glEnd();
   // revenir à la transformation courante
   glPopMatrix( );
}

void Jonction::Afficher() const
{
	glPushMatrix();
	glTranslated( m_Position.GetX(),m_Position.GetY(),m_Position.GetZ());
    glRotated(angle,0,0,1);

	if(selectionne==false)
	{
		glColor3d( coulr, coulg, coulb );
	}

	if(selectionne==true)
	{
		glColor3d( 0, 0, 1 );
	}

	dessJonction( m_Position.GetX(),m_Position.GetY(),m_Position.GetZ(), l, h, p );
	glPopMatrix( );
}

void Jonction::animer(double dt)
{

}
