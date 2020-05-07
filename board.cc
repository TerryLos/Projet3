#include"board.hh"
#include<iostream>
Board::Board(size_t size,float refSpeed){
	plate = Plate();
	tileSize = size;
	score=0;
	this->refSpeed = refSpeed;
	std::array<float,2> pos;
	pos[0]=15;pos[1]=21.5;

	pacman =  Pacman(pos,refSpeed);
	pacman.setRayon(0.8);
	pos[0]=13;pos[1]=12;

	test = Monster(pos,"Shadow",0.95*refSpeed);
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
	test.drawPlayer(window,tileSize,false,sf::Color(255,0,0));

}
void Board::monsterMove(){

	//mets la vitesse par défaut
	test.setSpeed(test.getSpeed());
	if(plate.getTile((size_t)test.getX(),(size_t)test.getY()).isTunnel()){
		test.setSpeed(0.55*test.getSpeed());

		teleport(test);
	}
	test.chase(plate,pacman);

}
void Board::teleport(Player p){

	if((size_t)p.getY() == 0){
		std::cout << " TELEPORT "<< std::endl;
		std::array<float,2> tmp;
		tmp[1] = 12;
		tmp[0] = 13;
		p.setPosition(tmp);
		std::cout << p.getPosition()[0] << " " << p.getPosition()[1] << std::endl;
	}
	if((size_t)p.getY() == plate.getLengthCol()){
			std::cout << " TELEPORT "<< std::endl;
		std::array<float,2> tmp;
		tmp[0] = p.getX();
		tmp[1] = 0;
		p.setPosition(tmp);
	}
}
void Board::playerMove(){
	/* Index inversion of roundedPos because of the true representation of the grid
	In the memory of the program */
	std::array<float,2> tmpPos;
	std::array<size_t,2> roundedPos;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move('l');

		if(!plate.getTile(roundedPos[1],roundedPos[0]-1).isPlayable() && abs(pacman.getPosition()[1]-(roundedPos[0])) <= pacman.getRayon()/2)
			pacman.move('r');

		if(pacman.eat(plate)){
			score+= pacman.eat(plate);
			Tile tile(0,false,roundedPos);
			plate.setTile(tile);
			plate.decountFood();
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move('r');

		if(!plate.getTile(roundedPos[1],roundedPos[0]+1).isPlayable() && abs(pacman.getPosition()[1]-(roundedPos[0]+1)) <= pacman.getRayon()/2 )
			pacman.move('l');

		if(pacman.eat(plate)){
			score+= pacman.eat(plate);
			Tile tile(0,false,roundedPos);
			plate.setTile(tile);
			plate.decountFood();
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move('u');

		if(!plate.getTile(roundedPos[1]-1,roundedPos[0]).isPlayable() && abs(pacman.getPosition()[0]-(roundedPos[1])) <= pacman.getRayon()/2 )
			pacman.move('d');

		if(pacman.eat(plate)){
			score+= pacman.eat(plate);
			Tile tile(0,false,roundedPos);
			plate.setTile(tile);
			plate.decountFood();
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move('d');

		if(!plate.getTile(roundedPos[1]+1,roundedPos[0]).isPlayable() && abs(pacman.getPosition()[0]-(roundedPos[1]+1)) <= pacman.getRayon()/2 )
			pacman.move('u');

		if(pacman.eat(plate)){

			score+= pacman.eat(plate);
			Tile tile(0,false,roundedPos);
			plate.setTile(tile);
			plate.decountFood();
		}
	}
	tmpPos = pacman.getPosition();
	roundedPos[1] = (size_t)tmpPos[0];
	roundedPos[0] = (size_t)tmpPos[1];
	
	if(plate.getTile(roundedPos[1],roundedPos[0]).isTunnel()){
		teleport(pacman);
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
