#ifndef POINTCTRL_H
#define POINTCTRL_H

#include "ObjetGL.h"


/**
 * Point de contr�le d'une trajectoire
 *
 */

class CPointCtrl : public CObjetGL  {
public:
	CPointCtrl();
	CPointCtrl(const CVecteur &pos);
	~CPointCtrl();

	void Afficher() const ;
	void animer(double dt){} ;

	/** d�place le point de contr�le */
	void deplacer( CVecteur decal) {m_Position = m_Position + decal; } ;

	void modifierCouleur(double ,double , double );

	// impression des attributs sur le ostream
	ostream& imprimer( ostream& out ) const { return out; }
   
};

#endif
