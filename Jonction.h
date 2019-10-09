#ifndef JONCTION_H
#define JONCTION_H

#include "Module.h"
#include "Constantes.h"
#include "Vecteur.h"
#include "ObjetGL.h"
#include <list>


class Jonction : public Module
{
private:
	bool b_connecte;
	double l;   // longueur
	double h;	// hauteur
	double p;	//profondeur
	double coulr, coulg, coulb; // couleur
	
public:

	Jonction( double longueur = 2,double hauteur =1,double profondeur =1,
           double r = 0, double g = 1, double b = 0 );
	~Jonction();
	
	inline void modifierLongueur( double longueur )
   { l = longueur; }
	inline void modifierHauteur( double hauteur )
   { h = hauteur; }
	inline void modifierProfondeur( double profondeur )
   { p = profondeur; }
   inline void modifierCouleur( double r, double g, double b )
   { coulr = r;  coulg = g; coulb = b; };

	void Afficher() const;
	void animer(double);

	// impression des attributs
   inline ostream& imprimer( ostream& o) const
   {
      o << "<JONCTION> "
        << "<LONGUEUR> " << l << "</LONGUEUR>"
		<< "<HAUTEUR> " << h << "</HAUTEUR>"
		<< "<PROFONDEUR> " << p << "</PROFONDEUR>"
        << "<RGB> " << coulr << " " << coulg << " " <<  coulb << "</RGB> "
        << "</JONCTION>"
      ;
      return o;
   }

};

#endif