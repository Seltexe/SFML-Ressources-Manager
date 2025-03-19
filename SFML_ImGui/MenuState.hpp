#pragma once
#include "State.hpp"
#include "AssetLoader.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <future>
#include "Window.hpp"

class MenuState : public State {
public:
    MenuState() : loadingDone(false) {}

    virtual ~MenuState() = default;

    void onEnter() override {
        std::cout << "Entering MenuState" << std::endl;
        loadingFuture = AssetLoader::loadAssetsAsync("../assets/assets.json", "menu");
    }

    void onExit() override {
        std::cout << "Exiting GameState" << std::endl;
    }

    void update(sf::Time dt) override;

    void render() override {
        if (!loadingDone) {
            sf::Font font;
            font.loadFromFile("../assets/fonts/arial.ttf");
            sf::Text loadingText("Loading...", font, 30);
            loadingText.setFillColor(sf::Color::White);
            loadingText.setOrigin(loadingText.getLocalBounds().width / 2, loadingText.getLocalBounds().height / 2);
            loadingText.setPosition(Window::getSize().x / 2, Window::getSize().y / 2);
            Window::draw(loadingText);
        }
        else {
            
        }
    }

private:
    std::future<bool> loadingFuture;
    bool loadingDone;
};