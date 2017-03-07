/*
 *Nom du fichier : PWM.h
 *Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi,
 *Auteurs: Mohamed Salah Eddine Kamate, Christian Lortie-Cloutier
 *2016-03-10
 * Cette classe sert a controler le PWM de facon materielle
 */

#ifndef PWM_H
#define PWM_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>

class PWM
{
	public : 
	
	// Méthode  pour ajuster le Piezo et qui prend en paramêtre  un numéro de la note du tableau des notes musicales
    void ajustementPiezo (uint8_t numero);

	// Méthode pour ajuster la fréquence du Piezo selon la note qui devrait être jouée
	void ajustementPiezo (float frequence);
    
    // fonction qui va ajuter le PWM en prenant en parametre les deux moteurs pour des fins de comparaison des registres
    void ajustementMoteur (uint8_t moteurGauche, uint8_t moteurDroit); 
	
	private :
};

	


#endif
