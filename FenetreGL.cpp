#include "FenetreGL.h"
#include "CRU.h"
#include "Propulsion.h"
#include "TransformationGL.h"
#include "ObjetGL.h"
#include "Vecteur.h"
#define BUFSIZE 512
#include "selection3D.h"

CFenetreGL::CFenetreGL( CGlutWindow& Parent, const CPoint2D& PosFenetre,
						const CRectangle& DimFenetre, const CCouleurGL CouleurFond )
			 :CAdvGlutWnd( Parent, PosFenetre, DimFenetre, CouleurFond )
{
	CGlutMaster::timerCallback((int) this);
	// Creer un menu temporairement (un exemple pour aider)

	int sub_zoom = glutCreateMenu(CGlutMaster::CallBackMenu);
	
	glutAddMenuEntry("Zoom  In", 16);
	glutAddMenuEntry("Zoom  Out", 17);

	int sub_zoom_elast = glutCreateMenu(CGlutMaster::CallBackMenu);
	glutAddMenuEntry("Zoom In", 2);
	glutAddMenuEntry("Zoom Out", 3);

	int sub_module = glutCreateMenu(CGlutMaster::CallBackMenu);
	glutAddMenuEntry("Sphère", 4);
	glutAddMenuEntry("Cube", 5);
	glutAddMenuEntry("Cylindre", 6);
	glutAddMenuEntry("Jonction", 7);
	glutAddMenuEntry("Propulsion",8);
	glutAddMenuEntry("OVI",9);

    glutCreateMenu(CGlutMaster::CallBackMenu);

    glutAddMenuEntry("Translation de la scène", 1);
	glutAddSubMenu("Zoom",sub_zoom);
	glutAddSubMenu("Zoom élastique",sub_zoom_elast);	
	glutAddSubMenu("Ajouter module",sub_module);
	
	glutAddMenuEntry("Selectionner/Deselectionner un objet", 18);
	glutAddMenuEntry("Mode jeu", 21);
	glutAddMenuEntry("Enregistrer", 20);
	glutAddMenuEntry("Charger", 19);
	glutAddMenuEntry("Réinitialiser", 14);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Se donner une fenêtre virtuelle par défaut de dimension commode.
	m_pTransformation->SetFenetreVirtuelle( -5.0, 5.0, -5.0, 5.0 );
	TrajectoireDebutee = false;
	OVICourant = NULL;
	//cout << endl << "Inside CFenetreGL::CFenetreGL()";

	int xmin,xmax,ymin,ymax;
	m_pTransformation->GetCloture(xmin,xmax,ymin,ymax);

	GLfloat Light_pos[]={xmax+xmax,0.0,0.0,1.0};//{-1.00,1.00,1.00,1.00};
	GLfloat Light_Ka[]={1.00,1.00,1.00,1.00};
	GLfloat Light_Kd[]={1.00,1.00,1.00,1.00};
	GLfloat Light_Ks[]={1.00,1.00,1.00,1.00};

	glLightfv(GL_LIGHT0,GL_POSITION,Light_pos);
	glLightfv(GL_LIGHT0,GL_AMBIENT,Light_Ka);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,Light_Kd);
	//glLightfv(GL_LIGHT0,GL_SPECULAR,Light_Ks);
	//angle d'ouverture du spot
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,45.0);

	//glColor3d( sh.GetCouleur_r(),sh.GetCouleur_g(),sh.GetCouleur_b() );
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_DEPTH_TEST);
}

CFenetreGL::~CFenetreGL()
{
}

void CFenetreGL::Afficher()
{

	// On efface l'ancienne vue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//On prépare la matrice de modélisation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m_pCamera->PositionnerCamera();

	//S'assurer que la fenêtre virtuelle est correcte
	//...

	// Éclairage
	//...

	//Afficher la scene
	mScene->afficher();

	//On permute le front et le back buffer.
	glutSwapBuffers();
}


void CFenetreGL::Menu(int NumMenu)
{
	m_iModeSouris = NumMenu;
}


void CFenetreGL::AfficherMenuEdition()
{

	int sub_zoom = glutCreateMenu(CGlutMaster::CallBackMenu);
	
	glutAddMenuEntry("Zoom  In", 16);
	glutAddMenuEntry("Zoom  Out", 17);

	int sub_zoom_elast = glutCreateMenu(CGlutMaster::CallBackMenu);
	glutAddMenuEntry("Zoom In", 2);
	glutAddMenuEntry("Zoom Out", 3);

	int sub_module = glutCreateMenu(CGlutMaster::CallBackMenu);
	glutAddMenuEntry("Sphère", 4);
	glutAddMenuEntry("Cube", 5);
	glutAddMenuEntry("Cylindre", 6);
	glutAddMenuEntry("Jonction", 7);
	glutAddMenuEntry("Propulsion",8);
	glutAddMenuEntry("OVI",9);

    glutCreateMenu(CGlutMaster::CallBackMenu);

    glutAddMenuEntry("Translation de la scène", 1);
	glutAddSubMenu("Zoom",sub_zoom);
	glutAddSubMenu("Zoom élastique",sub_zoom_elast);	
	glutAddSubMenu("Ajouter module",sub_module);
	
	glutAddMenuEntry("Selectionner/Deselectionner un objet", 18);
	glutAddMenuEntry("Mode jeu", 21);
	glutAddMenuEntry("Enregistrer", 20);
	glutAddMenuEntry("Charger", 19);
	glutAddMenuEntry("Réinitialiser", 14);

    glutAttachMenu(GLUT_RIGHT_BUTTON);


}

