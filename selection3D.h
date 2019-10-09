#ifndef _SELECTION3D_H_
#define _SELECTION3D_H_


#include "GlutMaster.h"
#include "GlutWindow.h"
#include "AdvGlutWnd.h"
#include "TransformationGL.h"
#include "Scene.h"

/*
#include <list>
#include "ObjetGL.h"
#include "Vecteur.h"
#include "OVI.h"
#include "Propulsion.h"
#include "Jonction.h"
#include "GlutMaster.h"
#include "GlutWindow.h"
#include "AdvGlutWnd.h"
#include "Station.h"
//#include "TransformationGL.h"
#include <fstream>
using namespace std;
*/

//


class selection3D
{
public:
    
int processHits (GLint hits, GLuint buffer[]);
	
private:

CTransformationGL* m_ppTransformation;
CScene * mmScene;

};

#endif _SELECTION3D_H_
