#pragma once
#include "State.hpp"
#include "StateManager.hpp"
#include "AssetLoader.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <future>

#include "../thirdparty/imgui/imgui.h"

class GameState : public State {
public:
    GameState() : loadingDone(false) {}

    virtual ~GameState() = default;

    /// <summary>
	/// Start loading assets in the background
    /// </summary>
    void onEnter() override {
        std::cout << "Entering GameState" << std::endl;
        loadingFuture = AssetLoader::loadAssetsAsync("../assets/assets.json", "game");
    }

    void onExit() override 
    {
        std::cout << "Exiting GameState" << std::endl;
    }


    void update(sf::Time dt) override;

    void render() override;

private:
    std::future<bool> loadingFuture;
    bool loadingDone;
};