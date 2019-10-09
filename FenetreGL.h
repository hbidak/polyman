#ifndef _FENETREGL_
#define _FENETREGL_

#include "GlutMaster.h"
#include "GlutWindow.h"
#include "AdvGlutWnd.h"

#include "Scene.h"
#include "CRU.h"
#include "objetGL.h"
#include "OVI.h"
#include "selection3D.h"
#include <fstream>
using namespace std;


/**
 * @class CFenetreGL
 * @brief Definition d'une classe qui s'occupe de la fenetre 
 *
 * Classe abstraite qui regit l'affichage, les menus, la souris et le clavier.
 *
 */


class CFenetreGL : public CAdvGlutWnd  
{
public:

	// Construction / Destruction
	//---------------------------
	CFenetreGL::CFenetreGL( CGlutWindow& Parent,
							const CPoint2D& PosFenetre,
							const CRectangle& DimFenetre, 
							const CCouleurGL CouleurFond );

	virtual ~CFenetreGL();

	// Fonctions virtuelles surchargées.
	//----------------------------------

	void Afficher();
	void ClicSouris(int button, int state, int x, int y);
	void Clavier(unsigned char Key, int x, int y);
	void MouseMove(int x, int y);
	void Menu(int NumMenu);
	void AfficherMenuEdition();
	void AfficherMenuModeJeu();
	void AfficherMenuSelectionObjet();

	void AfficherMenuRecommencerJeu();
	void AvancerTemps();
	void DemanderTimer();
	//int GetNbrOvi(){return NbrOvi;};

	void SetScene(CScene * pScene) {mScene = pScene;}
	void ClavierSpecial(int Key, int x, int y);
	int NbrOvi;

private:
	CScene * mScene;
	selection3D * m_p_selection3D;
	CObjetGL* adresse_module;
	CObjetGL* adresse_station;
	bool Rotation;
	bool Translation;
	bool Imprimer;
	bool Selection_Station;
	bool dupliquer;

	OVI* OVICourant;
	bool TrajectoireDebutee;
	bool Selection_objet;
	bool Mode_jeu;
	int Nom_station_touche;
	ofstream FicSortie;
	ifstream FicEntree;
	//int NbrOvi;
	

};

#endif  _FENETREGL_

