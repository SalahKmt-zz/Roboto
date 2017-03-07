/*
 * Nom du fichier : bouton.h 
 * Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi, Mohamed Salah Eddine Kamate et Christian Lortie-Cloutier
 * 2016-03-10 
 * Cette fonction determine si le bouton est pese ou pas
 */


#ifndef BOUTON_H
#define BOUTON_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 

class Bouton
{
public:

//Bouton(); // constructeur
//~Boutom(); // destructeur
bool boutonPese(); // fonction qui retournera un booleen

private:
};

#endif
