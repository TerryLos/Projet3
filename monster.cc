#include"monster.hh"

Monster::Monster(std::array<float,2> initPos,std::string name){
	setType('M');
	setPosition(initPos);
	this->name = name;
	
}
void Monster::chase(sf::RenderWindow *window,const Plate plate,const Pacman pac){
	lastPosition = plate.getTile((size_t)getY(),(size_t)getX());
	char c = getDisplacement(plate,window);

	if(!name.compare("Shadow")){
		setTarget(plate.getTile((size_t)pac.getY(),(size_t)pac.getX()));
		move(0.1,c);
		if(!plate.getTile(round(getY()),round(getX())).isPlayable())
			move(-0.1,c);
	}

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
char Monster::getDisplacement(const Plate plate,sf::RenderWindow *window){
	//Displacement by default
	char displacement =' ';
	float minDistance = std::numeric_limits<float>::infinity();
	std::vector<Tile> nextTile =  availableNextTile(plate);

	if(!name.compare("Shadow")){
		for(auto i = nextTile.cbegin();i!= nextTile.cend();i++){
			
			//std::cout<<minDistance << " " << getY() << " " << getX() <<" "<< target.getY()<<" "<< target.getX()<< std::endl;
			if(minDistance>euclidianDistance(*i)){
				minDistance = euclidianDistance(*i);

				if((size_t)getX() == i->getX()){
					if(getY() - i->getY() >0)
						displacement ='l';
					else
						displacement ='r';
				}
				else{
					if(getX() - i->getX() >0)
						displacement ='u';
					else
						displacement ='d';
				}
			}
		}
	}

	return displacement;
}
std::vector<Tile> Monster::availableNextTile(Plate plate){
	std::vector<Tile> vect;

	///if((size_t)getY()+1 <= plate.getLengthCol() && (size_t)getY()+1 <= plate.getLengthRow()){
		//if(plate.getTile((size_t)getY()+1,(size_t)getX()).isPlayable() && (plate.getTile((size_t)getY()+1,(size_t)getX()) != lastPosition))
		vect.push_back(plate.getTile((size_t)getY()+1,(size_t)getX()));

		//if(plate.getTile((size_t)getY(),(size_t)getX()+1).isPlayable() && (plate.getTile((size_t)getY(),(size_t)getX()+1) != lastPosition))
		vect.push_back(plate.getTile((size_t)getY(),(size_t)getX()+1));

	//}
	//if(getY()-1>=0 && getX()-1>=0){
	//if(plate.getTile((size_t)getY()-1,(size_t)getX()).isPlayable() && (plate.getTile((size_t)getY()-1,(size_t)getX()) != lastPosition))
		vect.push_back(plate.getTile((size_t)getY()-1,(size_t)getX()));
	//if(plate.getTile((size_t)getY(),(size_t)getX()-1).isPlayable() && (plate.getTile((size_t)getY(),(size_t)getX()-1) != lastPosition))
		vect.push_back(plate.getTile((size_t)getY(),(size_t)getX()-1));
	//}
	

	return vect;
}
float Monster::euclidianDistance(const Tile t){

	size_t deltaX = (target.getX()- t.getX());
	size_t deltaY = (target.getY()- t.getY());

	return sqrt((deltaX*deltaX)+(deltaY*deltaY));
}