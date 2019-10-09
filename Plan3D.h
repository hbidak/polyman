#ifndef _PLAN3D_
#define _PLAN3D_

#include "Vecteur.h"

/**
 * @class CPlan3D
 * @brief Definition de la classe qui cree un plan en 3 dimensions 
 *
 * Classe qui permet d'avoir un plan en 3D
 */


class CPlan3D  
{
public:
	// Construction / destruction
	//---------------------------

	CPlan3D(const CVecteur& Normale, const CPoint3D& PtDuPlan);
	virtual ~CPlan3D();


	// Fonctions d'accès
	//------------------

	CVecteur GetNormale() const {return m_Normale;}
	void GetParam(double& A, double& B, double& C, double& D) const;

private:

	//Un plan est défini par Ax + By + Cz + D = 0 où A, B et C sont les 
	//composantes en x, y et z d'un vecteur normal au plan.
	//-----------------------------------------------------------------

	CVecteur m_Normale;
	double m_D;
};

#endif 