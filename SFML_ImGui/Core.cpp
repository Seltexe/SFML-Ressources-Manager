#include "pch.h"
#include "Core.hpp"
#include "ButtonManager.hpp"

Core::Core()
{
	m_stateManager.changeState(std::make_unique<MenuState>());
}

void Core::update()
{
	restartClock();
	float dt = getDeltaTime();
	Window::update(dt);
	ButtonManager::update(dt);

	m_stateManager.update(m_time);
}

void Core::display()
{
	m_stateManager.render();
	m_window.display();
}

void Core::loop()
{
	while (m_window.isOpen()) {
		update();
		m_window.clear();
		display();
	}
	ImGui::SFML::Shutdown();
}

void Core::restartClock()
{
	m_time = m_clock.restart();
}

float Core::getDeltaTime()
{
	float dt = m_time.asSeconds();
	if (dt > 0.1f)
		return 0.1f;
	return dt;
}