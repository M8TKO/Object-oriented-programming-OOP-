#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include "Prozor.h"
#include "neprijatelj.h"
#include "metak.h"
#include "secret.h"
#include <fstream>

using namespace std;

class Igra {
public:
	sf::Time protekloVrijeme();
	void restartSata();
	Igra();
	~Igra();
	void obradiUlaz();
	void update();
	void renderiraj();
	Prozor* dohvatiProzor() {
		return &p;
	}
private:
	metak metak;
	int bodoviTopa;
	int najboljiRez;
	int zivoti;
	vector < vector < neprijatelj> > neprijatelji;
	void updateNeprijatelja();
	void pomakniTop();
	int provjeriGraniceTopa();
	void provjeriGraniceNeprijatelja();
	void postaviPomakNeprijatelja(sf::Vector2f V);
	sf::Vector2f dohvatiPomakNeprijatelja();
	float dohvatiSmjerNeprijatelja();
	void postaviSmjerNeprijatelja(float s);
	void dohvatiZivogNeprijatelja(int& k, int &l);
	void prviLijeviZivi(int& k, int& l);
	void prviDesniZivi(int& r, int& t);
	void povecajBrzinuNeprijatelja();
	void updateMetak(float t);
	void provjeriMetak();
	void provjeriPogodakTopa();
	bool postojiLiFile();
	void updateHighscore();
	void updateMetkeNeprijatelja();
	void provjeriPogodakNeprijatelja();
	bool jesmoLiZivi();
	void restart(bool next);
	void provjeriKrajNeprijatelja();
	void srediPocetak();
	bool jeLiPocetak() { return pocetak; }
	bool pobijedio();
	bool jeLiPauza() { return pauza; }
	void pomakniTajni();
	bool jeLiTajniZiv() { return tajni.ziv; }
	void updateBodove() { TexTvojiBodovi.setString(stringTvojiBodovi + to_string(bodoviTopa)); }
	void nacrtajSrca() { for (int i = 2; i >= 3-zivoti; i--) p.crtaj(srca[i]); }
	//void postaviTekst(string tekst,);
	//TODO: lol
	Prozor p;
	sf::Texture TopTex;
	sf::Sprite TopSprite;
	sf::Vector2f pomak, pocetni_pomak;
	float smjer; 
	sf::Clock sat;
	sf::Time vrijeme;
	float brzina = 300;
	float dolje = 0;
	sf::Vector2f prijasnjiPomak;
	float prijasnjiSmjer;
	std::ofstream outFile;
	std::ifstream inFile;
	string file = "highscore.txt";
	sf::Font font;
	sf::Text text;
	string ispisHigh = "\tNAJBOLJI REZULTAT: ";
	string ispisLoss = "Izgubio si! Stisni C ako zelis igrati ponovno!";
	sf::Text TexPonovno;
	sf::Text TexPocetak;
	string stringPocetak = "Stisni Enter za pocetak igre!\n\n\nkretanje lijevo: LEFTARROW\nkretanje desno: RIGHTARROW\npucanje: SPACE";
	sf::Text TexNext;
	string stringNext = "Pobjeda! Stisni C za sljedeæi level!";			
	sf::Text TexPauza;
	string stringPauza = "Pauza! Stisni Space za nastavak.";
	bool pocetak;
	int level = 1;
	bool pauza;
	sf::Text TexTvojiBodovi;
	string stringTvojiBodovi = "\tTrenutni bodovi: ";
	sf::Texture TexSrce;
	sf::Sprite srca[3];
	
	tajni tajni;

};

sf::Time Igra::protekloVrijeme() {
	return vrijeme;
}

void Igra::restartSata() {
	vrijeme = sat.restart();
}

void Igra::renderiraj() {
	p.ocisti();

	if (jeLiPauza()) {
		p.crtaj(TexPauza);
		p.prikazi();
		return;
	}
		

	if (jeLiPocetak()) {
		p.crtaj(TexPocetak);
		p.prikazi();
		return;
	}

	if (pobijedio()) {
		p.crtaj(TexNext);
		p.prikazi();
		return;
	}

	if (!jesmoLiZivi()) {
		p.crtaj(TexPonovno);
		p.prikazi();
		return;
	}

	p.crtaj(TopSprite);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++) {
			if( neprijatelji[i][j].ziv )
				p.crtaj(neprijatelji[i][j].dajSprite());
		}
	if (metak.ziv) {
		p.crtaj( metak.dajSprite() );
	}

	p.crtaj(text);
	p.crtaj(TexTvojiBodovi);
	nacrtajSrca();

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++)
			if (neprijatelji[i][j].metak.ziv)
				p.crtaj(neprijatelji[i][j].metak.sprite);

	if (jeLiTajniZiv())
		p.crtaj(tajni.sprite);

	p.prikazi();
}

