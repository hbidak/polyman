#ifndef _HEADER_CUBE_H_
#define _HEADER_CUBE_H_

#include <iostream>
using namespace std;

/**
 * @class   Cube
 * @brief  Définition d'une Geometrie de type Cubique
 *
 * Définition de la classe Cube
 */
class Cube 
{
public:
   Cube( double longueur = 1,
           double r = 1, double g = 0, double b = 0 );
   Cube( const Cube& s );
   const Cube& operator=( const Cube& s );

   // accesseurs et modificateurs:
   inline void modifierDimension( double longueur )
   { l = longueur; }
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
      o << "<CUBE> "
        << "<LONGUEUR> " << l << "</LONGUEUR>"
        << "<RGB> " << coulr << " " << coulg << " " <<  coulb << "</RGB> "
        << "</CUBE>"
      ;
      return o;
   }

private:
   double l;                   // longueur des cote
   double coulr, coulg, coulb; // couleur
};

#endif
