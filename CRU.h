#ifndef CRU_H
#define CRU_H

#include "Module.h"
#include "Constantes.h"
#include <list>



enum typeCRU {CONTROLE, RECHERCHE, UTILITAIRE};

class CRU : public Module
{
private:

	typeCRU type;
public:

	CRU(typeCRU tc);
	~CRU();
	
	void Afficher() const;
	void animer(double);
	void imprimer() const;
	void modifierCouleur(double ,double , double );

};

#endif