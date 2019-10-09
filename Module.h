#ifndef MODULE_H
#define MODULE_H

#include "ObjetGL.h"
#include "Constantes.h"
#include <list>


class Module: public CObjetGL
{
private:
	list<Module*> fils;

public:
	Module();
	~Module();
};



#endif

