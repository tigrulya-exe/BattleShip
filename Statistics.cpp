#include "Statistics.h"



void Statistics::setShots(){
	_player_shots[PlayerNum::First] = PLAYER_SHOTS_INIT_VALUE;
	_player_shots[PlayerNum::Second] = PLAYER_SHOTS_INIT_VALUE;

	_successful_shots[PlayerNum::First] = SUCCESSFUL_SHOTS_INIT_VALUE;
	_successful_shots[PlayerNum::Second] = SUCCESSFUL_SHOTS_INIT_VALUE;
}

Statistics::Statistics(){
	setShots();
}

void Statistics::playerShot(PlayerNum num_in){
	_player_shots[num_in]++;
}

void Statistics::successfulShot(PlayerNum num_in){
	_successful_shots[num_in]++;
}

int Statistics::getPlayerShots(PlayerNum num_in)
{
	return _player_shots[num_in];
}

int Statistics::getSuccessfulShot(PlayerNum num_in)
{
	return _successful_shots[num_in];
}

void Statistics::refresh(){
	setShots();
}
