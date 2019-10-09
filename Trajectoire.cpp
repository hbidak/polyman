#include "Trajectoire.h"

/**
 *
 * Constructeur de base
 */
CTrajectoire::CTrajectoire()         
{
	longueurTotale = 0.0;
	 k=0;
	  m_spline = new BSpline();
	//position_depart=
}

/**
 *
 * Constructeur de copie
 *
 * @param pCTrajectoire La trajectoire a copier
 */
CTrajectoire::CTrajectoire( const CTrajectoire& pCTrajectoire )
{
	longueurTotale = 0.0;
}

/**
 *
 * Destructeur
 */
CTrajectoire::~CTrajectoire()             
{
	while(!m_PtsControle.empty())
	{
      delete m_PtsControle.front();
      m_PtsControle.pop_back();
	}
}

/**
 *
 * Affichage de la trajectoire (penser à afficher les points de contrôle)
 *
 */
void CTrajectoire::Afficher() const
{	
	int i=0;
	//Parcours tous les points de controle et affiche
	vector<CPointCtrl*>::const_iterator pctrl = m_PtsControle.begin();
 	vector<CPointCtrl*>::const_iterator last = m_PtsControle.end();

	//CPointCtrl* pctrl;

	for(pctrl = m_PtsControle.begin(); pctrl != last; ++pctrl)
	{
		(*pctrl)->Afficher();
		
	}
	
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin( GL_LINE_STRIP );

	for(pctrl = m_PtsControle.begin(); pctrl != last; pctrl++)
	{
		CPoint3D v = (*pctrl)->GetPosition();
		glVertex3d(v.GetX(),v.GetY(),v.GetZ());	
	}
	glEnd();

}




/**
 *
 * Animation facultative
 *
 */
void CTrajectoire::animer(double dt)
{
	/* 
	CPoint3D tampon[];
	  i=0;
	  nbpointscontroles=0;


	//Parcours tous les points de controle  les conserve dans un tableau tampon
	list<CPointCtrl*>::const_iterator pctrl = m_PtsControle.begin();
 	list<CPointCtrl*>::const_iterator last = m_PtsControle.end();

	CPointCtrl* pctrl;

	for(pctrl = m_PtsControle.begin(); pctrl != last; ++pctrl)
	{

		tampon[i]=(*pctrl)->GetPosition;
		
	}

	 nbpointscontroles=i+1;
	 i=0;


	// je crée mes vecteur distance

	for (i=0,i<nbpointscontroles,i++)

	{

		CVecteur deplacement(tampon[i],tampon[i+1]);

		

	}

*/
  
}

/**
 * Ajoute un nouveau point de controle à la fin de la trajectoire
 * 
 * @param NouvPoint le point à ajouter
 */
void CTrajectoire::AjouterPtsControle(CVecteur NouvPoint)
{


	CPointCtrl* pControle;
	pControle = new CPointCtrl(NouvPoint);
	CPoint3D v=CPoint3D(NouvPoint.GetX(),NouvPoint.GetY(),NouvPoint.GetZ());

			
	pControle->SetPosition(v);

	m_PtsControle.push_back(pControle);  

	
}


/**
 * Ajoute un nouveau point de controle à la fin de la trajectoire
 * 
 * @param NouvPoint le point à ajouter
 */
void CTrajectoire::AjouterPtsSpline(CVecteur NouvPoints)
{


	CPointCtrl* pControles;
	pControles = new CPointCtrl(NouvPoints);
	CPoint3D vec=CPoint3D(NouvPoints.GetX(),NouvPoints.GetY(),NouvPoints.GetZ());

			
	pControles->SetPosition(vec);

	m_PtsControleSpline.push_back(pControles);  

	
}

/**
 *
 * Retourne le decalage a ajouter a la position des aliens
 *
 * @param avancement pourcentage selon la trajectoire (entre 0 et 1)
 */
