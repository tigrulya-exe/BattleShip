#pragma once
#include "WindowDrawerCreator.h"
#include <SFML/Audio.hpp>

extern const int GAMELOGO_DELAY;

namespace {
	const char* GAMELOGO_PATH = "Textures/Backgrounds/gamelogo.jpg";
	const char* WINDOW_TITLE = "Battleship";
	const int FRAMERATE_LIMIT = 120;
	const int WINDOW_WIDTH = 1000;
	const int WINDOW_LENGTH = 800;
	namespace musicPath {
		const char* MENU = "Music/menu.ogg";
	}
}

class GameView
{
public:
	virtual void render() = 0;
};

class SfmlView : public GameView {
	GameModel& _model;
	//sf::Music _main_theme;
	sf::RenderWindow _curr_sf_window;
	WindowDrawer* _curr_window_drawer;
	gameStage _curr_stage;	
	bool isBotAction();

	void checkStage(gameStage);
	void renderChanges();
	//void setMusic();
public:
	SfmlView(GameModel&);
	void render() override;
	sf::RenderWindow& getWindow();
	ViewEvent& getViewEvent(sf::Event&);
	void renderGameLogo();

	~SfmlView();
};