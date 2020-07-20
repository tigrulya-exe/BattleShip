#include "Controller.h"

#include <iostream>
#include <cmath>

MenuController::MenuController(GameModel &  model_in) : Controller(model_in){}

void MenuController::handleEvent_(ViewEvent& event_in) {
	GameModel& model = getModel();
	checkFirstPlayer(model.getFirstPlayerType());
	checkSecondPlayer(model.getSecondPlayerType());

	auto event_type = event_in._type;

	switch (event_type)
	{
	case EventType::Nothing:
		break;
	case EventType::ExitPressed:
		model.setClosed(true);
		break;
	case EventType::StartPressed:
		model.setStage(gameStage::Arrangement);
		break;
	case EventType::OptionsPressed:
		model.setStage(gameStage::Options);
		break;
	case EventType::HelpPressed:
		model.setStage(gameStage::Help);
		break;
	}
}

void Controller::init_players(){
	_first_player = _model.getFirstPlayer();
	_second_player = _model.getSecondPlayer();
}

void Controller::checkFirstPlayer(playerType type_in){
	if (type_in == _first_player->getType()) {
		return;
	}
	delete _first_player; 
	_first_player = PlayerFactory::getAccess().getPlayer(type_in);
}

void Controller::checkSecondPlayer(playerType type_in){
	if (type_in == _second_player->getType()) {
		return;
	}
	delete _second_player;
	_second_player = PlayerFactory::getAccess().getPlayer(type_in);
}

Controller::Controller(GameModel & model_in) : _model(model_in){
	init_players();
}

GameModel & Controller::getModel()
{
	return _model;
}

playerType OptionsController::setCurrentFirstPlayer(int add){
	static int i = 0;

	if (!i && add < 0)
		add = _player_types.size() + add;

	i = abs(add + i) % _player_types.size();	
	return _player_types[i];
}

playerType OptionsController::setCurrentSecondPlayer(int add){
	static int i = 0;

	if (!i && add < 0)
		add = _player_types.size() + add;

	i = abs(add + i) % _player_types.size();
	return _player_types[i];
}

void OptionsController::setPlayerTypes(){
	_player_types.push_back(playerType::Human);
	_player_types.push_back(playerType::easyBot);
	_player_types.push_back(playerType::hardBot);
}

OptionsController::OptionsController(GameModel &  model_in) : Controller(model_in) {
	setPlayerTypes();
}

void OptionsController::handleEvent_(ViewEvent& event_in) {
	GameModel& model = getModel();
	checkFirstPlayer(model.getFirstPlayerType());
	checkSecondPlayer(model.getSecondPlayerType());

	auto event_type = event_in._type;

	switch (event_type)
	{
	case EventType::Nothing:
		break;
	case EventType::BackPressed:
		model.setStage(gameStage::Menu);
		break;
	case EventType::FLeftPressed:
		model.setFirstPlayer(setCurrentFirstPlayer(SHIFT_LEFT));
		break;
	case EventType::FRightPressed:
		model.setFirstPlayer(setCurrentFirstPlayer(SHIFT_RIGHT));
		break;
	case EventType::SLeftPressed:
		model.setSecondPlayer(setCurrentSecondPlayer(SHIFT_LEFT));
		break;
	case EventType::SRightPressed:
		model.setSecondPlayer(setCurrentSecondPlayer(SHIFT_RIGHT));
		break;
	}
}

void ArrangementController::setHardBotCoords(Player* player_in, Field& field_in){
	if (player_in->getType() != playerType::hardBot) {
		return;
	}

	HardBot* hardBot = dynamic_cast<HardBot*>(player_in);
	hardBot->setCoords(field_in);
}

void ArrangementController::checkIfHardBot(){
	auto& model = getModel();
	
	setHardBotCoords(model.getCurrentPlayer(), model.getSecondField());
	Player* non_current_player = (model.getCurrentPlayerNum() == PlayerNum::First) ? model.getSecondPlayer() : model.getFirstPlayer();
	setHardBotCoords(non_current_player, model.getCurrentField());
}

ArrangementController::ArrangementController(GameModel & model_in) : Controller(model_in){}