CVecteur CTrajectoire::Evaluer(double avancement)
{

/*


	 CVecteur vecteur_deplacement;

	//CPoint3D position_actuelle=pos_actuelle;
	CPoint3D position_pctrl;
	CPoint3D position_pctrl_suivant;
	CPoint3D position_pctrl_last;

	list<CPointCtrl*>::const_iterator pctrl = m_PtsControle.begin();
	list<CPointCtrl*>::const_iterator pctrl_suivant = m_PtsControle.begin();
 	list<CPointCtrl*>::const_iterator last = m_PtsControle.end();

	pctrl_suivant++;
	

	while(pctrl_suivant!=last && pctrl!=last)
	{
			cout<<endl;
			position_pctrl=(*pctrl)->GetPosition();
			position_pctrl_suivant=(*pctrl_suivant)->GetPosition();
	cout<<"Position actuelle:"<<position_actuelle.GetX()<<" "<<position_actuelle.GetY()<<" "<<position_actuelle.GetZ()<<endl;
	cout<<"Position pctrl:"<<position_pctrl.GetX()<<" "<<position_pctrl.GetY()<<" "<<position_pctrl.GetZ()<<endl;
	cout<<"Position pctrl_suivant:"<<position_pctrl_suivant.GetX()<<" "<<position_pctrl_suivant.GetY()<<" "<<position_pctrl_suivant.GetZ()<<endl;
			
		
		if ((position_actuelle.GetX()> position_pctrl.GetX() ) && (position_actuelle.GetX() < position_pctrl_suivant.GetX())
			&& (position_actuelle.GetY()> position_pctrl.GetY() ) && (position_actuelle.GetY() < position_pctrl_suivant.GetY()))
		{
			cout<<"cas1"<<endl;
		 vecteur_deplacement=CVecteur(position_pctrl,position_pctrl_suivant);
		 return vecteur_deplacement;
		}

		if ( (position_actuelle.GetX()> position_pctrl.GetX()) && (position_actuelle.GetX() < position_pctrl_suivant.GetX())
			&& (position_actuelle.GetY()< position_pctrl.GetY() ) && (position_actuelle.GetY() > position_pctrl_suivant.GetY()))
		{
			cout<<"cas2"<<endl;
		 vecteur_deplacement=CVecteur(position_pctrl,position_pctrl_suivant);
		 return vecteur_deplacement;
		}

		if ( (position_actuelle.GetX()< position_pctrl.GetX()) && ( position_actuelle.GetX() > position_pctrl_suivant.GetX() )
			&& (position_actuelle.GetY()> position_pctrl.GetY()) && (position_actuelle.GetY() < position_pctrl_suivant.GetY()))
		{
			cout<<"cas3"<<endl;
		 vecteur_deplacement=CVecteur(position_pctrl,position_pctrl_suivant);
		 return vecteur_deplacement;
		}

		if ( (position_actuelle.GetX()< position_pctrl.GetX()) && (position_actuelle.GetX() > position_pctrl_suivant.GetX())
			&& (position_actuelle.GetY()< position_pctrl.GetY() ) && (position_actuelle.GetY() > position_pctrl_suivant.GetY()))
		{
			cout<<"cas4"<<endl;
		 vecteur_deplacement=CVecteur(position_pctrl,position_pctrl_suivant);
		 return vecteur_deplacement;
		}

		if (position_actuelle.GetX()-position_pctrl.GetX()<0.00001)
		{	
			if (position_actuelle.GetY()-position_pctrl.GetY()<0.00001)
			{
			
			//if(position_actuelle.GetY()==position_pctrl.GetY()) 
			//{	
			//	if(position_actuelle.GetZ()==position_pctrl.GetZ())
				//{
					cout<<"position_actuelle== position_pctrl"<<endl;
					vecteur_deplacement=CVecteur(position_pctrl,position_pctrl_suivant);
					return vecteur_deplacement;
			//	}
			}
		}

		

	
	
		pctrl++;
		pctrl_suivant++;
		
	}

	
	



	// methode a suivre :
	// - trouver les deux points de controle encadrant la position a evaluer
	// - calculer la distance restant a parcourir sur ce segment
	// - interpoler lineairement sur les deux points pour trouver le decalage (sera remplace par une spline plus tard)
	// a rajouter au vecteur m_PositionInit  


	return CVecteur();	

  


*/


return CVecteur();	//a effecer eventuellement










}




