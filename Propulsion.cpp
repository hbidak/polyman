#include "Propulsion.h"
#include "Vecteur.h"
#include "ObjetGL.h"



Propulsion::Propulsion(double rayon ,
					   double hauteur,
						double r , 
						double g , 
						double b ): ra( rayon ), h (hauteur),coulr( r ), coulg( g ), coulb( b )
{

}

Propulsion::~Propulsion()
{

}

static void dessCone( GLdouble x, GLdouble y, GLdouble z,
                         GLdouble rayon, GLdouble hauteur )
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
   //	glRotated(m_Up.GetTheta()*(180/3.14159265),0,0,1);

   glRotated(90,0,1,0);
   // et hop!
   glutSolidCone( rayon, hauteur, 12, 8 );
   // revenir à la transformation courante
   glPopMatrix( );
}

void Propulsion::Afficher() const
{

	glPushMatrix();
	glTranslated( m_Position.GetX(),m_Position.GetY(),m_Position.GetZ() );
   	glRotated(angle,0,0,1);

	if(selectionne==false)
	{
		glColor3d( coulr, coulg, coulb );
	}

	if(selectionne==true)
	{
		glColor3d( 0, 0, 1 );
	}
	dessCone( m_Position.GetX(),m_Position.GetY(),m_Position.GetZ(), ra, h );
	glPopMatrix( );
}

void Propulsion::animer(double dt)
{

}
