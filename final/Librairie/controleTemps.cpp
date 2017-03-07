/*
 *Nom du fichier : controleTemps.cpp
 *Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi, Mohamed Salah Eddine Kamate et Christian Lortie-Cloutier
 *2016-03-10 
 *controle des delais et de la minuterie (timer)
 */

#include "controleTemps.h"


void ControleTemps::partirMinuterie (uint16_t duree, uint16_t prescaler)
{
	minuterieExpiree = 0; // la minuterie expire a 0

	// mode CTC du timer 1 avec horloge divisee par 1024

	// interruption apres la duree specifiee

	TCNT1 = 0;

	OCR1A = duree; // la duree de la minuterie

	TCCR1A = 0x0C;//C = mode CTC 

	TCCR1B = prescaler;//met un prescaler selon la valeur entree en parametre

	TCCR1C = 0; 

	TIMSK1 = 0x02; //TIMER1_COMPA_vect

}


void ControleTemps::delaiUs(const float delai) // fonction qui controle les delais variables en us
{
	for (int i = 0; i < delai/10; i++){	
		_delay_us(10);
	}
}

void ControleTemps::delaiMs(const uint16_t delai) // fonction qui controle les delais variables en ms
{
        for (int i = 0; i < delai; i++){
                _delay_ms(1);
	}
}
