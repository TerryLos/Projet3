#include"pacman.hh"

Pacman::Pacman(std::array<float,2> initPos){
	setType('P');
	setPosition(initPos);
}
size_t Pacman::eat(Plate plateau){

	if(abs(getX()-round(getX())) <0.05 || abs(getY()-round(getY())) <0.05){

		if(plateau.getTile(round(getX()),round(getY())).isFood()){
			return 1;
		}

		else if(plateau.getTile(round(getX()),round(getY())).isPilz())
			return 2;

	}
	return 0;
}