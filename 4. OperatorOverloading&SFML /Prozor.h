#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Lopta.h"
#include <vector>
#include <initializer_list>
#include <random>

class Prozor {
private:
	sf::RenderWindow prozor;
	bool otvoren;
	std::vector<Lopta> lopte;
	sf::SoundBuffer audioSpremnik;
	sf::Sound Meow;
public:
	~Prozor();
	Prozor();
	bool jelOtvoren() const;
	void azuriraj();
	void ocisti();
	void prikazi();
	void crtaj();
	Prozor& operator+=(const Lopta&);
};

Prozor::Prozor() {
	prozor.create(sf::VideoMode(800, 600),
		"Loptanje");
	otvoren = true;

	audioSpremnik.loadFromFile("meow.wav");
	Meow.setBuffer(audioSpremnik);

}

bool Prozor::jelOtvoren() const {
	return otvoren;
}

void Prozor::azuriraj() {
	sf::Event d;
	while (prozor.pollEvent(d)) {
		if (d.type == sf::Event::Closed) {
			otvoren = false;
		}
		else if (d.type == sf::Event::KeyPressed) {

			if (d.key.code == sf::Keyboard::P) {
				for (auto& lopta : lopte) {
					++lopta;
				}
			}

			if (d.key.code == sf::Keyboard::M) {
				for (auto& lopta : lopte) {
					--lopta;
				}
			}

			if (d.key.code == sf::Keyboard::Z) {
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dis(0, lopte.size()-1);
				lopte[dis(gen)] + lopte[dis(gen)];
			}

			if (d.key.code == sf::Keyboard::I) {
				for (auto& lopta : lopte) 
					std::cout << lopta;
				std::cout << "###########" << std::endl;
				
			}

			if (d.key.code == sf::Keyboard::N) {
				*this += Lopta();
			}

			if (d.key.code == sf::Keyboard::B) {
				int sum = 0;
				for (auto& lopta : lopte) 
					if (lopte[0] == lopta)
						sum++;
				std::cout << "Broj kugli koje su iste kao pocetna: " << sum << std::endl;
				
				sum = 0;
				for (auto& lopta : lopte)
					if (lopte[0] != lopta)
						sum++;
				std::cout << "Broj kugli koje nisu iste kao pocetna: " << sum << std::endl;
			}
		
		}
	}
	for (auto& lopta : lopte)
		lopta.azuriraj(Meow);
}

Prozor::~Prozor() {
	prozor.close();
}

void Prozor::ocisti() {
	prozor.clear(sf::Color::White);
}

void Prozor::prikazi() {
	prozor.display();
}

void Prozor::crtaj() {
	for (auto& lopta : lopte)
		lopta.crtaj(prozor);
}

Prozor& Prozor::operator+=(const Lopta& lopta) {
	lopte.push_back(lopta);
	return *this;
}
