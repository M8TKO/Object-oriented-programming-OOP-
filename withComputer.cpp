
#include<SFML/Graphics.hpp>
#include<iostream>
#include"const.h"
#include"board.h"
#include"computer.h"



void withComputer(sf::RenderWindow& window) {
    board board;
    computer pc;
    int count = 0;
    bool isMouseClicked;
    while ( 1 ) {

        if (board.getPlayer() == -2) {
            while (1) {
                sf::Event event;
                window.pollEvent(event);
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
            }
            break;
        }

        window.clear();
        board.draw(window);
        if (!window.isOpen())
            break;
        if (board.full()) {
            std::cout << "Game over! ";
            break;
        }

        sf::Event event;

        isMouseClicked = false;
        while (board.getPlayer() == 1) { //ako smo mi na redu


            window.pollEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left && !isMouseClicked) {

                switch (board.click((float)event.mouseButton.x, (float)event.mouseButton.y, board.getPlayer())) {
                case 0: //nismo napravili potez
                    break;
                case 1: //napravili smo potez i sad je PC
                    board.changePlayer();
                    break;
                case 2: //player je odigrao i opet je on
                    break;
                }
                isMouseClicked = true;
            }

            if (event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Left) {
                isMouseClicked = false;
            }

            window.clear();
            board.draw(window);
            window.display();

            switch (board.win())
            {
            case 1:
                board.winner(window, "Victory!");
                break;
            case 2:
                board.winner(window, ":(((");
            default:
                break;
            }


            if (board.getPlayer() == -2) {
                while (1) {
                    sf::Event event;
                    window.pollEvent(event);
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        break;
                    }
                }
                break;
            }
           
        }

        
        if (!window.isOpen())
            break;
        
        int k;
        pc.randomStart();
        pc.move(window, board, 1, 2, k);   

        board.l = k;
        board.lines[k].player = 2; 
        
        

        if (!board.check(2, 1))
            board.changePlayer();

        switch (board.win())
        {
        case 1:
            board.winner(window, "Victory!");
            break;
        case 2:
            board.winner(window, ":(((");
        default:
            break;
        }

    }
}
