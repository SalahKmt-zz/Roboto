/*
 * Nom du fichier : bouton.cpp
 * Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi, Mohamed Salah Eddine Kamate et Christian Lortie-Cloutier
 * 2016-03-10 
 * Cette fonction determine si le bouton est pese ou pas
 */


#include "bouton.h"


bool Bouton::boutonPese()
{ 
	if (PIND & 0x04) 
	{
		_delay_ms (10); // Delai pour assurer que c'est bien l'utilisateur qui appuie sur le bouton
		if (PIND & 0x04)
		   return true;
		else
		   return false; // Le bouton n'est pas considere comme appuye s'il l'est pour moins de 25 ms
		
	}
	return false;
}
