#pragma once
#include "Player.h"
#include <cmath>
#include <map>
#include "ShipPlacer.h"
#include "BattleManager.h"
#include "Statistics.h"
//#include "Game.h"

class GameModel {
	using Ships = std::vector < ShipPlacer::Ships>;

	ShipPlacer _placer;
	BattleManager _manager;
	Statistics _stats;

	PlayerNum _current_player_num;

	Player* _first_player;
	Player* _second_player;
	Player* _current_player;

	Ships& _first_battleships;
	Ships& _second_battleships;
	Ships* _current_battleships;

	gameStage _current_stage;

	bool _isWindowClosed;
	bool _is_arrangement_finished;
	bool _is_game_finished;

	std::map<PlayerNum,Field*> _field_map;
	void initFieldMap();
	void refreshPlayers();

public:
	GameModel();
	
	PlayerNum getCurrentPlayerNum();

	playerType getCurrentPlayerType();
	playerType getFirstPlayerType();
	playerType getSecondPlayerType();

	void setFirstPlayer(playerType);
	void setSecondPlayer(playerType);
	void changePlayer();

	gameStage getCurrentStage();
	bool getClosed();
	void setClosed(bool);
	void setStage(gameStage);

	ShipPlacer& getShipPlacer();
	BattleManager& getBattleManager();

	Field& getCurrentField();
	Field& getSecondField();
	bool isArrangementFinished();

	void prepareToGameStage();
	void refresh();

	Player* getCurrentPlayer();
	Player* getFirstPlayer();
	Player* getSecondPlayer();

	Statistics& getStatistics();

	~GameModel();
};
