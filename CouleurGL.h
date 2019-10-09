#ifndef _COULEURGL_
#define _COULEURGL_

#include <GL/glut.h>
#include "rgbcolor.h"

/**
 * @class CCouleurGL
 * @brief Definition de la classe qui defini un type de couleur
 *
 * Classe qui permet de generer une couleur
 */


class CCouleurGL  
{
public:

	//Construction / Destruction
	//--------------------------

	CCouleurGL(unsigned char Red = 0, unsigned char Green = 0, unsigned char Blue = 0);
	virtual ~CCouleurGL(){;}

	//Fonctions d'accès
	//-----------------

	unsigned char GetRed() const {return m_ucRed;}
	unsigned char GetGreen() const {return m_ucGreen;}
	unsigned char GetBlue() const {return m_ucBlue;}

	void SetRed(unsigned char Red) {m_ucRed = Red;}
	void SetGreen(unsigned char Green) {m_ucGreen = Green;}
	void SetBlue(unsigned char Blue) {m_ucBlue = Blue;}

	void LoadStdColor(const float Red, const float Green, const float Blue);

	//Fonctions pour appliquer les couleurs
	//-------------------------------------
	void Apply() const {glColor3ub(m_ucRed, m_ucGreen, m_ucBlue);}

private:

	//Les attributs de la couleur 
	//Le type est unsigned char puisque ce type ne peut contenir que des
	//valeurs comprises dans l'intervalle [0,255]
	unsigned char m_ucRed, m_ucGreen, m_ucBlue;

};

#endif