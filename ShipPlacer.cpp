#include <cstdlib>
#include "ShipPlacer.h"
#include <time.h>
#include <random>
#include <algorithm>


void ShipPlacer::initBattleships(std::vector<Ships>& battleships){
	for (int i = SHIP_TYPE_COUNT; i > 0; --i) {
		battleships.push_back(Ships{});
	}

	for (int i = 0; i < SINGLEDECK_REMAINING_COUNT; ++i) {
		battleships[SINGLEDECK_INDEX].push_back(new SingleDeck);
		battleships[SINGLEDECK_INDEX][i]->refreshCoords();
	}

	for (int i = 0; i < DOUBLEDECK_REMAINING_COUNT; ++i) {
		battleships[DOUBLEDECK_INDEX].push_back(new DoubleDeck);
		battleships[DOUBLEDECK_INDEX][i]->refreshCoords();
	}

	for (int i = 0; i < THREEDECK_REMAINING_COUNT; ++i) {
		battleships[THREEDECK_INDEX].push_back(new ThreeDeck);
		battleships[THREEDECK_INDEX][i]->refreshCoords();
	}

	for (int i = 0; i < FOURDECK_REMAINING_COUNT; ++i) {
		battleships[FOURDECK_INDEX].push_back(new FourDeck);
		battleships[FOURDECK_INDEX][i]->refreshCoords();
	}
}

bool ShipPlacer::isCorrectCoords(int x, int y)
{
	return (x < FIELD_SIZE && x >= 0 && y >= 0 && y < FIELD_SIZE);
}

void ShipPlacer::setRandomCoords(){

	for (int i = 0; i < SHIP_TYPE_COUNT; ++i) {
		_random_ships.push_back(Ships{});
	}

	setHorizontalHeadCoords<SingleDeck>(SINGLEDECK_SIZE, _random_ships[SINGLEDECK_INDEX]);
	setVerticalHeadCoords<SingleDeck>(SINGLEDECK_SIZE, _random_ships[SINGLEDECK_INDEX]);
	setHorizontalHeadCoords<DoubleDeck>(DOUBLEDECK_SIZE, _random_ships[DOUBLEDECK_INDEX]);
	setVerticalHeadCoords<DoubleDeck>(DOUBLEDECK_SIZE, _random_ships[DOUBLEDECK_INDEX]);
	setHorizontalHeadCoords<ThreeDeck>(THREEDECK_SIZE, _random_ships[THREEDECK_INDEX]);
	setVerticalHeadCoords<ThreeDeck>(THREEDECK_SIZE, _random_ships[THREEDECK_INDEX]);
	setHorizontalHeadCoords<FourDeck>(FOURDECK_SIZE, _random_ships[FOURDECK_INDEX]);
	setVerticalHeadCoords<FourDeck>(FOURDECK_SIZE, _random_ships[FOURDECK_INDEX]);
}

ShipPlacer::ShipPlacer() : _ship_type(SINGLEDECK_INDEX), _is_correct_to_place(true) {
	_is_any_ship_available = true;
	is_first_player = true;
	_arrangement_layer = new Field;

	initBattleships(_first_battleships);
	initBattleships(_second_battleships);
	_current_battleships = &_first_battleships;

	_current_battleship = _first_battleships[SINGLEDECK_INDEX][FIRST_SHIP_INDEX];
	_arrangement_layer->setStartShip(_current_battleship);
	setRandomCoords();
}

Battleship * ShipPlacer::getCurrentBattleShip()
{
	return _current_battleship;
}

void ShipPlacer::setPlaceCorrectness(bool value){
	_is_correct_to_place = value;
}

bool ShipPlacer::getPlaceCorrectness()
{
	return _is_correct_to_place;
}

bool ShipPlacer::getShipAvailability()
{
return _is_any_ship_available;
}

void ShipPlacer::refreshShips() {
	for (auto iter = (*_current_battleships).begin(); iter != (*_current_battleships).end(); iter++) {
		(*iter)[FIRST_SHIP_INDEX]->refresh();
		(*iter)[FIRST_SHIP_INDEX]->getNumber() = 0;
	}
}

void ShipPlacer::checkShipAvailability() {
	if (_is_any_ship_available) {
		_current_battleship->setCoords(START_X, START_Y);
		_current_battleship->refreshCoords();
		_current_battleship->placeBorders(*_arrangement_layer);
		_arrangement_layer->setStartShip(_current_battleship);
	}
}

void ShipPlacer::changeCurrentShip() {
	if (!_current_battleship->getCount()) {
		changeCurrentShipType();
		return;
	}

	_current_battleship->getNumber()++;
	_current_battleship = (*_current_battleships)[_ship_type][_current_battleship->getNumber()];
}

