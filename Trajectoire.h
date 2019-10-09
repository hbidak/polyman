#ifndef TRAJECTOIRE_H
#define TRAJECTOIRE_H

#include "Vecteur.h"
#include "ObjetGL.h"
#include "BSpline.h"
#include "Pointctrl.h"
#include <list>
#include <vector>

/**
 * Trajectoir d'un groupe d'alien de même type
 *
 */
class CTrajectoire : public CObjetGL
{
public:
	CTrajectoire();
	CTrajectoire( const CTrajectoire& pCTrajectoire );
	~CTrajectoire( void );

	const CTrajectoire& operator=( const CTrajectoire& pCTrajectoire );

	void AjouterPtsControle(CVecteur nouveauPoint);
	bool GetPtsControle(int compteur,CVecteur &point_retournee);

//	CVecteur GetPointControle() const {return m_Position;}  

	void Afficher() const ;	
	void animer(double) ;
	ostream& imprimer( ostream& out ) const { return out; };

	void modifierCouleur(double ,double , double );

	//modif----pourtarjovi
	CVecteur Evaluer(double avancement);
	//CVecteur Evaluer(CPoint3D position_actuelle);

	std::vector<CPointCtrl*> m_PtsControle;
	std::vector<CPointCtrl*> m_PtsControleSpline;

	/***** ajout de jojo le 1 dec Pour les Splines ****/

	BSpline *m_spline;
   void AfficherSplines() const ; 
   void AjouterPtsControleSplines(CVecteur nouveauPoint);
   void AjouterPtsSpline(CVecteur NouvPoint);

	int k;

protected:
/**
 * Liste des points de contrôle
 *
 */
//	std::list<CPointCtrl*> m_PtsControle;
	
/**
 * Longueur totale de la trajectoire
 *
 */	
	double longueurTotale ;
	

};

#endif
