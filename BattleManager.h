#pragma once
#include <vector>
#include "Battleship.h"
#include "Player.h"
#include <map>

extern const int REMAINED_SHIPS;

class BattleManager
{
public:
	using Ships = std::vector<Battleship*>;
	void setShips(std::vector<Battleship*>&);

	BattleManager();
	bool checkCoords(int, int, Field&);
	void changePlayer();
	Ships& getCurrentShips(PlayerNum);
	void clear();
	bool isAnyShipAlive();

	int getRemainedShips(PlayerNum);
	~BattleManager();
private:
	std::map<PlayerNum, int> _ships_remained;

	void setRemainedShips();
	void checkIfDestroyed(Field&, Battleship*);
	std::map<PlayerNum, Ships> _ships;
	PlayerNum _curr_player;

};

