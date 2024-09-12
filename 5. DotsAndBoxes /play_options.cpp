#include <SFML/Graphics.hpp>
#include"play_options.h"
#include<iostream>


void playOptions::setNames(std::string s1, std::string s2) {
	playerText.setString( s1 );
	pcText.setString( s2 );
}

void playOptions::setFont(std::string f){
	F.loadFromFile(f);
	playerText.setFont(F);
	pcText.setFont(F);
}

void playOptions::setCSize(float s) {
	playerText.setCharacterSize(s);
	pcText.setCharacterSize(s);
}

void playOptions::setFColor(sf::Color c) {
	playerText.setFillColor( c) ;
	pcText.setFillColor(c);
}

void playOptions::centreText(sf::RenderWindow& window) {

	playerText.setOrigin( 
		playerText.getLocalBounds().left + playerText.getLocalBounds().width / 2.0f,
		playerText.getLocalBounds().top + playerText.getLocalBounds().height / 2.0f
	);

	playerText.setPosition(window.getSize().x * 0.25f, window.getSize().y / 2.0f);

	pcText.setOrigin(
		pcText.getLocalBounds().left + pcText.getLocalBounds().width / 2.0f,
		pcText.getLocalBounds().top + pcText.getLocalBounds().height / 2.0f
	);

	pcText.setPosition(window.getSize().x * 0.75f, window.getSize().y / 2.0f);
}

void playOptions::setSprite(sf::RenderWindow& window) {
	
	t1.loadFromFile("tiles.png");
	t2.loadFromFile("SmallCrate.png");

	back.setTexture(t1);
	back.setScale(1.25, 1.25);

	box_sprite1.setTexture(t2);
	box_sprite2.setTexture(t2);

	box_sprite1.setScale(6, 5);
	box_sprite2.setScale(6, 5);


	box_sprite1.setOrigin(
		box_sprite1.getLocalBounds().left + box_sprite1.getLocalBounds().width / 2.0f,
		box_sprite1.getLocalBounds().top + box_sprite1.getLocalBounds().height / 2.0f
	);

	box_sprite2.setOrigin(
		box_sprite2.getLocalBounds().left + box_sprite2.getLocalBounds().width / 2.0f,
		box_sprite2.getLocalBounds().top + box_sprite2.getLocalBounds().height / 2.0f
	);

	box_sprite1.setPosition( window.getSize().x * 0.25f , window.getSize().y / 2.0f );
	box_sprite2.setPosition(window.getSize().x * 0.75f, window.getSize().y / 2.0f);

}

int playOptions::draw(sf::RenderWindow& window) {

	setNames("2 players", "vs Computer");
	setFont("arial.ttf");
	setCSize(27);
	setFColor(sf::Color::Black);
	centreText(window);
	setSprite(window);
	window.clear();
	window.draw(back);
	window.display();

	while (window.isOpen()) {

		window.clear();

		window.draw(back);
		window.draw(box_sprite1);
		window.draw(box_sprite2);
		window.draw(playerText);
		window.draw(pcText);
		window.display();

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i pos = sf::Mouse::getPosition(window);

					if (box_sprite1.getGlobalBounds().contains(pos.x, pos.y))
						return 0;
					else if (box_sprite2.getGlobalBounds().contains(pos.x, pos.y))
						return 1;
				}
					

				
				
				break;
			default:
				break;
			}
		}
	}
	
	return 0;
}