void ShipPlacer::changeCurrentShipType() {
	bool flag = false;
	for (int i = (_ship_type + 1) % SHIP_TYPE_COUNT, k = 0; k < SHIP_TYPE_COUNT; i = (i + 1) % SHIP_TYPE_COUNT, k++) {
		if ((*_current_battleships)[i][FIRST_SHIP_INDEX]->getCount()) {
			flag = true;
			_ship_type = i;
			break;
		}
	}
	if (!flag) {
		_is_any_ship_available = false;
		return;
	}
 	_current_battleship = (*_current_battleships)[_ship_type][(*_current_battleships)[_ship_type][0]->getNumber()];
}

void ShipPlacer::changeOrientation() {
	if (_current_battleship->isPlaced())
		return;

	_current_battleship->changeOrientation();
	_current_battleship->refreshCoords();

	Battleship::Coords& coords = _current_battleship->getCoords();
	int size = coords.size();

	for (int i = 0; i < size; ++i) {
		if (!isCorrectCoords(coords[i].first, coords[i].second)) {
			_current_battleship->changeOrientation();
			_current_battleship->refreshCoords();
			return;
		}
	}

	_arrangement_layer->refresh();
	for (int i = 0; i < size; ++i) {
		_arrangement_layer->setState(CellState::Arr_Set, coords[i].first, coords[i].second);
	}
	_current_battleship->placeBorders(*_arrangement_layer);
}

void ShipPlacer::place(Field & field_in)
{
	if (_current_battleship->isPlaced() || !getPlaceCorrectness())
		return;

	Battleship::Coords& coords = _current_battleship->getCoords();
	int size = coords.size();

	for (int i = 0; i < size; ++i) {
		field_in.setState(CellState::Arr_Placed, coords[i].first, coords[i].second);
	}

	_current_battleship->setAsPlaced();
	_arrangement_layer->refresh();
}

void ShipPlacer::setRandomly(Field& field_in) {
	std::vector<int> ship_counter;

	clear(field_in);
	_is_any_ship_available = true;
	_is_correct_to_place = true;

	for (int i = SHIP_TYPE_COUNT; i > 0; --i) {
		ship_counter.push_back(i);
	}

	for (int i = 0; i < SHIP_TYPE_COUNT; ++i) {
		std::shuffle(_random_ships[i].begin(), _random_ships[i].end(), std::mt19937{ std::random_device{}() });
	}

	std::vector<Ships>& ships = (is_first_player) ? _first_battleships : _second_battleships;
	
	for (int i = SHIP_TYPE_COUNT - 1; i >= 0; --i) {
		ships[i].clear();
		for (int j = 0; _is_any_ship_available && ship_counter[i]; ++j){
			_current_battleship = _random_ships[i][j];
			if (isCorrectPlaced(field_in, _current_battleship)) {
				place(field_in);
				ships[i].push_back(_current_battleship);
				ship_counter[i]--;
			}
		}
	}

	_is_any_ship_available = false;
	_is_correct_to_place = false;
}

bool ShipPlacer::isCorrectPlaced(Field & field_in, Battleship* ship_in)
{
	Battleship::Coords& _coords = ship_in->getCoords();
	int size = _coords.size();

	for (int i = 0; i < size; ++i) {
		if (field_in.getState(_coords[i].first, _coords[i].second) == CellState::Arr_Placed) return false;
	}

	Battleship::Coords& _borders = ship_in->getBorders();
	int borders_size = _borders.size();

	for (int i = 0; i < borders_size; ++i) {
		if (!field_in.isCorrectCoords(_borders[i].first, _borders[i].second)) {
			continue;
		}
		if (field_in.getState(_borders[i].first, _borders[i].second) == CellState::Arr_Placed)
			return false;
	}

	return true;
}

void ShipPlacer::clear(Field& field_in){
	_arrangement_layer->refresh();
	field_in.refresh();
	
	for (auto ships : *_current_battleships) {
		for (auto ship : ships) {
			ship->clear();
		}
	}

	for (auto ships : _random_ships) {
		for (auto ship : ships) {
			ship->clear();
		}
	}
	_current_battleship->setCoords(START_X, START_Y);
}

ShipPlacer::~ShipPlacer(){
	delete _arrangement_layer;
}

void ShipPlacer::changePlayer() {

	if (is_first_player) {
		is_first_player = false;
		_current_battleships = &_second_battleships;
	}
	else {
		is_first_player = true;
		_current_battleships = &_first_battleships;
	}

	_current_battleship = (*_current_battleships)[SINGLEDECK_INDEX][FIRST_SHIP_INDEX];
	_ship_type = SINGLEDECK_INDEX;
	_is_any_ship_available = true;

	_arrangement_layer->setStartShip(_current_battleship);
}

Field & ShipPlacer::getArrangementLayer()
{
	return *_arrangement_layer;
}

