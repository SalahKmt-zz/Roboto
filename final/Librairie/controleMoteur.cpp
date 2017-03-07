/*
 * Nom du fichier : controleMoteur.cpp
 * Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi,
 * Auteurs: Mohamed Salah Eddine Kamate, Christian Lortie-Cloutier
 * 2016-03-10
 * Cette classe sert a controler les moteurs avec les fonctions avancer, reculer, bouger, tournerGauche, tournerDroite, tourner, arreter
 */

//vitesse: 0 à 100% du moteur

#include "controleMoteur.h"
#include "PWM.h"

void ControleMoteur::reculer(uint8_t vitesse){
	
	DDRD = 0xff; // PORT A est en mode sortie)
    PORTD |= 0x0c; // broches 
	pwm.ajustementMoteur(vitesse, vitesse-15); // -9 ajustement de vitesse de roue droite 
}

void ControleMoteur::avancer(uint8_t vitesse){
        DDRD = 0xff; // PORT D est en mode sortie)
        PORTD &= 0xf3; 
	pwm.ajustementMoteur(vitesse, vitesse-15); // -9 ajustement de vitesse de roue droite 
}

//direction: false = reculer, true = avancer
void ControleMoteur::bouger(bool direction, uint8_t vitesse){
	if(direction){
		avancer(vitesse); // appel a la fonction avancer de la classe controleMoteur
	}else{
		reculer(vitesse); // appel a la fonction reculer de la calsse controleMoteur
	}
}

void ControleMoteur::tournerGauche(uint8_t vitesse){
        DDRD = 0xff; // PORT D est en mode sortie)
        PORTD &= 0xf3; //
	pwm.ajustementMoteur(vitesse, 0);
}

void ControleMoteur::tournerDroite(uint8_t vitesse){
	DDRD = 0xff; // PORT A est en mode sortie)
    PORTD &= 0xf3; //
	pwm.ajustementMoteur(0, vitesse);
}

//direction: false = gauche, true = droite
void ControleMoteur::tourner(bool direction, uint8_t vitesse){
	if(direction){
		tournerDroite(vitesse);
	}else{
		tournerGauche(vitesse);
	}
}

void ControleMoteur::arreter(){
	DDRD = 0xff; // PORT A est en mode sortie)
    PORTD |= 0x0c;//
    pwm.ajustementMoteur(0,0);

}
