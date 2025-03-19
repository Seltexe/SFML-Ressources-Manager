#include "pch.h"
#include "Window.hpp"

sf::RenderWindow Window::m_window;
sf::RenderTexture Window::m_renderTexture;
sf::RectangleShape Window::m_rectangleShape;
sf::Text Window::m_text;
sf::Event Window::m_event;
bool Window::m_fullScreen;
sf::Vector2f Window::m_ratio;
sf::Font Window::m_font;
sf::RectangleShape Window::m_rectangleGame;
sf::View Window::m_view;
std::atomic<float> Window::m_mouseWheelScrollDelta{ 0.f };
std::atomic<bool> Window::m_hasFocus{ true };

Window::Window()
{
	tools::initTools();
	sf::VideoMode tmpVidMode = sf::VideoMode::getDesktopMode();
	sf::Uint32 style = sf::Style::Default;
	m_window.create(tmpVidMode, "SFML", style);
	m_renderTexture.create(tmpVidMode.width, tmpVidMode.height);
	m_rectangleShape.setSize(sf::Vector2f((float)tmpVidMode.width, (float)tmpVidMode.height));
	m_rectangleShape.setPosition(sf::Vector2f(0.f, 0.f));
	m_rectangleShape.setFillColor(sf::Color::White);
	m_fullScreen = (style == sf::Style::Fullscreen);
	m_ratio = sf::Vector2f(1920.f / (float)tmpVidMode.width, 1080.f / (float)tmpVidMode.height);
	m_font.loadFromFile("..\\assets\\fonts\\Arial.ttf");
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(50);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(5.f);
	m_text.setFont(m_font);
	m_window.setMouseCursorVisible(false);
	m_window.setFramerateLimit(60);
#pragma region imgui
	ImGui::SFML::Init(m_window);
	//you can use whatever imgui theme you like!
	//ImGui::StyleColorsDark();				
	//imguiThemes::yellow();
	//imguiThemes::gray();
	//imguiThemes::green();
	//imguiThemes::red();
	//imguiThemes::gray();
	imguiThemes::embraceTheDarkness();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.FontGlobalScale = 1.f;
#pragma endregion
	m_view.setCenter(sf::Vector2f(960.0f, 540.f));
	m_view.setRotation(0.0f);
	m_view.setSize(sf::Vector2f(1920.f, 1080.f));
	m_view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	m_enableScale = true;
}

void Window::update(float const& _dt)
{
	m_view.setSize(sf::Vector2f(1920.f / getRatioVec2().x, 1080.f / getRatioVec2().y));

#pragma region IMGUI
	ImGui::SFML::Update(m_window, sf::seconds(_dt));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
	ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGui::PopStyleColor(2);
#pragma endregion

	if (ButtonManager::isKeyPressed(sf::Keyboard::Key::F11) && hasFocus()) {
		m_fullScreen = !m_fullScreen;
		setFullscreen(m_fullScreen);
	}

	m_mouseWheelScrollDelta = 0.f;
	while (m_window.pollEvent(m_event))
	{
		if ((m_event.mouseWheelScroll.delta >= 0.999999f && m_event.mouseWheelScroll.delta <= 1.000001f) || (m_event.mouseWheelScroll.delta <= -0.999999f && m_event.mouseWheelScroll.delta >= -1.000001f))
			m_mouseWheelScrollDelta.store(m_event.mouseWheelScroll.delta);

		ImGui::SFML::ProcessEvent(m_event);
		if (m_event.type == sf::Event::Closed
			|| sf::Mouse::isButtonPressed(sf::Mouse::XButton1) && hasFocus()
			)
			m_window.close();
	}

	m_hasFocus.store(m_window.hasFocus());
}

void Window::display()
{
	float ratio = getRatio();

	m_renderTexture.display();
	m_textureTransition = m_renderTexture.getTexture();
	m_window.setView(m_window.getDefaultView());
	m_rectangleShape.setTexture(&m_textureTransition);
	m_rectangleShape.setScale(ratio, ratio);

	m_window.draw(m_rectangleShape);

	ImGui::SFML::Render(m_window);
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBg] = ImColor(45, 45, 48);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(255, 110, 0);
	style.Colors[ImGuiCol_Border] = ImColor(95, 0, 0);

	style.Colors[ImGuiCol_Button] = ImColor(255, 110, 0);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(100, 100, 100);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(150, 150, 150);
	style.Colors[ImGuiCol_Tab] = ImColor(255, 110, 0);

	style.Colors[ImGuiCol_TabActive] = ImColor(100, 100, 100);
	style.Colors[ImGuiCol_TabHovered] = ImColor(100, 100, 100);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(255, 110, 0);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 110, 0);



	ImGui::GetIO().FontGlobalScale = (ratio);
	m_window.display();
}

void Window::clear()
{
	m_renderTexture.clear(sf::Color::Black);
	m_window.clear(sf::Color::Black);
}


