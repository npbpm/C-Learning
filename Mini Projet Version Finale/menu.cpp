#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu(int Play, int Xorigin, int Yorigin) {
	Play_ = Play;
	Xorigin_ = Xorigin;
	Yorigin_ = Yorigin;
}

void Menu::loadMenu(sf::RenderWindow& window) {

	//BACKGROUND
	sf::VertexArray Menu(sf::Quads, 4);

	Menu[0].position = sf::Vector2f(Xorigin_, Yorigin_);
	Menu[1].position = sf::Vector2f(Xorigin_ + 150, Yorigin_);
	Menu[2].position = sf::Vector2f(Xorigin_ + 150, Yorigin_ + 50);
	Menu[3].position = sf::Vector2f(Xorigin_, Yorigin_ + 50);

	Menu[0].color = sf::Color(170, 170, 170, 50);	//For now all of the tiles are set to GREY, we must fill it with the color corresponding to his state
	Menu[1].color = sf::Color(170, 170, 170, 50);
	Menu[2].color = sf::Color(170, 170, 170, 50);
	Menu[3].color = sf::Color(170, 170, 170, 50);

	window.draw(Menu);

	//PLAY BUTTON

	sf::VertexArray Play(sf::Triangles, 3);

	Play[0].position = sf::Vector2f(Xorigin_+5, Yorigin_+5);
	Play[1].position = sf::Vector2f(Xorigin_ + 5, Yorigin_ + 45);
	Play[2].position = sf::Vector2f(Xorigin_ + 35, Yorigin_ + 23);

	Play[0].color = sf::Color(255, 255, 255, 255);
	Play[1].color = sf::Color(255, 255, 255, 255);
	Play[2].color = sf::Color(255, 255, 255, 255);

	window.draw(Play);

	//PAUSE BUTTON

	sf::VertexArray Pause1(sf::Quads, 4);

	Pause1[0].position = sf::Vector2f(Xorigin_ + 50, Yorigin_ + 5);
	Pause1[1].position = sf::Vector2f(Xorigin_ + 60, Yorigin_ + 5);
	Pause1[2].position = sf::Vector2f(Xorigin_ + 60, Yorigin_ + 45);
	Pause1[3].position = sf::Vector2f(Xorigin_ + 50, Yorigin_ + 45);

	Pause1[0].color = sf::Color(255, 255, 255, 255);
	Pause1[1].color = sf::Color(255, 255, 255, 255);
	Pause1[2].color = sf::Color(255, 255, 255, 255);
	Pause1[3].color = sf::Color(255, 255, 255, 255);

	window.draw(Pause1);

	sf::VertexArray Pause2(sf::Quads, 4);

	Pause2[0].position = sf::Vector2f(Xorigin_ + 70, Yorigin_ + 5);
	Pause2[1].position = sf::Vector2f(Xorigin_ + 80, Yorigin_ + 5);
	Pause2[2].position = sf::Vector2f(Xorigin_ + 80, Yorigin_ + 45);
	Pause2[3].position = sf::Vector2f(Xorigin_ + 70, Yorigin_ + 45);

	Pause2[0].color = sf::Color(255, 255, 255, 255);
	Pause2[1].color = sf::Color(255, 255, 255, 255);
	Pause2[2].color = sf::Color(255, 255, 255, 255);
	Pause2[3].color = sf::Color(255, 255, 255, 255);

	window.draw(Pause2);

	//NEXT ONE
	sf::VertexArray arrowBody(sf::Quads, 4);

	arrowBody[0].position = sf::Vector2f(Xorigin_ + 90, Yorigin_ + 20);
	arrowBody[1].position = sf::Vector2f(Xorigin_ + 125, Yorigin_ + 20);
	arrowBody[2].position = sf::Vector2f(Xorigin_ + 125, Yorigin_ + 30);
	arrowBody[3].position = sf::Vector2f(Xorigin_ + 90, Yorigin_ + 30);

	arrowBody[0].color = sf::Color(255, 255, 255, 255);
	arrowBody[1].color = sf::Color(255, 255, 255, 255);
	arrowBody[2].color = sf::Color(255, 255, 255, 255);
	arrowBody[3].color = sf::Color(255, 255, 255, 255);

	window.draw(arrowBody);

	sf::VertexArray arrowHead1(sf::Quads, 4);

	arrowHead1[0].position = sf::Vector2f(Xorigin_ + 110, Yorigin_ + 5);
	arrowHead1[1].position = sf::Vector2f(Xorigin_ + 120, Yorigin_ + 5);
	arrowHead1[2].position = sf::Vector2f(Xorigin_ + 135, Yorigin_ + 25);
	arrowHead1[3].position = sf::Vector2f(Xorigin_ + 125, Yorigin_ + 25);

	arrowHead1[0].color = sf::Color(255, 255, 255, 255);
	arrowHead1[1].color = sf::Color(255, 255, 255, 255);
	arrowHead1[2].color = sf::Color(255, 255, 255, 255);
	arrowHead1[3].color = sf::Color(255, 255, 255, 255);

	window.draw(arrowHead1);

	sf::VertexArray arrowHead2(sf::Quads, 4);

	arrowHead2[0].position = sf::Vector2f(Xorigin_ + 110, Yorigin_ + 45);
	arrowHead2[1].position = sf::Vector2f(Xorigin_ + 120, Yorigin_ + 45);
	arrowHead2[2].position = sf::Vector2f(Xorigin_ + 135, Yorigin_ + 25);
	arrowHead2[3].position = sf::Vector2f(Xorigin_ + 125, Yorigin_ + 25);

	arrowHead2[0].color = sf::Color(255, 255, 255, 255);
	arrowHead2[1].color = sf::Color(255, 255, 255, 255);
	arrowHead2[2].color = sf::Color(255, 255, 255, 255);
	arrowHead2[3].color = sf::Color(255, 255, 255, 255);

	window.draw(arrowHead2);


}

void Menu::changePlayState() {
	if (Play_ == 0) {
		Play_ = 1;
	}
	else {
		Play_ = 0;
	}
}