void CFenetreGL::AfficherMenuModeJeu()
{
	//int sub_quitter = glutCreateMenu(CGlutMaster::CallBackMenu);
	glutCreateMenu(CGlutMaster::CallBackMenu);
	glutAddMenuEntry("Mode edition", 22);
	glutAddMenuEntry("Recommencer jeu", 24);
	glutAddMenuEntry("Arreter le jeu", 23);
	
	//glutAddSubMenu("Quitter", sub_quitter);					
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void CFenetreGL::AfficherMenuRecommencerJeu()
{

	glutCreateMenu(CGlutMaster::CallBackMenu);						
	glutAddMenuEntry("PLAY", 21);					
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void CFenetreGL::AfficherMenuSelectionObjet()

{

	glutCreateMenu(CGlutMaster::CallBackMenu);
	glutAddMenuEntry("Translation objet", 11);
	glutAddMenuEntry("Rotation objet", 12);
	glutAddMenuEntry("Trajectoire OVI", 15);
	glutAddMenuEntry("Selectionner/Deselectionner un objet", 18);
	glutAddMenuEntry("Destruction module", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


}





void CFenetreGL::ClicSouris(int button, int state, int x, int y)
{
	CAdvGlutWnd::ClicSouris(button, state, x, y);

	CPoint2D DernierCoinSouris;
	
	char elementlu[50];
	double hauteur;
	double largeur;
	double x_virt;
	double y_virt;
	double z_virt;
	double nb_pts_controle;
	double angle;
	CObjetGL* CRU1;
	CObjetGL* CRU2;
	CObjetGL* CRU3;
	CObjetGL* propulsion1;
	CObjetGL* Jonction1;
	CObjetGL* OVI1;




	switch (m_iModeSouris)
			{
				case ARRETER_MODE_JEU:
				
				Mode_jeu=false;
				m_pTransformation->SetProjection(CTransformationGL::Orthogonale);
				m_pTransformation->AppliquerFenetre();
				m_pTransformation->MettreAJourFenetre();
				AfficherMenuEdition();			

				Redraw();				
				break;
				


				case RECOMMENCER_JEU :
					if (Imprimer==true)
				{
				if(Mode_jeu==true)
				Mode_jeu=false;
				m_pTransformation->SetProjection(CTransformationGL::Orthogonale);
				m_pTransformation->AppliquerFenetre();
				m_pTransformation->MettreAJourFenetre();
	

					cout<<endl<<endl<<endl;

					mScene->eliminerTousObjets();
					//cout<<"ca semble marcher"<<endl;
					FicEntree.open("enregistrer mode jeu.txt");
						if(FicEntree.fail())
							cout<<"Probleme d'ouverture pour la lecture"<<endl;
						else
						{
							while(!FicEntree.eof())
							{
								//cout<<"element lu"<<endl;
								FicEntree.getline(elementlu,50);
								//cout<<elementlu<<endl;
								
								if(strcmp(elementlu,"TYPE_OVI")==0)
								{
									//cout<<"identifie l'ovi";
									
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									OVI1=new OVI(CPoint3D(x_virt,y_virt,0),1,1, NbrOvi);
									OVI1->Sethauteur(2);
									OVI1->SetLargeur(2);
									OVI1->SetType(TYPE_OVI);
									OVI1->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										OVI1->SetSelectionne(false);
										else
										OVI1->SetSelectionne(true);
									mScene->ajouterObjet(OVI1);
									FicEntree.getline(elementlu,50);
									FicEntree>>nb_pts_controle;
									FicEntree.getline(elementlu,50);

									for(int i=0;i<nb_pts_controle;i++)
									{
										FicEntree>>x_virt>>y_virt>>z_virt;
									//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
										FicEntree.getline(elementlu,50);
										((OVI*)(OVI1))->AjouterPtsTrajectoire(x_virt, y_virt,0);
										mScene->ajouterObjet( ((OVI*)(OVI1))->GetTrajectoire());
									}

								}

								if(strcmp(elementlu,"TYPE_SPHERE")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									CRU1= new CRU(CONTROLE);
									CRU1->SetPosition(CPoint3D(x_virt,y_virt,0));
									CRU1->Sethauteur(2);
									CRU1->SetLargeur(2);
									CRU1->SetType(TYPE_SPHERE);
									CRU1->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										CRU1->SetSelectionne(false);
										else
										CRU1->SetSelectionne(true);
									mScene->ajouterObjet(CRU1);
								}
								
								if(strcmp(elementlu,"TYPE_CUBE")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
									//cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
									//cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									CRU2= new CRU(RECHERCHE);
									CRU2->SetPosition(CPoint3D(x_virt,y_virt,0));
									CRU2->Sethauteur(0.5);
									CRU2->SetLargeur(0.5);
									CRU2->SetType(TYPE_CUBE);
									CRU2->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										CRU2->SetSelectionne(false);
										else
										CRU2->SetSelectionne(true);
									mScene->ajouterObjet(CRU2);
								}

								if(strcmp(elementlu,"TYPE_CYLINDRE")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									CRU3= new CRU(UTILITAIRE);
									CRU3->SetPosition(CPoint3D(x_virt,y_virt,0));
									CRU3->Sethauteur(1);
									CRU3->SetLargeur(1);
									CRU3->SetType(TYPE_CYLINDRE);
									CRU3->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										CRU3->SetSelectionne(false);
										else
										CRU3->SetSelectionne(true);
									mScene->ajouterObjet(CRU3);
								}

								if(strcmp(elementlu,"TYPE_PRISME")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									Jonction1= new Jonction();
									Jonction1->SetPosition(CPoint3D(x_virt,y_virt,0));
									Jonction1->Sethauteur(1);
									Jonction1->SetLargeur(1);
									Jonction1->SetType(TYPE_PRISME);
									Jonction1->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										Jonction1->SetSelectionne(false);
										else
										Jonction1->SetSelectionne(true);
									mScene->ajouterObjet(Jonction1);
								}

								if(strcmp(elementlu,"TYPE_PROPULSION")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									propulsion1= new Propulsion();
									propulsion1->SetPosition(CPoint3D(x_virt,y_virt,0));
									propulsion1->Sethauteur(1);
									propulsion1->SetLargeur(1);
									propulsion1->SetType(TYPE_PROPULSION);
									propulsion1->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										propulsion1->SetSelectionne(false);
										else
										propulsion1->SetSelectionne(true);
									mScene->ajouterObjet(propulsion1);
								}

								if(strcmp(elementlu,"STATION")==0)
								{
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									mScene->vitesse_initiale_station(x_virt,y_virt,z_virt);
								}
							
							}
						//	cout<<"arrive a la fin";
							FicEntree.close();
							FicEntree.clear();
						}
				}
				
					
					/*
					glutCreateMenu(CGlutMaster::CallBackMenu);
					//glutAddMenuEntry("Quitter", 22);	
					//glutAddMenuEntry("PAUSE", 23);	
					glutAddMenuEntry("PLAY", 21);
					
					glutAttachMenu(GLUT_RIGHT_BUTTON);*/
			
				//Mode_jeu=true;
				Redraw();
				AfficherMenuRecommencerJeu();

			break;


			case MODE_JEU:
					Mode_jeu=true;
					m_pTransformation->SetProjection(CTransformationGL::Perspective);
					m_pTransformation->AppliquerFenetre();
					m_pTransformation->MettreAJourFenetre();

					//cout<<*mScene;
					FicSortie.open("enregistrer mode jeu.txt");
						if(FicSortie.fail())
							cout<<"Probleme d'ouverture du fichier d'enregistrement";
						else
							{
							FicSortie<<*mScene;
							FicSortie.close();
							Imprimer=true;
							}				
							
						if(button==GLUT_RIGHT_BUTTON)
						{

						//	cout<<"bouton droit"<<endl;
						
							Mode_jeu=false;
							

						}


						AfficherMenuModeJeu();

					/*
					int sub_quitter = glutCreateMenu(CGlutMaster::CallBackMenu);


					//glutAddMenuEntry("Arreter", 23);				
					glutAddMenuEntry("Revenir en mode edition", 22);
					glutAddMenuEntry("Recommencer jeu", 24);
					glutAddMenuEntry("Revenir au jeu", 21);

					glutCreateMenu(CGlutMaster::CallBackMenu);
					glutAddSubMenu("Quitter", sub_quitter);	


					
					glutAttachMenu(GLUT_RIGHT_BUTTON);*/

				break;		
				
					


			}














	if (button == GLUT_LEFT  && Mode_jeu==true)

	{  

		if (state == GLUT_DOWN)
		{
			if(Selection_Station==true)
			{
				Selection_Station=false;
			}

			//m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);

			GLuint selectBuf[BUFSIZE];
			GLint hits;
			GLint viewport[4];

			glGetIntegerv(GL_VIEWPORT,viewport);
	
			glSelectBuffer(BUFSIZE, selectBuf);
			(void) glRenderMode(GL_SELECT);
			
			glInitNames();
			glPushName(0);
			
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluPickMatrix((GLdouble)(x),(GLdouble)(viewport[3]-y),5,5,viewport);
			
			m_pTransformation->AppliquerFenetre();
						
			mScene->afficher();
			
			glPopMatrix();
			
			glFlush();
			hits=glRenderMode(GL_RENDER);
				
			Nom_station_touche=m_p_selection3D->processHits(hits, selectBuf);
			m_pTransformation->MettreAJourFenetre();

			if(Nom_station_touche>0)
			{
				cout<<"ici"<<endl;
				if(mScene->Selection_de_station3d(Nom_station_touche,adresse_station)==true)
				{
					Selection_Station=true;
					cout<<"station est selectionne"<<endl;
				}
			}
			
		}
	}




if (button == GLUT_MIDDLE_BUTTON ) 
	{
	
		switch (m_iModeSouris)
		{
			case TRAJECTOIRE_OVI:
			
                //rajouter un dernier point
				if(OVICourant != NULL)
				{
					CPoint3D posOvi = OVICourant->GetPosition();
					OVICourant->AjouterPtsTrajectoireSplines(posOvi.GetX(), posOvi.GetY(),0);
					//OVICourant->AjouterPtsTrajectoire(posOvi.GetX(), posOvi.GetY(),0);
	                
	                
					//mScene->ajouterObjet( OVICourant->GetTrajectoire() );

					//retomber sur les parametres du debut
					TrajectoireDebutee = false;
					OVICourant = NULL;
				}
				Redraw();
			break;
		}
	}




	if (button == GLUT_LEFT  && Mode_jeu!=true)
	{
		if (state == GLUT_DOWN)
		{
			switch (m_iModeSouris)
			{
			case MODE_TRANSLATION:
				m_DernierPtSouris = CPoint2D(x,y);
				//m_DernierPtSouris.imprimer();
			break;

			case ZOOM_IN:
				m_pTransformation->ZoomIn();
				Redraw();
			break;

			case ZOOM_OUT:
				m_pTransformation->ZoomOut();
				Redraw();
			break;

			case MODE_ELASTIQUE_ZOOM_IN:
				m_PtAncrage = CPoint2D(x,y);
				//PremierCoinSouris.imprimer();
				InitRectangleElastique(m_PtAncrage);
			break;

			case MODE_ELASTIQUE_ZOOM_OUT:
				m_PtAncrage = CPoint2D(x,y);
				//PremierCoinSouris.imprimer();
				InitRectangleElastique(m_PtAncrage);
			break;

			case AJOUTER_SPHERE:
				CRU1= new CRU(CONTROLE);
				m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
				CRU1->SetPosition(CPoint3D(x_virt,y_virt,0));
				CRU1->Sethauteur(2);
				CRU1->SetLargeur(2);
				CRU1->SetType(TYPE_SPHERE);
				CRU1->SetAngle(0.0);
				CRU1->SetSelectionne(false);
				mScene->ajouterObjet(CRU1);
				Redraw();
			break;

			case AJOUTER_CUBE:
				CRU2= new CRU(RECHERCHE);
				m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
				CRU2->SetPosition(CPoint3D(x_virt,y_virt,0));
				CRU2->Sethauteur(0.5);
				CRU2->SetLargeur(0.5);
				CRU2->SetType(TYPE_CUBE);
				CRU2->SetAngle(0.0);
				CRU2->SetSelectionne(false);
				mScene->ajouterObjet(CRU2);
				Redraw();
			break;

			case AJOUTER_CYLINDRE:
				CRU3= new CRU(UTILITAIRE);
				m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
				CRU3->SetPosition(CPoint3D(x_virt,y_virt,0));
				CRU3->Sethauteur(1);
				CRU3->SetLargeur(1);
				CRU3->SetType(TYPE_CYLINDRE);
				CRU3->SetAngle(0.0);
				CRU3->SetSelectionne(false);
				mScene->ajouterObjet(CRU3);
				Redraw();
			break;

			case AJOUTER_PRISME_RECTANGULAIRE:
				Jonction1= new Jonction();
				m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
				Jonction1->SetPosition(CPoint3D(x_virt,y_virt,0));
				Jonction1->Sethauteur(1);
				Jonction1->SetLargeur(1);
				Jonction1->SetType(TYPE_PRISME);
				Jonction1->SetAngle(0.0);
				Jonction1->SetSelectionne(false);
				mScene->ajouterObjet(Jonction1);
				Redraw();
			break;

			case AJOUTER_PROPULSION:
				propulsion1= new Propulsion();
				m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
				propulsion1->Sethauteur(1);
				propulsion1->SetLargeur(1);
				propulsion1->SetType(TYPE_PROPULSION);
				propulsion1->SetPosition(CPoint3D(x_virt,y_virt,0));
				propulsion1->SetAngle(0.0);
				propulsion1->SetSelectionne(false);
				mScene->ajouterObjet(propulsion1);
				Redraw();
			break;

			case AJOUTER_OVI:
				m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
				OVI1=new OVI(CPoint3D(x_virt,y_virt,0),1,1, NbrOvi);
				OVI1->Sethauteur(2);
				OVI1->SetLargeur(2);
				OVI1->SetType(TYPE_OVI);
				OVI1->SetAngle(0.0);
				OVI1->SetSelectionne(false);
				mScene->ajouterObjet(OVI1);
				Redraw();
			break;

			case DESTRUCTION_OBJET:
				m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
				//if(mScene->SelectionModule(CPoint3D (x_virt,y_virt,0),adresse_module))
				if(Selection_objet==true)
				{
					Selection_objet=false;
					mScene->destruction(adresse_module);
				//	cout<<"destruction dans fenetre gl"<<endl;
				}
				Redraw();
			//	cout<<"destruction dans fenetre gl, redraw"<<endl;
			break;

			case SELECTION_OBJET:

				m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
					if(Selection_objet==true)	
					{
						adresse_module->SetSelectionne(false);				

					}
				
					if(mScene->SelectionModule(CPoint3D (x_virt,y_virt,0),adresse_module))	
					{
						Selection_objet=true;
						adresse_module->SetSelectionne(true);

						AfficherMenuSelectionObjet();

						/*glutCreateMenu(CGlutMaster::CallBackMenu);
						glutAddMenuEntry("Translation objet", 11);
						glutAddMenuEntry("Rotation objet", 12);
						glutAddMenuEntry("Trajectoire OVI", 15);
						glutAddMenuEntry("Selectionner/Deselectionner un objet", 18);
						glutAddMenuEntry("Destruction module", 10);
						glutAttachMenu(GLUT_RIGHT_BUTTON);
						//cout<<"selection d'un obj"<<endl;*/

					}

					if(!mScene->SelectionModule(CPoint3D (x_virt,y_virt,0),adresse_module)  && Selection_objet==true)	
					{
						Selection_objet=false;
					
						AfficherMenuEdition();					

					}
					Redraw();
				
			break;

			case PROPRIETE_OBJET:

				glutCreateMenu(CGlutMaster::CallBackMenu);
				glutAddMenuEntry("Translation de la scène", 1);
				glutAttachMenu(GLUT_RIGHT_BUTTON);

				cout<<"imprime"<<endl;

				mScene->imprime();

			break;

		/*	case REINITIALISER:
				mScene->eliminerTousObjets();
				Redraw();
			break;
			*/

			case ENREGISTRER:
				cout<<*mScene;
				FicSortie.open("enregistrement.txt");
					if(FicSortie.fail())
						cout<<"Probleme d'ouverture du fichier d'enregistrement";
						else
						{
							FicSortie<<*mScene;
							FicSortie.close();
							Imprimer=true;
						}
			break;

			case CHARGER:
				if (Imprimer==true)
				{

					cout<<endl<<endl<<endl;
					NbrOvi=0;

					mScene->eliminerTousObjets();
					//cout<<"ca semble marcher"<<endl;
					FicEntree.open("enregistrement.txt");
						if(FicEntree.fail())
							cout<<"Probleme d'ouverture pour la lecture"<<endl;
						else
						{
							while(!FicEntree.eof())
							{
								//cout<<"element lu"<<endl;
								FicEntree.getline(elementlu,50);
								//cout<<elementlu<<endl;
								
								if(strcmp(elementlu,"TYPE_OVI")==0)
								{
									//cout<<"identifie l'ovi";
									
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									OVI1=new OVI(CPoint3D(x_virt,y_virt,0),1,1, NbrOvi);
									OVI1->Sethauteur(2);
									OVI1->SetLargeur(2);
									OVI1->SetType(TYPE_OVI);
									OVI1->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										OVI1->SetSelectionne(false);
										else
										OVI1->SetSelectionne(true);
									mScene->ajouterObjet(OVI1);
									FicEntree.getline(elementlu,50);
									FicEntree>>nb_pts_controle;
									FicEntree.getline(elementlu,50);

									for(int i=0;i<nb_pts_controle;i++)
									{
										FicEntree>>x_virt>>y_virt>>z_virt;
									//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
										FicEntree.getline(elementlu,50);
										((OVI*)(OVI1))->AjouterPtsTrajectoire(x_virt, y_virt,0);
										mScene->ajouterObjet( ((OVI*)(OVI1))->GetTrajectoire());
									}

								}

								if(strcmp(elementlu,"TYPE_SPHERE")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									CRU1= new CRU(CONTROLE);
									CRU1->SetPosition(CPoint3D(x_virt,y_virt,0));
									CRU1->Sethauteur(2);
									CRU1->SetLargeur(2);
									CRU1->SetType(TYPE_SPHERE);
									CRU1->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										CRU1->SetSelectionne(false);
										else
										CRU1->SetSelectionne(true);
									mScene->ajouterObjet(CRU1);
								}
								
								if(strcmp(elementlu,"TYPE_CUBE")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									CRU2= new CRU(RECHERCHE);
									CRU2->SetPosition(CPoint3D(x_virt,y_virt,0));
									CRU2->Sethauteur(0.5);
									CRU2->SetLargeur(0.5);
									CRU2->SetType(TYPE_CUBE);
									CRU2->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										CRU2->SetSelectionne(false);
										else
										CRU2->SetSelectionne(true);
									mScene->ajouterObjet(CRU2);
								}

								if(strcmp(elementlu,"TYPE_CYLINDRE")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									CRU3= new CRU(UTILITAIRE);
									CRU3->SetPosition(CPoint3D(x_virt,y_virt,0));
									CRU3->Sethauteur(1);
									CRU3->SetLargeur(1);
									CRU3->SetType(TYPE_CYLINDRE);
									CRU3->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										CRU3->SetSelectionne(false);
										else
										CRU3->SetSelectionne(true);
									mScene->ajouterObjet(CRU3);
								}

								if(strcmp(elementlu,"TYPE_PRISME")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									Jonction1= new Jonction();
									Jonction1->SetPosition(CPoint3D(x_virt,y_virt,0));
									Jonction1->Sethauteur(1);
									Jonction1->SetLargeur(1);
									Jonction1->SetType(TYPE_PRISME);
									Jonction1->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										Jonction1->SetSelectionne(false);
										else
										Jonction1->SetSelectionne(true);
									mScene->ajouterObjet(Jonction1);
								}

								if(strcmp(elementlu,"TYPE_PROPULSION")==0)
								{
									FicEntree.getline(elementlu,50);
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>largeur>>hauteur;
								//	cout<<largeur<<" "<<hauteur<<" "<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree>>angle;
								//	cout<<angle<<endl;
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									FicEntree.getline(elementlu,50);
									propulsion1= new Propulsion();
									propulsion1->SetPosition(CPoint3D(x_virt,y_virt,0));
									propulsion1->Sethauteur(1);
									propulsion1->SetLargeur(1);
									propulsion1->SetType(TYPE_PROPULSION);
									propulsion1->SetAngle(angle);
									if(strcmp(elementlu,"N")==0)
										propulsion1->SetSelectionne(false);
										else
										propulsion1->SetSelectionne(true);
									mScene->ajouterObjet(propulsion1);
								}

								if(strcmp(elementlu,"STATION")==0)
								{
									FicEntree>>x_virt>>y_virt>>z_virt;
								//	cout<<x_virt<<" "<<y_virt<<" "<<z_virt<<endl;
									FicEntree.getline(elementlu,50);
									mScene->vitesse_initiale_station(x_virt,y_virt,z_virt);
								}
							
							}
						//	cout<<"arrive a la fin";
							FicEntree.close();
							FicEntree.clear();
						}
				}
				Redraw();
				break;


				case DUPLIQUER_STATION:

					dupliquer=false;

					if(Selection_Station==true)
					{
						if(adresse_station->GetType()==TYPE_OVI)
							NbrOvi++;
						m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
						mScene->dupliquer_station(adresse_station,CPoint3D(x_virt,y_virt,0),NbrOvi);
						dupliquer=true;
						Selection_Station=false;
					}

					m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
					if(mScene->Selection_de_station(CPoint3D(x_virt,y_virt,0),adresse_station)==true)
					{
						if(dupliquer==false)
						{
							Selection_Station=true;
						}
						//	cout<<"station est selectionne"<<endl;
					}
					Redraw();
				break;
				

				case REINITIALISER:					

					mScene->eliminerTousObjets();
					Redraw();
				
				break;



				case TRAJECTOIRE_OVI:
				m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
				if(!TrajectoireDebutee)
				{
					if(mScene->SelectionModule(CPoint3D (x_virt,y_virt,0), adresse_module))	
					{
				
						if(adresse_module->GetType() == TYPE_OVI)
						{
							                        
							OVICourant = (OVI*) adresse_module;
							CPoint3D posCourante = adresse_module->GetPosition();
							if(OVICourant->GetTrajectoire()==NULL)
							{
							OVICourant->AjouterPtsTrajectoireSplines(posCourante.GetX(), posCourante.GetY(),0);								
							//OVICourant->AjouterPtsTrajectoire(posCourante.GetX(), posCourante.GetY(),0);
							//mScene->ajouterObjet( OVICourant->GetTrajectoire() );
							TrajectoireDebutee = true;
							}
						}
					}
				}
				else
				{
					if(OVICourant != NULL)
					{
						OVICourant->AjouterPtsTrajectoireSplines(x_virt, y_virt,0);
						//OVICourant->AjouterPtsTrajectoire(x_virt, y_virt,0);  //TODO: Revoir les parametres du point					
					}
				}
				Redraw();

			break;
			}
		}
		if (state == GLUT_UP)
		{
			switch (m_iModeSouris)
			{
			case MODE_ELASTIQUE_ZOOM_IN:
				DernierCoinSouris = CPoint2D(x,y);
				TermineRectangleElastique(DernierCoinSouris);				
				m_pTransformation->ZoomIn(m_PtAncrage, DernierCoinSouris);
				Redraw();
			break;

			case MODE_ELASTIQUE_ZOOM_OUT:
				DernierCoinSouris = CPoint2D(x,y);
				TermineRectangleElastique(DernierCoinSouris);
				//	cout<<"premier,dernier"<<endl;
				//	PremierCoinSouris.imprimer();
				//	DernierCoinSouris.imprimer();
				if(m_PtAncrage.GetX()!=DernierCoinSouris.GetX()  && m_PtAncrage.GetY()!=DernierCoinSouris.GetY())
				{
				m_pTransformation->ZoomOut(m_PtAncrage, DernierCoinSouris);
				}
				Redraw();
			break;

			case TRANSLATION_OBJET:
				mScene->mise_jour_station(adresse_module);
			break;

			}
		}
	}
	
}

void CFenetreGL::MouseMove(int x, int y)
{
	CPoint2D PtCourantSouris;
	CPoint2D PtPrecedentSouris;
	float dx,dy;
	double x_virt;
	double y_virt;
	double angle=0;

	if (BtnGaucheEnfonce())
	{
		switch (m_iModeSouris)
		{
		case MODE_TRANSLATION:
			PtCourantSouris= CPoint2D(x,y);
			PtPrecedentSouris= m_DernierPtSouris;
			//PtCourantSouris.imprimer();
			//PtPrecedentSouris.imprimer();
			//cout<<endl;
			m_pTransformation->TranslateFenetre(PtPrecedentSouris, PtCourantSouris);
			Redraw();
		break;

		case MODE_CAM:
		
			cout<<"je sui rentre en w"<<endl;
			PtCourantSouris= CPoint2D(x,y);
			PtPrecedentSouris= m_DernierPtSouris;
			dx=PtCourantSouris.GetX() - PtPrecedentSouris.GetX();
			dy=PtCourantSouris.GetY() - PtPrecedentSouris.GetY();
			if(fabs(dx)>0.1){
			if(dx>0)
			{
				m_pCamera->IncrementerAngleRotation(3);
				//cout<<"incremnet en x "<<point.GetX()<<endl;
			}
			else
			{
				m_pCamera->IncrementerAngleRotation(-3);

			}
			}
			if(fabs(dy)>0.1){

			if(dy>0)
			{
				m_pCamera->IncrementerAngleElevation(3);
				//cout<<"incremnet en y "<<point.GetY()<<endl;
			}
			else
			{
				m_pCamera->IncrementerAngleElevation(-3);

			}
			}
			/*point.SetY(PtCourantSouris.GetY() - PtPrecedentSouris.GetY());
			m_pCamera->IncrementerAngleRotation(point.GetX());
			cout<<"incremnet en x "<<point.GetX()<<endl;
			m_pCamera->IncrementerAngleElevation(point.GetY());
			cout<<"incremnet en y "<<point.GetY()<<endl;*/

			break;

		case MODE_ELASTIQUE_ZOOM_IN:
			PtCourantSouris= CPoint2D(x,y);
			MAJRectangleElastique(PtCourantSouris);
		break;

		case MODE_ELASTIQUE_ZOOM_OUT:
			PtCourantSouris= CPoint2D(x,y);
			MAJRectangleElastique(PtCourantSouris);
		break;

		case TRANSLATION_OBJET:
			m_pTransformation->TransformerEnVirtuel(x,y,x_virt,y_virt);
			
				if(Selection_objet==true)	
				{
							
					adresse_module->SetPosition(CPoint3D (x_virt,y_virt,0));
				}
				Redraw();
		break;

		case ROTATION_OBJET:
			PtCourantSouris= CPoint2D(x,y);
			PtPrecedentSouris= m_DernierPtSouris;
			
			if(Selection_objet==true)
			{
				if(PtCourantSouris.GetX()<PtPrecedentSouris.GetX())
				{
					angle=adresse_module->GetAngle();
					angle++;
					adresse_module->SetAngle(angle);
							
				}
		
				if(PtCourantSouris.GetX()>PtPrecedentSouris.GetX())
				{
					angle=adresse_module->GetAngle();
					angle--;
					adresse_module->SetAngle(angle);
				}
			}
			Redraw();
		break;
		}
	}

	m_DernierPtSouris = CPoint2D(x,y);


}

void CFenetreGL::Clavier(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case '+':
		if(Mode_jeu!=true)
		{
			m_pTransformation->ZoomIn();
			Redraw();
		}
		break;
	case '-':
		if(Mode_jeu!=true)
		{
			m_pTransformation->ZoomOut(); 	
			Redraw();
		}
		break;
	case 'q':
		m_iModeSouris=MODE_AUCUN;
		break;
	case 'Q':
		m_iModeSouris=MODE_AUCUN;
		break;
	case 'x':
		m_iModeSouris=ARRETER_MODE_JEU;
		AfficherMenuEdition();
		m_pTransformation->SetProjection(CTransformationGL::Orthogonale);
		m_pTransformation->AppliquerFenetre();
		m_pTransformation->MettreAJourFenetre();
		if(Mode_jeu==true)
			Mode_jeu=false;
		Redraw();
		break;
	case 'X':
		m_iModeSouris=ARRETER_MODE_JEU;
		AfficherMenuEdition();
		m_pTransformation->SetProjection(CTransformationGL::Orthogonale);
		m_pTransformation->AppliquerFenetre();
		m_pTransformation->MettreAJourFenetre();
		if(Mode_jeu==true)
			Mode_jeu=false;
		Redraw();
		break;
	case 't':
		m_iModeSouris=MODE_TRANSLATION;
		break;


	case 'T':
		m_iModeSouris=MODE_TRANSLATION;
		break;
	case 'i':
		m_iModeSouris=MODE_ELASTIQUE_ZOOM_IN;
		break;
	case 'I':
		m_iModeSouris=MODE_ELASTIQUE_ZOOM_IN;
		break;
	case 'o':
		m_iModeSouris=MODE_ELASTIQUE_ZOOM_OUT;
		break;
	case 'O':
		m_iModeSouris=MODE_ELASTIQUE_ZOOM_OUT;
		break;
	case '1':
		m_iModeSouris=AJOUTER_SPHERE;
		break;
	case '2':
		m_iModeSouris=AJOUTER_CUBE;
		break;
	case '3':
		m_iModeSouris=AJOUTER_CYLINDRE;
		break;
	case '4':
		m_iModeSouris=AJOUTER_PRISME_RECTANGULAIRE;
		break;
	case '5':
		m_iModeSouris=AJOUTER_PROPULSION;
		break;
	case '6':
		m_iModeSouris=AJOUTER_OVI;
		break;
	case 'd':
		m_iModeSouris=DESTRUCTION_OBJET;
		break;
	case 'D':
		m_iModeSouris=DESTRUCTION_OBJET;
		break;
	case 'm':
		m_iModeSouris=TRANSLATION_OBJET;
		break;
	case 'M':
		m_iModeSouris=TRANSLATION_OBJET;
		break;
	case 's':
		m_iModeSouris=SELECTION_OBJET;
		AfficherMenuSelectionObjet();
		break;
	case 'S':
		m_iModeSouris=SELECTION_OBJET;
		AfficherMenuSelectionObjet();
		break;
	case 'r':
		m_iModeSouris=ROTATION_OBJET;
		break;
	case 'R':
		m_iModeSouris=ROTATION_OBJET;
		break;
	case 'p':
		m_iModeSouris=PROPRIETE_OBJET;
		break;
	case 'P':
		m_iModeSouris=PROPRIETE_OBJET;
		break;
	case 'v':
		m_iModeSouris=TRAJECTOIRE_OVI;
		break;
	case 'V':
		m_iModeSouris=TRAJECTOIRE_OVI;
		break;
	case 'k':
		m_iModeSouris=REINITIALISER;
		break;
	case 'K':
		m_iModeSouris=REINITIALISER;
	break;
	case 'Y':
		m_iModeSouris=DUPLIQUER_STATION;
		break;
	case 'y':
		m_iModeSouris=DUPLIQUER_STATION;
	break;
	case 'e':
		m_iModeSouris=ENREGISTRER;
	break;
	case 'E':
		m_iModeSouris=ENREGISTRER;
	break;
	case 'w':
	case 'W':
		m_iModeSouris=MODE_CAM;
		break;
	case 'c':
		m_iModeSouris=CHARGER;
	break;
	case 'C':
		m_iModeSouris=CHARGER;
	break;
	case 'j':
		m_iModeSouris=MODE_JEU;
		Mode_jeu=true;
		m_pTransformation->SetProjection(CTransformationGL::Perspective);
		m_pTransformation->AppliquerFenetre();
		m_pTransformation->MettreAJourFenetre();
		FicSortie.open("enregistrer mode jeu.txt");
		if(FicSortie.fail())
			cout<<"Probleme d'ouverture du fichier d'enregistrement";
			else
			{
				FicSortie<<*mScene;
				FicSortie.close();
				Imprimer=true;
			}			

		Redraw();
		AfficherMenuModeJeu();
	break;
	case 'J':
		m_iModeSouris=MODE_JEU;
		Mode_jeu=true;
		m_pTransformation->SetProjection(CTransformationGL::Perspective);
		m_pTransformation->AppliquerFenetre();
		m_pTransformation->MettreAJourFenetre();
		FicSortie.open("enregistrer mode jeu.txt");
		if(FicSortie.fail())
			cout<<"Probleme d'ouverture du fichier d'enregistrement";
			else
			{
				FicSortie<<*mScene;
				FicSortie.close();
				Imprimer=true;
			}			

		Redraw();
		AfficherMenuModeJeu();
	break;
	/*
	case 'a':
		switch (m_iModeSouris)
		{
			case TRAJECTOIRE_OVI:
			
                //rajouter un dernier point
				if(OVICourant != NULL)
				{
					CPoint3D posOvi = OVICourant->GetPosition();
					OVICourant->AjouterPtsTrajectoire(posOvi.GetX(), posOvi.GetY(),0);
	                
					//mScene->ajouterObjet( OVICourant->GetTrajectoire() );

					//retomber sur les parametres du debut
					TrajectoireDebutee = false;
					OVICourant = NULL;
				}
				Redraw();
			break;
		}

	break;
	*/
		
	}
}

void CFenetreGL::ClavierSpecial(int Key, int x, int y)
{
		switch (Key)
		{
		case GLUT_KEY_RIGHT:

			if(Mode_jeu!=true)
			{
				m_pTransformation->DeplacerFenetre(-0.1,0);
				Afficher();
			}
			if(Selection_Station==true)
			{
				//cout<<"appui sur clavier"<<endl;
				mScene->Modifier_Vecteur_vitesse(adresse_station,0,-10);
				//appeler fonction qui modifie l'angle du vecteur deplacement
			}
			break;
		case GLUT_KEY_LEFT:
			if(Mode_jeu!=true)
			{
				m_pTransformation->DeplacerFenetre(0.1,0);
				Afficher();
			}
			if(Selection_Station==true)
			{
						//		cout<<"appui sur clavier"<<endl;
				mScene->Modifier_Vecteur_vitesse(adresse_station,0,10);
				//appeler fonction qui modifie l'angle du vecteur deplacement
			}
			break;
		case GLUT_KEY_UP:
			if(Mode_jeu!=true)
			{
				m_pTransformation->DeplacerFenetre(0,-0.1);
				Afficher();
			}
			if(Selection_Station==true)
			{
							//	cout<<"appui sur clavier"<<endl;
				mScene->Modifier_Vecteur_vitesse(adresse_station,0.1,0);
				//appeler fonction qui modifie la vitesse du vecteur deplacement
			}
			break;
		case GLUT_KEY_DOWN:
			if(Mode_jeu!=true)
			{
				m_pTransformation->DeplacerFenetre(0,0.1);
				Afficher();
			}
			if(Selection_Station==true)
			{
							//	cout<<"appui sur clavier"<<endl;
				mScene->Modifier_Vecteur_vitesse(adresse_station,-0.1,0);
				//appeler fonction qui modifie la vitesse du vecteur deplacement
			}
			break;
		}
			
	
/*
	if(Mode_jeu==true)
	{
		if(Selection_Station==true)
		{
			switch (Key)
			{
			case GLUT_KEY_RIGHT:
				cout<<"touche droite"<<endl;
			//	m_pTransformation->DeplacerFenetre(-0.1,0);
			//	Afficher();
			break;
			case GLUT_KEY_LEFT:
			//	m_pTransformation->DeplacerFenetre(0.1,0);
			//	Afficher();
			break;
			case GLUT_KEY_UP:
			//	m_pTransformation->DeplacerFenetre(0,-0.1);
			//	Afficher();
			break;
			case GLUT_KEY_DOWN:
			//	m_pTransformation->DeplacerFenetre(0,0.1);
			//	Afficher();
			break;
		}
	}
	*/
}


void CFenetreGL::AvancerTemps()
{
	double xmin,xmax,ymin,ymax;

	if(Mode_jeu==true)
	{
		m_pTransformation->GetFenetreVirtuelle(xmin,xmax,ymin,ymax);
		mScene->animer(0.02,xmin,xmax,ymin,ymax);
		Redraw();
	}
}


void CFenetreGL::DemanderTimer()
{
//	while(timer == true)
//	{
		CGlutMaster::timerCallback((int)this);
//	}
}