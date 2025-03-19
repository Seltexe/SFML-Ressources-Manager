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

    void render() override;

private:
    std::future<bool> loadingFuture;
    bool loadingDone;
};