void ArrangementController::handleEvent_(ViewEvent& event_in) {
	
	ShipPlacer& _placer = getModel().getShipPlacer();
	GameModel& model = getModel();
	checkFirstPlayer(model.getFirstPlayerType());
	checkSecondPlayer(model.getSecondPlayerType());
	 
	Field& curr_arr_field = _placer.getArrangementLayer();
	Field& curr_field = model.getCurrentField();
	Battleship* curr_ship = _placer.getCurrentBattleShip();

	static bool place_check = true;
	auto event_type = event_in._type;

	switch (event_type)
	{
	case EventType::Nothing:
		return;
	case EventType::RandomPressed:
		_placer.setRandomly(curr_field);
		return;
	case EventType::OrientationChanged:
		_placer.changeOrientation();
		break;
	case EventType::PlayerChanged:
		curr_arr_field.refresh();
		model.changePlayer();
		_placer.refreshShips();
		break;
	case EventType::RightArrowPressed:
		curr_ship->moveRight(curr_arr_field);
		break;
	case EventType::LeftArrowPressed:
		curr_ship->moveLeft(curr_arr_field);
		break;
	case EventType::DownArrowPressed:
		curr_ship->moveDown(curr_arr_field);
		break;
	case EventType::UpArrowPressed:
		curr_ship->moveUp(curr_arr_field);
		break;
	case EventType::BackPressed:
		model.setStage(gameStage::Menu);
		break;
	case EventType::ShipPlaced:
		if (!place_check) return;
		_placer.place(curr_field);
		_placer.changeCurrentShip();
		_placer.checkShipAvailability();
		break;
	case EventType::ShipTypeChanged:
		curr_arr_field.refresh();
		_placer.changeCurrentShipType();
		_placer.checkShipAvailability();
		break;
	case EventType::StartGamePressed:
		model.changePlayer();
		model.setStage(gameStage::GameStage);
		checkIfHardBot();
		model.prepareToGameStage();
	}
	// потом надо переделать 
	place_check = (_placer.isCorrectPlaced(curr_field,curr_ship)) ? true : false;
	_placer.setPlaceCorrectness(place_check);
}

bool GameController::isAnyShipAlive(BattleManager::Ships& ships)
{
	for (auto ship : ships) {
		if (ship->getState() != ShipState::Destroyed) {
			return true;
		}
	}
	return false;
}

GameController::GameController(GameModel & model_in) : Controller(model_in){}

void GameController::handleEvent_(ViewEvent& event_in){
	auto event_type = event_in._type;
	GameModel& model = getModel();
	Field& curr_field = model.getSecondField();
	BattleManager& manager = model.getBattleManager();
	Statistics& statistics = model.getStatistics();
	int x ,y;

	switch (event_type)
	{
	case EventType::Nothing:
		return;
	case EventType::Fire:
		x = event_in.cellPressed._x;
		y = event_in.cellPressed._y;
		statistics.playerShot(model.getCurrentPlayerNum());
		if (manager.checkCoords(x, y, curr_field)) {
			statistics.successfulShot(model.getCurrentPlayerNum());
			break;
		}
	case EventType::PlayerChanged:
		model.changePlayer();
		manager.changePlayer();
		break;
	}
	if (!manager.isAnyShipAlive()) {
		model.setStage(gameStage::Finish);
	}
}

FinishController::FinishController(GameModel & model_in) : Controller(model_in) {}

void FinishController::handleEvent_(ViewEvent & event_in) 
{
	auto event_type = event_in._type;
	GameModel& model = getModel();
	Field& curr_field = model.getCurrentField();
	BattleManager& manager = model.getBattleManager();

	switch (event_type){
	case EventType::Nothing:
		return;
	case EventType::StatisticsPressed:
		model.setStage(gameStage::Stats);
		break;
	case EventType::BackPressed:
		model.refresh();
		model.setStage(gameStage::Menu);
		break;
	case EventType::ExitPressed:
		model.setClosed(true);
		break;
	}
}

StatsController::StatsController(GameModel & model_in) : Controller(model_in){}

void StatsController::handleEvent_(ViewEvent& event_in){
	auto event_type = event_in._type;
	GameModel& model = getModel();

	switch (event_type) {
	case EventType::Nothing:
		return;
	case EventType::BackPressed:
		model.refresh();
		model.setStage(gameStage::Menu);
		break;
	}
}

HelpController::HelpController(GameModel & model_in) : Controller(model_in) {}

void HelpController::handleEvent_(ViewEvent & event_in)
{
	auto event_type = event_in._type;
	GameModel& model = getModel();

	switch (event_type) {
	case EventType::Nothing:
		return;
	case EventType::BackPressed:
		model.refresh();
		model.setStage(gameStage::Menu);
		break;
	}
}
