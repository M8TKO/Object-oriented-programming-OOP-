#include<SFML/Graphics.hpp>
#include<iostream>
#include"const.h"
#include"computer.h"
#include"board.h"



int computer::move(sf::RenderWindow& window, board& board,int d,int player, int& opt) {

	if  ( board.full() || d > depth)
		return board.count(2)-board.count(1);

	int max = -100, min = 100,opt_1 = -1,opt_2 = -1;
	
	int stop = start; std::cout << start << " " << (stop + 59) % 60 << std::endl;
	for (int i = start; ; i = (i + 1) % 60) {
		if (!board.lines[i].player) {
			board.lines[i].player = player;

			int next = (board.check(player, 0) ? player : 3 - player);
			int temp = move(window, board, d + 1, next, opt);
			if (temp > max) {
				opt_2 = i;
				max = temp;
			}
			if (temp < min) {
				opt_1 = i;
				min = temp;
			}

			board.lines[i].player = 0;
			if (board.squaresToAnimate[0] != -1)
				board.squares[board.squaresToAnimate[0]].player = 0;
			if (board.squaresToAnimate[1] != -1)
				board.squares[board.squaresToAnimate[1]].player = 0;
			board.squaresToAnimate[0] = board.squaresToAnimate[1] = -1;

		}
		if (i == (stop + 59)%60)
			break;
	}
	if (player == 1 ) {
		opt = opt_1;
		return min;
	}
	//ako je igrao PC
	opt = opt_2;
	return max;
		
}

void computer::randomStart() {

	std::random_device rand;
		std::mt19937 gen(rand());
		std::uniform_int_distribution<> distrib(0, 59);

		start = distrib(gen);
}