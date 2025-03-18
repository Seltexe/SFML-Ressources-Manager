#pragma once
#include "State.hpp"
#include <future>
#include <iostream>

class StateManager {
public:
    void changeState(std::unique_ptr<State> newState) {
        if (currentState) {
            currentState->onExit();
        }
        currentState = std::move(newState);
        currentState->setStateManager(this);
        currentState->onEnter();
    }

    void update(sf::Time dt) {
        if (currentState)
            currentState->update(dt);
    }

    void render(sf::RenderWindow& window) {
        if (currentState)
            currentState->render(window);
    }

private:
    std::unique_ptr<State> currentState;
};