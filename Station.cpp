#include "Station.h"

//int i=0;
/**
 *
 * Constructeur de base 
 * 
 */
Station::Station()
{
	double vitesse_station;
	double angle_station;
	double deplacementx;
	double deplacementy;
	double deplacementz=0;
	CVecteur vecteur_de_vitesse;

	srand((unsigned)time(NULL));
	vitesse_station=rand() % 10+1;
	angle_station=rand() % 360+1;
	angle_station=angle_station * 0.0174532925199432957692369076848861;
	deplacementx=vitesse_station*(cos(angle_station)/20);
	deplacementy=vitesse_station*(sin(angle_station)/20);
	vecteur_de_vitesse.SetX(deplacementx);
	vecteur_de_vitesse.SetY(deplacementy); 
	SetVitesse(vecteur_de_vitesse);
}

/**
 *
 * Destructeur de base 
 * 
 */
Station::~Station()
{
	while(!mStations.empty())
	{
    delete mStations.front();
	  mStations.pop_front();
	}
}


/**
 *
 * Animation de tout les stations 
 * 
 */
void Station::animer(double dt)
{
//	evalCollisions() ;
	CPoint3D point_initial;
	CVecteur vecteur_vitesse;
	CPoint3D point_central_station;

	// Afficher tous les elements du jeus
	list<CObjetGL*>::const_iterator dernier = mStations.end();
	for(list<CObjetGL*>::const_iterator obj = mStations.begin(); obj != dernier; ++obj)
	{
		vecteur_vitesse=GetVitesse();
		point_initial=(*obj)->GetPosition();
		point_initial.SetX(point_initial.GetX()+vecteur_vitesse.GetX());
		point_initial.SetY(point_initial.GetY()+vecteur_vitesse.GetY());
		point_initial.SetZ(0);
		(*obj)->SetPosition(point_initial);
	}

	point_central_station=GetPosition();
	point_central_station.SetX(point_central_station.GetX()+vecteur_vitesse.GetX());
	point_central_station.SetY(point_central_station.GetY()+vecteur_vitesse.GetY());
	point_central_station.SetZ(0);
	SetPosition(point_central_station);
}

/**
 *
 * Afficher la scène et son contenu
 *
 *
 */
void Station::Afficher() const
{

	// Afficher tous les elements du jeus
	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	if(dernier!=obj)
	{
		for(list<CObjetGL*>::const_iterator obj = mStations.begin(); obj != dernier; ++obj)
			(*obj)->Afficher();
	}
}


/**
 *
 * Imprimer les objets se trouvant sur la scene 
 * 
 */
