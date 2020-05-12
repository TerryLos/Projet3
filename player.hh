#ifndef PLAYER_HH
#define PLAYER_HH
#include<iostream>
#include<string>
#include<cmath>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include <ctime>

class Player{
public:
	Player() = default;
	explicit Player(char ty,std::array<float,2> initPos);
	void move(char direction);
	void drawPlayer(sf::RenderWindow *window,size_t tileSize,bool shape) const;
	std::array<float,2> getPosition() const;
	void setPosition(std::array<float,2> pos);
	float getX() const;
	float getY() const;
	float getRayon() const;
	void setSpeedInit(float speed);
	void setSpeed(float sp);
	float getSpeed() const;
	void setRayon(float ray);
	char getType() const ;
	void setType(char t);
	void setHide(bool state);
	bool getHide() const;
	void setColor(sf::Color color);
	sf::Color getNominalColor() const;
	
	void updateHiddenClock();
	void updateHiddenTime();
	float getHiddenTime();

	virtual char getDirection() const = 0;
	float getCurrSpeed(); // debuging
private:

	std::array<float,2> position;
	//p for pacman & m for monster
	char type;
	
	float nominalSpeed;
	float currentSpeed;

	float rayon;
	bool hidden;
	sf::Color currentColor;

protected:

	float hiddenTime;
	std::clock_t hiddenClock;
	sf::Color nominalColor;
};
#endif