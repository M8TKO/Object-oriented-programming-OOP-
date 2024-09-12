
#ifndef BOARD_H
#define BOARD_H


#include<vector>
#include<SFML/Graphics.hpp>
#include"const.h" //

class board;

class line {
	
	friend class board;
	friend class computer;
	friend void withComputer(sf::RenderWindow& window);
	sf::RectangleShape l;
	int player;
public:
	line() {
		player = 0;
	}
};

class square {
	friend void withComputer(sf::RenderWindow& window); //makni ovo
	friend class board;
	friend class computer;
	sf::RectangleShape s;
	int player = 0;
};

class board {
	friend class computer;
	friend void withComputer(sf::RenderWindow& window);
private:
	std::vector<line> lines;
	sf::RectangleShape back;
	std::vector<square> squares;
	sf::Sprite circles[36];
	sf::Sprite bigBackground;
	sf::Texture texBigBackground, texCircle;
	int l = -1;
	int player = 1;
	bool first = true;
	int squaresToAnimate[2] = { -1,-1 };
	
public:
	board() {
		lines.resize(60);
		squares.resize(25);
	}
	void draw(sf::RenderWindow& window);
	int click(float x, float y, int player);
	bool check(int k, int x);
	int count(int player);
	bool full();
	int getPlayer() { return player; }
	void changePlayer() { player = 3 - player; } // 1 --> 2 & 2 --> 1 :)a
	void setBigBackground();
	void setCircles();
	int win();
	void winner(sf::RenderWindow& window, std::string w);
};

#endif

