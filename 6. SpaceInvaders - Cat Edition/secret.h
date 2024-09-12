#pragma once
#include <iostream>
#include<string>
#include <SFML/Graphics.hpp>
#include <random>
#include "Igra.h"
#include "metak.h"
using namespace std;

class tajni {
	friend class Igra;
	sf::Texture Tex;
	sf::Sprite sprite;
	float brzina = 15;
	int bodovi = 10;
	sf::Vector2f smjer;
	bool ziv = false;

};