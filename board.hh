#ifndef BOARD_HH
#define BOARD_HH
#include<vector>
#include<math.h>
#include"plate.hh"
#include"monster.hh"
#include"pacman.hh"
#include"tile.hh"
#include <ctime>
#include<iostream>

class Board{
public:
	Board(size_t size,float refSpeed);
	Plate getPlate();
	size_t getTileSize();
	size_t getScore();
	Pacman getPacman();
	void printInPrompt();
	void playerMove();
	bool monsterMove(float timePlayed);
	void monsterOutOfHouse(Monster &monster);
	void teleport(Player &p);
	void drawBoard(sf::RenderWindow *window);
	void incIngameMonsters();

private:
	Pacman pacman;
	std::vector<Monster> ingameMonsters;
	std::array<Monster,4> monsters;
	Plate plate;
	size_t score;
	size_t tileSize;

	float refSpeed;
	char lastShortcut = 'e';

	const float hiddenTime = 30.0;
	const float scatterTime = 9.0;
	const float chaseTime = 30.0;
	const float panicTime = 7.0;
	float gameTime;

	//char pacmanSecondMove;

	void move(char);
	Tile getTileNext(size_t x, size_t y, char dir);
	bool isCloseEnough(std::array<float,2>, Tile, char);
	bool isPerpendicular(char x, char y);
	bool isBelowCenter(std::array<float,2> p, char direction);
};
#endif