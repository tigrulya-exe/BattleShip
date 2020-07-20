#pragma once
#include <map>
#include "Player.h"

namespace {
	const int PLAYER_SHOTS_INIT_VALUE = 0;
	const int SUCCESSFUL_SHOTS_INIT_VALUE = 0;
}

class Statistics
{
	std::map<PlayerNum, int> _player_shots;
	std::map<PlayerNum, int> _successful_shots;

	void setShots();
public:
	Statistics();
	void playerShot(PlayerNum);
	void successfulShot(PlayerNum);

	int getPlayerShots(PlayerNum);
	int getSuccessfulShot(PlayerNum);

	void refresh();
};

