#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "Menu.h"
using namespace std;

int main() {
	sf::RenderWindow window;	//Create the window instance
	cout << "Window Creation" << endl;

	sf::VideoMode currentMode = sf::VideoMode::getDesktopMode();	//Get the current system's resolution 

	window.create(currentMode, "Jeu de la vie", sf::Style::Default);	//Create the window we can see, size = 1000x1000 ; Title = Jeu de la vie

	Tilemap CurrentMap;

	int initialState = 1;	//1 means that we are indeed in the initialState of the game

	window.clear(sf::Color(255, 237, 220));

	Menu menu(initialState);
	menu.loadMenu(window);

	CurrentMap.load(window, initialState);
	Tilemap FutureMap(CurrentMap);	//We create another TileMap, exactly the same ad the current one, but it will correspond to the future state of the Tilemap

	window.display();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {	//Close the window when we press the X button on the top bar
				window.close();
			}

			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::R) {
					ifstream StateSave("Initial.txt");
					int* stateSave = new int[2500];
					for (unsigned int i = 0; i < 2500; i++) {
						int state;
						StateSave >> state;
						stateSave[i] = state;
					}
					StateSave.close();
					CurrentMap.loadFromFile(stateSave);
					window.clear(sf::Color(255, 237, 220));
					menu.loadMenu(window);
					CurrentMap.load(window, 0);	// InitialState = 0
					window.display();
				}
			}

			else if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				//We detect if the click was inside the grid in order to define the initial state
				if (mousePos.x >= CurrentMap.getXorigin() && mousePos.x <= CurrentMap.getXorigin() + CurrentMap.getXsize() && mousePos.y >= CurrentMap.getYorigin() && mousePos.y <= CurrentMap.getYorigin() + CurrentMap.getYsize() && menu.getPlayState() == 1) {
					CurrentMap.defineInitialState(window, mousePos);
					window.clear(sf::Color(255, 237, 220));
					menu.loadMenu(window);
					CurrentMap.load(window, 0);	// InitialState = 0
					window.display();
				}
				else if (mousePos.x >= menu.getXorigin() + 5 && mousePos.x <= menu.getXorigin() + 28 && mousePos.y >= menu.getYorigin() && mousePos.y <= menu.getYorigin() + 45 && menu.getPlayState() == 1) {
					//Check when the Play button gets pushed
					menu.changePlayState();	//Here the Play state goes to 0 so that we can no longer change tiles manually
					//Save initial state in a .txt file
					ofstream initialStateSave("Initial.txt");
					for (unsigned int i = 0; i < CurrentMap.getTiles(); i++) {
						initialStateSave << CurrentMap.getTileMap()[i]->getState() << endl;
					}
					initialStateSave.close();
				}
				else if (mousePos.x >= menu.getXorigin() + 50 && mousePos.x <= menu.getXorigin() + 80 && mousePos.y >= menu.getYorigin() && mousePos.y <= menu.getYorigin() + 45 && menu.getPlayState() == 0) {	
					//Checks if the pause button was pushed
					menu.changePlayState();	//Here the Play state goes to 1 so that the game is paused
				}
				else if(mousePos.x >= menu.getXorigin() + 90 && mousePos.x <= menu.getXorigin() + 135 && mousePos.y >= menu.getYorigin() && mousePos.y <= menu.getYorigin() + 45 && menu.getPlayState() == 1){
					int* newStates = FutureMap.nextTileMapState(CurrentMap);
					for (unsigned int i = 0; i < CurrentMap.getTiles(); i++) {
						if (newStates[i] != CurrentMap.getTileMap()[i]->getState()) CurrentMap.getTileMap()[i]->changeState();
					}
					//CurrentMap = FutureMap;
					window.clear(sf::Color(255, 237, 220));
					menu.loadMenu(window);
					CurrentMap.load(window, 0);
					window.display();
				}
			}
		}
		if (menu.getPlayState() == 0) {
			int* newStates = FutureMap.nextTileMapState(CurrentMap);
			for (unsigned int i = 0; i < CurrentMap.getTiles(); i++) {
				if (newStates[i] != CurrentMap.getTileMap()[i]->getState()) CurrentMap.getTileMap()[i]->changeState();
			}
			//CurrentMap = FutureMap;
			window.clear(sf::Color(255, 237, 220));
			menu.loadMenu(window);
			CurrentMap.load(window, menu.getPlayState());
			window.display();
		}
	}

	

	return 0;
}