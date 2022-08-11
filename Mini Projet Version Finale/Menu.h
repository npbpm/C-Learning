#pragma once
#include <SFML/Graphics.hpp>

//Classe crée par Nicolás Pérez

class Menu { 
	unsigned int Play_;	//Paramètre qui définit le mode d'affichage du jeu, soit en mode play (0), soit en mode pause(1)
	unsigned int Xorigin_;	//On définit l'origine pour l'affichage du menu
	unsigned int Yorigin_;
public:
	Menu(int Play = 1, int Xorigin = 1300, int Yorigin = 250);	//Constructeur par défaut du Menu
	void loadMenu(sf::RenderWindow &window);	//Fonction qui permet l'affichage du Menu
	void changePlayState();	//Méthode permettant de changer l'état de Play_ pour changer le mode du jeu
	int getPlayState() { return Play_; }	//Méthode permettant d'obtenir l'état actuel du paramètre Play_
	int getXorigin() { return Xorigin_; }	//Méthode permettant d'obtenir l'origine du Menu, utile pour l'affichage et pour la détection du click
	int getYorigin() { return Yorigin_; }

};