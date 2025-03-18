#pragma once
#include "State.hpp"
#include "AssetLoader.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <future>

class GameState : public State {
public:
    GameState() : loadingDone(false) {}

    virtual ~GameState() = default;

    void onEnter() override {
        std::cout << "Entering GameState" << std::endl;
        loadingFuture = AssetLoader::loadAssetsAsync("../assets/assets.json", "game");
    }

    void onExit() override {
        std::cout << "Exiting GameState" << std::endl;
    }

    void update(sf::Time dt) override {
        if (!loadingDone && loadingFuture.valid() && loadingFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            loadingDone = loadingFuture.get();
        }
    }

    void render(sf::RenderWindow& window) override {
        if (!loadingDone) {
            sf::Font font;
            font.loadFromFile("../assets/fonts/arial.ttf");
            sf::Text loadingText("Loading...", font, 30);
            loadingText.setFillColor(sf::Color::White);
			loadingText.setOrigin(loadingText.getLocalBounds().width / 2, loadingText.getLocalBounds().height / 2);
            loadingText.setPosition(1280 / 2, 720 / 2);
            window.draw(loadingText);
        }
        else {
            auto& textureManager = ResourceManager<sf::Texture>::GetInstance();
            sf::Sprite playerSprite;
            playerSprite.setTexture(textureManager.Get("background6"));
            window.draw(playerSprite);
        }
    }

private:
    std::future<bool> loadingFuture;
    bool loadingDone;
};