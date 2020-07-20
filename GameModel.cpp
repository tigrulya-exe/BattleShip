#include "GameModel.h"
#include "PlayerCreator.h"

void GameModel::initFieldMap() {
	_field_map[PlayerNum::First] = new Field;
	_field_map[PlayerNum::Second] = new Field;
}

void GameModel::refreshPlayers(){
	auto first_type = _first_player->getType();
	auto second_type = _second_player->getType();

	delete _first_player;
	delete _second_player;

	_first_player = PlayerFactory::getAccess().getPlayer(first_type);
	_second_player = PlayerFactory::getAccess().getPlayer(second_type);
	_current_player = _first_player;
}

GameModel::GameModel() : _current_stage(gameStage::Menu), _first_battleships(_placer._first_battleships), _second_battleships(_placer._second_battleships){
	_current_player_num = PlayerNum::First;
	initFieldMap();
	
	_first_player = new HumanPlayer{};
	_second_player = new HumanPlayer{};
	_current_player = _first_player;
}

PlayerNum GameModel::getCurrentPlayerNum()
{
	return _current_player_num;
}

playerType GameModel::getCurrentPlayerType()
{
	return _current_player->getType();
}

playerType GameModel::getFirstPlayerType()
{
	return _first_player->getType();
}

playerType GameModel::getSecondPlayerType()
{
	return _second_player->getType();
}

void GameModel::setFirstPlayer(playerType type_in){
	delete _first_player;
	_first_player = PlayerFactory::getAccess().getPlayer(type_in);
	_current_player = _first_player;
}

void GameModel::setSecondPlayer(playerType type_in){
	delete _second_player;
	_second_player = PlayerFactory::getAccess().getPlayer(type_in);
}

void GameModel::changePlayer(){

	if (_current_player_num == PlayerNum::First) {
		_current_player_num = PlayerNum::Second;
		_current_player = _second_player;
		_current_battleships = &_second_battleships;
	}
	else {
		_current_player_num = PlayerNum::First;
		_current_player = _first_player;
		_current_battleships =  &_first_battleships;
	}
	
	if (_current_stage == Arrangement) {
		_placer.changePlayer();
	}
}

gameStage GameModel::getCurrentStage()
{
	return _current_stage;
}

void GameModel::setClosed(bool value){
	_isWindowClosed = value;
}

void GameModel::setStage(gameStage stage_in){
	_current_stage = stage_in;
}

Field& GameModel::getCurrentField()
{
	return *_field_map[_current_player_num];
}

Field & GameModel::getSecondField()
{
	PlayerNum tmp = (_current_player_num == First) ? PlayerNum::Second : PlayerNum::First;

	return *_field_map[tmp];
}

bool GameModel::isArrangementFinished()
{
	return (_current_player_num == PlayerNum::Second && !_placer.getShipAvailability());
}

void GameModel::prepareToGameStage(){
	for (auto ships : _second_battleships) {
		_manager.setShips(ships);
	}
	_manager.changePlayer();
	for (auto ships : _first_battleships) {
		_manager.setShips(ships);
	}
	_manager.changePlayer();

	
}

void GameModel::refresh(){
	_placer.clear(*_field_map[First]);
	_placer.changePlayer();
	_placer.clear(*_field_map[Second]);
	_placer.changePlayer();

	_current_player_num = PlayerNum::First;
	_is_game_finished = false;
	_is_arrangement_finished = false;
	_manager.clear();

	_stats.refresh();
	refreshPlayers();
}

Player * GameModel::getCurrentPlayer(){
	return _current_player;
}

Player * GameModel::getFirstPlayer()
{
	return _first_player;
}

Player* GameModel::getSecondPlayer()
{
	return _second_player;
}

Statistics & GameModel::getStatistics()
{
	return _stats;
}

GameModel::~GameModel(){
	delete _first_player;
	delete _second_player;

	delete _field_map[PlayerNum::First];
	delete _field_map[PlayerNum::Second];
}


bool GameModel::getClosed()
{
	return _isWindowClosed;
}

std::vector<std::vector<CellState>>& Field::getField()
{
	return _field;
}

ShipPlacer& GameModel::getShipPlacer() {
	return _placer;
}

BattleManager & GameModel::getBattleManager()
{
	return _manager;
}