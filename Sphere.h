#ifndef _HEADER_SPHERE_H_
#define _HEADER_SPHERE_H_

#include <iostream>
using namespace std;

/**
 * @class   Sphere
 * @brief  Définition d'une Geometrie de type Sphère
 *
 * Définition de la classe Sphere
 */
class Sphere 
{
public:
   Sphere( double rayon = 2,
           double r = 1, double g = 0, double b = 0 );
   Sphere( const Sphere& s );
   const Sphere& operator=( const Sphere& s );

   // accesseurs et modificateurs:
   inline void modifierRayon( double rayon )
   { r = rayon; }
   inline void modifierCouleur( double r, double g, double b )
   { coulr = r;  coulg = g; coulb = b; };

   int GetCouleur_r() const {return coulr;}
   int GetCouleur_g() const {return coulg;}
   int GetCouleur_b() const {return coulb;}

   // affichage
   void Afficher( double x, double y, double z ) const;

   // impression des attributs
   inline ostream& imprimer( ostream& o) const
   {
      o << "<SPHERE> "
        << "<RAYON> " << r << "</RAYON>"
        << "<RGB> " << coulr << " " << coulg << " " <<  coulb << "</RGB> "
        << "</SPHERE>"
      ;
      return o;
   }

private:
   double r;                   // rayon
   double coulr, coulg, coulb; // couleur
};

#endif
