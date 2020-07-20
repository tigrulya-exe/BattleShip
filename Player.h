#pragma once
#include "ViewEvent.h"
#include <vector>
#include <map>
#include <algorithm>
#include "Battleship.h"

namespace {
	const int HIT_DELAY_RAND = 2;
}

enum playerType { easyBot, hardBot, Human };
enum PlayerNum { First, Second };
enum  gameStage { Menu, Options, Help, Arrangement, GameStage, Finish , Stats };

class Player
{
	ViewEvent _tmp_event;
	playerType _type;
public:
	Player(playerType);
	virtual ViewEvent& play(gameStage, PlayerNum) = 0;
	ViewEvent& getTmpEvent();
	playerType& getType();
	virtual ~Player() {};
};

class HumanPlayer : public Player {
public:
	HumanPlayer();
	ViewEvent& play(gameStage, PlayerNum) override;
};

class EasyBot : public Player {
	using Coords = std::vector<std::pair<int, int>>;
	Coords _coords;
	void setCoords();
	int _coords_offset;
	bool _is_ready_to_start;
public:
	EasyBot();
	ViewEvent& play(gameStage, PlayerNum) override;
	void shoot() ;
	~EasyBot();
};

class HardBot : public Player {
	using Coords = std::vector<std::pair<int, int>>;
	using Coord = std::pair<int, int>;

	Coords _ship_coords;
	Coords _coords;
	void setCoords();

	int _coords_offset;
	int _ships_offset;
	
	bool _is_ready_to_start;

	void hitShoot();
	void setHitDelay();
	int _hit_delay;
public:
	HardBot();
	ViewEvent& play(gameStage, PlayerNum) override;
	void shoot();
	void refreshCoords(Battleship*);

	void setCoords(Field&);
};