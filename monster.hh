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
	explicit Monster(std::array<float,2> initPos,std::string name,float speed);
	void chase(const Plate plate,const Pacman pac);
	std::string getName() const;
	void setMode(std::string mo);
	void setTarget(const Tile t);
	char getDisplacement(const Plate plate);
	float euclidianDistance(const Tile t);


private:
	std::vector<Tile> availableNextTile(Plate plate);

	std::string name;
	std::string mode;
	Tile target;
	Tile lastPosition;

};
char opposite(char c);
#endif