void Station::Imprimer( ostream& out) const
{
	CPoint3D point;
	CVecteur vecteur_vitesse;

	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	if(dernier!=obj)
	{
		for(list<CObjetGL*>::const_iterator obj = mStations.begin(); obj != dernier; ++obj)
		{
			point=(*obj)->GetPosition();

			if((*obj)->GetType()==TYPE_SPHERE)
			{
				out<<endl;
				out<<"TYPE_SPHERE"<<endl;
				out<<"POSITION"<<endl;
				out<<point.GetX()<<" "<<point.GetY()<<" "<<point.GetZ()<<endl;
				out<<"DIMENSION DE L'AIRE DE SELECTION "<<endl;
				out<<(*obj)->GetLargeur()*2<<" "<<(*obj)->Gethauteur()*2<<endl;
				out<<"ANGLE"<<endl;
				out<<(*obj)->GetAngle()<<endl;
				out<<"SELECTIONNE"<<endl;
				if((*obj)->GetSelectionne()==true)
					out<<"O"<<endl;
					else
						out<<"N"<<endl;
			}

			if((*obj)->GetType()==TYPE_CUBE)
			{
				out<<endl;
				out<<"TYPE_CUBE"<<endl;
				out<<"POSITION"<<endl;
				out<<point.GetX()<<" "<<point.GetY()<<" "<<point.GetZ()<<endl;
				out<<"DIMENSION DE L'AIRE DE SELECTION "<<endl;
				out<<(*obj)->GetLargeur()*2<<" "<<(*obj)->Gethauteur()*2<<endl;
				out<<"ANGLE"<<endl;
				out<<(*obj)->GetAngle()<<endl;
				out<<"SELECTIONNE"<<endl;
				if((*obj)->GetSelectionne()==true)
					out<<"O"<<endl;
					else
						out<<"N"<<endl;
			}

			if((*obj)->GetType()==TYPE_CYLINDRE)
			{
				out<<endl;
				out<<"TYPE_CYLINDRE"<<endl;
				out<<"POSITION"<<endl;
				out<<point.GetX()<<" "<<point.GetY()<<" "<<point.GetZ()<<endl;
				out<<"DIMENSION DE L'AIRE DE SELECTION "<<endl;
				out<<(*obj)->GetLargeur()*2<<" "<<(*obj)->Gethauteur()*2<<endl;
				out<<"ANGLE"<<endl;
				out<<(*obj)->GetAngle()<<endl;
				out<<"SELECTIONNE"<<endl;
				if((*obj)->GetSelectionne()==true)
					out<<"O"<<endl;
					else
						out<<"N"<<endl;
			}

			if((*obj)->GetType()==TYPE_PRISME)
			{
				out<<endl;
				out<<"TYPE_PRISME"<<endl;
				out<<"POSITION"<<endl;
				out<<point.GetX()<<" "<<point.GetY()<<" "<<point.GetZ()<<endl;
				out<<"DIMENSION DE L'AIRE DE SELECTION "<<endl;
				out<<(*obj)->GetLargeur()*2<<" "<<(*obj)->Gethauteur()*2<<endl;
				out<<"ANGLE"<<endl;
				out<<(*obj)->GetAngle()<<endl;
				out<<"SELECTIONNE"<<endl;
				if((*obj)->GetSelectionne()==true)
					out<<"O"<<endl;
					else
						out<<"N"<<endl;
			}

			if((*obj)->GetType()==TYPE_PROPULSION)
			{
				out<<endl;
				out<<"TYPE_PROPULSION"<<endl;
				out<<"POSITION"<<endl;
				out<<point.GetX()<<" "<<point.GetY()<<" "<<point.GetZ()<<endl;
				out<<"DIMENSION DE L'AIRE DE SELECTION "<<endl;
				out<<(*obj)->GetLargeur()*2<<" "<<(*obj)->Gethauteur()*2<<endl;
				out<<"ANGLE"<<endl;
				out<<(*obj)->GetAngle()<<endl;
				out<<"SELECTIONNE"<<endl;
				if((*obj)->GetSelectionne()==true)
					out<<"O"<<endl;
					else
						out<<"N"<<endl;
			}
		}
	}
	vecteur_vitesse=GetVitesse();
	out<<endl<<"STATION"<<endl;
	out<<vecteur_vitesse.GetX()<<" "<<vecteur_vitesse.GetY()<<" "<<vecteur_vitesse.GetZ()<<endl;
}

/**
 *
 * destruction de tous les modules composant une station 
 * 
 */
void Station::eliminerTousStations( void )
{
	mStations.clear();
}


const Station& Station::operator=( const Station& b )
{
	return( *this );
}


/**
 *
 * Ajoute une station a une liste  
 * 
 */
void Station::AjouterStation( CObjetGL* obj) 
{
//	obj->afficher_propriete();

//	cout<<mStations.empty();
	mStations.push_back(obj);
	Centre_gravite();
//	cerr<<"ca fonctionne le push back"<<endl;
}



/**
 *
 * retourne false si objet ne touche pas la station, retourne vrai si touche
 * 
 */
