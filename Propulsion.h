#ifndef PROPULSION_H
#define PROPULSION_H

#include "Module.h"
#include "Constantes.h"
#include <list>

class Propulsion : public Module
{
private:
   double ra;   // rayon
   double h;
   double coulr, coulg, coulb; // couleur

public:

	Propulsion( double rayon = 1,double hauteur =1,
           double r = 1, double g = 1, double b = 0 );
	~Propulsion();

	inline void modifierRayon( double rayon )
   { ra = rayon; }
	inline void modifierHauteur( double hauteur )
   { h = hauteur; }
   inline void modifierCouleur( double r, double g, double b )
   { coulr = r;  coulg = g; coulb = b; };

	void Afficher() const;
	void animer(double);

// impression des attributs
   inline ostream& imprimer( ostream& o) const
   {
      o << "<PROPULSION> "
        << "<RAYON> " << ra << "</RAYON>"
		<< "<HAUTEUR> " << h << "</HAUTEUR>"
        << "<RGB> " << coulr << " " << coulg << " " <<  coulb << "</RGB> "
        << "</PROPULSION>"
      ;
      return o;
   }

};

#endif