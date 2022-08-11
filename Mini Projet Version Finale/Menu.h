#pragma once
#include <SFML/Graphics.hpp>

//Classe cr�e par Nicol�s P�rez

class Menu { 
	unsigned int Play_;	//Param�tre qui d�finit le mode d'affichage du jeu, soit en mode play (0), soit en mode pause(1)
	unsigned int Xorigin_;	//On d�finit l'origine pour l'affichage du menu
	unsigned int Yorigin_;
public:
	Menu(int Play = 1, int Xorigin = 1300, int Yorigin = 250);	//Constructeur par d�faut du Menu
	void loadMenu(sf::RenderWindow &window);	//Fonction qui permet l'affichage du Menu
	void changePlayState();	//M�thode permettant de changer l'�tat de Play_ pour changer le mode du jeu
	int getPlayState() { return Play_; }	//M�thode permettant d'obtenir l'�tat actuel du param�tre Play_
	int getXorigin() { return Xorigin_; }	//M�thode permettant d'obtenir l'origine du Menu, utile pour l'affichage et pour la d�tection du click
	int getYorigin() { return Yorigin_; }

};