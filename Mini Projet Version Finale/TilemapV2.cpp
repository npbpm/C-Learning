#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tilemap.h"
#include "Tile.h"
using namespace std;

Tilemap::Tilemap(unsigned int XSize, unsigned int YSize, unsigned int tiles, unsigned int width, unsigned int height, float Xorigin, float Yorigin) {
	XSize_ = XSize;
	YSize_ = YSize;
	tiles_ = tiles;
	width_ = width;
	height_ = height;
	Xorigin_ = Xorigin;
	Yorigin_ = Yorigin;
}

Tilemap::Tilemap(Tilemap& currentMap) {
	XSize_ = currentMap.getXsize();
	YSize_ = currentMap.getYsize();
	tiles_ = currentMap.getTiles();
	width_ = currentMap.getWidth();
	height_ = currentMap.getHeight();
	Xorigin_ = currentMap.getXorigin();
	Yorigin_ = currentMap.getYorigin();
	for (unsigned int i = 0; i < currentMap.getTileMap().size(); i++) {
		tileMap_.push_back(currentMap.getTileMap()[i]);
	}
}

void Tilemap::printTileMap() {
	for (unsigned int i = 0; i < tileMap_.size(); i++) {
		cout << tileMap_[i]->getState()<<endl;
		cout << tileMap_[i]->getXoriginMax()<<endl;
		cout << tileMap_[i]->getXoriginMin()<<endl;
		cout << tileMap_[i]->getYoriginMax()<<endl;
		cout << tileMap_[i]->getYoriginMin()<<endl;
	}
}

void Tilemap::load(sf::RenderWindow &window, int initialState) {
	short dead = 0;

	if(initialState == 1){
		for (unsigned int i = 0; i < width_; i++) {
			for (unsigned int j = 0; j < height_; j++) {

				sf::VertexArray Carre;
				
				Tile* tile = new Tile(dead, Xorigin_ + i * 20, Yorigin_ + j * 20, Xorigin_ + (i + 1) * 20, Yorigin_ + (j + 1) * 20);
				Carre = tile->createTile();
				tileMap_.push_back(tile);

			//The tileMap table is created linearily, so every single value is one next to the other
			//The table is created column by column, that means that inside the table
			// the values that are next to each other represent tiles one below or above the other

				window.draw(Carre);
			}
		}
	}
	else {
		for (unsigned int i = 0; i < tileMap_.size(); i++) {
			sf::VertexArray Carre;
			Carre = tileMap_[i]->createTile();

			window.draw(Carre);
		}
	}

	for (unsigned int i = 0; i <= width_; i++) {
		sf::VertexArray VerticalLimits(sf::Lines, 2);

		VerticalLimits[0].position = sf::Vector2f(Xorigin_ + i * 20, Yorigin_);
		VerticalLimits[1].position = sf::Vector2f(Xorigin_ + i * 20, YSize_ );

		VerticalLimits[0].color = sf::Color(255, 255, 255, 255);
		VerticalLimits[1].color = sf::Color(255, 255, 255, 255);

		window.draw(VerticalLimits);
	}

	for (unsigned int j = 0; j <= height_; j++) {
		sf::VertexArray HorizontalLimits(sf::Lines, 2);

		HorizontalLimits[0].position = sf::Vector2f(Xorigin_ , Yorigin_ + j * 20);
		HorizontalLimits[1].position = sf::Vector2f(XSize_, Yorigin_ + j * 20);

		HorizontalLimits[0].color = sf::Color(255, 255, 255, 255);
		HorizontalLimits[1].color = sf::Color(255, 255, 255, 255);

		window.draw(HorizontalLimits);
	}

}

void Tilemap::defineInitialState(sf::RenderWindow &window, sf::Vector2i mousePos) {
	//We look at every single tile of the grid and see if the click was inside of them
	for (unsigned int i = 0; i <= tileMap_.size(); i++) {
		if (mousePos.x >= tileMap_[i]->getXoriginMin() && mousePos.x <= tileMap_[i]->getXoriginMax() && mousePos.y >= tileMap_[i]->getYoriginMin() && mousePos.y <= tileMap_[i]->getYoriginMax()) {
			tileMap_[i]->changeState();
			break;
		}
	}
			
}