bool Station::Verif_station(CObjetGL* ptr) const
{


	CObjetGL* objet;
	//i=0;
	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	CPoint3D Pos_ref;
	CPoint3D Pos_comparaison;

	Pos_ref =ptr->GetPosition();

	bool trouveObj=false;
	while (obj!=dernier)
	{
		objet=*obj;
		if(objet->GetType()!=6)
		{
			Pos_comparaison =objet->GetPosition();
			//les quatre coins
			if(Pos_ref.GetX()+ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()+ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()+ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()+ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				return true;
			}

			if(Pos_ref.GetX()+ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()+ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()-ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()-ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				return true;
			}

			if(Pos_ref.GetX()-ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()-ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()+ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()+ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				return true;
			}

			if(Pos_ref.GetX()-ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()-ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()-ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()-ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				return true;
			}

			//les quatre point milieu
				if(Pos_ref.GetX()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()+ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()+ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				return true;
			}

			if(Pos_ref.GetX()+ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()+ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				return true;
			}

			if(Pos_ref.GetX()-ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()-ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				return true;
			}

			if(Pos_ref.GetX()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()-ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()-ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				return true;
			}
		}
			obj++;
		//cout<<"boucle"<<endl;

	}
	return false;
}
 

/**
 *
 * retourne l'objet pour lequel le point selectionne est inclu dans sa bounding box
 * 
 */
bool Station::SelectionModule(CPoint3D Point,CObjetGL* &ptr) const
{

	ptr=NULL;
	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	CPoint3D PositionPiece;


	bool trouveObj=false;
	while (obj!=dernier)
	{
		ptr=*obj;
		PositionPiece =ptr->GetPosition();
		if(PositionPiece.GetX()-ptr->GetLargeur() < Point.GetX() && Point.GetX()<PositionPiece.GetX()+ptr->GetLargeur() && 
			PositionPiece.GetY()-ptr->Gethauteur() < Point.GetY() && Point.GetY()<PositionPiece.GetY()+ptr->Gethauteur())
		{
		    //cout<<"selection du module"<<endl;
			//obj->Afficher();
			//(*obj)->modifierCouleur(0,0,1);
			ptr= *obj;
			
			return true;
		}
		obj++;
		//cout<<"boucle"<<endl;

	}
	return false;
}


/**
 *
 * detruit un objet
 * 
 */
void Station::destruction(CObjetGL* obj)
{
	mStations.remove(obj);
	if(mStations.size()==0)
		eliminerTousStations();

	if(mStations.size()!=0)
		Centre_gravite();
}


/**
 *
 * Vérifie si la station est incluse dans la liste
 * 
 */
bool Station::Station_incluse(CObjetGL* ptr)
{

	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	while (obj!=dernier)
	{
		if(ptr==*obj)
		{
			return true;
		}
		obj++;
	}
	return false;
}


bool Station::Station_Copie(CObjetGL* &ptr)
{


	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	
		if(dernier==obj)
		{
			//	cout<<"retourne faux"<<endl;		
			return false;

		}
			else
			{
					//cout<<"retourne vrai"<<endl;
				ptr=*obj;
				return true;	
			}

}


/**
 *
 * Compare les station une a une pour savoir si elle se touche
 * 
 */
