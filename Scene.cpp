#include "Scene.h"


int i=0;

/**
 *
 * Fonction d'initialisation d'une nouvelle scène
 *
 * @return void
 * @exception
 *
 */
CScene::CScene( void )
{
	initialiser();
}

/**
 *
 * Opérateur de copie
 *
 * @param b La scène à copier :

 *
 */
const CScene& CScene::operator=( const CScene& b )
{
	return( *this );
}

/**
 *
 * Destructeur.
 *
 *
 */
CScene::~CScene( void )
{
	// On suppose qu'un Objet n'est pas dans plusieurs scènes,
	// donc on efface tous les Objets
	while(!mObjets.empty())
	{
	  delete mObjets.front();
	  mObjets.pop_front();
	}
}

/**
 *
 * Initialise le contenu de la scène 
 *
 *
 */
void CScene::initialiser()
{
	//CObjetGL* ovi1= new OVI(CPoint3D(1,1.5,0), 1,1.2f);

	//ajouterObjet( ovi1 );
}


/**
 *
 * Detecte les collisions entre objets
 *
 */
void CScene::evalcollisions()
{

	list<CObjetGL*>::const_iterator dernier_boucle1 = mObjets.end();
	list<CObjetGL*>::const_iterator dernier_boucle2 = mObjets.end();

	int i=0;
	int j=0;
	int compteur=0;
	CObjetGL* Objet_en_collision1;
	CObjetGL* Objet_en_collision2;
	CPoint3D position_station1;
	double largeur_station1;
	double hauteur_station1;
	CPoint3D position_station2;
	double largeur_station2;
	double hauteur_station2;


	for(list<CObjetGL*>::const_iterator obj_boucle1 = mObjets.begin(); obj_boucle1 != dernier_boucle1; ++obj_boucle1)
	{	
		if((*obj_boucle1)->GetType()!=TYPE_OVI)
		{
			position_station1=((Station*)(*obj_boucle1))->GetPosition();
			largeur_station1=((Station*)(*obj_boucle1))->GetLargeur();
			hauteur_station1=((Station*)(*obj_boucle1))->GetHauteur();
		}
			else
			{
				position_station1=(*obj_boucle1)->GetPosition();
				largeur_station1=(*obj_boucle1)->GetLargeur();
				hauteur_station1=(*obj_boucle1)->Gethauteur();
			}

		for(list<CObjetGL*>::const_iterator obj_boucle2 = mObjets.begin(); obj_boucle2 != dernier_boucle2; ++obj_boucle2)
		{
			if((*obj_boucle2)->GetType()!=TYPE_OVI)
			{
				position_station2=((Station*)(*obj_boucle2))->GetPosition();
				largeur_station2=((Station*)(*obj_boucle2))->GetLargeur();
				hauteur_station2=((Station*)(*obj_boucle2))->GetHauteur();
			}
				else
				{
					position_station1=(*obj_boucle2)->GetPosition();
					largeur_station1=(*obj_boucle2)->GetLargeur();
					hauteur_station1=(*obj_boucle2)->Gethauteur();
				}

			if(i!=j)
			{
				//Type de collision entre deux station
				if(position_station1.GetX()+largeur_station1<position_station2.GetX()+largeur_station2 && position_station1.GetX()+largeur_station1>position_station2.GetX()-largeur_station2 &&
				position_station1.GetY()+hauteur_station1<position_station2.GetY()+hauteur_station2 && position_station1.GetY()+hauteur_station1>position_station2.GetY()-hauteur_station2 )
				{
					//cout<<"condition collision 1"<<endl;
					//si on a 2 stations
					if((*obj_boucle1)->GetType()!=TYPE_OVI  && (*obj_boucle2)->GetType()!=TYPE_OVI)
					{
					//	cout<<"if 1"<<endl;
						//vérifier la collisions avec tout les modules composant la station1
						while(((Station*)(*obj_boucle1) )->retour_module_station(Objet_en_collision1, compteur)!=false)
						{
						//	cout<<"boucle retour module"<<endl;
							//si il y a collision
							if(((Station*)(*obj_boucle2))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
							{
								if(jonction_de_station(Objet_en_collision1,Objet_en_collision2)==true)
								{
									
								}
									else
									{
										mise_a_jour_collision(Objet_en_collision1);
										//	cout<<"mise a jour 1 faite"<<endl;
										mise_a_jour_collision(Objet_en_collision2);
										return;
									//	cout<<"mise a jour 2 faite"<<endl;
									}
							}
								compteur++;
						}
						compteur=0;
					}

					//si on a une station et un OVI
					if((*obj_boucle1)->GetType()==TYPE_OVI  && (*obj_boucle2)->GetType()!=TYPE_OVI)
					{
						//	cout<<"if 2"<<endl;
						Objet_en_collision1=*obj_boucle1;
						if(((Station*)(*obj_boucle2))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
						{
							//destruction(Objet_en_collision1);
							mise_a_jour_collision(Objet_en_collision2);
							return;

						}
						
					}

					//si on a une station et un OVI
					if((*obj_boucle1)->GetType()!=TYPE_OVI  && (*obj_boucle2)->GetType()==TYPE_OVI)
					{
						//	cout<<"if 3"<<endl;
						Objet_en_collision1=*obj_boucle2;
						if(((Station*)(*obj_boucle1))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
						{
							//destruction(Objet_en_collision1);
							mise_a_jour_collision(Objet_en_collision2);
							return;
						}
					
					}

				}

				//Type de collision entre deux station
				if(position_station1.GetX()+largeur_station1<position_station2.GetX()+largeur_station2 && position_station1.GetX()+largeur_station1>position_station2.GetX()-largeur_station2 &&
				position_station1.GetY()-hauteur_station1<position_station2.GetY()+hauteur_station2 && position_station1.GetY()-hauteur_station1>position_station2.GetY()-hauteur_station2 )
				{
					//cout<<"condition collision 1"<<endl;
					//si on a 2 stations
					if((*obj_boucle1)->GetType()!=TYPE_OVI  && (*obj_boucle2)->GetType()!=TYPE_OVI)
					{
					//	cout<<"if 1"<<endl;
						//vérifier la collisions avec tout les modules composant la station1
						while(((Station*)(*obj_boucle1))->retour_module_station(Objet_en_collision1, compteur)!=false)
						{
						//	cout<<"boucle retour module"<<endl;
							//si il y a collision
							if(((Station*)(*obj_boucle2))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
							{
								if(jonction_de_station(Objet_en_collision1,Objet_en_collision2)==true)
								{
									
								}
									else
									{
										mise_a_jour_collision(Objet_en_collision1);
										//	cout<<"mise a jour 1 faite"<<endl;
										mise_a_jour_collision(Objet_en_collision2);
										return;
									//	cout<<"mise a jour 2 faite"<<endl;
									}
							}
								compteur++;
						}
						compteur=0;
					}

					//si on a une station et un OVI
					if((*obj_boucle1)->GetType()==TYPE_OVI  && (*obj_boucle2)->GetType()!=TYPE_OVI)
					{
						//	cout<<"if 2"<<endl;
						Objet_en_collision1=*obj_boucle1;
						if(((Station*)(*obj_boucle2))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
						{
							//destruction(Objet_en_collision1);
							mise_a_jour_collision(Objet_en_collision2);
							return;

						}
						
					}

					//si on a une station et un OVI
					if((*obj_boucle1)->GetType()!=TYPE_OVI  && (*obj_boucle2)->GetType()==TYPE_OVI)
					{
						//	cout<<"if 3"<<endl;
						Objet_en_collision1=*obj_boucle2;
						if(((Station*)(*obj_boucle1))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
						{
							//destruction(Objet_en_collision1);
							mise_a_jour_collision(Objet_en_collision2);
							return;
						}
					
					}

				}

				//Type de collision entre deux station
				if(position_station1.GetX()-largeur_station1<position_station2.GetX()+largeur_station2 && position_station1.GetX()-largeur_station1>position_station2.GetX()-largeur_station2 &&
				position_station1.GetY()+hauteur_station1<position_station2.GetY()+hauteur_station2 && position_station1.GetY()+hauteur_station1>position_station2.GetY()-hauteur_station2 )
				{
					//cout<<"condition collision 1"<<endl;
					//si on a 2 stations
					if((*obj_boucle1)->GetType()!=TYPE_OVI  && (*obj_boucle2)->GetType()!=TYPE_OVI)
					{
					//	cout<<"if 1"<<endl;
						//vérifier la collisions avec tout les modules composant la station1
						while(((Station*)(*obj_boucle1))->retour_module_station(Objet_en_collision1, compteur)!=false)
						{
						//	cout<<"boucle retour module"<<endl;
							//si il y a collision
							if(((Station*)(*obj_boucle2))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
							{
								if(jonction_de_station(Objet_en_collision1,Objet_en_collision2)==true)
								{
									
								}
									else
									{
										mise_a_jour_collision(Objet_en_collision1);
										//	cout<<"mise a jour 1 faite"<<endl;
										mise_a_jour_collision(Objet_en_collision2);
										return;
									//	cout<<"mise a jour 2 faite"<<endl;
									}
							}
								compteur++;
						}
						compteur=0;
					}

					//si on a une station et un OVI
					if((*obj_boucle1)->GetType()==TYPE_OVI  && (*obj_boucle2)->GetType()!=TYPE_OVI)
					{
						//	cout<<"if 2"<<endl;
						Objet_en_collision1=*obj_boucle1;
						if(((Station*)(*obj_boucle2))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
						{
							//destruction(Objet_en_collision1);
							mise_a_jour_collision(Objet_en_collision2);
							return;

						}
						
					}

					//si on a une station et un OVI
					if((*obj_boucle1)->GetType()!=TYPE_OVI  && (*obj_boucle2)->GetType()==TYPE_OVI)
					{
						//	cout<<"if 3"<<endl;
						Objet_en_collision1=*obj_boucle2;
						if(((Station*)(*obj_boucle1))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
						{
							//destruction(Objet_en_collision1);
							mise_a_jour_collision(Objet_en_collision2);
							return;
						}
					
					}

				}

				//Type de collision entre deux station
				if(position_station1.GetX()-largeur_station1<position_station2.GetX()+largeur_station2 && position_station1.GetX()-largeur_station1>position_station2.GetX()-largeur_station2 &&
				position_station1.GetY()-hauteur_station1<position_station2.GetY()+hauteur_station2 && position_station1.GetY()-hauteur_station1>position_station2.GetY()-hauteur_station2 )
				{
					//cout<<"condition collision 1"<<endl;
					//si on a 2 stations
					if((*obj_boucle1)->GetType()!=TYPE_OVI  && (*obj_boucle2)->GetType()!=TYPE_OVI)
					{
					//	cout<<"if 1"<<endl;
						//vérifier la collisions avec tout les modules composant la station1
						while(((Station*)(*obj_boucle1))->retour_module_station(Objet_en_collision1, compteur)!=false)
						{
							//cout<<"boucle retour module"<<endl;
							//si il y a collision
							if(((Station*)(*obj_boucle2))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
							{
								if(jonction_de_station(Objet_en_collision1,Objet_en_collision2)==true)
								{
									
								}
									else
									{
										mise_a_jour_collision(Objet_en_collision1);
										//cout<<"mise a jour 1 faite"<<endl;
										mise_a_jour_collision(Objet_en_collision2);
										return;
									//	cout<<"mise a jour 2 faite"<<endl;
									}
							}
								compteur++;
						}
						compteur=0;
					}

					//si on a une station et un OVI
					if((*obj_boucle1)->GetType()==TYPE_OVI  && (*obj_boucle2)->GetType()!=TYPE_OVI)
					{
						//	cout<<"if 2"<<endl;
						Objet_en_collision1=*obj_boucle1;
						if(((Station*)(*obj_boucle2))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
						{
							//destruction(Objet_en_collision1);
							mise_a_jour_collision(Objet_en_collision2);
							return;

						}
						
					}

					//si on a une station et un OVI
					if((*obj_boucle1)->GetType()!=TYPE_OVI  && (*obj_boucle2)->GetType()==TYPE_OVI)
					{
						//	cout<<"if 3"<<endl;
						Objet_en_collision1=*obj_boucle2;
						if(((Station*)(*obj_boucle1))->Eval_collision_2_station(Objet_en_collision1,Objet_en_collision2)==true)
						{
							//destruction(Objet_en_collision1);
							mise_a_jour_collision(Objet_en_collision2);
							return;
						}
					
					}

				}

			}
			j++;
		}
		i++;
	}
}


/**
 *
 * Detecte les limite de la scene et fait rebondir les objets lorsqu'il sorte des limites
 *
 */
void CScene::evalrebonds(double xmin,double xmax,double ymin,double ymax)
{

	CPoint3D position_station;
	double largeur;
	double hauteur;
	bool changement=false;
	CVecteur vecteur_initial_vitesse;
	CVecteur nouveau_vecteur_vitesse;

	list<CObjetGL*>::const_iterator dernier = mObjets.end();

	for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
	{

		if((*obj)->GetType()!=TYPE_OVI)
		{
			position_station=((Station*)(*obj))->GetPosition();
	//		cout<<position_station.GetX<<" "<<position_station.GetY()<<endl;
			largeur=((Station*)(*obj))->GetLargeur();
			hauteur=((Station*)(*obj))->GetHauteur();
			vecteur_initial_vitesse=((Station*)(*obj))->GetVitesse();

//			cout<<"largeur-hauteur"<<largeur<<" "<<hauteur<<endl;


			//vérifie si dépasse côté gauche
			if(position_station.GetX()-largeur<xmin)
			{
				//cout<<"condition 1"<<endl;
				nouveau_vecteur_vitesse.SetX(-vecteur_initial_vitesse.GetX());
				nouveau_vecteur_vitesse.SetY(vecteur_initial_vitesse.GetY());
				changement=true;

				if(position_station.GetX()-largeur<xmin-0.5)
				{
				//	cout<<"changement position 1"<<endl;
					((Station*)(*obj))->Modif_position_station(2,0);
					((Station*)(*obj))->Centre_gravite();
				}
			}

			//vérifie si dépasse côté droit
			if(position_station.GetX()+largeur>xmax)
			{
				//cout<<"condition 2"<<endl;
				nouveau_vecteur_vitesse.SetX(-vecteur_initial_vitesse.GetX());
				nouveau_vecteur_vitesse.SetY(vecteur_initial_vitesse.GetY());
				changement=true;

				if(position_station.GetX()+largeur>xmax+0.5)
				{
					//cout<<"changement position 2"<<endl;
					((Station*)(*obj))->Modif_position_station(-2,0);
					((Station*)(*obj))->Centre_gravite();
				}
			}

			//vérifie si dépasse en bas
			if(position_station.GetY()-hauteur<ymin)
			{
				//cout<<"condition 3"<<endl;
				nouveau_vecteur_vitesse.SetX(vecteur_initial_vitesse.GetX());
				nouveau_vecteur_vitesse.SetY(-vecteur_initial_vitesse.GetY());
				changement=true;

				if(position_station.GetY()-hauteur<ymin-0.5)
				{
					//cout<<"changement position 3"<<endl;
					((Station*)(*obj))->Modif_position_station(0,2);
					((Station*)(*obj))->Centre_gravite();
				}
			}

			//vérifie si dépasse en haut
			if(position_station.GetY()+hauteur>ymax)
			{
				//cout<<"condition 4"<<endl;
				nouveau_vecteur_vitesse.SetX(vecteur_initial_vitesse.GetX());
				nouveau_vecteur_vitesse.SetY(-vecteur_initial_vitesse.GetY());
				changement=true;
				
				if(position_station.GetY()+hauteur>ymax+0.5)
				{
					//cout<<"changement position 4"<<endl;
					((Station*)(*obj))->Modif_position_station(0,-2);
					((Station*)(*obj))->Centre_gravite();
				}

			}
			
			if(changement==true)
			{
				((Station*)(*obj))->SetVitesse(nouveau_vecteur_vitesse);
				changement=false;
			}

		}
	}


}

/**
 * @fn  void CScene::animer( )
 *
 * Anime les objets de la scène 
 *
 * @param  dt intervalle de temps communiqué par Graphique
 *
 */
void CScene::animer(double dt,double xmin,double xmax,double ymin,double ymax)
{
	evalrebonds(xmin,xmax,ymin,ymax);
	evalcollisions();

	// Afficher tous les elements du jeus
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
	{
		(*obj)->animer(dt);
	}

}

/**
 *
 * Afficher la scène et son contenu
 *
 *
 */
void CScene::afficher() const
{
	int compteur=1;

	// Afficher tous les elements du jeus
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	list<CObjetGL*>::const_iterator obj = mObjets.begin();


	if(dernier!=obj)
	{
		for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
		{
			glLoadName(compteur);
			(*obj)->Afficher();
			compteur++;
		}
		
	}
}

/**
 * Imprime le contenu de la scène (à compléter)
 *
 */
void CScene::imprimer( ostream& out ) const
{
	CPoint3D point;
 	// Afficher tous les elements du jeus
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	list<CObjetGL*>::const_iterator obj = mObjets.begin();

	if(dernier!=obj)
	{
		for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
		{
			point=(*obj)->GetPosition();

			if((*obj)->GetType()==TYPE_OVI)
			{
				out<<endl;
				out<<"TYPE_OVI"<<endl;
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
				out<<"TRAJECTOIRE"<<endl;
				out<<*((OVI*)(*obj));

			}

			else
			{
				if(((Station*)(*obj))->grosseur_liste()==false)
				{
					out<<endl;
					out<<*((Station*)(*obj));
				}

			}
			i++;
		}
	}
}


/**
 * Permet d'ajouter des module)
*/

bool CScene::SelectionModule(CPoint3D Point,CObjetGL* &ptr) const
{
	i=0;
	ptr=NULL;
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	list<CObjetGL*>::const_iterator obj = mObjets.begin();

	CPoint3D PositionPiece;


	bool trouveObj=false;
	while (obj!=dernier)
	{
		//cout<<"ds selection de module"<<endl;
		if((*obj)->GetType()==TYPE_OVI)
		{
				//	cout<<"ds selection de ovi"<<endl;
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
		else
		{
			//cout<<"ds selection de autre type"<<endl;
			if(((Station*)(*obj))->SelectionModule(Point,ptr))
			{
				return true;
			}
			obj++;
		}
	}
	return false;
  }




void CScene::eliminerTousObjets( void )
{
	mObjets.clear();
}


void CScene::ajouterObjet( CObjetGL* ptr)
{ 
	cout<<"entre dans ajouter station"<<endl;
	Station* station_a_detruire;
	int compteur=0;

	int j=0;
	bool trouverobj=false;
	CObjetGL* Objet_a_copier;
	list<CObjetGL*>::const_iterator premiere_liste = mObjets.end();

	if(ptr->GetType()==6)
	{
		cout<<"ajout ovi dans liste objet"<<endl;
		mObjets.push_back(ptr);
		cout<<"ovi added "<<endl;
	}

	if(ptr->GetType()!=TYPE_OVI)
	{
		list<CObjetGL*>::const_iterator dernier = mObjets.end();
		list<CObjetGL*>::const_iterator obj = mObjets.begin();

		if(dernier!=obj)
		{
			for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
			{
				if((*obj)->GetType()!=TYPE_OVI)
				{
					if(((Station*)(*obj))->Verif_station(ptr))
					{
						//si deja ajouter a une station, pour ne pas qu'il s'ajoute a 2 station ou plus...
						if(trouverobj==true)
						{
							cout<<"ne sera pas cree deux fois"<<endl;
							station_a_detruire=((Station*)(*obj));
							cout<<"liste station trouvee"<<endl;
							mObjets.remove(station_a_detruire);
							cout<<"liste station retiree"<<endl;

							while(station_a_detruire->retour_module_station(Objet_a_copier, compteur)!=false)
							{
								cout<<"objet ajouter a la premiere liste"<<endl;
							((Station*)(*premiere_liste))->AjouterStation(Objet_a_copier);
							//cout<<compteur<<endl;
							compteur++;
							
							}
							compteur=0;
							return;
							/*
							while((((Station*)(*obj))->Station_Copie(Objet_a_copier))!=false)
							{
								Objet_a_copier->afficher_propriete();
								mise_jour_station(Objet_a_copier);
							}
							*/
						}

						//quand on doit l'ajouter a une station
						if(trouverobj==false)
						{
							cout<<"push dans une station"<<endl;
							((Station*)(*obj))->AjouterStation(ptr);
							trouverobj=true;
							premiere_liste=obj;
						}
				

					}

				}
			}
		}

		//si ne touche a aucune autre station, on crée une nouvelle station
		if(trouverobj==false)
		{
			//cout<<"nouvelle station"<<endl;
			Station* nouvelle=new Station();
			nouvelle->AjouterStation(ptr);
			mObjets.push_back(nouvelle);
		}
	}
	
}

/*
// retourne faux si l'objet ne touche a aucun autre objets, sinon elle retourne vrai 
bool CScene::Verif_station(CObjetGL* ptr) const
{
	CObjetGL* objet;
	i=0;
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	list<CObjetGL*>::const_iterator obj = mObjets.begin();

	CPoint3D Pos_ref;
	CPoint3D Pos_comparaison;

	Pos_ref =ptr->GetPosition();

	bool trouveObj=false;
	while (obj!=dernier)
	{
		objet=*obj;
		if(objet->GetType()!=6 && objet!=ptr)
		{
			Pos_comparaison =objet->GetPosition();
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
		}
			obj++;
		//cout<<"boucle"<<endl;

	}
	return false;
}
*/

void CScene::imprime() const
{
	//cout<<"dans la fct imprimer"<<endl;
	
	// Afficher tous les elements du jeus
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	list<CObjetGL*>::const_iterator obj = mObjets.begin();

	if(dernier!=obj)
	{
		for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
		{
			if((*obj)->GetType()==TYPE_OVI)
			{
				(*obj)->afficher_propriete();
			}
				else
				{
				//	cout<<"appel de station"<<endl;
					((Station*)(*obj))->afficher_propriete();
				}

		}
	}
}

/*
void CScene::enregistrer()
{
	cout<<"dans la fct imprimer"<<endl;
	
	// Afficher tous les elements du jeus
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	list<CObjetGL*>::const_iterator obj = mObjets.begin();

	if(dernier!=obj)
	{
		for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
		{
			(*obj)->imprimer_objet();
		}
	}
}
*/

void CScene::destruction(CObjetGL* ptr)
{
	list<CObjetGL*>::const_iterator dernier = mObjets.end();

	if(ptr->GetType()==TYPE_OVI)
	{
		mObjets.remove(ptr);
	}

	if(ptr->GetType()!=TYPE_OVI)
	{


		for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
		{
			if((*obj)->GetType()!=TYPE_OVI)
			{
				if(((Station*)(*obj))->Station_incluse(ptr))
				{
					((Station*)(*obj))->destruction(ptr);
									
				}
					
			}
					
		}
				
	}
		

	
}





// permet de voir s'il y a de nouvelle station ou des station à enlever ou ajouter un obj à une station
void CScene::mise_jour_station(CObjetGL* ptr)
{
//	cout<<"entre dans mis a jour station"<<endl;

	CObjetGL* Objet_en_collision1;
	int compteur=0;
	Station* station_a_detruire;

	bool premiere_entre=false;

		list<CObjetGL*>::const_iterator liste = mObjets.begin();
		list<CObjetGL*>::const_iterator dernier = mObjets.end();

			//permet de connaitre la premiere liste de ptr
	for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
		{
			if((*obj)->GetType()!=TYPE_OVI)
			{
				if(((Station*)(*obj))->Station_incluse(ptr))
				{
					station_a_detruire=((Station*)(*obj));
				}
			}
		}
							
	if(ptr->GetType()!=TYPE_OVI)
	{
			//cout<<"se rend ici"<<endl;
		//appel de la fonction destruction de module
		//cout<<"Retrait de ce module de ca station d'origine"<<endl;
		destruction(ptr);
		//appel de la fonction ajouter
		//cout<<"Ajout d'une module dans une autre station"<<endl;
		mObjets.remove(station_a_detruire);
		ajouterObjet(ptr);
		//cout<<"retour mis a jour station"<<endl;
		//mObjets.remove(station_a_detruire);
		//	cout<<"retour a jour station"<<endl;

		while(station_a_detruire->retour_module_station(Objet_en_collision1, compteur)!=false)
		{
		//	cout<<"objet ajouter"<<endl;
			ajouterObjet(Objet_en_collision1);		
			compteur++;
			//cout<<compteur<<endl;
		}
		compteur=0;
/*
		//faire une fonction qui vérifie si la station initiale de Ptr ne doit pas etre separe
		while((((Station*)(*liste))->Verification_station_avant(pointeur)!=false))
		{

			//cout<<"Retrait de ce module de ca station d'origine"<<endl;
			destruction(pointeur);

			if(premiere_entre==false)
			{
				//cout<<"nouvelle station"<<endl;
				Station* nouvelle=new Station();
				nouvelle->AjouterStation(pointeur);
				mObjets.push_back(nouvelle);
				premiere_entre=true;
			}
			else
			{
				//appel de la fonction ajouter
				//cout<<"Ajout d'une module dans une autre station"<<endl;
				ajouterObjet(pointeur);
			}
		}
*/

	cout<<endl<<endl<<endl;

	}
}

/*
void CScene::Copier_station_liste_a_autre(list<CObjetGL*>::const_iterator premiere_liste,list<CObjetGL*>::const_iterator deuxieme_liste)
{
	
}
*/



void CScene::vitesse_initiale_station(double x,double y, double z)
{
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	
	dernier--;
	CVecteur Vitesse_initiale;
	Vitesse_initiale.SetXYZ(x,y,z);

	//SetVitesse(CVecteur Vitesse)

	((Station*)(*dernier))->SetVitesse(Vitesse_initiale);
}



bool CScene::Selection_de_station(CPoint3D point_clique,CObjetGL* &ptr)
{
		ptr=NULL;
		list<CObjetGL*>::const_iterator dernier = mObjets.end();
		list<CObjetGL*>::const_iterator obj = mObjets.begin();

		CPoint3D PositionStation;
		double largeur;
		double hauteur;

	while (obj!=dernier)
	{
		
		if((*obj)->GetType()==TYPE_OVI)
		{
			PositionStation=(*obj)->GetPosition();

			if(PositionStation.GetX()-(*obj)->GetLargeur() < point_clique.GetX() && point_clique.GetX()<PositionStation.GetX()+(*obj)->GetLargeur() && 
			PositionStation.GetY()-(*obj)->Gethauteur() < point_clique.GetY() && point_clique.GetY()<PositionStation.GetY()+(*obj)->Gethauteur())
			{
				ptr= *obj;
				return true;
			}
		}

		if((*obj)->GetType()!=TYPE_OVI)
		{
			PositionStation=((Station*)(*obj))->GetPosition();
			largeur=((Station*)(*obj))->GetLargeur();
			hauteur=((Station*)(*obj))->GetHauteur();

			if(PositionStation.GetX()-largeur < point_clique.GetX() && point_clique.GetX()<PositionStation.GetX()+largeur && 
			PositionStation.GetY()-hauteur < point_clique.GetY() && point_clique.GetY()<PositionStation.GetY()+hauteur)
			{
				((Station*)(*obj))->RetourPremierModule(ptr);
				return true;
			}		
		}
		obj++;
	
	}
	return false;
}


void CScene::Modifier_Vecteur_vitesse(CObjetGL* station_selectionne,double vitesse,double angle)
{

	cout<<"entre ici"<<endl;

	CVecteur Vecteur_vitesse;
	CVecteur Nouvelle_vitesse;
	double Norme_vitesse;
	double Norme_nouvelle_vitesse;
	double Angle_vitesse;
	double Nouveau_x;
	double Nouveau_y;

	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	list<CObjetGL*>::const_iterator obj = mObjets.begin();

		while (obj!=dernier)
		{
			if((*obj)->GetType()!=TYPE_OVI)
			{
				if(((Station*)(*obj))->Station_incluse(station_selectionne)==true)
				{
					Vecteur_vitesse=((Station*)(*obj))->GetVitesse();
					

					Norme_vitesse=pow(pow(Vecteur_vitesse.GetX(),2)+pow(Vecteur_vitesse.GetY(),2),0.5);
					Angle_vitesse=Vecteur_vitesse.GetTheta();
					Norme_vitesse=Norme_vitesse+vitesse;
					Angle_vitesse=Angle_vitesse+angle*0.0174532925199432957692369076848861;
					
					Nouveau_x=Norme_vitesse*(cos(Angle_vitesse));
					Nouveau_y=Norme_vitesse*(sin(Angle_vitesse));
					Nouvelle_vitesse.SetX(Nouveau_x);
					Nouvelle_vitesse.SetY(Nouveau_y); 
					Norme_nouvelle_vitesse=pow(pow(Nouvelle_vitesse.GetX(),2)+pow(Nouvelle_vitesse.GetY(),2),0.5);
				
					if(Norme_nouvelle_vitesse>1.5)
					{
						Nouvelle_vitesse.SetX(Vecteur_vitesse.GetX());
						Nouvelle_vitesse.SetY(Vecteur_vitesse.GetY());
					}
						else
						{
							Nouvelle_vitesse.SetX(Nouveau_x);
							Nouvelle_vitesse.SetY(Nouveau_y);
						}
						
					if(Norme_nouvelle_vitesse<0.03)
					{

					//	cout<<"vitesse trop petite"<<Nouveau_x<<" "<<Nouveau_y<<endl;
						Nouvelle_vitesse.SetX(-Vecteur_vitesse.GetX()*1.5);
						Nouvelle_vitesse.SetY(-Vecteur_vitesse.GetY()*1.5);
					}
						
				//	cout<<"nouvellle vitesse en x,y:"<<Nouvelle_vitesse.GetX()<<" "<<Nouvelle_vitesse.GetY()<<endl;
					((Station*)(*obj))->SetVitesse(Nouvelle_vitesse);
				}
					
			}
		obj++;
		}
	
}


void CScene::mise_a_jour_collision(CObjetGL* ptr)
{
	CObjetGL* Objet_en_collision1;

	Station* station_a_detruire;
	int compteur=0;
//cout<<"entre dans mis a jour collision"<<endl;
bool premiere_entre=false;
	//CObjetGL* pointeur;
		list<CObjetGL*>::const_iterator liste = mObjets.begin();
		list<CObjetGL*>::const_iterator dernier = mObjets.end();

			//permet de connaitre la premiere liste de ptr
	for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
		{
			if((*obj)->GetType()!=TYPE_OVI)
			{
				if(((Station*)(*obj))->Station_incluse(ptr))
				{
					station_a_detruire=((Station*)(*obj));
				}
			}
		}
//cout<<"entre dans mis a jour collision 2"<<endl;	
				
	if(ptr->GetType()!=TYPE_OVI)
	{
		
		//appel de la fonction destruction de module
		//cout<<"Retrait de ce module de ca station d'origine"<<endl;
		destruction(ptr);
		//cout<<"se rend ici"<<endl;
		mObjets.remove(station_a_detruire);
		//cout<<"liste enlever"<<endl;


		while(station_a_detruire->retour_module_station(Objet_en_collision1, compteur)!=false)
		{
		//	cout<<"objet ajouter"<<endl;
			ajouterObjet(Objet_en_collision1);		
			compteur++;
			//cout<<compteur<<endl;
		}
		compteur=0;
	}


}


bool CScene::jonction_de_station(CObjetGL* objet1,CObjetGL* objet2)
{
	CVecteur vitesse_objet1;
	CVecteur vitesse_objet2;
	CVecteur vitesse_resultante;
	double Norme_vitesse;
	int compteur=0;
	CObjetGL* module_a_modifier;


list<CObjetGL*>::const_iterator liste1 = mObjets.begin();
list<CObjetGL*>::const_iterator liste2 = mObjets.begin();
list<CObjetGL*>::const_iterator dernier = mObjets.end();

			//permet de connaitre la premiere liste de ptr
	for(list<CObjetGL*>::const_iterator obj = mObjets.begin(); obj != dernier; ++obj)
	{
		if((*obj)->GetType()!=TYPE_OVI)
		{
			if(((Station*)(*obj))->Station_incluse(objet1))
			{
				liste1=obj;
			}

			if(((Station*)(*obj))->Station_incluse(objet2))
			{
				liste2=obj;
			}
		}

	}

	if(objet1->GetType()==TYPE_PRISME)
	{
		vitesse_objet1=((Station*)(*liste1))->GetVitesse();
		vitesse_objet2=((Station*)(*liste2))->GetVitesse();
		vitesse_resultante.SetX(vitesse_objet1.GetX()-vitesse_objet2.GetX());
		vitesse_resultante.SetY(vitesse_objet1.GetY()-vitesse_objet2.GetY());
		vitesse_resultante.SetZ(0);
		Norme_vitesse=pow(pow(vitesse_resultante.GetX(),2)+pow(vitesse_resultante.GetY(),2),0.5);
		if(Norme_vitesse<0.5)
		{
			//cout<<"Jonction de module"<<endl;
			while(((Station*)(*liste2))->retour_module_station(module_a_modifier, compteur)!=false)
			{
				destruction(module_a_modifier);
				((Station*)(*liste1))->AjouterStation(module_a_modifier);
				compteur++;
			}
			compteur=0;
			return true;
		}
		
	}

	if(objet2->GetType()==TYPE_PRISME)
	{
		vitesse_objet1=((Station*)(*liste1))->GetVitesse();
		vitesse_objet2=((Station*)(*liste2))->GetVitesse();
		vitesse_resultante.SetX(vitesse_objet1.GetX()-vitesse_objet2.GetX());
		vitesse_resultante.SetY(vitesse_objet1.GetY()-vitesse_objet2.GetY());
		vitesse_resultante.SetZ(0);
		Norme_vitesse=pow(pow(vitesse_resultante.GetX(),2)+pow(vitesse_resultante.GetY(),2),0.5);
		if(Norme_vitesse<0.5)
		{
		//	cout<<"Jonction de module"<<endl;
			while(((Station*)(*liste1))->retour_module_station(module_a_modifier, compteur)!=false)
			{
				destruction(module_a_modifier);
				((Station*)(*liste2))->AjouterStation(module_a_modifier);
				compteur++;
			}
			compteur=0;
			return true;
		}
		
	}
	
//	cout<<"retourne faux"<<endl;
	return false;
}

void CScene::dupliquer_station(CObjetGL* premier_objet_liste, CPoint3D point_clique,int NbrOvi)
{
	CTrajectoire* trajectoire_ovi;
	CObjetGL* OVI1;
	CObjetGL* CRU1;
	CObjetGL* CRU2;
	CObjetGL* CRU3;
	CObjetGL* Jonction1;
	CObjetGL* propulsion1;
	CObjetGL* module_a_dupliquer;
	int compteur=0;
	CVecteur point_retournee;
	CVecteur vitesse_module_dupliquer;
	CPoint3D pos_ovi_dupliquer;
	CPoint3D pos_station;
	CPoint3D pos_module;
	CPoint3D pos_reference;
	int dimension;

	cout<<"entre dans dupliquer station"<<endl;
	premier_objet_liste->afficher_propriete();

	Station* station_a_dupliquer;
	CObjetGL* ovi_a_dupliquer;
	
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	list<CObjetGL*>::const_iterator obj;


	if(premier_objet_liste->GetType()!=TYPE_OVI)
	{
		for(obj = mObjets.begin(); obj != dernier; ++obj)
			{
				if((*obj)->GetType()!=TYPE_OVI)
				{
					if(((Station*)(*obj))->Station_incluse(premier_objet_liste))
					{
						station_a_dupliquer=((Station*)(*obj));
						dimension=station_a_dupliquer->nb_module_inclus();
						//cout<<"dimension"<<dimension<<endl;
					}
				}
			}
		while(station_a_dupliquer->retour_module_station(module_a_dupliquer, compteur)!=false && compteur<dimension)
		{
				if(module_a_dupliquer->GetType()==TYPE_SPHERE)
				{
					CRU1= new CRU(CONTROLE);
					pos_station=station_a_dupliquer->GetPosition();
					pos_module=module_a_dupliquer->GetPosition();
					pos_reference.SetX(pos_module.GetX()-pos_station.GetX());
					pos_reference.SetY(pos_module.GetY()-pos_station.GetY());
					pos_reference.SetZ(0);
					CRU1->SetPosition(CPoint3D(point_clique.GetX()+pos_reference.GetX(),point_clique.GetY()+pos_reference.GetY(),point_clique.GetZ()+pos_reference.GetZ()));
					CRU1->Sethauteur(2);
					CRU1->SetLargeur(2);
					CRU1->SetType(TYPE_SPHERE);
					CRU1->SetAngle(module_a_dupliquer->GetAngle());
					CRU1->SetSelectionne(false);
					ajouterObjet(CRU1);					
				}
			

				if(module_a_dupliquer->GetType()==TYPE_CUBE)
				{
					CRU2= new CRU(RECHERCHE);
					pos_station=station_a_dupliquer->GetPosition();
					pos_module=module_a_dupliquer->GetPosition();
					pos_reference.SetX(pos_module.GetX()-pos_station.GetX());
					pos_reference.SetY(pos_module.GetY()-pos_station.GetY());
					pos_reference.SetZ(0);
					CRU2->SetPosition(CPoint3D(point_clique.GetX()+pos_reference.GetX(),point_clique.GetY()+pos_reference.GetY(),point_clique.GetZ()+pos_reference.GetZ()));
					CRU2->Sethauteur(0.5);
					CRU2->SetLargeur(0.5);
					CRU2->SetType(TYPE_CUBE);
					CRU2->SetAngle(module_a_dupliquer->GetAngle());
					CRU2->SetSelectionne(false);
					ajouterObjet(CRU2);
				}

				if(module_a_dupliquer->GetType()==TYPE_CYLINDRE)
				{
					CRU3= new CRU(UTILITAIRE);
					pos_station=station_a_dupliquer->GetPosition();
					pos_module=module_a_dupliquer->GetPosition();
					pos_reference.SetX(pos_module.GetX()-pos_station.GetX());
					pos_reference.SetY(pos_module.GetY()-pos_station.GetY());
					pos_reference.SetZ(0);
					CRU3->SetPosition(CPoint3D(point_clique.GetX()+pos_reference.GetX(),point_clique.GetY()+pos_reference.GetY(),point_clique.GetZ()+pos_reference.GetZ()));
					CRU3->Sethauteur(1);
					CRU3->SetLargeur(1);
					CRU3->SetType(TYPE_CYLINDRE);
					CRU3->SetAngle(module_a_dupliquer->GetAngle());
					CRU3->SetSelectionne(false);
					ajouterObjet(CRU3);
				}
			

				if(module_a_dupliquer->GetType()==TYPE_PRISME)
				{
					Jonction1= new Jonction();
					pos_station=station_a_dupliquer->GetPosition();
					pos_module=module_a_dupliquer->GetPosition();
					pos_reference.SetX(pos_module.GetX()-pos_station.GetX());
					pos_reference.SetY(pos_module.GetY()-pos_station.GetY());
					pos_reference.SetZ(0);
					Jonction1->SetPosition(CPoint3D(point_clique.GetX()+pos_reference.GetX(),point_clique.GetY()+pos_reference.GetY(),point_clique.GetZ()+pos_reference.GetZ()));
					Jonction1->Sethauteur(1);
					Jonction1->SetLargeur(1);
					Jonction1->SetType(TYPE_PRISME);
					Jonction1->SetAngle(module_a_dupliquer->GetAngle());
					Jonction1->SetSelectionne(false);
					ajouterObjet(Jonction1);
				}

				if(module_a_dupliquer->GetType()==TYPE_PROPULSION)
				{
					propulsion1= new Propulsion();
					pos_station=station_a_dupliquer->GetPosition();
					pos_module=module_a_dupliquer->GetPosition();
					pos_reference.SetX(pos_module.GetX()-pos_station.GetX());
					pos_reference.SetY(pos_module.GetY()-pos_station.GetY());
					pos_reference.SetZ(0);
					propulsion1->SetPosition(CPoint3D(point_clique.GetX()+pos_reference.GetX(),point_clique.GetY()+pos_reference.GetY(),point_clique.GetZ()+pos_reference.GetZ()));
					propulsion1->SetLargeur(1);
					propulsion1->SetType(TYPE_PROPULSION);
					propulsion1->SetAngle(module_a_dupliquer->GetAngle());
					propulsion1->SetSelectionne(false);
					ajouterObjet(propulsion1);
				}

			compteur++;
		}
		vitesse_module_dupliquer=station_a_dupliquer->GetVitesse();
		vitesse_initiale_station(vitesse_module_dupliquer.GetX(),vitesse_module_dupliquer.GetY(),0);
	}

	if(premier_objet_liste->GetType()==TYPE_OVI)
	{
		for(obj = mObjets.begin(); obj != dernier; ++obj)
		{
			if(premier_objet_liste==*obj)
			{
				ovi_a_dupliquer=*obj;
			}
		}
		cout<<"se rend ici"<<endl;
		OVI1=new OVI(CPoint3D(point_clique.GetX(),point_clique.GetY(),point_clique.GetZ()),1,1,NbrOvi);
		OVI1->Sethauteur(ovi_a_dupliquer->Gethauteur());
		OVI1->SetLargeur(ovi_a_dupliquer->GetLargeur());
		OVI1->SetType(TYPE_OVI);
		OVI1->SetAngle(ovi_a_dupliquer->GetAngle());
		OVI1->SetSelectionne(false);
		ajouterObjet(OVI1);

		pos_ovi_dupliquer=ovi_a_dupliquer->GetPosition();

		trajectoire_ovi=((OVI*)(ovi_a_dupliquer))->GetTrajectoire();
		while(trajectoire_ovi->GetPtsControle(compteur,point_retournee)!=false)
		{
			cout<<"ajout de pts a la trajectoire"<<endl;
			((OVI*)(OVI1))->AjouterPtsTrajectoire(point_retournee.GetX()-pos_ovi_dupliquer.GetX()+point_clique.GetX(),point_retournee.GetY()-pos_ovi_dupliquer.GetY()+point_clique.GetY(),point_retournee.GetZ()-pos_ovi_dupliquer.GetZ()+point_clique.GetZ());
			compteur++;
		}
	}
}


bool CScene::Selection_de_station3d(int numero_station,CObjetGL* &ptr)
{
	int i=1;
	ptr=NULL;
	list<CObjetGL*>::const_iterator dernier = mObjets.end();
	list<CObjetGL*>::const_iterator obj = mObjets.begin();

	while (i!=200)
	{
		if(i==numero_station)
		{
			((Station*)(*obj))->RetourPremierModule(ptr);
			return true;
		}	
		i++;
		obj++;	
	}
return false;
}
