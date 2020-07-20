#pragma once
#include <SFML/Graphics.hpp>
#include "EventHandlerCreator.h"
#include "GameModel.h"
#include "GameView.h"
#include "Player.h"
#include "PlayerCreator.h"
#include <vector>
#include <map>

namespace {
	const int SHIFT_LEFT = -1;
	const int SHIFT_RIGHT = 1;
}

class Controller
{
	GameModel& _model;
	Player* _first_player;
	Player* _second_player;
	Player* _current_player;
	// construct players;
	void init_players();
protected:
	void checkFirstPlayer(playerType);
	void checkSecondPlayer(playerType);
public:
	Controller(GameModel&);
	virtual void handleEvent_(ViewEvent&) = 0;
	GameModel& getModel();
	virtual ~Controller() {};
};

class MenuController : public Controller {
public:
	MenuController(GameModel&);
	void handleEvent_(ViewEvent&) override;
};

class OptionsController : public Controller {
	// vector contains order of players in options
	std::vector<playerType> _player_types;
	playerType setCurrentFirstPlayer(int);
	playerType setCurrentSecondPlayer(int);
	void setPlayerTypes();
public:
	OptionsController(GameModel&);
	void handleEvent_(ViewEvent&) override;
};

class ArrangementController : public Controller {
	void setHardBotCoords(Player*, Field&);
	void checkIfHardBot();
public:
	ArrangementController(GameModel&);
	void handleEvent_(ViewEvent&) override;
};

class GameController : public Controller {
	bool isAnyShipAlive(BattleManager::Ships&);
public:
	GameController(GameModel&);
	void handleEvent_(ViewEvent&) override;
};

class FinishController : public Controller {
public:
	FinishController(GameModel&);
	void handleEvent_(ViewEvent&) override;
};

class StatsController : public Controller {
public:
	StatsController(GameModel&);
	void handleEvent_(ViewEvent&) override;
};

class HelpController : public Controller {
public:
	HelpController(GameModel&);
	void handleEvent_(ViewEvent&) override;
};