void Igra::update() {
	p.update();

	if (jeLiPocetak()) 
		return;
	
	if (jeLiPauza())
		return;
	

	if (pobijedio())
		return;

	if (!jesmoLiZivi())
		return;
	provjeriKrajNeprijatelja();
	
	
		
	pomakniTajni();
	pomakniTop();
	updateNeprijatelja();
	updateMetkeNeprijatelja();
	updateMetak(protekloVrijeme().asSeconds());
	provjeriPogodakTopa();
	updateHighscore();
	updateBodove();
	provjeriPogodakNeprijatelja();
}

int Igra::provjeriGraniceTopa() {
	if (smjer == 1 && TopSprite.getPosition().x + TopSprite.getLocalBounds().width / 2 >= p.dohvatiVelicinu().x)
		return smjer = 0;
	if (smjer == -1 && TopSprite.getPosition().x - TopSprite.getLocalBounds().width / 2 <= 0)
		return smjer = 0;
	return smjer;	
}

void Igra::provjeriGraniceNeprijatelja() {
	
	if (dolje > p.dohvatiVelicinu().y / (float) 20 ) {
		dolje = 0;
		postaviPomakNeprijatelja(sf::Vector2f(1.f,0.f));
		postaviSmjerNeprijatelja(-prijasnjiSmjer);
		povecajBrzinuNeprijatelja();
		return;
	}

	if (dolje > 0)
		return;
		

	int s = dohvatiSmjerNeprijatelja(),k = 11,l = 11,r = -1,t = -1;
	prviLijeviZivi(k, l);
	prviDesniZivi(r, t);
	if (s == 1 && neprijatelji[r][t].sprite.getPosition().x + neprijatelji[r][t].sprite.getLocalBounds().width / 2 >= p.dohvatiVelicinu().x) {
		dolje = 1;
		prijasnjiSmjer = dohvatiSmjerNeprijatelja();
	}
		
	if (s == -1 && neprijatelji[k][l].sprite.getPosition().x - neprijatelji[k][l].sprite.getLocalBounds().width / 2 <= 0) {
		dolje = 1;
		prijasnjiSmjer = dohvatiSmjerNeprijatelja();
		postaviSmjerNeprijatelja(1);
		
	}
		
}

void Igra::postaviPomakNeprijatelja(sf::Vector2f V) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++)
			neprijatelji[i][j].pomak = V;
}

sf::Vector2f Igra::dohvatiPomakNeprijatelja() {
	int k, l;
	dohvatiZivogNeprijatelja(k, l);
	return neprijatelji[k][l].pomak;
}

void Igra::postaviSmjerNeprijatelja(float s) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++)
			neprijatelji[i][j].smjer = s;
}

float Igra::dohvatiSmjerNeprijatelja() {
	int k, l; 
	dohvatiZivogNeprijatelja(k, l); 
	return  neprijatelji[k][l].smjer;
}

void Igra::dohvatiZivogNeprijatelja(int& k, int& l) {
	for(int i = 0; i < 5;i++)
		for(int j = 0; j < 11;j++)
			if (neprijatelji[i][j].ziv) {
				k = i; 
				l = j;
				return;
			}

}

void Igra::pomakniTop() {
	smjer = provjeriGraniceTopa();
	TopSprite.move(pomak * smjer * brzina * protekloVrijeme().asSeconds());
}

void Igra::povecajBrzinuNeprijatelja() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++)
			neprijatelji[i][j].povecajBrzinu();
}

void Igra::updateNeprijatelja() {

	provjeriGraniceNeprijatelja();
	if (dolje) {
		postaviPomakNeprijatelja(sf::Vector2f(0.f, 1.f));
		dolje += 0.1;
	}		
		

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++)
			neprijatelji[i][j].pomakniNeprijatelja(protekloVrijeme().asSeconds());
}

void Igra::obradiUlaz() {
	smjer = 0;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && jesmoLiZivi() && !jeLiPauza()) {
		smjer = -1;
		//updejtPomaka();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && jesmoLiZivi() && !jeLiPauza()) {
		smjer = 1;
		//updejtPomaka();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !(metak.ziv) && jesmoLiZivi() && !jeLiPauza()) {
		metak.namjestiMetak(TopSprite.getPosition());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !jesmoLiZivi()) {
		restart(false);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && jeLiPocetak() ) {
		pocetak = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && pobijedio() ) {
		level++;
		restart(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !jeLiPauza()) {
		pauza = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jeLiPauza()) {
		pauza = false;
	}
}

