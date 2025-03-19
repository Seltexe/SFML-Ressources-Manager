#pragma once
#include "State.hpp"
#include "Window.hpp"
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
        {

            currentState->update(dt);
        }
    }

    void render() {
        if (currentState)
            currentState->render();
    }

private:
    std::unique_ptr<State> currentState;
};