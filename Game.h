#pragma once
#include <SFML/Graphics.hpp>
#include "ControllerCreator.h"
#include "Player.h"
#include "EventHandlerCreator.h"
#include "GameView.h"
#include "GameModel.h"

class Game {
	ControllerFactory& _controller_factory;
	SfmlView _view;
	GameModel _model;
public:
	Game();
	void execute();
};

