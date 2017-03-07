/**********************************************************************************************
* Auteur(s)     : Evelyne Lafontaine-Michel, Hicham El Fouladi,
						Mohamed Salah Eddine Kamate et Christian Lortie-Cloutier

* Description   :
			l'epreuve finale d'INF1995. 
				*Le robot doit effectuer le parcours :
				*prendre la direction dictee par les boutons poussoirs dans les embranchements
				*faire la boucle
				*allumer les dels lorsque la photoresistance passe dans le tunnel
				*emettre un son aigu quand il passera sur les poitillées

* Date de creation     : 2016-03-23
* Date de modification : 2016-03-23
**************************************************************************************************/

#define F_CPU 6000000
#include <avr/io.h>
#include <util/delay.h>
#include <controleMoteur.h>
#include <ControleDel.h>
#include <PWM.h>
#include <can.h>
#define C1 (PINC&0x01)
#define C2 (PINC&0x02) 
#define C3 (PINC&0x04)
#define C4 (PINC&0x08) 
#define C5 (PINC&0x10)


volatile char direction[3];
volatile uint8_t indiceDirections;

ControleDel del;	
ControleMoteur moteur;
PWM pwm;
can convertisseur;
bool lecture[6];
enum Etat {depart, ajustement, coin, virageDroit, boucle, checkpoint, pointilles, embranchementU, embranchementV, arret};



/************************************************************************************************************************************
* fonction: allumerDelGauche
* description: 	allumera la del gauche du breadboard
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
void allumerDelGauche(){
	del.portBSortie();
	PORTB = 0x2;
	_delay_ms(500);
	PORTB = 0;
	_delay_ms(500);
	del.portBEntree();
}

/************************************************************************************************************************************
* fonction: allumerDelDroite
* description: 	permet d'allumer la del droite du breadboard
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
void allumerDelDroite(){
	del.portBSortie();
	PORTB = 0x20;
	_delay_ms(500);
	PORTB = 0;
	_delay_ms(500);
	del.portBEntree();
}

/************************************************************************************************************************************
* fonction: lireCapteur
* description: 	permet de mettre chaque PIN lue dans un tableau
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
void lireCapteur(){
	lecture[1] = C1;
	lecture[2] = C2;
	lecture[3] = C3;
	lecture[4] = C4;
	lecture[5] = C5;
}

/************************************************************************************************************************************
* fonction: vide
* description: 	tester si le robot est au dessus d'un vide	
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/

bool vide(){
	
	if (!(lecture[1]) && !(lecture[2]) && !(lecture[3]) && !(lecture[4]) && !(lecture[5])){
		//allumerDelGauche();
		return true;
	}
	return false;
}


/************************************************************************************************************************************
* fonction: videDelai(){
* description: 	tester pour un vide avec un "anti-rebond (delai)" 
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/

bool videDelai(){
	if (!(lecture[1]) && !(lecture[2]) && !(lecture[3]) && !(lecture[4]) && !(lecture[5])){
		_delay_ms(50);
		//test de rebond avec une nouvelle lecture
		if (!(C1) && !(C2) && !(C3) && !(C4) && !(C5)){
			return true;
		}
	}
	return false;
}


/************************************************************************************************************************************
* fonction: lignePleine
* description: 	tester si tous les capteurs sont allumes
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/

bool lignePleine(){
	if ((lecture[1]) && (lecture[2]) && (lecture[3]) && (lecture[4]) && (lecture[5])){
		_delay_ms(50);
		//test de rebond avec une nouvelle lecture
		if ((C1) && (C2) && (C3) && (C4) && (C5)){
			return true;
		}
	}
	return false;
}

/************************************************************************************************************************************
* fonction: brancheEnV
* description: tester pour l'embranchement en flèche (ou V)
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/

//test pour l'embranchement en flèche (ou V)
bool brancheEnV(){
	
	return ((lecture[1] && lecture[3] && lecture[5]) || (lecture[2] && lecture[3] && lecture[5]) || (lecture[5] && lecture[4] && lecture[2]) || (lecture[1] && lecture[3] && lecture[4]));
	
}


/************************************************************************************************************************************
* fonction: conditionCoin
* description: 	tester si on est arrivé à un coin
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/

bool conditionCoin(){
	if ((!C1 && !C2 && C3 && C4 && C5) || (!C1 && C2 && C3 && C4 && C5)){
		moteur.arreter();
		_delay_ms(200);
	
		if (!C1){
			return true;
		}
	}
/*
		if (C1 && C2 && C3 && C4 && C5){
			return false;
		}
		if ((!C1 && !C2 && C3 && C4 && C5) || (!C1 && C2 && C3 && C4 && C5)){
			_delay_ms(50);
			if (C1 && C2 && C3 && C4 && C5){
				return false;
			}
			//test de rebond avec une nouvelle lecture
			if ((!C1 && !C2 && C3 && C4 && C5) || (!C1 && C2 && C3 && C4 && C5)){
				_delay_ms(50);
				if (C1 && C2 && C3 && C4 && C5){
					return false;
				}
				if ((!C1 && !C2 && C3 && C4 && C5) || (!C1 && C2 && C3 && C4 && C5)){
					_delay_ms(50);
					if (C1 && C2 && C3 && C4 && C5){
						return false;
					}
					if ((!C1 && !C2 && C3 && C4 && C5) || (!C1 && C2 && C3 && C4 && C5)){
						return true;
					}
				}
			}
		}
	
*/
	return false;
}

