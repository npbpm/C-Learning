#include "SFML/Graphics.hpp"
#include "Tile.h"
using namespace std;

Tile::Tile(short state, float XoriginMin, float YoriginMin, float XoriginMax, float YoriginMax) {
	state_ = state;
	XoriginMin_ = XoriginMin;
	YoriginMin_ = YoriginMin;
	XoriginMax_ = XoriginMax;
	YoriginMax_ = YoriginMax;
}

sf::VertexArray Tile::createTile() {
	sf::VertexArray tile(sf::Quads, 4);

	tile[0].position = sf::Vector2f(XoriginMin_ , YoriginMin_ );
	tile[1].position = sf::Vector2f(XoriginMax_ , YoriginMin_ );
	tile[2].position = sf::Vector2f(XoriginMax_ , YoriginMax_ );
	tile[3].position = sf::Vector2f(XoriginMin_ , YoriginMax_ );
	
	if (state_ == 1) {
		tile[0].color = sf::Color(187, 187, 187,255);	//For now all of the tiles are set to GREY, we must fill it with the color corresponding to his state
		tile[1].color = sf::Color(187, 187, 187,255);
		tile[2].color = sf::Color(187, 187, 187,255);
		tile[3].color = sf::Color(187, 187, 187,255);
	}
	else {
		tile[0].color = sf::Color(0, 0, 0, 255);	//For now all of the tiles are set to BLACK, we must fill it with the color corresponding to his state
		tile[1].color = sf::Color(0, 0, 0, 255);
		tile[2].color = sf::Color(0, 0, 0, 255);
		tile[3].color = sf::Color(0, 0, 0, 255);
	}
	
	return tile;
}

void Tile::changeState() {
	if (state_ == 1)
		state_ = 0;
	else if (state_ == 0) state_ = 1;
}

void Tile::changeOrigin(float XoriginMin, float YoriginMin, float XoriginMax, float YoriginMax) {
	XoriginMin_ = XoriginMin;
	YoriginMin_ = YoriginMin;
	XoriginMax_ = XoriginMax;
	YoriginMax_ = YoriginMax;
}
