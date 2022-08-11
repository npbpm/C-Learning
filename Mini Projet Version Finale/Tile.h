#pragma once

//Classe cr�e par Nicol�s P�rez

class Tile {
	short state_;	//On d�finit l'�tat de la cellule, 1 pour vivant, 0 pour morte
	float XoriginMin_;	//On d�finit le Xmin de la cellule
	float XoriginMax_;	//On d�finit le Xmax de la cellule
	float YoriginMin_;	//On d�finit le Ymin de la cellule
	float YoriginMax_;	//On d�finit le Ymax de la cellule
public:
	Tile(short state = 0, float XoriginMin = 30, float YoriginMin = 30, float XoriginMax = 50, float YoriginMax = 50);	//Constructeur par d�faut de la cellule, toutes les cellules sont d�finis comme mortes par d�faut
	void changeState();	//M�thode permettant de changer l'�tat de la cellule
	void changeOrigin(float XoriginMin, float YoriginMin, float XoriginMax, float YoriginMax);	//M�thode permettant de changer les coordonn�es de la cellule, elle est utile uniquement au moment de cr�ation de la grille
	short getState() { return state_; }	//M�thode permettant d'obtenir l'�tat actuel de la cellule
	float getXoriginMin() { return XoriginMin_; }	//On r�cup�re les coordonn�es de la cellule, utile pour d�tecter sur quelle cellule on clique.
	float getYoriginMin() { return YoriginMin_; }
	float getXoriginMax() { return XoriginMax_; }
	float getYoriginMax() { return YoriginMax_; }
	sf::VertexArray createTile();	//Fonction permettant la cr�ation de l'objet Tile sur SFML.
};