#include"monster.hh"

Monster::Monster(std::array<float,2> initPos,std::string name,float speed){
	setType('M');
	setPosition(initPos);
	setSpeed(speed);
	this->name = name;

}

void Monster::chase(const Plate plate,const Pacman pac){
	lastPosition = plate.getTile((size_t)getX(),(size_t)getY());
	char c = getDisplacement(plate);

	if(!name.compare("Shadow")){
		
		setTarget(plate.getTile((size_t)pac.getX(),(size_t)pac.getY()));
		move(c);
		if(!plate.getTile((size_t)getX(),(size_t)getY()).isPlayable())
			move(opposite(c));
	}

}
char opposite(char c){
	if( c == 'd')
		return 'u';
	if( c == 'u')
		return 'd';
	if( c == 'l')
		return 'r';
	if( c == 'r')
		return 'l';

	return ' ';
}
std::string Monster::getName() const{
	return name;
}
void Monster::setMode(std::string mo){
	mode = mo;
}
void Monster::setTarget(const Tile t){
	target =t;
}
char Monster::getDisplacement(const Plate plate){
	//Displacement by default
	char displacement =' ';
	float minDistance = std::numeric_limits<float>::infinity();
	std::vector<Tile> nextTile =  availableNextTile(plate);

	if(!name.compare("Shadow")){
		for(auto i = nextTile.cbegin();i!= nextTile.cend();i++){
			
			if(minDistance>euclidianDistance(*i)){

				minDistance = euclidianDistance(*i);

				if((size_t)getY()-1 == i->getX() )
					displacement ='l';

				if((size_t)getY()+1 == i->getX() )
					displacement ='r';

				if((size_t)getX()-1 == i->getY() )
					displacement ='u';

				if((size_t)getX()+1 == i->getY() )
					displacement ='d';
				
			}
		}
	}

	return displacement;
}
std::vector<Tile> Monster::availableNextTile(Plate plate){
	std::vector<Tile> vect;

	if((size_t)getX() < plate.getLengthCol() && (size_t)getY() < plate.getLengthRow()){

		if(plate.getTile((size_t)getX()+1,(size_t)getY()).isPlayable() && (plate.getTile((size_t)getX()+1,(size_t)getY()) != lastPosition))
			vect.push_back(plate.getTile((size_t)getX()+1,(size_t)getY()));


		if(plate.getTile((size_t)getX(),(size_t)getY()+1).isPlayable() && (plate.getTile((size_t)getX(),(size_t)getY()+1) != lastPosition))
			vect.push_back(plate.getTile((size_t)getX(),(size_t)getY()+1));


	}
	if(getY()-1>=0 && getX()-1>=0){
		if(plate.getTile((size_t)getX()-1,(size_t)getY()).isPlayable() && (plate.getTile((size_t)getX()-1,(size_t)getY()) != lastPosition))
			vect.push_back(plate.getTile((size_t)getX()-1,(size_t)getY()));

		
		if(plate.getTile((size_t)getX(),(size_t)getY()-1).isPlayable() && (plate.getTile((size_t)getX(),(size_t)getY()-1) != lastPosition))
			vect.push_back(plate.getTile((size_t)getX(),(size_t)getY()-1));

		
	}
	

	return vect;
}
float Monster::euclidianDistance(const Tile t){

	size_t deltaX = (target.getY()- t.getX());
	size_t deltaY = (target.getX()- t.getY());

	return sqrt((deltaX*deltaX)+(deltaY*deltaY));
}