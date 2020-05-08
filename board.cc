#include"board.hh"

Board::Board(size_t size,float refSpeed){
	plate = Plate();
	tileSize = size;
	score=0;
	this->refSpeed = refSpeed;
	std::array<std::array<float,2>,5> pos = {{ { {20,14} } , { {14,12} }, { {17,12} } ,{ {17,14} } , { {17,16} } }};
	std::array<std::string,4> names = { {"Shadow","Speedy","Bashful","Pokey"} };
	std::array<sf::Color,5> color =  { {sf::Color(255,255,0),sf::Color(255,0,0),sf::Color(250,197,246),sf::Color(0,255,255),sf::Color(247,187,20)} };

	pacman = Pacman(pos[0],refSpeed);
	pacman.setRayon(0.8);
	pacman.setColor(color[0]);

	for(int i=0;i<4;i++){
		monsters[i] = Monster(pos[i+1],names[i],0.95*refSpeed);
		monsters[i].setRayon(1.6);
		monsters[i].setColor(color[i+1]);
		monsters[i].setMode("chase");

	}

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
	pacman.setColor(sf::Color(255,255,0));
	pacman.drawPlayer(window,tileSize,true);

	for( auto i = monsters.cbegin(); i!= monsters.cend();i++)
		i->drawPlayer(window,tileSize,false); 


}
void Board::monsterMove(){


	for(auto monster = monsters.begin();monster != monsters.end();monster++){

		monster->setSpeed(0.95*refSpeed);

		if(plate.getTile((size_t)monster->getX(),(size_t)monster->getY()).isTunnel()){
			monster->setSpeed(0.55*monster->getSpeed());

			teleport(*monster);
		}
		if(plate.getTile((size_t)monster->getX(),(size_t)monster->getY()).isFantomHouse())
			monsterOutOfHouse(monster);

		if(!monster->getMode().compare("chase") && !plate.getTile((size_t)monster->getX(),(size_t)monster->getY()).isFantomHouse())
			monster->chase(plate,plate.getTile((size_t)pacman.getX(),(size_t)pacman.getY()),pacman.getDirection());

	}

}
void Board::monsterOutOfHouse(Monster *monster) {
	monster->chase(plate,plate.getTile(15,12),'o');
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
	size_t value =0;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move('l');
		pacman.setDirection('l');

		if(!plate.getTile(roundedPos[1],roundedPos[0]-1).isPlayable() && abs(pacman.getPosition()[1]-(roundedPos[0])) <= pacman.getRayon()/2){
			pacman.move('r');
			pacman.setDirection('r');
		}

		value = pacman.eat(plate,monsters);
		if(value){
			score+= value;
			if(value <= 50){
				Tile tile(0,false,roundedPos);
				plate.setTile(tile);
				plate.decountFood();
			}
			
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move('r');
		pacman.setDirection('r');

		if(!plate.getTile(roundedPos[1],roundedPos[0]+1).isPlayable() && abs(pacman.getPosition()[1]-(roundedPos[0]+1)) <= pacman.getRayon()/2 ){
			pacman.move('l');
			pacman.setDirection('l');
		}

		value = pacman.eat(plate,monsters);
		if(value){
			score+= value;
			if(value <= 50){
				Tile tile(0,false,roundedPos);
				plate.setTile(tile);
				plate.decountFood();
			}
			
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move('u');
		pacman.setDirection('u');

		if(!plate.getTile(roundedPos[1]-1,roundedPos[0]).isPlayable() && abs(pacman.getPosition()[0]-(roundedPos[1])) <= pacman.getRayon()/2 ){
			pacman.move('d');
			pacman.setDirection('d');
		}

		value = pacman.eat(plate,monsters);
		if(value){
			score+= value;
			if(value <= 50){
				Tile tile(0,false,roundedPos);
				plate.setTile(tile);
				plate.decountFood();
			}
			
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		tmpPos = pacman.getPosition();
		roundedPos[1] = (size_t)tmpPos[0];
		roundedPos[0] = (size_t)tmpPos[1];
		pacman.move('d');
		pacman.setDirection('d');

		if(!plate.getTile(roundedPos[1]+1,roundedPos[0]).isPlayable() && abs(pacman.getPosition()[0]-(roundedPos[1]+1)) <= pacman.getRayon()/2 ){
			pacman.move('u');
			pacman.setDirection('u');
		}

		value = pacman.eat(plate,monsters);
		if(value){
			score+= value;
			if(value <= 50){
				Tile tile(0,false,roundedPos);
				plate.setTile(tile);
				plate.decountFood();
			}
			
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
	std::array<float,2> tmpPos2 = monsters[0].getPosition();
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