int* Tilemap::nextTileMapState(Tilemap& currentTileMap) {
	vector<Tile*> currentState = currentTileMap.getTileMap();
	int* newStates = new int[2500];
	for (unsigned int i = 0; i < currentState.size(); i++) {
		newStates[i] = currentState[i]->getState();
	}
	for (unsigned int i = 0; i < currentState.size(); i++) {	//This case is only for the cells in the middle portion of the grid, not for the ones on the first and last column
		//First rule
		int living = 0;
		living = checkSideTiles(currentState[i], currentState);
		//cout << "Tile: " << i << " ; Living: " << living << endl;
		if (currentState[i]->getState() == 0 && living == 3) {	//If the cell is dead it can revive
			newStates[i] = 1;
			continue;
		}
		else if (currentState[i]->getState() == 1 && living != 2 && living != 3) {
			//If the cell is living, it can die
			newStates[i] = 0;
			continue;

		}
	}
	return newStates;
}

int Tilemap::checkSideTiles(Tile *currentTile, vector<Tile*> tileMap) {	//We check how many living tiles there are around the tile we are looking at
	int living = 0;
	int index;
	for (unsigned int i = 0; i < tileMap.size(); i++) {
		if (tileMap[i] == currentTile) {
			index = i;		//We get the index of our tile inside the table
			break;
		}
	}

	if (index >= 51 && index < tileMap.size() - 51) {	//This case is only for the cells in the middle portion of the grid, not for the ones on the first and last column

		for (unsigned int i = 49; i < 52; i++) {	//We check the 3 left tiles
			if (tileMap[index - i]->getState() == 1) {
				living++;
			}
			if (tileMap[index + i]->getState() == 1) {	//We check the 3 right tiles
				living++;
			}
		}

		if (tileMap[index - 1]->getState() == 1) living++;
		if (tileMap[index + 1]->getState() == 1) living++;

	}
	else if (index < 49 && index != 0) {	//TOP LEFT CORNER AND BOTTOM LEFT CORNER INGORED
		//We use a "spherical" system, where we consider the tiles at the extremes next to each other.
		for (unsigned int i = 2449; i < 2452; i++) {	//We check the 3 left tiles
			if (tileMap[index + i]->getState() == 1) {
				living++;
			}
		}

		for (unsigned int i = 50; i < 53; i++) {
			if (tileMap[index + i]->getState() == 1) {	//We check the 3 right tiles
				living++;
			}
		}

		if (tileMap[index - 1]->getState() == 1) living++;
		if (tileMap[index + 1]->getState() == 1) living++;
	}
    
    else if (index > 2450 && index != 2499) {    //TOP RIGHT CORNER AND BOTTOM RIGHT CORNER INGORED
        //We use a "spherical" system, where we consider the tiles at the extremes next to each other.
        for (unsigned int i = 2449; i < 2452; i++) {    //We check the 3 right tiles
            if (tileMap[index - i]->getState() == 1) {
                living++;
            }
        }

        for (unsigned int i = 49; i < 52; i++) {
            if (tileMap[index - i]->getState() == 1) {    //We check the 3 left tiles
                living++;
            }
        }

        if (tileMap[index - 1]->getState() == 1) living++;
        if (tileMap[index + 1]->getState() == 1) living++;
    }
    else if (index == 0){ //FOR THE TOP LEFT CORNER
        
		if (tileMap[index + 1]->getState() == 1) living++;
		if (tileMap[50]->getState() == 1) living++;
		if (tileMap[51]->getState() == 1) living++;
		if (tileMap[2451]->getState() == 1) living++;	//Bottom Left
		if (tileMap[2450]->getState() == 1) living++;	//Left
		if (tileMap[49]->getState() == 1) living++;	//Top
		if (tileMap[99]->getState() == 1) living++;	//Top right
		if (tileMap[index]->getState() == 1) living++;	//We consider the top left corner as the same state as the 0 index tile
    }
    else if (index == 49){ //FOR THE BOTTOM LEFT CORNER
       
        if (tileMap[0]->getState() == 1) { //We check the bottom tile
            living++;
        }
        if (tileMap[48]->getState() == 1) { //We check the top tile
            living++;
        }
        if (tileMap[99]->getState() == 1) { //We check the right tile
            living++;
        }
        if (tileMap[2499]->getState() == 1) { //We check the left tile
            living++;
        }
		if (tileMap[50]->getState() == 1) living++;	//We check the bottom right corner
		if (tileMap[98]->getState() == 1) living++;	//We check the top right corner
		if (tileMap[2498]->getState() == 1) living++;	//We check the top left corner
		if (tileMap[index]->getState() == 1) living++;		//We consider the bottom left corner as the same state as the 49 index tile	
    }

    else if (index == 2450){ //FOR THE TOP RIGHT CORNER
        
        if (tileMap[2400]->getState() == 1) { //We check the left tile
            living++;
        }
        if (tileMap[2401]->getState() == 1) { //We check the bottom left tile
            living++;
        }
        if (tileMap[2451]->getState() == 1) { //We check the bottom tile
            living++;
        }
        if (tileMap[1]->getState() == 1) { //We check the bottom right tile
            living++;
        }
		if (tileMap[2449]->getState() == 1) living++; //We check the top left tile
		if (tileMap[2499]->getState() == 1) living++; //We check the top tile
		if (tileMap[0]->getState() == 1) living++;	//We check the right tile
		if (tileMap[index]->getState() == 1) living++; //We consider the top Right corner as the same state as the 2450 index tile
    }
    else if (index == 2499){ //FOR THE BOTTOM RIGHT CORNER
        
        if (tileMap[index]->getState() == 1) { //We consider the bottom Right corner as the same state as the 2450 index tile
            living++;
        }
        if (tileMap[2400]->getState() == 1) { //We check the bottom left tile
            living++;
        }
        if (tileMap[2449]->getState() == 1) { //We check the bottom tile
            living++;
        }
        if (tileMap[2498]->getState() == 1) { //We check the top tile
            living++;
        }
		if (tileMap[49]->getState() == 1) living++; //We check the right tile
		if (tileMap[2449]->getState() == 1) living++; //We check the left tile
		if (tileMap[48]->getState() == 1) living++; //We check the top right tile
		if (tileMap[2448]->getState() == 1) living++; //We check the left tile
    }
	else if (index == 2449) { //FOR THE BOTTOM RIGHT CORNER

	if (tileMap[index-49]->getState() == 1) { //Bottom 
		living++;
	}
	if (tileMap[2350]->getState() == 1) { //We check the bottom left tile
		living++;
	}
	if (tileMap[2450]->getState() == 1) { //We check the bottom right tile
		living++;
	}
	if (tileMap[2399]->getState() == 1) { //We check the left tile
		living++;
	}
	if (tileMap[2499]->getState() == 1) living++; //We check the right tile
	if (tileMap[index-1]->getState() == 1) living++; //We check the top tile
	if (tileMap[2398]->getState() == 1) living++; //We check the top left tile
	if (tileMap[2498]->getState() == 1) living++; //We check the top right tile
	}
	else if (index == 50) { //FOR THE BOTTOM RIGHT CORNER

	if (tileMap[index + 1]->getState() == 1) { //Bottom 
		living++;
	}
	if (tileMap[1]->getState() == 1) { //We check the bottom left tile
		living++;
	}
	if (tileMap[101]->getState() == 1) { //We check the bottom right tile
		living++;
	}
	if (tileMap[0]->getState() == 1) { //We check the left tile
		living++;
	}
	if (tileMap[100]->getState() == 1) living++; //We check the right tile
	if (tileMap[99]->getState() == 1) living++; //We check the top tile
	if (tileMap[49]->getState() == 1) living++; //We check the top left tile
	if (tileMap[149]->getState() == 1) living++; //We check the top right tile
	}

	return living;
}

void Tilemap::loadFromFile(int* file) {
	for (unsigned int i = 0; i < tiles_; i++) {
		if (tileMap_[i]->getState() != file[i]) {
			tileMap_[i]->changeState();
		}
	}
}