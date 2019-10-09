#ifndef _HEADER_CYLINDRE_H_
#define _HEADER_CYLINDRE_H_

#include <iostream>
using namespace std;

/**
 * @class   Cylindre
 * @brief  Definition d'une Geometrie de type Cylindre
 *
 * Définition de la classe Cylindre.
 *
 */
class Cylindre
{
public:
   Cylindre( double rayon = 1, double hauteur = 1,
             double r = 1, double g = 0, double b = 0 );
   Cylindre( const Cylindre& s );
   const Cylindre& operator=( const Cylindre& s );

   // accesseurs et modificateurs:
   inline void modifierHauteur( double hauteur )
   { h = hauteur; }
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
   inline ostream& imprimer( ostream& o ) const
   {
      o << "<CYLINDRE> "
        << "<HAUTEUR> " << h << "</HAUTEUR>"
        << "<RAYON> " << r << "</RAYON>"
        << "<RGB> " << coulr << " " << coulg << " " <<  coulb << "</RGB> "
        << "</CYLINDRE>"
      ;
      return o;
   }
   friend ostream& operator<<( ostream& o, const Cylindre& s ) { return o; };

private:
   double h, r;                // hauteur et rayon
   double coulr, coulg, coulb; // couleur
};

#endif
