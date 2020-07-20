#include "PlayerCreator.h"

namespace {
	bool setPlayerRegister() {
		PlayerFactory& factory = PlayerFactory::getAccess();
		factory.registerPlayer<HumanPlayer>(playerType::Human);
		factory.registerPlayer<EasyBot>(playerType::easyBot);
		factory.registerPlayer<HardBot>(playerType::hardBot);
		return true;
	}

	bool tmp = setPlayerRegister();
};

void PlayerFactory::initPlayerRegister(playerType type_in, std::shared_ptr<IPlayerCreator> Player_creator) {
	_players[type_in] = Player_creator;
}

Player* PlayerFactory::getPlayer(playerType type_in)
{
	return _players[type_in]->createPlayer();
}

PlayerFactory & PlayerFactory::getAccess()
{
	static PlayerFactory factory;
	return factory;
}