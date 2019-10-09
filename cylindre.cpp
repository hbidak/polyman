#include <GL/glut.h>
#include "cylindre.h"
#include "Vecteur.h"
#include "ObjetGL.h"

/**
 * @fn  Cylindre::Cylindre( double rayon, double hauteur, double r, double g, double b )
 *
 *
 *
 * @param const double rayon :
 * @return void
 *
 */
Cylindre::Cylindre( double rayon,
                    double hauteur,
                    double r,
                    double g,
                    double b ) 
					: r( rayon ), h(hauteur), coulr( r ), coulg( g ), coulb( b )
{
}

/**
 * @fn  Cylindre::Cylindre( const Cylindre& s )
 *
 *
 *
 * @param const Cylindre& s :
 * @return void
 * @exception
 *
 */
Cylindre::Cylindre( const Cylindre& s ) : r( s.r ), h(s.h)
{

}

/**
 * @fn  const Cylindre& Cylindre::operator=( const Cylindre& s )
 *
 *
 *
 * @param const Cylindre& s :
 * @return void
 * @exception
 *
 */
const Cylindre& Cylindre::operator=( const Cylindre& s )
{
	r = s.r;
	h = s.h;
   return *this;
}

/**
 * @fn  static void dessCylindre( GLdouble x, GLdouble y, GLdouble z, GLenum style, GLdouble haut, GLdouble rayon )

 * @param GLdouble x, y, z : centre du disque
 * @param GLenum style : GLU_FILL, GLU_LINE ou GLU_POINT
 * @param GLdouble rayon : rayon
 * @return void
 *
 */
static void dessCylindre( GLdouble x, GLdouble y, GLdouble z,
                          GLenum style, GLdouble haut, GLdouble rayon )
{

	//cout<<"dess_cyl";
   // définition d'un objet quadric
   static GLUquadricObj *quadric = NULL;
   // si c'est la première fois alors ...
   if ( quadric == NULL ) quadric = gluNewQuadric( );
   // initialiser l'apparence
   gluQuadricNormals( quadric, GLU_SMOOTH );
   // choisir le style
   gluQuadricDrawStyle( quadric, style );
   // sauvegarder la transformation courante
   glPushMatrix( );
   // le centre du cylindre est à ...
   //glTranslated( x, y, z );
   //   glRotated(m_Up.GetTheta()*(180/3.14159265),0,0,1);
   // et hop!
   gluCylinder( quadric, rayon, rayon, haut, 12, 8 );
   // revenir à la transformation courante
   glPopMatrix( );
}

static void dessDisque( GLdouble x, GLdouble y, GLdouble z,
                        GLenum style, GLdouble rayonInt, GLdouble rayonExt )
{
   // définition d'un objet quadric
   static GLUquadricObj *quadric = NULL;
   // si c'est la première fois alors ...
   if ( quadric == NULL ) quadric = gluNewQuadric( );
   // choisir le style
   gluQuadricDrawStyle( quadric, style );
   // sauvegarder la transformation courante
   glPushMatrix( );
   // le centre du disque est à ...
   //glTranslated( x, y, z );
   //   glRotated(m_Up.GetTheta()*(180/3.14159265),0,0,1);
   // et hop!
   gluDisk( quadric, rayonInt, rayonExt, 20, 1 );
   // revenir à la transformation courante
   glPopMatrix( );
}


/**
 * @fn  void Cylindre::afficher( double x, double y, double z ) const
 *
 *
 *
 * @param double x :
 * @param double y :
 * @param double z :
 * @return void
 * @exception
 *
 */
void Cylindre::Afficher( double x, double y, double z ) const
{
   //glColor3d( coulr, coulg, coulb );
   dessCylindre( x, y, z, GLU_FILL, h, r );
   dessDisque( x, y, z+h/2, GLU_FILL, 0, r );
   dessDisque( x, y, z-h/2, GLU_FILL, 0, r );

}
