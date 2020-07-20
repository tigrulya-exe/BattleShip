#include "Player.h"
#include <random>
#include <algorithm>
#include <SFML/Graphics.hpp>

HumanPlayer::HumanPlayer() : Player(playerType::Human){}

ViewEvent& HumanPlayer::play(gameStage, PlayerNum){
	getTmpEvent()._type = EventType::Nothing;

	return getTmpEvent();
}


void EasyBot::setCoords() {

	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			_coords.push_back(std::make_pair(i,j));
		}
	}

	std::shuffle(_coords.begin(), _coords.end(),std::mt19937{ std::random_device{}() });
}

EasyBot::EasyBot() : _coords_offset(0), Player(playerType::easyBot), _is_ready_to_start(false){
	setCoords();
}

ViewEvent& EasyBot::play(gameStage stage_in, PlayerNum num_in){
	ViewEvent& tmp_event = getTmpEvent();
	
	tmp_event._type = EventType::Nothing;

	EventType after_arrangement_action;
	switch (stage_in)
	{
	case Arrangement:
		after_arrangement_action = (num_in == PlayerNum::First) ? EventType::PlayerChanged : EventType::StartGamePressed;
		tmp_event._type = (_is_ready_to_start) ? after_arrangement_action : EventType::RandomPressed;
		_is_ready_to_start = true;
		break;
	case GameStage:
		tmp_event._type = EventType::Fire;
		shoot();
		break;
	}
	return tmp_event;
}

void EasyBot::shoot(){
	ViewEvent& tmp = getTmpEvent();
	tmp.cellPressed.SetCoords(_coords[_coords_offset].first, _coords[_coords_offset].second);
	_coords_offset++;
}

EasyBot::~EasyBot(){
	_coords.clear();
}

Player::Player(playerType type_in) : _type (type_in){}

ViewEvent & Player::getTmpEvent()
{
	return _tmp_event;
}

playerType & Player::getType()
{
	return _type;
}

void HardBot::setCoords(){

	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			_coords.push_back(std::make_pair(i, j));
		}
	}

	std::shuffle(_coords.begin(), _coords.end(), std::mt19937{ std::random_device{}() });
}

void HardBot::hitShoot(){
	ViewEvent& tmp = getTmpEvent();
	tmp.cellPressed.SetCoords(_ship_coords[_ships_offset].first, _ship_coords[_ships_offset].second);
	_ships_offset++;
	setHitDelay();
}

void HardBot::setHitDelay(){
	_hit_delay = std::rand() % HIT_DELAY_RAND + 1;
}

HardBot::HardBot() : _coords_offset(0), Player(playerType::hardBot), _is_ready_to_start(false), _ships_offset(0){
	setHitDelay();
}

ViewEvent & HardBot::play(gameStage stage_in, PlayerNum num_in)
{
	ViewEvent& tmp_event = getTmpEvent();

	tmp_event._type = EventType::Nothing;

	EventType after_arrangement_action;
	switch (stage_in)
	{
	case Arrangement:
		after_arrangement_action = (num_in == PlayerNum::First) ? EventType::PlayerChanged : EventType::StartGamePressed;
		tmp_event._type = (_is_ready_to_start) ? after_arrangement_action : EventType::RandomPressed;
		_is_ready_to_start = true;
		break;
	case GameStage:
		tmp_event._type = EventType::Fire;
		if (_hit_delay){
			shoot();
			_hit_delay--;
			break;
		}
		hitShoot();
	}
	return tmp_event;
}

void HardBot::shoot(){

	ViewEvent& tmp = getTmpEvent();
	tmp.cellPressed.SetCoords(_coords[_coords_offset].first, _coords[_coords_offset].second);
	_coords_offset++;
}

void HardBot::refreshCoords(Battleship* ship_in) {
	auto& coords = ship_in->getCoords();
	auto& borders = ship_in->getBorders();

	for (auto& pair : coords) {
		remove(_coords.begin(), _coords.end(), pair);
	}

	for (auto& pair : borders) {
		remove(_coords.begin(), _coords.end(), pair);
	}
}

void HardBot::setCoords(Field & field_in){
	auto& field = field_in.getField();
	
	int i = 0;

	for (auto& column : field) {
		for (auto& state : column) {
			HardBot::Coords& coords = (state == CellState::Arr_Water) ? _coords : _ship_coords;
			coords.push_back(std::make_pair(i / FIELD_SIZE, i % FIELD_SIZE));
			++i;
		}
	}

	std::shuffle(_coords.begin(), _coords.end(), std::mt19937{ std::random_device{}() });
	std::shuffle(_ship_coords.begin(), _ship_coords.end(), std::mt19937{ std::random_device{}() });

}
