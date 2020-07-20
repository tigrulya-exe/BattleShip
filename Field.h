#pragma once
#include <utility>
#include <vector>

class Battleship;

enum  CellState { Arr_Water, Arr_Set, Arr_Placed, Arr_Border, Clear, Miss, Hit, Kill };

namespace {
	const int FIELD_SIZE = 10;
}

class Field {
	std::vector<std::vector<CellState>> _field;
public:
	Field();

	CellState getState(int, int);
	void setState(CellState, int, int);
	std::vector<std::vector<CellState>>& getField();
	void refresh();
	void setStartShip(Battleship*);

	int getSize();
	bool isCorrectCoords(int, int);

};