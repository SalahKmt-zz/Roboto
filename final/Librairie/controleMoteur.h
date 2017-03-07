/*
 *Nom du fichier : PWM.h
 *Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi,
 *Auteurs: Mohamed Salah Eddine Kamate, Christian Lortie-Cloutier
 *2016-03-10
 * Cette classe sert a controler le PWM de facon materielle
 */

#ifndef CONTROLEMOTEUR_H
#define CONTROLEMOTEUR_H 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include "PWM.h"


class ControleMoteur

{ 
	public:
// fonction avancer qui prend en parametre un uint8_t qui sera consideré comme la vitesse 
void avancer(uint8_t vitesse); 

// fonction reculer qui prend en parametre un uint8_t qui sera consideré comme la vitesse 
void reculer(uint8_t vitesse);

//direction: false = reculer, true = avancer
void bouger(bool direction, uint8_t vitesse);

// fonction trounerGauche qui prend en parametre un uint8_t qui sera consideré comme la vitesse 
void tournerGauche(uint8_t vitesse);

// fonction trounerDroite qui prend en parametre un uint8_t qui sera consideré comme la vitesse 
void tournerDroite(uint8_t vitesse);

//fonction direction: false = gauche, true = droite
void tourner(bool direction, uint8_t vitesse);

// fonction arreter qui arretera de faire tourner les moteurs
void arreter();

// attribut pwm qui sera utilisé dans l'implémentation des différentes fonctions
PWM pwm;

private:
// ne rien faire ici
};

#endif
