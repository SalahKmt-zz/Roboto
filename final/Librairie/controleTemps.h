/*
 *Nom du fichier : controleTemps.h
 *Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi,
 *Auteurs: Mohamed Salah Eddine Kamate, Christian Lortie-Cloutier
 *2016-03-10 
 *controle des delais et de la minuterie (timer)
 */


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>



class ControleTemps
{
public :

volatile uint8_t minuterieExpiree;

// fonction de controle de la minuterie
void partirMinuterie (uint16_t duree, uint16_t prescaler); 

// fonction qui controle les delais de facon variable (us)
void delaiUs(const float delai); 

// fonction qui controle les delais de facon variable (ms)
void delaiMs(const uint16_t delai); 

private : 
// ne rien faire ici
};
