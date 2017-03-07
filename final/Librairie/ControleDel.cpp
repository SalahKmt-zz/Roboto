/*
 * Nom du fichier : controleDel.cpp
 * Auteurs: Evelyne Lafontaine-Michel, Hicham El Fouladi, Mohamed Salah Eddine Kamate et Christian Lortie-Cloutier
 * 2016-03-10 
 * Controle de la del
 */

#include "ControleDel.h"

//ControleDel::ControleDel(){} // constructeur par defaut


void ControleDel::clignoter(){ 
	
	PORTA = ROUGE;
	_delay_ms(15.0);
	PORTA = VERT;
	_delay_ms(15.0);

}


void ControleDel::controlerDel(Etat etat)
{

	DDRA = 0xff; // PORT A est en mode sortie)

	if (etat == ETEINT)
	{
		PORTA = 0x00;
	_delay_ms(30.0);
	} 
		
	if (etat == VERT)
	{
	PORTA = 0x01;
	_delay_ms(30.0);
	}
	
	if (etat == ROUGE) 
	{
		PORTA = 0x02;
	_delay_ms(30.0);
	
	}

	if (etat == AMBRE)
	clignoter();

}

//Ajuste le port B pour recevoir les boutons sur le breadboard en entrée
void ControleDel::portBEntree()
{
	// broche 0 en sortie, GND pour DEL gauche
	// broche 1 en entrée, bouton gauche
	// broche 4 en sortie, GND pour DEL droite
	// broche 5 en entrée, bouton droit
	// le reste en sortie
	DDRB = 0xdd; 
}

//fonction qui met le port B en sortie
void ControleDel::portBSortie()
{
	DDRB = 0xff;
}

// fonction pour allumer les dels du breadboard
void ControleDel::allumerDelExterne()
{
	portBSortie();
	PORTB = 0x22;
}	

// fonction pour eteindre les dels du breadboard
void ControleDel::eteindreDelExterne()
{
	portBSortie();
	PORTB &= 0x0;
}				

void ControleDel::activerDelsExterneAvecBoutons()
{
	PORTB &= 0xee; //PORTB0 et PORTB2 = 0, GND pour les DELs sur le breadboard
}






//ControleDel::~ControleDel()
//{
// destructeur de la classe controleDel
//}
							  
