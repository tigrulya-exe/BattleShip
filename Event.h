#pragma once
#include <SFML/Graphics.hpp>
//
#include "GameView.h"

class Event_
{
	//tmp sol
	sf::Event _event;
	sf::Event& getEvent_();
public:
	Event_(sf::Event&);
	virtual void handleEvent_(SfmlView&) = 0;
};

class CloseEvent_ : public Event_{
public:
	CloseEvent_(sf::Event&);
	void handleEvent_(SfmlView&) override;
};