#include "CRU.h"
#include "Sphere.h"
#include "cylindre.h"
#include "cube.h"
#include "Propulsion.h"

CRU::CRU(typeCRU tc)
:type(tc)
{
	
}

CRU::~CRU()
{

}

void CRU::Afficher() const
{
Sphere sh;
Cylindre cy;
Cube cu;
//Sphere sh(2,1,0,0);
//Cylindre cy(1,1,1,0,0);
//Cube cu(1,1,0,0);

	glPushMatrix();
	glTranslated( m_Position.GetX(),m_Position.GetY(),m_Position.GetZ() );
   	glRotated(angle,0,0,1);

	if(selectionne==true)
	{
		GLfloat materiel_Ka[]={0.0, 0.0, 1.0,1.0};
		GLfloat materiel_Kd[]={0.85,0.61,0.54,1.00};
		GLfloat materiel_Ks[]={0.33,0.33,0.52,1.00};
		GLfloat materiel_Ke[]={1.00,1.00,1.00,1.00};
		//GLfloat materiel_Se=10;

		glMaterialfv(GL_FRONT,GL_AMBIENT,materiel_Ka);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,materiel_Ka);
		glMaterialfv(GL_FRONT,GL_SPECULAR,materiel_Ka);
		glMaterialfv(GL_FRONT,GL_EMISSION,materiel_Ka);	
		//glColor3d( 0, 0, 1 );
	}

	switch (type)
		{
			case CONTROLE:
				if(selectionne==false)
				{

						GLfloat materiel_Ka[]={sh.GetCouleur_r(),sh.GetCouleur_g(),sh.GetCouleur_b(),1.0};
						GLfloat materiel_Kd[]={1.0,1.0,1.0,1.0};//0.85,0.61,0.54,1.00};
						GLfloat materiel_Ks[]={0.33,0.33,0.52,1.00};
						GLfloat materiel_Ke[]={1.00,1.00,1.00,1.00};
						//GLfloat materiel_Se=10;

						glMaterialfv(GL_FRONT,GL_AMBIENT,materiel_Ka);
						glMaterialfv(GL_FRONT,GL_DIFFUSE,materiel_Ka);
						glMaterialfv(GL_FRONT,GL_SPECULAR,materiel_Ka);
						glMaterialfv(GL_FRONT,GL_EMISSION,materiel_Ka);				
						
					//glColor3d( sh.GetCouleur_r(),sh.GetCouleur_g(),sh.GetCouleur_b() );
							
				}
			sh.Afficher(m_Position.GetX(),m_Position.GetY(),m_Position.GetZ());
			break;

			case RECHERCHE:
				if(selectionne==false)
				{
					GLfloat materiel_Ka[]={cu.GetCouleur_r(),cu.GetCouleur_g(), cu.GetCouleur_b(),1.0};
					GLfloat materiel_Kd[]={0.85,0.61,0.54,1.00};
					GLfloat materiel_Ks[]={0.33,0.33,0.52,1.00};
					GLfloat materiel_Ke[]={1.00,1.00,1.00,1.00};
					//GLfloat materiel_Se=10;

					glMaterialfv(GL_FRONT,GL_AMBIENT,materiel_Ka);
					glMaterialfv(GL_FRONT,GL_DIFFUSE,materiel_Ka);
					glMaterialfv(GL_FRONT,GL_SPECULAR,materiel_Ka);
					glMaterialfv(GL_FRONT,GL_EMISSION,materiel_Ka);	
					//glColor3d( cu.GetCouleur_r(),cu.GetCouleur_g(), cu.GetCouleur_b());
				}
			cu.Afficher(m_Position.GetX(),m_Position.GetY(),m_Position.GetZ());
			break;

			case UTILITAIRE:
				if(selectionne==false)
				{
					GLfloat materiel_Ka[]={cy.GetCouleur_r(),cy.GetCouleur_g(),cy.GetCouleur_b(),1.0 };
					GLfloat materiel_Kd[]={0.85,0.61,0.54,1.00};
					GLfloat materiel_Ks[]={0.33,0.33,0.52,1.00};
					GLfloat materiel_Ke[]={1.00,1.00,1.00,1.00};
					//GLfloat materiel_Se=10;

					glMaterialfv(GL_FRONT,GL_AMBIENT,materiel_Ka);
					glMaterialfv(GL_FRONT,GL_DIFFUSE,materiel_Ka);
					glMaterialfv(GL_FRONT,GL_SPECULAR,materiel_Ka);
					glMaterialfv(GL_FRONT,GL_EMISSION,materiel_Ka);	
					//glColor3d( cy.GetCouleur_r(),cy.GetCouleur_g(),cy.GetCouleur_b() );
				}
			cy.Afficher(m_Position.GetX(),m_Position.GetY(),m_Position.GetZ());
			break;

		}

	glPopMatrix();
}

void CRU::animer(double dt)
{

}

void CRU::modifierCouleur(double couleur_r,double couleur_g, double couleur_b)
{

Sphere sh;
Cylindre cy;
Cube cu;

	switch (type)
		{
			case CONTROLE:
			sh.modifierCouleur(couleur_r,couleur_g,couleur_b);
			break;

			case RECHERCHE:
			cu.modifierCouleur(couleur_r,couleur_g,couleur_b);
			break;

			case UTILITAIRE:
			cy.modifierCouleur(couleur_r,couleur_g,couleur_b);
			break;

		}
}
