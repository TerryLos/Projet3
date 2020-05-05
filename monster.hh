#ifndef MONSTER_HH
#define MONSTER_HH
#include"player.hh"
#include"pacman.hh"
#include"plate.hh"
#include"tile.hh"
#include<string>
#include<math.h>

class Monster : public Player {
public:
	Monster() = default;
	explicit Monster(std::array<float,2> initPos,std::string name);
	void chase(sf::RenderWindow *window,const Plate plate,const Pacman pac);
	std::string getName() const;
	void setMode(std::string mo);
	void setTarget(const Tile t);
	char getDisplacement(const Plate plate,sf::RenderWindow *window);
	float euclidianDistance(const Tile t);

private:
	std::vector<Tile> availableNextTile(Plate plate);
	std::string name;
	std::string mode;
	Tile target;
	Tile lastPosition;
};
#endif