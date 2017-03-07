/*
 * Nom du fichier : Memoire.cpp
 * Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi, Mohamed Salah Eddine Kamate et Christian Lortie-Cloutier
 * 2016-03-10 
 * Cette classe definit les fonctions qui seront utilisées pour la manipulation de la memoire 
 */
 
#include "Memoire.h"

Memoire::Memoire()
{} // constructeur par defaut



Memoire::~Memoire()
{} // destructeur de la classe 


void Memoire::transmissionUART ( uint8_t donnee ) // De l'USART vers le PC
{

	while(!(UCSR0A & (1<<UDRE0))){
		}
	UDR0 = donnee;
}

void Memoire::transmissionPC ( uint8_t *donnee ) // De l'UART vers le PC
{
	while (!(UCSR0A & (1<<RXC0))){
		} 
	*donnee = UDR0;
}

void Memoire::initialisationUART ( void ) {

	// 2400 bauds. Nous vous donnons la valeur des deux

	// premier registres pour vous éviter des complications

	UBRR0H = 0;

	UBRR0L = 0xCF;

	// permettre la reception et la transmission par le UART0

//	UCSR0A = 0x00 ;

	// Bits 3 et 4 à 1 pour permettre la reception et la transmission
//	UCSR0B = 0x18;

	// Format des trames: 8 bits, 1 stop bits, none parity
	// Bits 2 et 3 à 1
//	UCSR0C = 0x6 ;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //page 187 doc. Atmel
	UCSR0A = 0x00;
/* Set frame format: 8 bits data, 1 bits stop , without parity */
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

}
