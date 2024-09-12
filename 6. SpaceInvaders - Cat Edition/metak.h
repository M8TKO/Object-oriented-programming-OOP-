#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class metak {
	friend class Prozor;
	friend class Igra;
	friend class neprijatelj;
	bool enemy;
	bool ziv;
	sf::Texture Tex;
	sf::Sprite sprite;
	sf::Vector2f smjer;
	float brzina;
public:
	void prijatelj();
	void neprijatelj();
	void namjestiMetak(sf::Vector2f V);
	void unisti(); 
	sf::Sprite& dajSprite() { return sprite; }
};

void metak::prijatelj() {
	if (Tex.loadFromFile(".\\Slike\\nasMetak.png"))
		cout << "sve okej" << endl;
	sprite.setTexture(Tex);
	sprite.setOrigin(
		sprite.getLocalBounds().width / 2,
		sprite.getLocalBounds().height / 2
	);
	enemy = false;
	ziv = false;
	smjer = sf::Vector2f(0.f, -1.f);
	brzina = 500;
}

void metak::neprijatelj() {

	Tex.loadFromFile(".\\Slike\\neprijateljMetak.png");
		
	sprite.setTexture(Tex);
	sprite.setOrigin(
		sprite.getLocalBounds().width / 2,
		sprite.getLocalBounds().height / 2
	);
	enemy = true;
	ziv = false;
	smjer = sf::Vector2f(0.f, 1.f);
	brzina = 100;
}


void metak::namjestiMetak(sf::Vector2f V) {
	sprite.setPosition(
		V.x,
		V.y
	);
	ziv = true;
}