#include"board.hh"
#include<iostream>
Board::Board(size_t size){
	plate = Plate();
	tileSize = size;
	score=0;
	std::array<float,2> pos;
	pos[0]=15;pos[1]=21.5;
	pacman =  Pacman(pos);
	pacman.setRayon(0.8);
	pos[0]=13;pos[1]=11;
	test = Monster(pos,"Shadow");
	test.setRayon(1.6);
}
Plate Board::getPlate(){
	return plate;
}
size_t Board::getScore(){
	return score;
}

size_t Board::getTileSize(){
	return tileSize;
}
void Board::drawBoard(sf::RenderWindow *window){
	plate.drawPlate(window,tileSize);
	pacman.drawPlayer(window,tileSize,true,sf::Color(255,255,0));
	//test.chase(window,plate,pacman);
	//test.drawPlayer(window,tileSize,false,sf::Color(255,0,0));

}
void Board::playerMove(){
	/* Index inversion of roundedPos because of the true representation of the grid
	In the memory of the program */
	std::array<float,2> tmpPos;
	std::array<size_t,2> roundedPos;

	std::cout<< pacman.getPosition()[0] << " " << pacman.getPosition()[1] << " "<< pacman.getRayon() << std::endl;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move(0.2,'l');

		if(!plate.getTile(roundedPos[1],roundedPos[0]-1).isPlayable() && abs(pacman.getPosition()[1]-(roundedPos[0]-1)) < pacman.getRayon()/2)
			pacman.move(0.2,'r');

		if(pacman.eat(plate)){
			score+= pacman.eat(plate);
			Tile tile(0,false,roundedPos);
			plate.setTile(tile);
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move(0.2,'r');

		if(!plate.getTile(roundedPos[1],roundedPos[0]+1).isPlayable() && abs(pacman.getPosition()[0]-(roundedPos[1]+1)) < pacman.getRayon()/2 )
			pacman.move(0.2,'l');

		if(pacman.eat(plate)){
			score+= pacman.eat(plate);
			Tile tile(0,false,roundedPos);
			plate.setTile(tile);
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move(0.2,'u');

		if(!plate.getTile(roundedPos[1]-1,roundedPos[0]).isPlayable() && abs(pacman.getPosition()[1]-(roundedPos[0]-1)) < pacman.getRayon()/2 )
			pacman.move(0.2,'d');

		if(pacman.eat(plate)){
			score+= pacman.eat(plate);
			Tile tile(0,false,roundedPos);
			plate.setTile(tile);
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move(0.1,'d');

		if(!plate.getTile(roundedPos[1]+1,roundedPos[0]).isPlayable() && abs(pacman.getPosition()[0]-(roundedPos[1]+1)) < pacman.getRayon()/2 )
			pacman.move(0.1,'u');

		if(pacman.eat(plate)){
			score+= pacman.eat(plate);
			Tile tile(0,false,roundedPos);
			plate.setTile(tile);
		}
	}
}
void Board::printInPrompt(){
	std::array<float,2> tmpPos = pacman.getPosition();
	std::array<float,2> tmpPos2 = test.getPosition();
	for(size_t i =0;i<plate.getLengthRow();i++){
		for(size_t j =0;j<plate.getLengthCol();j++){
			if(plate.getTile(i,j).isWall())
				std::cout<<" ";
			else if(!(i== round(tmpPos[0]) && j== round(tmpPos[1])) && !(i== round(tmpPos2[0]) && j== round(tmpPos2[1])))
				std::cout<<plate.getTile(i,j).getType();
			else if(!(i== round(tmpPos2[0]) && j== round(tmpPos2[1])))
				std::cout<<"P";
			else 
				std::cout<<"C";
		}
		std::cout<<"\n";
	}
}
Pacman Board::getPacman(){
	return pacman;
}
