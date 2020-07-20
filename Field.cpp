#include "Battleship.h"

Field::Field(){
	for (int i = 0; i < FIELD_SIZE; ++i) {
		_field.push_back(std::vector<CellState>());
		for (int j = 0; j < FIELD_SIZE; ++j) {
			_field[i].push_back(Arr_Water);
		}
	}
}

CellState Field::getState(int x, int y)
{
	return _field[x][y];
}

void Field::setState(CellState state_in, int x, int y) {
	_field[x][y] = state_in;
}

void Field::refresh() {
	for (auto iter = _field.begin(); iter != _field.end(); iter++) {
		for (auto it = iter->begin(); it != iter->end(); it++) {
			*it = Arr_Water;
		}
	}
}

void Field::setStartShip(Battleship* ship_in) {

	Battleship::Coords& coords = ship_in->getCoords();

	for (auto coord : coords) {
		setState(Arr_Set, coord.first, coord.second);
	}
}

int Field::getSize()
{
	return _field.size();
}

bool Field::isCorrectCoords(int x, int y){
	return (x <= FIELD_SIZE - 1 && x >= 0 && y >= 0 && y <= FIELD_SIZE - 1);
}
