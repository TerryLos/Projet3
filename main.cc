#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include<string>
#include<iostream>
#include <cstdlib>
#include"board.hh"
#include"plate.hh"


int main(){
	Plate plate;
	std::clock_t start = std::clock();
	Board board(24, 0.16);
	sf::RenderWindow window(sf::VideoMode(board.getPlate().getLengthCol()*board.getTileSize(),board.getPlate().getLengthRow()*board.getTileSize()),"Pacorona");
	size_t k=0;
	srand(time(NULL));
	float timePlayed=0;

	while(window.isOpen()){
		sf::Event event;

		window.clear();
		board.drawBoard(&window);
		board.playerMove();

		timePlayed = ( std::clock() - start ) / (float) CLOCKS_PER_SEC;
		if(board.monsterMove(timePlayed)){
			std::cout << "END OF THE GAME "<< std::endl;
			//end game
			return 1;
		}

		k++;
		window.display();
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;

}