#include "pch.h"
#include "MenuState.hpp"
#include "GameState.hpp"

void MenuState::update(sf::Time dt)
{
	if (!loadingDone && loadingFuture.valid() && loadingFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
		loadingDone = loadingFuture.get();
	}
	
	if (loadingDone)
	{
		ImGui::Begin("Menu State");
		ImGui::End();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			std::cout << "Entering GameState..." << std::endl;
			if (stateManager) {
				stateManager->changeState(std::make_unique<GameState>());
			}
		}
	}
}
