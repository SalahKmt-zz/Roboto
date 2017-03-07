/*
 * Nom du fichier : Memoire.h
 * Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi, Mohamed Salah Eddine Kamate et Christian Lortie-Cloutier
 * 2016-03-10 
 * Cette classe definit les fonctions qui seront utiliser pour la manipulation de la memoire 
 */


#ifndef MEMOIRE_H
#define MEMOIRE_H

#define F_CPU 8000000
#include <avr/io.h>
#include "memoire_24.h"

class Memoire
{
public:

// constructeur par defaut
Memoire(); 

// destructeur de la classe
~Memoire();  

// De l'USART vers le PC 
void transmissionUART ( uint8_t donnee ); 

 // transmission de PC vers UART
void transmissionPC( uint8_t *donnee);

// fonction qui initialise le  UART
void initialisationUART ( void ); 

private:

};

# endif
