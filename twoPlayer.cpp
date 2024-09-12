
#include<SFML/Graphics.hpp>
#include<iostream>
#include"const.h" //
#include"board.h"

//GOTOVO

void twoPlayer(sf::RenderWindow& window) {

    board board;
    bool isMouseClicked = false;

    while (window.isOpen()) {

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

        sf::Event event;
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) {
            window.close();
            break;
        }


        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left && !isMouseClicked) {

            switch (board.click(event.mouseButton.x, event.mouseButton.y, board.getPlayer())) {
            case 0: //player nije napravio potez ili je dovršio kvadratiæ
                break;
            case 1: //player je odigrao, i red je na sljedem igracu
                board.changePlayer();
                break;
            }

            isMouseClicked = true;
        }

        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left) {
            isMouseClicked = false;
        }



    }

}
//#include<SFML/Graphics.hpp>
//#include<iostream>
//#include"const.h"
//#include"board.h"
//
//void twoPlayer(sf::RenderWindow& window) {
//	board board;
//    bool isMouseClicked = false;
//
//    while (window.isOpen()) {
//
//		board.draw(window);       
//        sf::Event event;       
//        window.pollEvent(event);
//        if (event.type == sf::Event::Closed) {
//            window.close();
//            break;
//        }
//
//        
//        if ( event.type == sf::Event::MouseButtonPressed &&
//             event.mouseButton.button == sf::Mouse::Left && !isMouseClicked) {
//          
//            switch (board.click(event.mouseButton.x, event.mouseButton.y)) {
//            case 0: //player nije napravio potez  
//                break; 
//            case 1: //player je odigrao, i red je na sljedem igracu
//                
//                board.changePlayer();
//                break;
//            case 2: //player je odigrao i opet je on
//           
//                break;
//            case 3: //player je odigrao i izgubio TU FALI JOS SLUCAJEVA
//                
//                break;
//            }
//
//            isMouseClicked = true; 
//        }
//
//        if (event.type == sf::Event::MouseButtonReleased &&
//            event.mouseButton.button == sf::Mouse::Left) {
//            isMouseClicked = false; 
//        }
//       
//
//
//    }
//	
//}