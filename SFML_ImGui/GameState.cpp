#include "pch.h"
#include "GameState.hpp"
#include "MenuState.hpp"


void GameState::update(sf::Time dt)
{
    if (!loadingDone && loadingFuture.valid() && loadingFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        loadingDone = loadingFuture.get();
    }
    
    if (loadingDone)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            std::cout << "Retour au menu..." << std::endl;
            if (stateManager) {
                stateManager->changeState(std::make_unique<MenuState>());
            }
        }

        ImGui::Begin("Game State");
        ImGui::End();
    }
}
