#ifndef COMPUTER_H
#define COMPUTER_H

#include"board.h"
#include <random>

//GOTOVO

class computer {
	int start = 0;
public:
	double depth = 3;
	int move(sf::RenderWindow& window,board& board,int d,int player, int& opt); //trazeci najbolji potez, vratiti cemo broj obojanih kvadratica od PC-a
	void randomStart();
};

#endif // !COMPUTER_H