void Igra::restart(bool next)  {
	if (!next)
		level = 1;

	bodoviTopa = (next)? bodoviTopa : 0;
	zivoti = 3;
	metak.ziv = false;
	
	sf::Vector2u velp = p.dohvatiVelicinu();
	TopSprite.setPosition(
		velp.x / 2.f,
		velp.y * (19.0f / 20.0f)
	);
	pomak = pocetni_pomak = sf::Vector2f(1.f, 0.f);
	smjer = 0;

	if (level > 1)
		velp.y += 50 * level;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			neprijatelji[i][j].namjesti(i, j, velp);
			neprijatelji[i][j].ziv = true;
			neprijatelji[i][j].metak.ziv = false;
			neprijatelji[i][j].pomak = neprijatelji[i][j].pocetni_pomak = sf::Vector2f(1.f, 0.f);
			neprijatelji[i][j].brzina = neprijatelji[i][j].pocetnaBrzina = (next) ? neprijatelji[i][j].pocetnaBrzina * 1.2 : 12;			
		}
	}

}

Igra::Igra() : p("Space Invaders", sf::Vector2u(800, 800)) {
	pocetak = true;
	bodoviTopa = 0;
	pauza = false;
	zivoti = 3;
	TopTex.loadFromFile(".\\Slike\\top.png");
	TopSprite.setTexture(TopTex);
	TopSprite.setOrigin(
		TopSprite.getLocalBounds().width / 2,
		TopSprite.getLocalBounds().height / 2
	);
	sf::Vector2u velp = p.dohvatiVelicinu();
	TopSprite.setPosition(
		velp.x / 2.f,
		velp.y * (19.0f/20.0f)
	);
	pomak = pocetni_pomak = sf::Vector2f(1.f, 0.f);
	smjer = 0;

	neprijatelji.resize(5);
	for (int i = 0; i < 5; i++) {
		neprijatelji[i].resize(11);
		for (int j = 0; j < 11; j++) {
			neprijatelji[i][j].namjesti(i, j, velp);
			neprijatelji[i][j].ziv = true;
			neprijatelji[i][j].pomak = neprijatelji[i][j].pocetni_pomak = sf::Vector2f(1.f, 0.f);
		}
	}

	metak.prijatelj();

	bool postoji = postojiLiFile();

	
	if (postoji){
		inFile.open(file);
		string pom;
		getline(inFile, pom);
		najboljiRez = stoi(pom);
		 cout << pom;
		inFile.close();
	}
	else {
		outFile.open(file);
		outFile << (najboljiRez = 0);
		outFile.close();
	}
		

	font.loadFromFile(".\\Fontovi\\Montez-Regular.ttf");
	text.setFont(font);
	text.setString(ispisHigh + to_string(najboljiRez));
	text.setOutlineColor(sf::Color(18, 153, 23));
	text.setOutlineThickness(3);
	TexPonovno.setCharacterSize(60);

	TexPonovno.setFont(font);
	TexPonovno.setString(ispisLoss);
	TexPonovno.setCharacterSize(50);

	TexPonovno.setOrigin(
		TexPonovno.getLocalBounds().width / 2,
		TexPonovno.getLocalBounds().height / 2
	);
	TexPonovno.setPosition(
		velp.x / 2.f,
		velp.y / 2.f
	);

	TexPonovno.setOutlineColor(sf::Color(18, 153, 23));
	TexPonovno.setOutlineThickness(10);
	//
	TexPocetak.setFont(font);
	TexPocetak.setString(stringPocetak);
	TexPocetak.setCharacterSize(70);
	TexPocetak.setOrigin(
		TexPocetak.getLocalBounds().width / 2,
		TexPocetak.getLocalBounds().height / 2
	);
	TexPocetak.setPosition(
		velp.x / 2.f,
		velp.y / 2.f
	);

	TexPocetak.setOutlineColor(sf::Color(18, 153, 23));
	TexPocetak.setOutlineThickness(10);
	//
	TexNext.setFont(font);
	TexNext.setString(stringNext);
	TexNext.setCharacterSize(60);
	TexNext.setOrigin(
		TexNext.getLocalBounds().width / 2,
		TexNext.getLocalBounds().height / 2
	);
	TexNext.setPosition(
		velp.x / 2.f,
		velp.y / 2.f
	);

	TexNext.setOutlineColor(sf::Color(18, 153, 23));
	TexNext.setOutlineThickness(10);
	//
	TexPauza.setFont(font);
	TexPauza.setString(stringPauza);
	TexPauza.setCharacterSize(50);

	TexPauza.setOrigin(
		TexPauza.getLocalBounds().width / 2,
		TexPauza.getLocalBounds().height / 2
	);
	TexPauza.setPosition(
		velp.x / 2.f,
		velp.y / 2.f
	);

	TexPauza.setOutlineColor(sf::Color(18, 153, 23));
	TexPauza.setOutlineThickness(10);
	//
	TexTvojiBodovi.setFont(font);
	TexTvojiBodovi.setString(stringTvojiBodovi + to_string(bodoviTopa));


	TexTvojiBodovi.setPosition(
		text.getPosition().x ,
		text.getPosition().y + text.getLocalBounds().height+5
	);

	TexTvojiBodovi.setOutlineColor(sf::Color(18, 153, 23));
	TexTvojiBodovi.setOutlineThickness(10);

	//
	tajni.smjer = sf::Vector2f(-1.f, 0.f);
	tajni.Tex.loadFromFile(".\\Slike\\tajni.png");
	tajni.sprite.setTexture(tajni.Tex);
	

	//srca
	TexSrce.loadFromFile(".\\Slike\\srce.png");
	for (int i = 0; i < 3; i++) {
		srca[i].setTexture(TexSrce);
		srca[i].setOrigin(
			srca[i].getLocalBounds().width,
			0
		);
		srca[i].setPosition(
			velp.x - (2-i)* srca[i].getLocalBounds().width,
			0
		);
	}
		

}

