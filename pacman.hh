#ifndef PACMAN_HH
#define PACMAN_HH
#include"player.hh"
#include"plate.hh"
#include<math.h>

class Pacman : public Player {
public:
	Pacman() = default;
	explicit Pacman(std::array<float,2> initPos);
	size_t eat(Plate plateau);
};
#endif