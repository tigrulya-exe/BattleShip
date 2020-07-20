#include "BattleManager.h"
#include <iostream>

const int REMAINED_SHIPS = 10;

void BattleManager::setShips(std::vector<Battleship*>& ships_in){
	for (auto ship : ships_in) {
		_ships[_curr_player].push_back(ship);
	}
}

BattleManager::BattleManager() : _curr_player(PlayerNum::First){
	setRemainedShips();
}

bool BattleManager::checkCoords(int x, int y, Field& field_in){
	for (auto ship : _ships[_curr_player]) {
		if (ship->isContains(x, y)) {
			ship->takeHit();
			field_in.getField()[x][y] = CellState::Hit;
			checkIfDestroyed(field_in, ship);
			return true;
		}
	}
	field_in.getField()[x][y] = CellState::Miss;
	return false;
}

void BattleManager::changePlayer(){
	_curr_player = (_curr_player == PlayerNum::First) ? PlayerNum::Second : PlayerNum::First;
}

void BattleManager::setRemainedShips(){
	_ships_remained[PlayerNum::First] = REMAINED_SHIPS;
	_ships_remained[PlayerNum::Second] = REMAINED_SHIPS;
}

void BattleManager::checkIfDestroyed(Field& field_in, Battleship* ship){
	if (ship->getState() != ShipState::Destroyed) {
		return;
	}

	PlayerNum tmp = (_curr_player == PlayerNum::First) ? PlayerNum::Second : PlayerNum::First;
	_ships_remained[tmp]--;

	Battleship::Coords& coords = ship->getCoords();
	Battleship::Coords& borders = ship->getBorders();

	for (auto coord : coords) {
		field_in.getField()[coord.first][coord.second] = CellState::Kill;
	}

	for (auto coord : borders) {
		if (field_in.isCorrectCoords(coord.first, coord.second)) {
			field_in.getField()[coord.first][coord.second] = CellState::Miss;
		}
	}
}

void BattleManager::clear(){
	_curr_player = PlayerNum::First;
	_ships[PlayerNum::First].clear();
	_ships[PlayerNum::Second].clear();
	setRemainedShips();
}

bool BattleManager::isAnyShipAlive(){
	if (!_ships_remained[PlayerNum::First] || !_ships_remained[PlayerNum::Second])
		return false;

	return true;
}


int BattleManager::getRemainedShips(PlayerNum num_in)
{
	return _ships_remained[num_in];
}

BattleManager::~BattleManager(){
	for (auto ship : _ships[PlayerNum::First]) {
		delete ship;
	}

	for (auto ship : _ships[PlayerNum::Second]) {
		delete ship;
	}
}

BattleManager::Ships & BattleManager::getCurrentShips(PlayerNum num_in)
{
	return _ships[num_in];
}