void Igra::prviLijeviZivi(int &k, int& l) {
	l = 11;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < l; j++) 
			if (neprijatelji[i][j].ziv) {
				k = i;
				l = j;
				break;
			}
}
void Igra::prviDesniZivi(int &r, int &t) {
	t = -1;
	for (int i = 0; i < 5; i++)
		for (int j = 10; j > t; j--)
			if (neprijatelji[i][j].ziv) {
				t = j;
				r = i;
				break;
			}
}

void Igra::updateMetak(float t) {

	provjeriMetak();

	if (metak.ziv) {
		(metak.sprite).move(metak.smjer * metak.brzina * t);
	}
		
}


void Igra::provjeriPogodakTopa() {
	if (!metak.ziv)
		return;
	for(int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++) {

			if ( !neprijatelji[i][j].ziv || !(metak.sprite.getGlobalBounds().intersects(neprijatelji[i][j].sprite.getGlobalBounds())))
				continue;
			bodoviTopa += neprijatelji[i][j].bodovi;
			metak.ziv = false;
			neprijatelji[i][j].ziv = false;
			cout << bodoviTopa << endl;
		}

	if (tajni.ziv && metak.sprite.getGlobalBounds().intersects(tajni.sprite.getGlobalBounds())) {
		tajni.ziv = false;
		metak.ziv = false;
		bodoviTopa += tajni.bodovi;
	}
		
}

Igra::~Igra() {}


void Igra::provjeriMetak() {
	if (metak.sprite.getPosition().y < 0)
		metak.ziv = false;
}

bool Igra::postojiLiFile() {
	ifstream dat(file);
	return dat.is_open();
}


void Igra::updateHighscore() {
	if (bodoviTopa <= najboljiRez)
		return;
	najboljiRez = bodoviTopa;
	outFile.open(file);
	outFile << najboljiRez;
	outFile.close();
	text.setString(ispisHigh + to_string(najboljiRez));
	
}

void Igra::updateMetkeNeprijatelja() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++)
			neprijatelji[i][j].pomakniMetak(protekloVrijeme().asSeconds());
}

void Igra::provjeriPogodakNeprijatelja() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++)
			if (neprijatelji[i][j].provjeriPogodakMetka(TopSprite) )
				zivoti--;
}

bool Igra::jesmoLiZivi() {
	if (zivoti < 1)
		return false;
	return true;
}

void Igra::provjeriKrajNeprijatelja() {
	for (int i = 4; i > -1; i--)
		for (int j = 10; j > -1; j--)
			if (neprijatelji[i][j].ziv && 
				neprijatelji[i][j].dajSprite().getPosition().y + neprijatelji[i][j].dajSprite().getLocalBounds().height/2 > p.dohvatiVelicinu().y) {
				zivoti = 0;
				break;
			}
				
		
}

bool Igra::pobijedio() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 11; j++)
			if (neprijatelji[i][j].ziv)
				return false;
	return true;
}

void Igra::pomakniTajni() {

	if (tajni.ziv && tajni.sprite.getPosition().x + tajni.sprite.getLocalBounds().width < 0) {
		tajni.ziv = false;
		return;
	}

	if (jeLiTajniZiv()) {
		tajni.sprite.move(tajni.smjer*tajni.brzina* protekloVrijeme().asSeconds());
		return;
	}

	


		

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 5000);

	if (distr(gen) == 5) {
		tajni.ziv = true;
		tajni.sprite.setPosition(p.dohvatiVelicinu().x, TopSprite.getPosition().y - 200);
	}
		
}