void Window::drawRecMiniMap(sf::Vector2f const& _pos, sf::Vector2f const& _size, sf::RenderStates const& _renderStates)
{
	m_rectangleGame.setFillColor(sf::Color::Black);
	m_rectangleGame.setPosition(_pos);
	m_rectangleGame.setOrigin(sf::Vector2f(0.0f, 0.0f));
	m_rectangleGame.setSize(_size);
	m_rectangleGame.setRotation(0.f);
	m_rectangleGame.setTexture(nullptr);
	m_renderTexture.draw(m_rectangleGame, _renderStates);
}

void Window::draw(sf::Drawable const& _toDraw, sf::RenderStates const& _renderStates)
{
	m_renderTexture.draw(_toDraw, _renderStates);
}

void Window::draw(sf::Vector2f const& _pos, sf::Vector2f const& _origin, sf::Vector2f const& _size,
	sf::Color const& _color, float const& _angle, sf::Texture const* _texture)
{
	m_rectangleGame.setFillColor(_color);
	m_rectangleGame.setPosition(_pos);
	m_rectangleGame.setOrigin(_origin);
	m_rectangleGame.setSize(_size);
	m_rectangleGame.setRotation(_angle);
	m_rectangleGame.setTexture(_texture);
	m_renderTexture.draw(m_rectangleGame);
}

void Window::drawRessourceTexture(sf::Texture const* _texture)
{
	m_rectangleGame.setFillColor(sf::Color::White);
	m_rectangleGame.setPosition(sf::Vector2f());
	m_rectangleGame.setOrigin(sf::Vector2f());
	m_rectangleGame.setSize(sf::Vector2f(1920.f, 1080.f));
	m_rectangleGame.setRotation(0.0f);
	m_rectangleGame.setTexture(_texture);
	m_rectangleGame.setScale(sf::Vector2f(1.f, 1.f));
	m_rectangleGame.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	m_renderTexture.draw(m_rectangleGame);
}

void Window::draw(sf::Vector2f const& _pos, sf::Vector2f const& _origin, sf::Vector2f const& _size, sf::IntRect const& _rect, sf::Color const& _color, float const& _angle, sf::Texture* const& _texture, sf::Vector2f const& _scale)
{
	m_rectangleGame.setFillColor(_color);
	m_rectangleGame.setPosition(_pos);
	m_rectangleGame.setOrigin(_origin);
	m_rectangleGame.setSize(_size);
	m_rectangleGame.setRotation(_angle);
	m_rectangleGame.setTexture(_texture);
	m_rectangleGame.setTextureRect(_rect);
	m_rectangleGame.setScale(_scale);
	m_renderTexture.draw(m_rectangleGame);
	m_rectangleGame.setScale(sf::Vector2f(1.f, 1.f));

}


void Window::draw(sf::Vector2f const& _pos, sf::Vector2f const& _size, sf::RenderStates& _renderState)
{
	m_rectangleGame.setFillColor(sf::Color::White);
	m_rectangleGame.setPosition(_pos);
	m_rectangleGame.setOrigin(sf::Vector2f(0.f, 0.f));
	m_rectangleGame.setSize(_size);
	m_rectangleGame.setRotation(0.f);
	m_renderTexture.draw(m_rectangleGame, _renderState);
}

void Window::draw(sf::RenderStates& _renderState, sf::Vector2f const& _pos, sf::Vector2f const& _size, sf::Texture* _texture)
{
	m_rectangleGame.setFillColor(sf::Color::White);
	m_rectangleGame.setPosition(_pos);
	m_rectangleGame.setSize(_size);
	m_rectangleGame.setOrigin(_size / 2.f);
	m_rectangleGame.setTexture(_texture);
	m_renderTexture.draw(m_rectangleGame, _renderState);
}

void Window::draw(sf::Vector2f const& _pos, sf::Vector2f const& _pos2, sf::Color const& _color, sf::Texture const* _texture)
{
	m_rectangleGame.setFillColor(_color);
	m_rectangleGame.setPosition(_pos2);
	sf::Vector2f _size{ tools::getMagnitudeBetween2Vectors(_pos, _pos2),6.f };
	float angle = std::atan2(_pos.y - _pos2.y, _pos.x - _pos2.x) * RAD2DEG;

	m_rectangleGame.setOrigin(sf::Vector2f(0.f, _size.y / 2.f));
	m_rectangleGame.setSize(_size);
	m_rectangleGame.setRotation(angle);
	m_rectangleGame.setTexture(_texture);
	m_renderTexture.draw(m_rectangleGame);
}

void Window::draw(sf::Texture const* _texture, sf::IntRect const& _rect, sf::Vector2f const& _pos/*, sf::Vector2f const& _origin*/, sf::Vector2f const& _scale, float _rotation)
{
	m_rectangleGame.setTexture(_texture);
	m_rectangleGame.setTextureRect(_rect);
	m_rectangleGame.setPosition(_pos);
	sf::Vector2f size(_rect.getSize());
	m_rectangleGame.setSize(size);
	m_rectangleGame.setOrigin(size * 0.5f);
	m_rectangleGame.setScale(_scale);
	m_rectangleGame.setRotation(_rotation);
	m_rectangleGame.setFillColor(sf::Color::Color::Color::Color::Color::White);
	m_renderTexture.draw(m_rectangleGame);

	m_rectangleGame.setScale(sf::Vector2f(1.f, 1.f));
	m_rectangleGame.setRotation(0.f);
}

