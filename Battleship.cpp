#include "Battleship.h"

int SingleDeck::_remaining_count = 4;
int DoubleDeck::_remaining_count = 3;
int ThreeDeck::_remaining_count = 2;
int FourDeck::_remaining_count = 1;

int SingleDeck::_number = 0;
int DoubleDeck::_number = 0;
int ThreeDeck::_number = 0;
int FourDeck::_number = 0;


void Battleship::clear(){
	getCount() = 5 - _size;
	_is_placed = false;
	_state = ShipState::Undamaged;
	getNumber() = 0;
	_lifes = _size;
}

bool Battleship::isContains(int x, int y)
{
	for (auto coord : _coords) {
		if (coord.first == x && coord.second == y) {
			return true;
		}
	}

	return false;
}

void SingleDeck::refresh(){
	_remaining_count = SINGLEDECK_REMAINING_COUNT;
}

int& SingleDeck::getCount()
{
	return _remaining_count;
}

int & SingleDeck::getNumber()
{
	return _number;
}

int & DoubleDeck::getNumber()
{
	return _number;
}
int & ThreeDeck::getNumber()
{
	return _number;
}
int & FourDeck::getNumber()
{
	return _number;
}

Battleship::Battleship(int size) : _orientation(Horizontal), _x(START_X), _y(START_Y), _is_placed(false), _lifes(size),_size(size),_state(Undamaged){}

int Battleship::getSize()
{
	return _size;
}

Orientation Battleship::getOrientation()
{
	return _orientation;
}

Battleship::Coords& Battleship::getCoords()
{
	return _coords;
}

Battleship::Coords& Battleship::getBorders()
{
	return _borders;
}

void Battleship::refreshCoords(){
	_coords.clear();
	if (_orientation == Horizontal) {
		for (int i = 0; i < _size; ++i) {
			_coords.push_back(std::make_pair(_x + i, _y));
		}
	}
	else {
		for (int i = 0; i < _size; ++i) {
			_coords.push_back(std::make_pair(_x , _y + i));
		}
	}
	_borders.clear();
	setBorders();
}

void Battleship::setCoords(int x, int y){
	_x = x;
	_y = y;
	refreshCoords();
}

void Battleship::setBorders(){

	if (_orientation == Horizontal) {
		for (int i = 0; i < _size; ++i) {
			_borders.push_back(std::make_pair(_coords[i].first, _coords[i].second + 1));
			_borders.push_back(std::make_pair(_coords[i].first, _coords[i].second - 1));
		}
		for (int i = -1 ; i < 2; i++) {
			_borders.push_back(std::make_pair(_coords[0].first - 1, _coords[0].second + i));
			_borders.push_back(std::make_pair(_coords[0].first + _size, _coords[0].second + i));
		}
	}
	else {
		for (int i = 0; i < _size; ++i) {
			_borders.push_back(std::make_pair(_coords[i].first + 1, _coords[i].second));
			_borders.push_back(std::make_pair(_coords[i].first - 1, _coords[i].second));
		}
		for (int i = -1; i < 2; i++) {
			_borders.push_back(std::make_pair(_coords[0].first + i, _coords[0].second - 1));
			_borders.push_back(std::make_pair(_coords[0].first + i, _coords[0].second + _size));
		}
	}
}


void Battleship::changeOrientation(){
	_orientation = (_orientation == Horizontal) ? Vertical : Horizontal;
}

void Battleship::moveRight(Field& field_in){
	if (_is_placed)
		return;
	
	int field_size = field_in.getSize();

	if ((_x == (field_size - _size) && _orientation == Horizontal) || (_x == field_size - 1 && _orientation == Vertical))
		return;
	
	field_in.refresh();
	for (int i = 0; i < _size; ++i) {
		field_in.setState(Arr_Set, _coords[i].first + 1, _coords[i].second);
	}

	_x++;
	refreshCoords();
	placeBorders(field_in);
}

void Battleship::moveLeft(Field& field_in) {
	if (_is_placed)
		return;	
	if (_x == 0)
		return;
	
	field_in.refresh();
	for (int i = 0; i < _size; ++i) {
		field_in.setState(Arr_Set, _coords[i].first - 1, _coords[i].second);
	}

	_x--;
	refreshCoords();
	placeBorders(field_in);
}

void Battleship::moveUp(Field&  field_in){
	if (_is_placed)
		return;
	if (_y == 0)
		return;

	field_in.refresh();
	for (int i = 0; i < _size; ++i) {
		field_in.setState(Arr_Set, _coords[i].first , _coords[i].second - 1);
	}

	_y--;
	refreshCoords();
	placeBorders(field_in);
}

void Battleship::moveDown(Field&  field_in){
	if (_is_placed)
		return;

	int field_size = field_in.getSize();

	if ((_y == (field_size - _size) && _orientation == Vertical) || (_y == field_size - 1 && _orientation == Horizontal))
		return;

	field_in.refresh();
	for (int i = 0; i < _size; ++i) {
		field_in.setState(Arr_Set, _coords[i].first, _coords[i].second + 1);
	}

	_y++;
	refreshCoords();
	placeBorders(field_in);
}


void Battleship::placeBorders(Field& field_in){
	for (auto iter = _borders.begin(); iter != _borders.end(); iter++) {
		if (field_in.isCorrectCoords(iter->first, iter->second)) {
			field_in.setState(Arr_Border, iter->first, iter->second);
		}
	}
}

bool Battleship::isCorrectPlaced(Field & field_in) {

	int size = _coords.size();

	for (int i = 0; i < size; ++i) {
		if (field_in.getState(_coords[i].first, _coords[i].second) == Arr_Placed) 
			return false;
	}
	
	int borders_size = _borders.size();

	for (int i = 0; i < borders_size; ++i) {
		if (!field_in.isCorrectCoords(_borders[i].first, _borders[i].second)) {
			continue;
		}
		if (field_in.getState(_borders[i].first, _borders[i].second) == Arr_Placed) 
			return false;
	}

	return true;
}

bool Battleship::isPlaced()
{
	return _is_placed;
}


void Battleship::setAsPlaced(){
	_is_placed = true;
	this->getCount()--;
}

void Battleship::takeHit()
{
	_state = Damaged;
	_lifes--;
	if (!_lifes) {
		_state = Destroyed;
	}
}

ShipState Battleship::getState()
{
	return _state;
}

void DoubleDeck::refresh(){
	_remaining_count = DOUBLEDECK_REMAINING_COUNT;
}

int& DoubleDeck::getCount()
{
	return _remaining_count;
}

void ThreeDeck::refresh(){
	_remaining_count = THREEDECK_REMAINING_COUNT;
}

int& ThreeDeck::getCount()
{
	return _remaining_count;
}

void FourDeck::refresh(){
	_remaining_count = FOURDECK_REMAINING_COUNT;
}

int& FourDeck::getCount()
{
	return _remaining_count;
}