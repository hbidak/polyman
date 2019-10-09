// CouleurGL.cpp: implementation of the CCouleurGL class.
//
//////////////////////////////////////////////////////////////////////

#include "CouleurGL.h"
#include "Macros.h"

/*------------------------------------------------------------------
  Fonction :	CCouleurGL::CCouleurGL

  Description :	Construction d'un objet de type CCouleurGL

  Paramètres :

	 unsigned char Red : La propriété Rouge de la couleur.
	 unsigned char Green : La propriété verte de la couleur.
	 unsigned char Blue : La propriété Bleu de la couleur.

  Valeur retournée :	Aucune (constructeur) : 

  Par : 2000-12-8 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
CCouleurGL::CCouleurGL(unsigned char Red, unsigned char Green, unsigned char Blue)
{
	m_ucRed = Red;
	m_ucGreen = Green;
	m_ucBlue = Blue;
}



/*------------------------------------------------------------------
  Fonction :	CCouleurGL::LoadStdColor

  Description :	Cette fonction permet de charger une couleur standard 
				telle que contenu dans le fichier rgbcolor.h

  *****************************************************
  Exemple d'application:	
  
		CCouleurGL Coul;
		Coul.LoadStdColor(STD_LemonChiffon);

  *****************************************************

  Paramètres :
	 const float Red : La couleur rouge.
	 const float Green : la couleur verte
	 const float Blue : la couleur bleu.

	 Note : ces couleurs doivent être dans l'intervalle [0,1]

  Valeur retournée :	void : 

  Par : 2000-12-18 Maxime Beaudry
  MAJ: 
------------------------------------------------------------------*/
void CCouleurGL::LoadStdColor(const float Red, const float Green, const float Blue)
{
	if (DANS_INTERVALLE(Red, 0.0,1.0))
		m_ucRed = (int) (255*Red + 0.5);
	else
		m_ucRed = 0;

	if (DANS_INTERVALLE(Green, 0.0, 1.0))
		m_ucGreen = (int) (255*Green + 0.5);
	else
		m_ucGreen = 0;

	if (DANS_INTERVALLE(Blue, 0.0, 1.0))
		m_ucBlue = (int) (255*Blue + 0.5);
	else
		m_ucBlue = 0;
}