#include"player.hh"

Player::Player(char ty,std::array<float,2> initPos){
	type=ty;
	position = initPos;
}

void Player::move(float distance,char direction){
	if(distance < 0 || (direction!='u' && direction!='d' && direction!='l' && direction!='r')){
		std::cout<<"Player::move negative distance or unrecognized direction !"<<std::endl;
		return;
	}
	if(direction=='u')
		position[0] -= distance;
	if(direction=='d')
		position[0] += distance;
	if(direction=='r')
		position[1] += distance;
	if(direction=='l')
		position[1] -= distance;
}

std::array<float,2> Player::getPosition() const{
	return position;
}
float Player::getX() const{
	return position[0];
}

float Player::getY() const{
	return position[1];
}

char Player::getType() const{
	return type;
	}

void Player::setType(char t){
	type = t;
}

void Player::setPosition(std::array<float,2> pos){
	position = pos;
}

void Player::drawPlayer(sf::RenderWindow *window,size_t tileSize,bool sha,sf::Color color) const{

	if(sha){
		sf::CircleShape shape(tileSize*0.8);
		shape.setPosition(position[1]*tileSize,position[0]*tileSize);
		shape.setFillColor(color);
		window->draw(shape);
	}
	else{
		sf::RectangleShape shape(sf::Vector2f(tileSize*1.6,tileSize*1.6));
		shape.setPosition((position[1]-0.25)*tileSize,(position[0]-0.25)*tileSize);
		shape.setFillColor(color);
		window->draw(shape);
	}
}
