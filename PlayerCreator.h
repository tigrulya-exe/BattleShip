#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "GameModel.h"


class IPlayerCreator {
public:
	virtual Player* createPlayer() = 0;
};

template <class T>
class PlayerCreator : public IPlayerCreator {
public:
	T* createPlayer() override { return new T{}; }
};

class PlayerFactory {
	std::map<enum playerType, std::shared_ptr<IPlayerCreator>> _players;
	void initPlayerRegister(enum playerType, std::shared_ptr<IPlayerCreator>);
	PlayerFactory() = default;
public:
	template <class T>
	void registerPlayer(enum playerType player_type) {
		auto player_creator = std::make_shared<PlayerCreator<T>>();
		PlayerFactory::getAccess().initPlayerRegister(player_type, player_creator);
	}
	Player* getPlayer(playerType);
	static PlayerFactory& getAccess();
};