void CTrajectoire::modifierCouleur(double ,double , double )
{
	//TODO
}
   


bool CTrajectoire::GetPtsControle(int compteur,CVecteur &point_retournee)
{
	int i=0;

	CPoint3D position_pt_controle;

	vector<CPointCtrl*>::const_iterator premier = m_PtsControle.begin();
 	vector<CPointCtrl*>::const_iterator dernier = m_PtsControle.end();
	
	cout<<"entre dans get pts controle"<<endl;
	while(premier!=dernier)
	{
		if(i==compteur)
		{
			position_pt_controle=(*premier)->GetPosition();
			point_retournee.SetXYZ(position_pt_controle.GetX(),position_pt_controle.GetY(),position_pt_controle.GetZ());
			return true;
		}

		i++;
		premier++;
	}
	cout<<"retourne faux"<<endl;
	return false;

}


void CTrajectoire::AjouterPtsControleSplines(CVecteur nouveauPoint)
{

	int i,n;
	double* ptNodal;
	CPointCtrl *pt;
	pt=new CPointCtrl(nouveauPoint);
	CPoint3D v=CPoint3D(nouveauPoint.GetX(),nouveauPoint.GetY(),nouveauPoint.GetZ());
	pt->SetPosition(v);

	m_PtsControle.push_back(pt);
		//cout<<"Taille du vecteur de points :"<< 	m_PtsControle.size()<<endl;

	longueurTotale+=1;
	if(longueurTotale==0)
	{
		k=0;
	}
	if(longueurTotale==1)
	{
		k=1;
	}
	else if(longueurTotale==2)
	{
		k=2;
	}
	else if(longueurTotale==3)
	{
		k=3;
	}
	else if(longueurTotale>=4)
	{
		k=4;
	}
	else
	{
		k=4;
	}/*
	if(longueurTotale==10)
	{
		k=4;
	}*/

	n = longueurTotale;
	ptNodal=new double[n+k];
		
	for(i=0;i<(n+k);i++)
	{
		if(i<k)
		{
			
			ptNodal[i]=0;
		}
		else if(i>=k && i<=n)
		{
		
			ptNodal[i]=(double(i)-double(k)+1.0)/(double(n)-double(k)+1.0);
		}
		else if(i>n)
		{
			ptNodal[i]=1;			
		}


		
	}


	m_spline->setVecteurNodal(ptNodal,n+k);

	
  
}


void CTrajectoire::AfficherSplines() const
{

	vector<CPointCtrl*>::const_iterator pctrl = m_PtsControle.begin();
 	vector<CPointCtrl*>::const_iterator last = m_PtsControle.end();	

	
	//std::list<CPointCtrl*>::const_iterator itp;
	double X=0,Y=0,i;
	double tmpX,tmpY;
	float d;
	//CPointCtrl* pControle;
	//m_PtsControleSpline.clear();

	

	glColor3f(1.0f,0.0f,0.0f);
	if(m_PtsControle.size()>1)
	{
		glBegin( GL_LINE_STRIP );
		for(d=0;d<=1;d+=0.01)
		{
			for(i=0,pctrl = m_PtsControle.begin(); pctrl != last; ++pctrl,i++)
				{
					tmpX=((*pctrl)->GetPosition()).GetX();
					tmpY=((*pctrl)->GetPosition()).GetY();
					//cout<<"Passer par fonction:"<<endl;
				

					X+= m_spline->evalN(i,k,d)*((*pctrl)->GetPosition().GetX() );
					
					Y+= m_spline->evalN(i,k,d)* ((*pctrl)->GetPosition().GetY() ) ;		
				}
			

				
				//pControle = new CPointCtrl(CVecteur (X,Y,0));			

				//m_PtsControleSpline[d]=pControle; 

			
				glVertex2f(X,Y);
				X=0;
				Y=0;
		}
		glEnd();
	}

  for(pctrl = m_PtsControle.begin(); pctrl != last; ++pctrl)
	{
		(*pctrl)->Afficher();
	}

}