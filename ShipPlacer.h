#pragma once
#include <vector>
#include <map>
#include <cmath>
#include "Battleship.h"

namespace {
	const int SINGLEDECK_INDEX = 0;
	const int DOUBLEDECK_INDEX = 1;
	const int THREEDECK_INDEX = 2;
	const int FOURDECK_INDEX = 3;

	const int FIRST_SHIP_INDEX = 0;
}

class GameModel;

class ShipPlacer
{
	using Ships = std::vector<Battleship*>;
	int _ship_type;
	Battleship* _current_battleship;
	bool _is_any_ship_available;
	Field* _arrangement_layer;
	bool _is_correct_to_place;
	bool is_first_player;

	std::vector<Ships> _random_ships;

	std::vector <Ships> _first_battleships;
	std::vector <Ships> _second_battleships;
	std::vector <Ships>* _current_battleships;

	void initBattleships(std::vector<Ships>&);
	bool isCorrectCoords(int,int);

	template<class T>
	void setHorizontalHeadCoords(int size, Ships& ships) {
		int cycle_size = FIELD_SIZE - size + 1;

		for (int i = 0, k = 0; i < cycle_size; ++i) {
			for (int j = 0; j < FIELD_SIZE; ++j, ++k) {
				ships.push_back(new T{});
				ships[k]->setCoords(i, j);
			}
		}
	}

	template<class T>
	void setVerticalHeadCoords(int size, Ships & ships) {
		int cycle_size = FIELD_SIZE - size + 1;

		for (int i = 0, k = FIELD_SIZE * cycle_size; i < FIELD_SIZE; ++i) {
			for (int j = 0; j < cycle_size; ++j, ++k) {
				ships.push_back(new T{});
				ships[k]->changeOrientation();
				ships[k]->setCoords(i, j);
			}
		}
	}

	void setRandomCoords();
public:
	ShipPlacer();
	void changePlayer(); 

	Field& getArrangementLayer();
	Battleship* getCurrentBattleShip();

	void setPlaceCorrectness(bool);
	bool getPlaceCorrectness();
	bool getShipAvailability();
	void refreshShips();
	void checkShipAvailability();

	void changeCurrentShip();
	void changeCurrentShipType();

	void changeOrientation();
	void place(Field&);
	void setRandomly(Field&);

	bool isCorrectPlaced(Field&, Battleship*);
	void clear(Field&);

	~ShipPlacer();
	friend GameModel;
};

