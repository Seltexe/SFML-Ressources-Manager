#include "pch.h"
#include "ButtonManager.hpp"

float ButtonManager::m_timerKeyboard = 0.f;
float ButtonManager::m_timerMouse = 0.f;
float ButtonManager::m_dt = 0.0f;

void ButtonManager::update(float _dt)
{
	m_dt = _dt;
	m_timerKeyboard += _dt;
	m_timerMouse += _dt;
}

bool ButtonManager::isKeyPressed(sf::Keyboard::Key _key, float _timer)
{
	if (m_timerKeyboard > _timer && sf::Keyboard::isKeyPressed(_key)) {
		m_timerKeyboard = 0.f;
		return true;
	}
	return false;
}

bool ButtonManager::isMouseButtonPressed(sf::Mouse::Button _button, float _timer)
{
	if (m_timerMouse > _timer && sf::Mouse::isButtonPressed(_button)) {
		m_timerMouse = 0.f;
		return true;
	}
	return false;
}

bool ButtonManager::isMouseAtPos(sf::Vector2f _pos, float _radius)
{
	if (tools::getSqrMagnitudeBetween2Vectors(getMousePos(), _pos) < _radius * _radius)
	{
		return true;
	}
	return false;
}

sf::Vector2f ButtonManager::getMousePos()
{
	return static_cast<sf::Vector2f>(sf::Mouse::getPosition());
}
