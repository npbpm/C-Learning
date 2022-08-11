#pragma once

//Classe crée par Nicolás Pérez

class Tile {
	short state_;	//On définit l'état de la cellule, 1 pour vivant, 0 pour morte
	float XoriginMin_;	//On définit le Xmin de la cellule
	float XoriginMax_;	//On définit le Xmax de la cellule
	float YoriginMin_;	//On définit le Ymin de la cellule
	float YoriginMax_;	//On définit le Ymax de la cellule
public:
	Tile(short state = 0, float XoriginMin = 30, float YoriginMin = 30, float XoriginMax = 50, float YoriginMax = 50);	//Constructeur par défaut de la cellule, toutes les cellules sont définis comme mortes par défaut
	void changeState();	//Méthode permettant de changer l'état de la cellule
	void changeOrigin(float XoriginMin, float YoriginMin, float XoriginMax, float YoriginMax);	//Méthode permettant de changer les coordonnées de la cellule, elle est utile uniquement au moment de création de la grille
	short getState() { return state_; }	//Méthode permettant d'obtenir l'état actuel de la cellule
	float getXoriginMin() { return XoriginMin_; }	//On récupère les coordonnées de la cellule, utile pour détecter sur quelle cellule on clique.
	float getYoriginMin() { return YoriginMin_; }
	float getXoriginMax() { return XoriginMax_; }
	float getYoriginMax() { return YoriginMax_; }
	sf::VertexArray createTile();	//Fonction permettant la création de l'objet Tile sur SFML.
};