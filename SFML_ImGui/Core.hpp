#pragma once
#include "tools.hpp"
#include "Window.hpp"
#include "StateManager.hpp"
#include "MenuState.hpp"

class Core
{
public:
	Core();
	void loop();
private:
	void restartClock();
	float getDeltaTime();
	void update();
	void display();
	sf::Time m_time;
	sf::Clock m_clock;
	Window m_window;
	StateManager m_stateManager;
};

