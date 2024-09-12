#include<iostream>
#include<SFML/Graphics.hpp>

#include"const.h" //
#include"play_options.h" //
#include"twoPlayer.h" //
#include"board.h"
#include"withComputer.h"

//GOTOVO

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Zatvaranje kvadrata");
    playOptions opt;

    switch ( opt.draw(window) )
    {
    case 0:
        twoPlayer(window);
        break;
    case 1:
        withComputer(window);
        break;
    default:
        break;
    }
        
    return 0;
}