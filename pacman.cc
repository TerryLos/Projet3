#include"pacman.hh"

Pacman::Pacman(std::array<float,2> initPos,float speed){
	setType('P');
	setPosition(initPos);
	setSpeedInit(speed);
}
size_t Pacman::eat(Plate plateau){

	//place une tolérancesur le centre de la case car vu qu'on est en point flotant,
	//il peut exister une petite différence dans les positions.
	if(abs(getX()-((size_t)getX() +0.5)) <0.05 || abs(getY()-((size_t)getY()+0.5)) <0.05){

		if(plateau.getTile((size_t)getX(),(size_t)getY()).isFood()){
			return 1;
		}

		else if(plateau.getTile((size_t)getX(),(size_t)getY()).isPilz())
			return 2;

	}
	return 0;
}