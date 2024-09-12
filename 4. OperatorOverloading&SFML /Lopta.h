#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include "Prozor.h"
#include <initializer_list>

class Lopta {
private:
	sf::CircleShape lopta;
	sf::Vector2f pomak;
	int nasumicni(int i, int j);
public:
	Lopta();
	Lopta(const Lopta&);
	void azuriraj(sf::Sound& S);
	Lopta(std::initializer_list<float> il);
	void crtaj(sf::RenderWindow&);
	Lopta& operator++();
	bool operator==(const Lopta& L) { return lopta.getRadius() == L.lopta.getRadius(); }
	bool operator!=(const Lopta& L) { return !(*this == L); }
	Lopta& operator--();	
	Lopta operator--(int);
	Lopta& operator=(std::initializer_list<float>);
	void operator+(Lopta&);

	operator float() const { return lopta.getRadius(); }
	friend std::ostream& operator<<(std::ostream&, const Lopta&);
};

int Lopta::nasumicni(int i, int j) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(i, j);
	return dis(gen);
}

Lopta::Lopta() {
	
	lopta.setRadius(nasumicni(10,20));
	lopta.setOrigin(lopta.getRadius(), lopta.getRadius());

	lopta.setFillColor(sf::Color(nasumicni(50, 220), nasumicni(50, 220), nasumicni(50, 220)));
	lopta.setPosition(nasumicni(0, 800), nasumicni(0, 600));
	pomak.x = 0.1f;
	pomak.y = 0.1f;

	std::cout << (float)*this << std::endl;

}

Lopta::Lopta(const Lopta& L) {
	lopta = L.lopta;
	pomak.x = L.pomak.x;
	pomak.y = L.pomak.y;
}

void Lopta::azuriraj(sf::Sound& S) {
	if ( (lopta.getPosition().x - lopta.getRadius() <= 0 && pomak.x < 0 ) ||
		(lopta.getPosition().x + lopta.getRadius() >= 800 && pomak.x > 0))
	{
		pomak.x = -pomak.x;
		S.play();
	}
	if ( (lopta.getPosition().y - lopta.getRadius() <= 0 && pomak.y < 0)
		|| (lopta.getPosition().y + lopta.getRadius() >= 600 && pomak.y >0))
	{
		pomak.y = -pomak.y;
		S.play();
	}
	lopta.setPosition(lopta.getPosition()
		+ pomak);
}

void Lopta::crtaj(sf::RenderWindow& prozor) {
	prozor.draw(lopta);
}

Lopta& Lopta::operator++() {
	lopta.setRadius(lopta.getRadius() + 1);
	lopta.setOrigin(lopta.getRadius(), lopta.getRadius());
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Lopta& L) {

	std::cout << "-----------" << std::endl;

	std::cout << "Radijus: " << L.lopta.getRadius() << std::endl
		<< "Polozaj: (" << L.lopta.getPosition().x << "," << L.lopta.getPosition().y << ")" << std::endl;
	return os;
}

Lopta& Lopta::operator--() {
	if (lopta.getRadius() >= 2) {
		lopta.setRadius(lopta.getRadius() - 1);
		lopta.setOrigin(lopta.getRadius(), lopta.getRadius());
	}
		
	return *this;
}
Lopta Lopta::operator--(int) {
	Lopta L(*this);
	--(*this);
	return L;
}

Lopta& Lopta::operator=(std::initializer_list<float> il) {
	auto it = il.begin();

	lopta.setPosition(*it++, *it++);
	lopta.setRadius(*it); 
	lopta.setOrigin(lopta.getRadius(), lopta.getRadius());

	return *this;
}

Lopta::Lopta(std::initializer_list<float> il) {
	Lopta L;
	L = il;
	*this = L;
}

void Lopta::operator+(Lopta& L) {
	float r = L.lopta.getRadius();

	L.lopta.setRadius(r + lopta.getRadius() );
	L.lopta.setOrigin(L.lopta.getRadius(), L.lopta.getRadius());

	lopta.setRadius(r + lopta.getRadius());
	lopta.setOrigin(lopta.getRadius(), lopta.getRadius());
}
