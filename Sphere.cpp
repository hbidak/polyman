#include <GL/glut.h>
#include "Sphere.h"
#include "Vecteur.h"
#include "ObjetGL.h"

/**
 * @fn  Sphere::Sphere( double rayon, double r, double g, double b )
 *
 *
 *
 * @param const double rayon :
 * @return void
 *
 */
Sphere::Sphere( double rayon,
                double r,
                double g,
                double b )
   : r( rayon ), coulr( r ), coulg( g ), coulb( b )
{

}

/**
 * @fn  Sphere::Sphere( const Sphere& s )
 *
 *
 *
 * @param const Sphere& s :
 * @return void
 * @exception
 *
 */
Sphere::Sphere( const Sphere& s ) : r( s.r )
{

}

/**
 * @fn  const Sphere& Sphere::operator=( const Sphere& s )
 *
 *
 *
 * @param const Sphere& s :
 * @return void
 * @exception
 *
 */
const Sphere& Sphere::operator=( const Sphere& s )
{
   r = s.r; return *this;
}

#if 0
/**
 * @fn  static void dessPoint( GLdouble x, GLdouble y, GLdouble z, GLdouble rayon )

 * @param GLdouble x, y, z : centre
 * @param GLdouble rayon : rayon (en pixels)
 * @return void
 *
 */
static void dessPoint( GLdouble x, GLdouble y, GLdouble z,
                       GLdouble rayon )
{
   // activer le lissage des points
   glEnable( GL_POINT_SMOOTH );
   // indiquer le rayon
   glPointSize( rayon );
   // utiliser la primitive GL_POINTS
   glBegin( GL_POINTS );
   glVertex3f( x, y, z );
   glEnd( );
   // désactiver le lissage des points
   glDisable( GL_POINT_SMOOTH );
}
#endif

#if 0
/**
 * @fn  static void dessDisque( GLdouble x, GLdouble y, GLdouble z, GLenum style, GLdouble rayonInt, GLdouble rayonExt )

 * @param GLdouble x, y, z : centre du disque
 * @param GLenum style : GLU_FILL, GLU_LINE ou GLU_POINT
 * @param GLdouble rayonInt : rayon intérieur
 * @param GLdouble rayonExt : rayon extérieur
 * @return void
 *
 */
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
   glTranslated( x, y, z );
   // et hop!
   gluDisk( quadric, rayonInt, rayonExt, 20, 1 );
   // revenir à la transformation courante
   glPopMatrix( );
}
#endif

/**
 * @fn  static void dessSphere( GLdouble x, GLdouble y, GLdouble z, GLenum style, GLdouble rayon )

 * @param GLdouble x, y, z : centre du disque
 * @param GLenum style : GLU_FILL, GLU_LINE ou GLU_POINT
 * @param GLdouble rayon : rayon
 * @return void
 *
 */
static void dessSphere( GLdouble x, GLdouble y, GLdouble z,
                        GLenum style, GLdouble rayon )
{
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
   // le centre de la sphère est à ...
   //glTranslated( x, y, z );
   //glRotated(m_Up.GetTheta()*(180/3.14159265),0,0,1);
   // et hop!
   gluSphere( quadric, rayon, 12, 8 );
   // revenir à la transformation courante
   glPopMatrix( );
}


/**
 * @fn  void Sphere::afficher( double x, double y, double z ) const
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
void Sphere::Afficher( double x, double y, double z ) const
{
   //glColor3d( coulr, coulg, coulb );

   dessSphere( x, y, z, (enum GLenum) GLU_FILL, r );
   //dessSphere( x, y, z, GLU_LINE, r );
   //dessDisque( x, y, z, (enum GLenum) GLU_FILL, 0.1, r );
   //dessPoint( x, y, z, 10.0*r );
}

