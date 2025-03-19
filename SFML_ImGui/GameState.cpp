#include "pch.h"
#include "GameState.hpp"
#include "MenuState.hpp"


void GameState::update(sf::Time dt)
{
	// Do not touch this
    if (!loadingDone && loadingFuture.valid() && loadingFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        loadingDone = loadingFuture.get();
    }
    
	// Where the magic happens
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

void GameState::render()
{
    // Do not touch this
    if (!loadingDone) {
        sf::Font font;
        font.loadFromFile("../assets/fonts/arial.ttf");
        sf::Text loadingText("Loading...", font, 30);
        loadingText.setFillColor(sf::Color::White);
        loadingText.setOrigin(loadingText.getLocalBounds().width / 2, loadingText.getLocalBounds().height / 2);
        loadingText.setPosition(Window::getSize().x / 2, Window::getSize().y / 2);
        Window::draw(loadingText);
    }

	// Where the magic happens
    if (loadingDone) 
    {
        auto& textureManager = ResourceManager<sf::Texture>::GetInstance();
        sf::Sprite playerSprite;
        playerSprite.setTexture(textureManager.Get("background6"));
        Window::draw(playerSprite);
    }
}
