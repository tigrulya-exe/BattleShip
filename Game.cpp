#include "Game.h"
#include "Window.h"
#include <iostream>

Game::Game() : _controller_factory(ControllerFactory::getAccess()), _view(_model){}

void Game::execute(){
	_view.renderGameLogo();

	sf::Event _event;
	_event.type = sf::Event::Count;
	
	while (_view.getWindow().isOpen()) {
		while (_view.getWindow().pollEvent(_event)) {
			if (_event.type == sf::Event::Closed) {
				_model.setClosed(true);
			}
		_controller_factory.getController(_model)->handleEvent_(_view.getViewEvent(_event));
		}
		_view.render();
	}
}