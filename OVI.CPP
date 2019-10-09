#include "OVI.h"
#include "Vecteur.h"
#include "ObjetGL.h"

/**
 *
 * Constructeur de base 
 * 
 */
OVI::OVI(CPoint3D pos, double hauteur, double largeur, int NbrOvi)
{
	m_Position= pos;
	m_Hauteur = hauteur;
	m_Largeur = largeur;
	traj = NULL;
	//trajS=NULL;
	type = TYPE_OVI;
	pourcentage= 0;
	pcourant= 0 ;
	Mode_Jeu=false;	 
	Nlight= NbrOvi;

}

/**
 *
 * Destructeur de base 
 * 
 */
OVI::~OVI()
{
	if(traj != NULL)
		delete traj;
}

void OVI::Afficher() const
{
	cout<<"afficher ovi"<<endl;
	bool pos= true;
	CVecteur point_retournee;
	//Definition d'un tableau de lumieres
	int lumiere[]={GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5};
	
	GLfloat Light_pos[4];//={m_Position.GetX()+(m_Largeur/2.0), (m_Position.GetY()+(m_Hauteur/2.0)), m_Position.GetZ() +(m_Hauteur/2.0),1.0};//{-1.00,1.00,1.00,1.00};
	GLfloat Light_Ka[]={0.5,0.5,0.5,1.00};
	GLfloat Light_Kd[]={1.00,1.00,1.00,1.00};
	GLfloat Light_Ks[]={1.00,1.00,1.00,1.00};
	GLfloat Light_direction[4];//={1.0,0.0,0.0};
	/****************************************************************************/
	//Definition de la directon du spot en fonction du pt courant et point precedent de traj
	if(traj!=NULL)
	{
		cout<<"traj=true"<<endl;
		if(traj->m_PtsControle.size()>=2)
		{
			cout<<"traj>2 "<<endl;
			//int suivant=pcourant+1;
			//if(suivant>=traj->m_PtsControle.size()-1)suivant=0;
			CVecteur Dir(traj->m_PtsControle[0]->GetPosition(),traj->m_PtsControle[1]->GetPosition());
			Dir.Normalize();
			// definition de la direction
			Light_direction[0]=Dir.GetX();
			Light_direction[1]=Dir.GetY();
			Light_direction[2]= Dir.GetZ();
			Light_direction[3]= 0.0;
			//GLfloat Light_direction[]={Dir.GetX(),Dir.GetY(),Dir.GetZ()};

			if(true)//pos && traj->GetPtsControle(2,point_retournee))
			{
				point_retournee.SetXYZ(traj->m_PtsControle[1]->GetPosition().GetX(),traj->m_PtsControle[1]->GetPosition().GetY(),traj->m_PtsControle[1]->GetPosition().GetZ());//coordonnee du 2eme pt de la trajectoire
				if(point_retournee.GetZ()>= m_Position.GetZ())//pour l axe Z il faut definir DZ=Zmax-Zmin
				{
					cout<<"Zt>Zobj "<<endl;
					if(point_retournee.GetX()>= (m_Position.GetX()+ (m_Largeur/2.0)))
					{
						cout<<"Xt>Xobj "<<endl;
						if(point_retournee.GetY()>= (m_Position.GetY()+ (m_Hauteur/2.0)))
						{
							Light_pos[0]=(m_Position.GetX()+ (m_Largeur/2.0));
							Light_pos[1]=(m_Position.GetY()+(m_Hauteur/2.0));
							Light_pos[2]= m_Position.GetZ()+(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
						if(point_retournee.GetY()< (m_Position.GetY()- (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX()+ (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY()-(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()+(m_Hauteur/2.0);
							Light_pos[3]= 1.0;							
						}
						else
						{
							Light_pos[0]=m_Position.GetX()+ (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY();
							Light_pos[2]= m_Position.GetZ()+(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
					}
					if(point_retournee.GetX()< (m_Position.GetX()+ (m_Largeur/2.0)))
					{
						cout<<"Xt<Xobj"<<endl;
						if(point_retournee.GetY()> (m_Position.GetY()+ (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX()- (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY()+(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()+(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
							
						if(point_retournee.GetY()< (m_Position.GetY()- (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX()- (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY()-(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()+(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}							
						else
						{
							Light_pos[0]=m_Position.GetX()- (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY();
							Light_pos[2]= m_Position.GetZ()+(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
							
					}
					else
					{
						if(point_retournee.GetY()> (m_Position.GetY()+ (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX();
							Light_pos[1]=m_Position.GetY()+(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()+(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}							
						if(point_retournee.GetY()< (m_Position.GetY()- (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX();
							Light_pos[1]=m_Position.GetY()-(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()+(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
							
						else
						{
							Light_pos[0]=m_Position.GetX()- (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY();
							Light_pos[2]= m_Position.GetZ()+(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
							
					
					}
				}
				if(point_retournee.GetZ()< m_Position.GetZ())
				{
					cout<<"Zt<Zobj "<<endl;
					if(point_retournee.GetX()>= (m_Position.GetX()+ (m_Largeur/2.0)))
					{
						cout<<"Xt>Xobj "<<endl;
						if(point_retournee.GetY()>= (m_Position.GetY()+ (m_Hauteur/2.0)))
						{
							Light_pos[0]=(m_Position.GetX()+ (m_Largeur/2.0));
							Light_pos[1]=(m_Position.GetY()+(m_Hauteur/2.0));
							Light_pos[2]= m_Position.GetZ()-(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
						if(point_retournee.GetY()< (m_Position.GetY()- (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX()+ (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY()-(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()-(m_Hauteur/2.0);
							Light_pos[3]= 1.0;							
						}
						else
						{
							Light_pos[0]=m_Position.GetX()+ (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY();
							Light_pos[2]= m_Position.GetZ()-(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
					}
					if(point_retournee.GetX()< (m_Position.GetX()+ (m_Largeur/2.0)))
					{
						cout<<"Xt<Xobj"<<endl;
						if(point_retournee.GetY()> (m_Position.GetY()+ (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX()- (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY()+(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()-(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
							
						if(point_retournee.GetY()< (m_Position.GetY()- (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX()- (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY()-(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()-(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}							
						else
						{
							Light_pos[0]=m_Position.GetX()- (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY();
							Light_pos[2]= m_Position.GetZ()-(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
							
					}
					else
					{
						if(point_retournee.GetY()> (m_Position.GetY()+ (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX();
							Light_pos[1]=m_Position.GetY()+(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()-(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}							
						if(point_retournee.GetY()< (m_Position.GetY()- (m_Hauteur/2.0)))
						{
							Light_pos[0]=m_Position.GetX();
							Light_pos[1]=m_Position.GetY()-(m_Hauteur/2.0);
							Light_pos[2]= m_Position.GetZ()-(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
							
						else
						{
							Light_pos[0]=m_Position.GetX()- (m_Largeur/2.0);
							Light_pos[1]=m_Position.GetY();
							Light_pos[2]= m_Position.GetZ()-(m_Hauteur/2.0);
							Light_pos[3]= 1.0;
						}
							
					
					}
				}

			}
		}
	}
	
	
	
	
	/***********************************************************************************************************/
	if(traj!=NULL)
		if(traj->m_PtsControle.size()>=2 && Mode_Jeu)
		{
			glLightfv(lumiere[Nlight],GL_POSITION,Light_pos);
			glLightfv(lumiere[Nlight],GL_AMBIENT,Light_Ka);
			glLightfv(lumiere[Nlight],GL_DIFFUSE,Light_Kd);	
			//cout<<"pos light [ "<<Light_pos[0]<<", "<<Light_pos[1]<<", "<<Light_pos[2]<<", "<<Light_pos[3]<<" ] "<<endl;
				//angle d'ouverture du spot
			glLightf(lumiere[Nlight], GL_SPOT_CUTOFF,15.0);
			glLightfv(lumiere[Nlight], GL_SPOT_DIRECTION,Light_direction);
			glEnable(GL_LIGHTING);
			glEnable(lumiere[Nlight]);
		}		
	glDisable(GL_LIGHT0);

	// Exemple d'affichage
	glPushMatrix();
	glTranslatef(m_Position.GetX(), m_Position.GetY(), m_Position.GetZ());
	glRotated(angle,0,0,1);
	glScalef(m_Largeur, m_Hauteur,1);

	if(selectionne==false)
	{
		GLfloat materiel_Ka[]={0.5, 0.76, 0.79,1.0};
		GLfloat materiel_Kd[]={0.85,0.61,0.54,1.00};
		GLfloat materiel_Ks[]={0.33,0.33,0.52,1.00};
		GLfloat materiel_Ke[]={1.00,1.00,1.00,1.00};
		//GLfloat materiel_Se=10;

		glMaterialfv(GL_FRONT,GL_AMBIENT,materiel_Ka);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,materiel_Ka);
		glMaterialfv(GL_FRONT,GL_SPECULAR,materiel_Ka);
		glMaterialfv(GL_FRONT,GL_EMISSION,materiel_Ka);
		//glColor3d(1, 0.5, 0.5);
	}

	if(selectionne==true)
	{
		GLfloat materiel_Ka[]={0.0, 0.0, 1.0  ,1.0};
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
	
	glBegin( GL_LINE_LOOP );
	for(int i=0;i<1000;i++)
	{
		float i_f= (((float)i)/1000)*(2*PI) ;

		glVertex2f(cos(i_f*6), sin(i_f*8));
	}
	glEnd();

	glPopMatrix();

	if(traj!=NULL)
		//&& Mode_Jeu==false)
	{
		traj->AfficherSplines(); 
	}

	//Mode_Jeu=false;
	cout<<"fin aff ovi"<<endl;
}

void OVI::animer(double dt)
{
	//vector<CPointCtrl*>::const_iterator pctrl = m_PtsControle.begin();
 //	vector<CPointCtrl*>::const_iterator last = m_PtsControle.end();	
	
	int i=0;
	double tempX=0, tempY=0, tempZ=0,X=0,Y=0, Z=0;

	Mode_Jeu=true;	

	if(traj!=NULL)

	if(traj->m_PtsControle.size()>=2)

	{		

		
			
			for(i=0;i<traj->m_PtsControle.size();i++)
			{

				tempX=traj->m_PtsControle[i]->GetPosition().GetX();
				tempY=traj->m_PtsControle[i]->GetPosition().GetY();
				tempZ=traj->m_PtsControle[i]->GetPosition().GetZ();	
				
				

				X+= traj->m_spline->evalN(i,traj->k,pourcentage)*tempX;		
					
				Y+= traj->m_spline->evalN(i,traj->k,pourcentage)*tempY;
			
				Z+= traj->m_spline->evalN(i,traj->k,pourcentage)*tempZ;
			}

			
			CPoint3D v(X,Y,Z);

			m_Position=v;
			pourcentage +=0.01;//dt=0.02

			if(pourcentage>=1)
				{
				pourcentage=0;

				//pcourant=0;		
	
				}
		//	else
			//	pcourant++;;
		
	

			//m_Position +=V*dt;


		/*pourcentage +=dt;

		if(pourcentage>=1)
		{
			pourcentage=0;

			pcourant++;
		
	
		}
		*/

		/*if(pcourant>traj->m_PtsControle.size()-2)
		{
			pcourant = 0;
	
		}*/
		
		
	}





}

void OVI::modifierCouleur(double couleur_r,double couleur_g, double couleur_b)
{
//	OVI ovi1;
//	ovi1.modifierCouleur(couleur_r, couleur_g, couleur_b);
}

void OVI::AjouterPtsTrajectoire(double x0,double y0,double z0)
{
	CVecteur v(x0,y0,z0);
	if(traj == NULL) // si la trajectoire n'existe pas encore
		traj = new CTrajectoire();

	traj->AjouterPtsControle(v);
}

CTrajectoire* OVI::GetTrajectoire()
{
	return traj;
}


/*
void OVI::GetPointsControles()
{
CPoint3D position_point_controle;

if(traj!=NULL)

appel +=

	if(traj->m_PtsControle.size()>=2)
		{

		position_point_controle=traj->m_PtsControle[pcourant]->GetPosition()

	
		}

	

	
}
*/
void OVI::Imprimer( ostream& out ) const
{
	
	if(traj==NULL)
	{
		out<<"0"<<endl;
	}


	if (!traj== NULL)
	{
		out<<traj->m_PtsControle.size()<<endl;
		
		CPoint3D ptcontrole;


		//Parcours tous les points de controle et affiche
		vector<CPointCtrl*>::const_iterator pctrl = traj->m_PtsControle.begin();
 		vector<CPointCtrl*>::const_iterator last = traj->m_PtsControle.end();

		//CPointCtrl* pctrl;

		for(pctrl = traj->m_PtsControle.begin(); pctrl != last; pctrl++)
		{ 
			ptcontrole=(*pctrl)->GetPosition();
			out<<ptcontrole.GetX()<<" "<<ptcontrole.GetY()<<" "<<ptcontrole.GetZ()<<endl;

		}
	}
			out<<"FIN POINTS CONTROLES"<<endl;	
}


void OVI::AjouterPtsTrajectoireSplines(double x0,double y0,double z0)
{

	
	CVecteur v(x0,y0,z0);
	if(traj == NULL) // si la trajectoire n'existe pas encore
		traj = new CTrajectoire();

	traj->AjouterPtsControleSplines(v);


}