bool Station::Verification_station_avant(CObjetGL* &pointeur)
{
	//cout<<"entre dans verif station avant"<<endl;
	bool objet_se_touche=false;
	int i=0;
	int j=0;
	CObjetGL* objet;
	CObjetGL* ptr;
	CPoint3D Pos_ref;
	CPoint3D Pos_comparaison;

	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();
	list<CObjetGL*>::const_iterator apres_obj = mStations.begin();

	
if(mStations.size()!=1)
{
	while (obj!=dernier)
	{
	//	cout<<"entre dans verif station avant1"<<endl;
		while(apres_obj!=dernier)
		{
			
			//	cout<<"entre dans verif station avant2"<<endl;
			if(i!=j)
			{
				//cout<<"entre ici dans verif station"<<endl;
				objet=*obj;
				ptr=*apres_obj;
				Pos_comparaison =objet->GetPosition();
				Pos_ref=ptr->GetPosition();
				

				objet->afficher_propriete();
				ptr->afficher_propriete();
		
				if(objet->GetType()!=6)
				{
					Pos_comparaison =objet->GetPosition();
					//les quatre coins
					if(Pos_ref.GetX()+ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()+ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
						Pos_ref.GetY()+ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()+ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
					{
						objet_se_touche=true;
						//	cout<<"1"<<endl;
					}

					if(Pos_ref.GetX()+ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()+ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
						Pos_ref.GetY()-ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()-ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
					{
						objet_se_touche=true;
						//	cout<<"2"<<endl;
					}

					if(Pos_ref.GetX()-ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()-ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
						Pos_ref.GetY()+ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()+ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
					{
						objet_se_touche=true;
						//	cout<<"3"<<endl;
					}

					if(Pos_ref.GetX()-ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()-ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
						Pos_ref.GetY()-ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()-ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
					{
						objet_se_touche=true;
						//	cout<<"4"<<endl;
					}

					//les quatre point milieu
						if(Pos_ref.GetX()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()>Pos_comparaison.GetX()-objet->GetLargeur() &&
						Pos_ref.GetY()+ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()+ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
					{
						objet_se_touche=true;
						//	cout<<"5"<<endl;
					}
	
					if(Pos_ref.GetX()+ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()+ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
						Pos_ref.GetY()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()>Pos_comparaison.GetY()-objet->Gethauteur() )
					{
						objet_se_touche=true;
						//	cout<<"6"<<endl;
					}

					if(Pos_ref.GetX()-ptr->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()-ptr->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
						Pos_ref.GetY()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()>Pos_comparaison.GetY()-objet->Gethauteur() )
					{
						objet_se_touche=true;
						//	cout<<"7"<<endl;
					}

					if(Pos_ref.GetX()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()>Pos_comparaison.GetX()-objet->GetLargeur() &&
						Pos_ref.GetY()-ptr->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()-ptr->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
					{
						objet_se_touche=true;
						//	cout<<"8"<<endl;
					}
	
					
				}
			}
		j++;		
		apres_obj++;
		}//deuxième while

	if(objet_se_touche==false)
	{
	//	cout<<"ne touche pas a aucun objet de la station donc doit etre retirer"<<endl;
		pointeur=*obj;
		return true;
	}
	i++;
	obj++;
	//objet_se_touche=false;
		//cout<<"boucle"<<endl;

	}//premier while
}
	return false;

}			

/**
 *
 * Calcule le centre de gravite d'une station
 * 
 */
void Station::Centre_gravite()
{
	double y_max;
	double y_min;
	double x_min;
	double x_max;
	double largeur;
	double hauteur;

	CPoint3D Position_objet;
	CPoint3D centre_station;

	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	Position_objet=(*obj)->GetPosition();
	y_max=Position_objet.GetY();
	y_min=Position_objet.GetY();
	x_max=Position_objet.GetX();
	x_min=Position_objet.GetX();

	obj++;

	while(obj!=dernier)
	{
		Position_objet=(*obj)->GetPosition();

		if(Position_objet.GetY()<y_min)
		{
			y_min=Position_objet.GetY();
		}

		if(Position_objet.GetY()>y_max)
		{
			y_max=Position_objet.GetY();
		}

		if(Position_objet.GetX()<x_min)
		{
			x_min=Position_objet.GetX();
		}

		if(Position_objet.GetX()>x_max)
		{
			x_max=Position_objet.GetX();
		}
		
		obj++;
	}

	if(y_max!=y_min)
	{
		centre_station.SetY(y_min+(y_max-y_min)/2);
		hauteur=2+(y_max-y_min)/2;
	}

	if(y_max==y_min)
	{
		centre_station.SetY(y_min);
		hauteur=2;
	}

	if(x_max!=x_min)
	{
		centre_station.SetX(x_min+(x_max-x_min)/2);
		largeur=2+(x_max-x_min)/2;
	}

	if(x_max==x_min)
	{
		centre_station.SetX(x_min);
		largeur=2;
	}

	centre_station.SetZ(0);

	SetPosition(centre_station);
	SetLargeur(largeur);
	SetHauteur(hauteur);

	//cout<<"Centre gravite: "<<centre_station.GetX()<<" "<<centre_station.GetY()<<" "<<centre_station.GetZ()<<endl;
	//cout<<"largeur "<<largeur<<" hauteur "<<hauteur<<endl<<endl;

}

/**
 *
 * retourne le premier module d'une liste de station
 * 
 */
void Station::RetourPremierModule(CObjetGL* &ptr)
{
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	ptr= *obj;
}


void Station::Modif_position_station(double x,double y)
{
	CPoint3D position_objet;

	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();
	//cout<<"arrive ici"<<endl;

	while (obj!=dernier)
	{
		//cout<<"dans la boucle 1"<<endl;
		position_objet=(*obj)->GetPosition();
		//cout<<"dans la boucle 2"<<endl;
		(*obj)->SetPosition(CPoint3D(position_objet.GetX()+x,position_objet.GetY()+y,position_objet.GetZ()));
	//	cout<<"dans la boucle 3"<<endl;
		obj++;
	}
//	cout<<"sort de la"<<endl;
}



/**
 *
 * retourne vrai et l'adresse de l'objet qui est touche si collision, retourne faux sinon
 * 
 */
bool Station::Eval_collision_2_station(CObjetGL* objet_reference,CObjetGL* &objet_qui_touche) const
{


	CObjetGL* objet;
	//i=0;
	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	CPoint3D Pos_ref;
	CPoint3D Pos_comparaison;

	Pos_ref =objet_reference->GetPosition();

	bool trouveObj=false;
	while (obj!=dernier)
	{
		objet=*obj;
		if(objet->GetType()!=6)
		{
			Pos_comparaison =objet->GetPosition();
			//les quatre coins
			if(Pos_ref.GetX()+objet_reference->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()+objet_reference->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()+objet_reference->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()+objet_reference->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				objet_qui_touche=*obj;
				return true;
			}

			if(Pos_ref.GetX()+objet_reference->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()+objet_reference->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()-objet_reference->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()-objet_reference->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				objet_qui_touche=*obj;
				return true;
			}

			if(Pos_ref.GetX()-objet_reference->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()-objet_reference->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()+objet_reference->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()+objet_reference->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				objet_qui_touche=*obj;
				return true;
			}

			if(Pos_ref.GetX()-objet_reference->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()-objet_reference->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()-objet_reference->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()-objet_reference->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				objet_qui_touche=*obj;
				return true;
			}

			//les quatre point milieu
				if(Pos_ref.GetX()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()+objet_reference->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()+objet_reference->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				objet_qui_touche=*obj;
				return true;
			}

			if(Pos_ref.GetX()+objet_reference->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()+objet_reference->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				objet_qui_touche=*obj;
				return true;
			}

			if(Pos_ref.GetX()-objet_reference->GetLargeur()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()-objet_reference->GetLargeur()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				objet_qui_touche=*obj;
				return true;
			}

			if(Pos_ref.GetX()<Pos_comparaison.GetX()+objet->GetLargeur() && Pos_ref.GetX()>Pos_comparaison.GetX()-objet->GetLargeur() &&
				Pos_ref.GetY()-objet_reference->Gethauteur()<Pos_comparaison.GetY()+objet->Gethauteur() && Pos_ref.GetY()-objet_reference->Gethauteur()>Pos_comparaison.GetY()-objet->Gethauteur() )
			{
				objet_qui_touche=*obj;
				return true;
			}
		}
			obj++;
		//cout<<"boucle"<<endl;

	}
	return false;
}

/**
 *
 * retourne les modules composant une station un après l'autre, tant que la liste n'a pas été
 * parcourue au complet
 * 
 */
bool Station::retour_module_station(CObjetGL* &ptr, int compteur)
{

	//cout<<"entre dans retour module station "<<compteur<<"   ";
	int i=0;
	list<CObjetGL*>::const_iterator dernier = mStations.end();
	list<CObjetGL*>::const_iterator obj = mStations.begin();

	//cout<<"entre dans retour module station"<<endl;
	while(obj!=dernier)
	{
		if(i==compteur)
		{
		//	cout<<"retourne vrai"<<endl;
			ptr=*obj;
			return true;
		}

		i++;
		obj++;
	}
//	cout<<"retourne faux"<<endl;
	return false;
}

/**
 *
 * retourne faux si liste non vide.  Retourne vrai si vide
 * 
 */
bool Station::grosseur_liste()
{
	int dimension;
	dimension=mStations.size();
	//cout<<"dimension liste:"<<dimension<<endl;
	if(dimension==0)
	{
		return true;
	}
	else
		return false;
}


int Station::nb_module_inclus()
{
	int dimension;
	dimension=mStations.size();
	return dimension;
}