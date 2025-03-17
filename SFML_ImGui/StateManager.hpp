#pragma once
#include "State.hpp"
#include <memory>
#include <future>
#include <iostream>

class StateManager {
public:
    StateManager() = default;
    ~StateManager() = default;

    // Changer d'état
    void changeState(std::unique_ptr<State> newState) 
    {
        if (currentState) 
        {
            currentState->onExit();
        }
        currentState = std::move(newState);

        std::cout << "Asynchronous loading of the state..." << std::endl;
        auto future = std::async(std::launch::async, [this]() {
            currentState->loadResources();
            });

        future.wait();

        currentState->onEnter();
    }

    void update(sf::Time dt) 
    {
        if (currentState)
            currentState->update(dt);
    }

    void render(sf::RenderWindow& window)
    {
        if (currentState)
            currentState->render(window);
    }

private:
    std::unique_ptr<State> currentState;
};