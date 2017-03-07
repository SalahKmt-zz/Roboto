/*
 *Nom du fichier : controleDel.h
 *Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi, Mohamed Salah Eddine Kamate et Christian Lortie-Cloutier
 *2016-03-10 
 * controle de la del
 */


#ifndef CONTROLEDEL_H
#define CONTROLEDEL_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 
#include <can.h>


class ControleDel
{
public:

//ControleDel();
enum Etat {ETEINT,VERT,ROUGE,AMBRE};  // enumeration des etats de la del 
void clignoter();					  // fonction clignoter 
void controlerDel(Etat); 			  // fonction pour controler la del

void portBEntree();						// fonction qui met le port B en entree (sauf la pin 0 et 2 qui servent à la mise à la terre pour les DELs)
void portBSortie();						// fonction qui met le port B en sortie

void allumerDelExterne();				// fonction pour allumer les dels du breadboard
void eteindreDelExterne();				// fonction pour eteindre les dels du breadboard

void activerDelsExterneAvecBoutons();	// fonction pour allumer les dels avec les boutons du breadboard







//~ControleDel();						  // destructeur de la classe controleDel	


private:

// ne rien faire ici
};

#endif
