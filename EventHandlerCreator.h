#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Event.h"


//TODO
//RENAME: это интерфейс для EventHandlerCreator
class IEventCreator {
public:
	virtual Event_* createEvent(sf::Event&) = 0;
};

template <class T>
class EventCreator : public IEventCreator {
public:
	T* createEvent(sf::Event& event_in) override { return new T(event_in); }
};

class EventFactory {
	std::map<sf::Event::EventType, std::shared_ptr<IEventCreator>> _events;
	void initEventRegister(sf::Event::EventType, std::shared_ptr<IEventCreator>);
	EventFactory() = default;
public:
	template <class T>
	void registerEvent(sf::Event::EventType event_type) {
		auto event_creator = std::make_shared<EventCreator<T>>();
		EventFactory::getAccess().initEventRegister(event_type, event_creator);
	}
	Event_* getEvent_(sf::Event&);
	static EventFactory& getAccess();
};