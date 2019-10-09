// Plan3D.cpp: implementation of the CPlan3D class.
//
//////////////////////////////////////////////////////////////////////

#include "Plan3D.h"
#include "Point3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlan3D::CPlan3D(const CVecteur& Normale, const CPoint3D& PtDuPlan)
{
	if (Normale.IsNull())
		throw ("Impossible de construire un plan puisqu'il n'a pas de normale");

	m_Normale = Normale;
	m_D = -(Normale.GetX()*PtDuPlan.GetX() + Normale.GetY()*PtDuPlan.GetY() + Normale.GetZ()*PtDuPlan.GetZ());
}

CPlan3D::~CPlan3D()
{

}

void CPlan3D::GetParam(double& A, double& B, double& C, double& D) const
{
	A = m_Normale.GetX();
	B = m_Normale.GetY();
	C = m_Normale.GetZ();
	D = m_D;
}