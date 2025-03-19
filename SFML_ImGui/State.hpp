#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class StateManager;

class State {
public:
    virtual ~State() = default;

#pragma region virtual
    /// <summary>
	/// Called when entering the state
    /// </summary>
    virtual void onEnter() = 0;

    /// <summary>
	/// Called when exiting the state
    /// </summary>
    virtual void onExit() = 0;

    /// <summary>
	/// Update the state
    /// </summary>
    /// <param name="dt"></param>
    virtual void update(sf::Time dt) = 0;

    /// <summary>
	/// Render the state
    /// </summary>
    /// <param name="window"></param>
    virtual void render() = 0;
#pragma endregion

	void setStateManager(StateManager* stateManager) {
		this->stateManager = stateManager;
	}

protected:
	StateManager* stateManager = nullptr;
};
