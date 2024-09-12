
#include<SFML/Graphics.hpp>
#include"const.h"
#include"board.h"
#include<iostream>


void board::draw(sf::RenderWindow& window) {



	back.setSize(sf::Vector2f(6 * rs + 5 * rb, 6 * rs + 5 * rb));
	back.setPosition(180, 180);
	back.setFillColor(sf::Color(200, 200, 200, 25));

	if (first) {
		first = false;
		setBigBackground();
		setCircles();
	}
		
		
	
	

	int k = (l == -1) ? 1 : 100;
	float alpha = 0.01, beta;
	for (int r = 0; r < k; r++) {
		window.clear();
		window.draw(bigBackground);
		window.draw(back);
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 5; j++) {
				if (i * 5 + j == l)
					beta = alpha;
				else
					beta = 1;
				lines[i * 5 + j].l.setSize(sf::Vector2f(beta * rb, rs));
				lines[i * 5 + j].l.setPosition(180 + j * rb + (j + 1) * rs, 180 + i * (rb + rs));
				lines[i * 5 + j].l.setOutlineThickness(2);


				switch (lines[i * 5 + j].player)
				{
				case 0:
					lines[i * 5 + j].l.setFillColor(sf::Color(beta*150, beta * 150, beta * 150));
					break;
				case 1:
					lines[i * 5 + j].l.setFillColor(sf::Color(245, beta * 191, 66));
					break;
				case 2:
					lines[i * 5 + j].l.setFillColor(sf::Color(beta * 100, beta * 250, beta * 50));
					break;
				default:
					break;
				}

				window.draw(lines[i * 5 + j].l);
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {

				if (30 + i * 6 + j == l)
					beta = alpha;
				else
					beta = 1;
				lines[30 + i * 6 + j].l.setSize(sf::Vector2f(rs, beta * rb));
				lines[30 + i * 6 + j].l.setPosition(180 + j * rb + rs * j, 180 + (i + 1) * rs + i * rb);
				lines[30 + i * 6 + j].l.setOutlineThickness(2);

				switch (lines[30 + i * 6 + j].player)
				{
				case 0: 
					lines[30 + i * 6 + j].l.setFillColor(sf::Color(beta * 150, beta * 150, beta * 150));
					break;
				case 1:
					lines[30 + i * 6 + j].l.setFillColor(sf::Color(245, beta * 191, 66));
					break;
				case 2:
					lines[30 + i * 6 + j].l.setFillColor(sf::Color(beta * 100, beta * 250, beta * 50));
					break;
				default:
					break;
				}

				window.draw(lines[30 + i * 6 + j].l);
			}
		}

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++) {
				squares[i * 5 + j].s.setSize(sf::Vector2f(rb, rb));
				squares[i * 5 + j].s.setPosition(180 + rs * (j + 1) + rb * j, 180 + rs * (i + 1) + rb * i);
				squares[i * 5 + j].s.setOutlineThickness(1);

				if (i * 5 + j == squaresToAnimate[0] || i * 5 + j == squaresToAnimate[1])
					beta = alpha;
				else
					beta = 1;

				switch (squares[i * 5 + j].player)
				{
				case 1: 
					squares[i * 5 + j].s.setFillColor(sf::Color(210, beta * 182, 60));
					break;
				case 2:
					squares[i * 5 + j].s.setFillColor(sf::Color(163, beta * 219, 99));
					break;
				default:
					squares[i * 5 + j].s.setFillColor(sf::Color(150, 150, 150,0));
					break;
				}

				window.draw(squares[i * 5 + j].s);
			}

		for (int i = 0; i < 36; i++)
			window.draw(circles[i]);

		alpha += 0.01;
		window.display();
		sf::sleep(sf::milliseconds(5));

	}
	squaresToAnimate[0] = squaresToAnimate[1] = -1;
	l = -1;

	switch (win())
	{
	case 1:
		winner(window,"Player 1 wins");
		break;
	case 2:
		winner(window,"Player 2 wins");
		break;
	default:
		break;
	}
}

int board::click(float x, float y, int player) {

	for (int i = 0; i < 30; i++)
		if (x > lines[i].l.getPosition().x && x < (lines[i].l.getPosition().x + rb) &&
			y > lines[i].l.getPosition().y && y < (lines[i].l.getPosition().y + rs))
			if (lines[i].player == 0) {
				lines[i].player = player;
				l = i;
				
				if (!check(player, 1))
					return 1;
				return 0;


			}



	for (int i = 30; i < 60; i++)
		if (x > lines[i].l.getPosition().x && x < (lines[i].l.getPosition().x + rs) &&
			y > lines[i].l.getPosition().y && y < (lines[i].l.getPosition().y + rb)) {
			if (lines[i].player == 0) {
				lines[i].player = player;
				l = i;
				if (!check(player, 1))
					return 1;
				return 0;
			}
		}

	return 0;
}

bool board::check(int k, int x) {
	bool found = false;
	int r = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if ((!squares[i * 5 + j].player || squares[i * 5 + j].player > 2) && lines[5 * i + j].player && lines[5 * i + j + 5].player && lines[30 + 6 * i + j].player && lines[30 + 6 * i + j + 1].player) {
				if (x)
					squares[i * 5 + j].player = k;
				else
					squares[i * 5 + j].player = k + 3;
				found = true;
				squaresToAnimate[r++] = i * 5 + j;
			}



	return found;
}

int board::count(int player) {
	int count = 0;
	for (int i = 0; i < 25; i++)
		if (squares[i].player == player || squares[i].player == player + 3)
			count++;
	return count;
}

bool board::full() {
	for (int i = 0; i < 60; i++)
		if (!lines[i].player)
			return false;
	return true;
}

void board::setBigBackground() {
	texBigBackground.loadFromFile("tiles.png");
	bigBackground.setTexture(texBigBackground);
	bigBackground.setScale(1.25, 1.25);
}

void board::setCircles() {
	texCircle.loadFromFile("rockCircle.png");
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++) {
			circles[i * 6 + j].setTexture(texCircle);
			circles[i * 6 + j].setOrigin(15, 15);
			circles[i * 6 + j].setPosition(180 + rs * j + rb * j, 180 + rs * i + rb * i);
		}

}

int board::win() {
	if (!full())
		return 0;
	
	
	if (count(1) > 12)
		player = 1;
	else
		player = 2;
		
	return player;
	


}

void board::winner(sf::RenderWindow& window,std::string w) {
	setBigBackground();

	sf::RectangleShape R;
	R.setPosition(180, 180);
	R.setSize(sf::Vector2f(6 * rs + 5 * rb, 6 * rs + 5 * rb));
	R.setFillColor(sf::Color::Black);

	sf::Text T;
	T.setString(w);
	T.setCharacterSize(35);
	sf::Font F;
	F.loadFromFile("arial.ttf");
	T.setFont(F);

	T.setOrigin(
		T.getLocalBounds().left + T.getLocalBounds().width / 2.0f,
		T.getLocalBounds().top + T.getLocalBounds().height / 2.0f
	);

	T.setPosition(640 * 0.5f, 640 *0.5f);
	window.clear();
	window.draw(bigBackground);
	window.draw(R);
	window.draw(T);
	window.display();
	player = -2;

}