void Window::drawText(std::string const& _text, sf::Vector2f const& _pos, int const& _charactereSize, sf::Color const& _color, sf::Color const& _outLineColor, float _outLineThickness, bool isCenter)
{
	m_text.setString(_text);
	m_text.setPosition(_pos);
	m_text.setCharacterSize(_charactereSize);
	m_text.setFillColor(_color);
	m_text.setOutlineColor(_outLineColor);
	m_text.setOutlineThickness(_outLineThickness);
	if (isCenter)
	{
		centerText();
	}
	else
	{
		m_text.setOrigin(sf::Vector2f(0.0f, 0.0f));
	}

	m_renderTexture.draw(m_text);
}

sf::FloatRect Window::getdrawTextBounds()
{
	auto bounds = m_text.getGlobalBounds();
	/*bounds.width *= m_ratio.x;
	bounds.height *= m_ratio.y;*/
	/*bounds.left *= m_ratio.x;
	bounds.top *= m_ratio.y;*/
	return bounds;
}


void Window::draw(std::string _textContent, sf::Vector2f _pos, bool _centered, sf::Color _color)
{
	m_text.setString(_textContent);
	m_text.setPosition(_pos);
	if (_centered)
		centerText();
	else
		m_text.setOrigin(sf::Vector2f(0.f, 0.f));
	m_text.setFillColor(_color);
	m_renderTexture.draw(m_text);
}

void Window::setTextParameter(std::string _textContent, sf::Vector2f _pos, bool _centered, sf::Color _color)
{
	m_text.setString(_textContent);
	m_text.setPosition(_pos);
	if (_centered)
		centerText();
	m_text.setFillColor(_color);
}

bool Window::isOpen()
{
	return m_window.isOpen();
}

bool Window::isHoveringText(sf::Vector2i _pos)
{
	if (m_text.getGlobalBounds().contains((sf::Vector2f)_pos))
		return true;
	return false;
}

bool Window::isHoveringText()
{
	if (m_text.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition()))
		return true;
	return false;
}

sf::Vector2i Window::getSize()
{
	return static_cast<sf::Vector2i>(m_window.getSize());
}

void Window::setMousePosAtCenter()
{
	sf::Mouse::setPosition(sf::Vector2i(m_window.getSize().x / 2, m_window.getSize().y / 2), m_window);
}

sf::Vector2i Window::getMousePosWindowRelative()
{
	return sf::Mouse::getPosition(m_window);
}

float Window::getRatio()
{
	if (m_enableScale)
	{
		auto vec2 = sf::Vector2f(m_window.getSize().x / 1920.f, m_window.getSize().y / 1080.f);
		if (vec2.x < vec2.y)
			return vec2.x;
		return vec2.y;
	}
	return 1.f;

}

sf::Vector2f Window::getRatioVec2()
{
	if (m_enableScale)
		return sf::Vector2f(m_window.getSize().x / 1920.f, m_window.getSize().y / 1080.f);
	return sf::Vector2f(1.f, 1.f);
}

bool Window::hasFocus()
{
	return m_hasFocus.load();
}

void Window::setMouseCursorVisible(bool _value)
{
	m_window.setMouseCursorVisible(_value);
}

void Window::setFullscreen(bool _isFullscreen)
{
	if (_isFullscreen)
	{
		m_window.create(sf::VideoMode(1920, 1080), "SFML", sf::Style::Fullscreen);
	}
	else
	{
		m_window.create(sf::VideoMode(1920, 1080), "SFML", sf::Style::Default);
	}
}

void Window::setVarFullscreen(bool _isFullscreen)
{
	m_fullScreen = _isFullscreen;
}

void Window::setLimitFPS(int _value)
{
	m_window.setFramerateLimit(_value);
}

void Window::setVsync(bool _isVsync)
{
	m_window.setVerticalSyncEnabled(_isVsync);
}

void Window::setRenderTextView(sf::View)
{
	//m_renderTexture.setView(ViewManager::getView());
}

void Window::setView(sf::Vector2f const& _centerPos, sf::Vector2f const& _size, sf::FloatRect const& _viewPort, float const& _angle)
{
	m_view.setCenter(_centerPos);
	m_view.setRotation(_angle);
	m_view.setSize(_size);
	m_view.setViewport(_viewPort);

	m_renderTexture.setView(m_view);
}

void Window::setView(bool _defaultView)
{
	m_renderTexture.setView(_defaultView ? m_renderTexture.getDefaultView() : m_view);
}

void Window::centerText()
{
	sf::FloatRect bounds = m_text.getGlobalBounds();
	m_text.setOrigin(sf::Vector2f(bounds.width / 2.f, bounds.height / 2.f));
}