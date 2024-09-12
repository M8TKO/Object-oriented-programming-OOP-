#ifndef PLAY_OPTIONS_H
#define PLAY_OPTIONS_H

#include <SFML/Graphics.hpp>
#include<string>
//GOTOVO

class playOptions {
	sf::Text playerText, pcText;
	sf::Texture t1, t2;
	sf::Font F;
	sf::Sprite back, box_sprite1,box_sprite2;
public:
	void setNames(std::string s1, std::string s2);
	void setFont(std::string f);
	void setCSize(float s);
	void setFColor(sf::Color c);
	void centreText(sf::RenderWindow& window);
	void setSprite(sf::RenderWindow& window);
	int draw(sf::RenderWindow& window);
};

#endif 

