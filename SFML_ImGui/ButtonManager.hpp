#pragma once
#include "tools.hpp"


class ButtonManager
{
public:
	static void update(float _dt);
	static bool isKeyPressed(sf::Keyboard::Key _key, float _timer = 0.2f);
	static bool isMouseButtonPressed(sf::Mouse::Button _button, float _timer = 0.2f);
	static bool isMouseAtPos(sf::Vector2f _pos, float _radius);
	inline static float getDt() { return m_dt; }
	static sf::Vector2f getMousePos();
private:
	static float m_timerKeyboard;
	static float m_dt;
	static float m_timerMouse;
};