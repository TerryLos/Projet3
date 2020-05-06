#include"player.hh"

Player::Player(char ty,std::array<float,2> initPos){
	type=ty;
	rayon = 0;
	position = initPos;
}

void Player::move(float distance,char direction){

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
float Player::getRayon() const{
	return rayon;
}
void Player::setRayon(float ray){
	rayon = ray;
}

void Player::drawPlayer(sf::RenderWindow *window,size_t tileSize,bool sha,sf::Color color) const{

	if(sha){
		sf::CircleShape shape(tileSize*rayon);
		shape.setOrigin(tileSize*getRayon(),tileSize*getRayon());
		shape.setPosition(position[1]*tileSize,position[0]*tileSize);
		shape.setFillColor(color);
		window->draw(shape);

	}
	else{
		sf::RectangleShape shape(sf::Vector2f(tileSize*rayon,tileSize*rayon));
		shape.setOrigin(tileSize*getRayon()/2,tileSize*getRayon()/2);
		shape.setPosition(position[1]*tileSize*getRayon(),position[0]*tileSize*getRayon());
		shape.setFillColor(color);
		window->draw(shape);
	}
}