/************************************************************************************************************************************
* fonction: jouerSonAigu
* description: 	joue un son aigu avec le Piezo
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
	
void jouerSonAigu(){
	pwm.ajustementPiezo((uint8_t)60);
}


/************************************************************************************************************************************
* fonction: jouerSonGrave
* description: joue un son aigu avec le Piezo
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
void jouerSonGrave(){
	pwm.ajustementPiezo((uint8_t)50);
}

/************************************************************************************************************************************
* fonction: arreterSon
* description: 	arrete de jouer le son du Piezo
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
void arreterSon(){
	pwm.ajustementPiezo((float)0.0);
}

/************************************************************************************************************************************
* fonction: initialisation
* description: 	fonction de départ du parcourt, lit les données des boutons poussoirs 
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
void initialisation()
{
	
	//permets aux dels d'être activées par les boutons
	del.activerDelsExterneAvecBoutons();
	
	indiceDirections = 0;
	//lecture de 3 pressage de bouton
	while (indiceDirections < 3)
	{ 
		if (PINB & 0x02 || PINB& 0x20) 
		{
			_delay_ms (10); // Delai pour assurer que c'est bien l'utilisateur qui appuie sur le bouton
			if (PINB & 0x02) // bouton gauche sur le breadboard 
			{
				//on mémorise la direction désirée dans le tableau de directions
				direction[indiceDirections] = 'G';
				++indiceDirections;
			}else{ // bouton droit sur le breadboard
				//on mémorise la direction désirée dans le tableau de directions
				direction[indiceDirections] = 'D';
				++indiceDirections;
			}
			while(PINB & 0x02 || PINB& 0x20) { // Tant que le bouton est pressé, ne rien faire d'autre
				_delay_ms (10);
			}
		
		}

	}
	
	indiceDirections = 0;
	
	_delay_ms(1000);
	//remettre les dels en sortie
	del.portBSortie();
}


/************************************************************************************************************************************
* fonction: controlerPhotoresistance
* description: 	controler les dels dependamment de la valeur lue par la photoresistance
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
// 
void controlerPhotoresistance()
{
	uint8_t valeurLue = convertisseur.lecture(0) >> 2;
	//Voltage fort, lumière faible
	if (valeurLue < 230){
	del.allumerDelExterne();
	}else{
		del.eteindreDelExterne();
	} 	
}	


/************************************************************************************************************************************
* fonction: avancer
* description: 	fonction qui d'ajustement du robot sur les lignes en s'ajustant sur le détecteur du centre
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
void avancer(){
	
	// si 3e del du capteur aller tout droit	
	if (lecture[3]){
		moteur.avancer(125);
	}

	// ajustement vers la droite
	if (lecture[4] || lecture[5]){
		pwm.ajustementMoteur(80, 125); // revenir légèrement vers la droite
	}

	// ajustement vers la gauche
	else if (lecture[2] || lecture[1]){
		pwm.ajustementMoteur(125, 60); // revenir légèrement vers la gauche
	}
}

/************************************************************************************************************************************
* fonction: avancerBrancheVGauche
* description: 	fonction qui ajuste le robot quand il prendra la branche gauche du branchement en V
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
void avancerBrancheVGauche(){
	
	// si 3e del du capteur aller tout droit	
	if (lecture[3] || lecture[5] || lecture [4]){
		moteur.avancer(125);
	}

	// ajustement vers la droite
	if (vide()){
		pwm.ajustementMoteur(60, 125); // revenir légèrement vers la droite
	}

	// ajustement vers la gauche
	else if (lecture[2] || lecture[1]){
		pwm.ajustementMoteur(125, 60); // revenir légèrement vers la gauche
	}
}
/************************************************************************************************************************************
* fonction: ajusterEmbranchementU
* description: 	dicte la direction à prendre dans le branchement en U dépendamment des boutons poussoirs
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
void ajusterEmbranchementU()
{
	if (indiceDirections <= 2){
		// si bouton poussoir gauche 
		if (direction[indiceDirections] == 'G'){
			while(vide()){
				pwm.ajustementMoteur(125, 60);
				lireCapteur();
			}
		// si bouton poussoir droit
		}else if (direction[indiceDirections] == 'D'){
			while(vide()){
				pwm.ajustementMoteur(60, 125);
				lireCapteur();
			}
		}
		++indiceDirections;	
	}
}	

/************************************************************************************************************************************
* fonction: ajusterEmbranchementV
* description: 	dicte la direction à prendre dans le branchement en V dépendamment des boutons poussoirs
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
	
void ajusterEmbranchementV()
{
	if (indiceDirections <= 2){
		if (direction[indiceDirections] == 'G'){
			do{
				pwm.ajustementMoteur(125, 60);
				lireCapteur();
				} while(!vide());
			
			do {
				lireCapteur();
				pwm.ajustementMoteur(60, 125);
			}while (!lecture[4]);
			do{
				lireCapteur();
				avancerBrancheVGauche(); //Pour compenser la force des moteurs
			}while (!vide());
			
			while(vide()){
				lireCapteur();
				pwm.ajustementMoteur(60, 125);
			}
				
		}else if (direction[indiceDirections] == 'D'){
			do{
				pwm.ajustementMoteur(60, 125);
				lireCapteur();
			}while(!(lecture[1] && !lecture[2] && !lecture[3] && !lecture[4] && !lecture[5]));
		
			do{
				lireCapteur();
				avancer();
			}while(!vide());
			
			while(vide()){
				lireCapteur();
				pwm.ajustementMoteur(125, 60);
			}
		}
		++indiceDirections;	
	}
}


/************************************************************************************************************************************
* fonction: main
* description: 	fonction principale
* Paramètres: aucun
* Retour: aucun
************************************************************************************************************************************/
int main ()
{
	
	Etat etatTrajet = depart;
	
	DDRC = 0x00; // detecteur de ligne (broches 0-5)
	DDRA = 0x00; // photorésistance (broche 0)
	DDRD = 0xff; // moteurs (broches 

/*	
	premiereLigne = false;
	deuxiemeLigne = false;
	tournerDroite = false;
	*/
	
	//tests	
	del.allumerDelExterne();
	_delay_ms(100);
	del.eteindreDelExterne();
	_delay_ms(100);
	//fin tests
	uint8_t compteurBoucle = 0;
	uint8_t compteurCheckpoint = 0;
	uint8_t compteurPointilles = 0;
	uint8_t estApresCoin = false;
	for (;;)
	{
	
		
		lireCapteur();
		
		switch (etatTrajet){
			
			case depart:
				initialisation(); // controler les dels du breadboard avec les boutons poussoir
				/*
				for (uint8_t i = 0; i < 3; ++i){
					if (direction[i] == 'G'){
						allumerDelGauche();
					}else if (direction[i] == 'D'){
						allumerDelDroite();
					}
				}*/
				etatTrajet = checkpoint;
				break;
				
			case checkpoint:
				estApresCoin = false;
				if (compteurCheckpoint < 3){
					avancer();	
										
					if (brancheEnV()){
						etatTrajet = embranchementV;
						break;
					}else if (videDelai()){
						etatTrajet = embranchementU;
						break;
					}
				}else{
					etatTrajet = arret;
				}
				break;
			case ajustement:
				//arreterSon();
				del.eteindreDelExterne();
				avancer();
				controlerPhotoresistance();
				
				if (conditionCoin()){
					etatTrajet = coin;
				}
				else if (lignePleine()){ 
					if (compteurBoucle == 3){
						etatTrajet = boucle;
					}else{
						bool check1 = false;
						bool check2 = false;
						bool check3 = false;
						do{
							avancer();
							lireCapteur();
							check1 = true;
						}while(lignePleine());
						do{
							avancer();
							lireCapteur();
							check2 = true;
						}while (!lecture[1] && !lecture[5]);
						do{
							avancer();
							lireCapteur();
							check3 = true;
						}while(lignePleine());
						if (check1 && check2 && check3){
							moteur.avancer(125);
							_delay_ms(500);
							compteurBoucle = 0;
							etatTrajet = checkpoint;
							compteurCheckpoint++;
							break;
						}
					}
				}
				
				if(videDelai() && estApresCoin){
					etatTrajet = pointilles;
				}
				break;
			case coin:
				moteur.avancer(125);
				_delay_ms(500);
				moteur.arreter();
				_delay_ms(200);
				
				lireCapteur();
				if(videDelai()){
					
					etatTrajet = virageDroit;
					break;
				}else if ((lecture[1] || lecture[2] || lecture [3] || lecture[4] || lecture[5]) && estApresCoin){
					etatTrajet = boucle;
					break;
				}
				break;
			case virageDroit:
				estApresCoin = true;
				del.allumerDelExterne();
				/*
				del.allumerDelExterne();
				moteur.avancer(110);
				_delay_ms(500);
				moteur.arreter();
				_delay_ms(250);
				*/
				
				//dans le cas du premier virage pour entamer la boucle,
				//entamer un virage pour ne pas être gêné par la ligne
				//sur laquelle le robot se trouve déjà et bien effectuer le virage
				if (compteurBoucle == 3){
					moteur.tournerDroite(100);
					_delay_ms(200);
				}
				if  (compteurBoucle == 4){
					moteur.avancer(125);
					_delay_ms(500);
				}
				do {
					moteur.tournerDroite(90);
					lireCapteur();
				} while(!lecture[4]);
				moteur.arreter();
				_delay_ms(100);
				avancer();
				/*
				do {
					
					if (C4 || C5){
						pwm.ajustementMoteur(20, 100);
					}
					if (C2 || C1){
						pwm.ajustementMoteur(110, 0);
					}
				}while (!C3);
				*/
				etatTrajet = ajustement;
				del.eteindreDelExterne();
				
				break;
			case boucle:
				estApresCoin = false;
				//jouerSonGrave();
				//_delay_ms(100);
				//arreterSon();
				switch(compteurBoucle){
					case 0:
						++compteurBoucle;
						etatTrajet = ajustement;
						break;
					case 1:
						++compteurBoucle;
						etatTrajet = ajustement;
						break;
					case 2:
						++compteurBoucle;
						etatTrajet = virageDroit;
						break;
					case 3:
						++compteurBoucle;
						etatTrajet = virageDroit;
						break;
					default:
						etatTrajet = ajustement;
						break;
				}
				break;
			case pointilles:
				switch(compteurPointilles){
					case 0:
						do{
							avancer();
							lireCapteur();
						}while(vide());
						++compteurPointilles;
						etatTrajet = ajustement;
						break;
					case 1:
						do{
							avancer();
							lireCapteur();
						}while(vide());
						++compteurPointilles;
						etatTrajet = ajustement;
						break;
					case 2:
						jouerSonAigu();
						do{
							avancer();
							lireCapteur();
						}while(vide());
						++compteurPointilles;
						etatTrajet = ajustement;
						break;
					case 3:
						do{
							avancer();
							lireCapteur();
						}while(vide());
						++compteurPointilles;
						etatTrajet = ajustement;
						break;
					case 4:
						do{
							avancer();
							lireCapteur();
						}while(vide());
						++compteurPointilles;
						etatTrajet = ajustement;
						break;
					case 5:
						do{
							avancer();
							lireCapteur();
						}while(vide());
						++compteurPointilles;
						etatTrajet = ajustement;
						break;
					case 6:
						do{
							avancer();
							lireCapteur();
						}while(vide());
						++compteurPointilles;
						arreterSon();
						etatTrajet = ajustement;
						break;
					default:
						etatTrajet = ajustement;
						break;
					}
					break;
				break;
			case embranchementU:
				estApresCoin = false;
				ajusterEmbranchementU();
				etatTrajet = ajustement;
				compteurBoucle = 0;
				break;
			case embranchementV:
				estApresCoin = false;
				ajusterEmbranchementV();
				etatTrajet = ajustement;
				compteurBoucle = 0;
				break;
			case arret:
				moteur.arreter();
				break;
		}

	}
	
	return 0;
}
