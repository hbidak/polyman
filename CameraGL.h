#ifndef CCameraGL_H
#define CCameraGL_H

#include "Point3D.h"
#include "Vecteur.h"
#include <assert.h>

/**
 * @class CCameraGL
 * @brief Definition de la classe qui regit la camera
 *
 * Classe qui permet de definir les comportements d'une camera en 3D.
 */


class CCameraGL
{
public : 
	

	//Construction / destruction
	//---------------------------

	CCameraGL(const double& DisObs, const CPoint3D& PtVise, const double& AngElev, const double& AngleRot);
	CCameraGL(const CCameraGL& Source);
	const CCameraGL& operator = (const CCameraGL& Droite);
	~CCameraGL(){;}


	//Fonctions d'acces
	//------------------

	void SetPtVise(const CPoint3D& Pt) {m_PointVise = Pt; m_EstAJour = false;}
	void SetAngleElevation(double Angle);
	void SetAngleRotation(double Angle);
	void SetDistanceObservateur(const double Dis) {assert(Dis>0); m_EstAJour = false; m_DistanceObservateur = Dis;}
	void IncrementerAngleRotation(const double Increment);
	void IncrementerAngleElevation(const double Increment);

	const CPoint3D GetPtVise() const {return m_PointVise;}
	const double GetAngleElevation() const {return m_AngleElevation;}
	const double GetAngleRotation() const {return m_AngleRotation;}
	const double GetDistanceObservateur() const {return m_DistanceObservateur;}
	

	//Equivalent de gluLookAt
	//-----------------------
	void PositionnerCamera();

private : 
  
	//La distance entre la cam�ra et le point vis�
	double m_DistanceObservateur;

	//La position du point vis�.
	CPoint3D m_PointVise;

	//L'angle d'�l�vation au-dessus du plan x-y
	double m_AngleElevation;

	//L'angle qui fait se deplacer en rond autour de l'axe des z
	double m_AngleRotation;

	//********************************
	// Ces param�tres sont � calculer
	// en fonction des param�tres
	// pr�c�dents
	//********************************

	//La position de la cam�ra 
	CPoint3D m_PositionCamera;

	//Le up vector.
	CVecteur m_Up;

	//Indique si les param�tres � calculer sont � jour.
	bool m_EstAJour;
};

#endif
