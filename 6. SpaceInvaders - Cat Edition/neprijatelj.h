#pragma once

#include <iostream>
#include<string>
#include <SFML/Graphics.hpp>
#include <random>
#include "Igra.h"
#include "metak.h"
using namespace std;


class neprijatelj {
	friend class Igra;
	sf::Texture Tex;
	sf::Sprite sprite;
	int bodovi;
	bool ziv = true;
	sf::Vector2f pomak, pocetni_pomak;
	float smjer = 1;
	float brzina = 12;
	float kut = 0;
	float kutnaBrzina = 50;
	float pocetnaBrzina = 12;
	metak metak;
public:
	void setTex(string s);
	neprijatelj();
	sf::Sprite& dajSprite() { return sprite; }
	void namjesti(int i, int j, sf::Vector2u V);
	string randomTex();
	void pomakniNeprijatelja(float);
	void noviMetak();
	void pomakniMetak(float t);
	void provjeriGraniceMetka();
	bool provjeriPogodakMetka(sf::Sprite V);
	void povecajBrzinu() { brzina += brzina * 0.2; } //0.2
};

string neprijatelj::randomTex() {
	string a[3] = { ".\\Slike\\cat2.png",".\\Slike\\bird.png",".\\Slike\\turtle.png" };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 100);
	int random_number = distr(gen);
	int rd_tex;
	if (random_number <= 20) {
		bodovi = 4;
		rd_tex = 2;
	}
		
	else if (random_number <= 40) {
		rd_tex = 1;
		bodovi = 2;
	}
		
	else {
		rd_tex = 0;
		bodovi = 1;
	}
		
	return a[rd_tex];
}

void neprijatelj::setTex(string s) {
	Tex.loadFromFile(s);
	sprite.setTexture(Tex);
	
}

neprijatelj::neprijatelj() {
	setTex(randomTex());

	sprite.setOrigin(
		sprite.getLocalBounds().width / 2,
		sprite.getLocalBounds().height / 2
	);
	
}

void neprijatelj::namjesti(int i, int j, sf::Vector2u V) {
	float x = V.x / 2 + ((float)(j - 5)) * V.x / 13,
		y = V.y / 4 + ((float)(i - 2)) * V.y / 15;
	sprite.setPosition(
		x ,
		y
	);

	metak.neprijatelj();
}

void neprijatelj::pomakniNeprijatelja(float t) {
	sprite.move(pomak * smjer * brzina * t);
	kut += kutnaBrzina * t;
	sprite.setRotation(kut);
}

void neprijatelj::noviMetak() {

	if (metak.ziv || !ziv)
		return;

	

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1, 10000);
	int random_number = distr(gen);

	if (random_number <= bodovi ) {
		metak.namjestiMetak(sprite.getPosition());
	}


}

void neprijatelj::provjeriGraniceMetka() {
	if (!metak.ziv)
		return;

	if (metak.sprite.getPosition().y > 2000) //ovo mozda bolje napravi
		metak.ziv = false;
}

void neprijatelj::pomakniMetak(float t) {

	noviMetak();
	provjeriGraniceMetka();

	if (metak.ziv)
		metak.sprite.move(metak.smjer * metak.brzina * t);
}

bool neprijatelj::provjeriPogodakMetka(sf::Sprite V) {
	if (!metak.ziv)
		return false;
	
	if (metak.sprite.getGlobalBounds().intersects(V.getGlobalBounds())) {
		metak.ziv = false;
		return true;
	}
		
	return false;
}