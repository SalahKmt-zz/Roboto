/*
 *Nom du fichier : tp5.3.cpp
 *Auteurs: Evelyne Lafontaine-Michel et Hicham El Fouladi
 *2016-01-28
 *Résolution du problème 3, tp 5
 *
 */


#include "PWM.h"

// declaration du tableau de frequences pour les notes musicales
float tableauFrequences[37] = {110.0, 116.5409404, 123.4708253,
	 130.8127827, 138.5913155, 146.832384, 155.5634919, 164.8137785,
	 174.6141157, 184.9972114, 195.997718, 207.6523488, 220.0,
	 233.0818808, 246.9416506, 261.6255653, 277.182631, 293.6647679,
	 311.1269837, 329.6275569, 349.2282314, 369.9944227, 391.995436,
	 415.3046976, 440.0, 466.1637615, 493.8833013, 523.2511306,
	 554.365262, 587.3295358, 622.2539674, 659.2551138, 698.4564629,
	 739.9888454, 783.990872, 830.6093952, 880.0};

// ajustement du Piezo pour usiliser les fréquences
void PWM::ajustementPiezo (uint8_t numero){

	ajustementPiezo(tableauFrequences[numero - 45]); 
}                     


void PWM::ajustementPiezo (float frequence)
{
	// mise a un de la sortie OC1A sur comparaison
	// reussie en mode PWM phase et fréquence correcte    
	// et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5    
	// page 130 de la description technique du ATmega324PA)    
	
	// si frequence = 0 on ajuste le registre TCCR0A a 0 
	if (frequence == 0.0){
		TCCR0A = 0x00;
	}
	
	// sinon on ajuste les parties du registre TCCR0A suivantes
	else
	{ 
    TCCR0A |= (1 << COM0A0) | (0 << WGM00) | (1 << WGM01) |(1 << COM0B1);
    
    // division d'horloge par 256 - implique une frequence de PWM fixe 
    // on ajuste la frequence a une valeur raisonnable  pour l'utilisation des notes   
	OCR0A = 8000000 / (256 * (frequence) *2);     
		
	TCCR0B |= (1 << CS02);
	}
	
	
}

void PWM::ajustementMoteur (uint8_t moteurDroit, uint8_t moteurGauche)
{
    // mise a un des sorties OC1A et OC1B sur comparaison
	// reussie en mode PWM 8 bits, phase correcte    
	// et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5    
	// page 130 de la description technique du ATmega324PA)    
	
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    
    // ajuster OCR1A et OCR1B aux moteurs Gauche et Droite respectivement pour des fins de comparaison
	OCR1A = moteurDroit;    
	OCR1B = moteurGauche;    
	
		        
	TCCR1B = 0x02;    
	TCCR1C = 0x00;
}

