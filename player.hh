#ifndef PLAYER_HH
#define PLAYER_HH
#include<iostream>
#include<string>
#include<math.h>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

class Player{
public:
	Player() = default;
	explicit Player(char ty,std::array<float,2> initPos);
	void move(float distance,char direction);
	void drawPlayer(sf::RenderWindow *window,size_t tileSize,bool shape,sf::Color color) const;
	std::array<float,2> getPosition() const;
	void setPosition(std::array<float,2> pos);
	float getX() const;
	float getY() const;
	char getType() const ;
	void setType(char t);

private:
	std::array<float,2> position;
	//p for pacman & m for monster
	char type;
};
#endif