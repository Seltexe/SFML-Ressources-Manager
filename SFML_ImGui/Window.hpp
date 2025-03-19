#pragma once
#include "tools.hpp"
#include "../thirdparty/imgui/imgui.h"
#include "../thirdparty/imgui/imgui-SFML.h"
#include "../thirdparty/imgui/imguiThemes.h"

class Window
{
public:
	Window();
	static void update(float const& _dt);
	static void display();
	static void clear();
	static void drawRecMiniMap(sf::Vector2f const& _pos, sf::Vector2f const& _size, sf::RenderStates const& _renderStates = sf::RenderStates::Default);
	static void draw(sf::Drawable const& _toDraw, sf::RenderStates const& _renderStates = sf::RenderStates::Default);
	static void draw(sf::Vector2f const& _pos, sf::Vector2f const& _origin, sf::Vector2f const& _size,
		sf::Color const& _color = sf::Color::White, float const& _angle = 0.f, sf::Texture const* _texture = nullptr);

	static void drawRessourceTexture(sf::Texture const* _texture);

	static void draw(sf::Vector2f const& _pos, sf::Vector2f const& _origin, sf::Vector2f const& _size, sf::IntRect const& _rect, sf::Color const& _color, float const& _angle, sf::Texture* const& _texture, sf::Vector2f const& _scale = sf::Vector2f(5.375f, 5.375f));

	static void draw(sf::Vector2f const& _pos, sf::Vector2f const& _size,
		sf::RenderStates& _renderState);
	static void draw(sf::RenderStates& _renderState, sf::Vector2f const& _pos, sf::Vector2f const& _size, sf::Texture* _texture = nullptr);

	static void draw(std::string _textContent, sf::Vector2f _pos, bool _centered = true, sf::Color _color = sf::Color::White);
	void draw(sf::Vector2f const& _pos, sf::Vector2f const& _pos2, sf::Color const& _color, sf::Texture const* _texture);
	static void draw(sf::Texture const* _texture, sf::IntRect const& _rect, sf::Vector2f const& _pos/*, sf::Vector2f const& _origin*/, sf::Vector2f const& _scale = sf::Vector2f(1.f, 1.f), float _rotation = 0.f);
	static void drawText(std::string const& _text, sf::Vector2f const& _pos, int const& _charactereSize, sf::Color const& _color, sf::Color const& _outLineColor = sf::Color::White, float _outLineThickness = 0.0f, bool isCenter = false);
	static inline sf::FloatRect getTextRect() { return m_text.getGlobalBounds(); }

	static sf::Texture getTextureRenderTexture() { return m_textureTransition; }

	static sf::FloatRect getdrawTextBounds();
	static void setTextParameter(std::string _textContent, sf::Vector2f _pos, bool _centered = true, sf::Color _color = sf::Color::White);
	static bool isOpen();
	static bool isHoveringText(sf::Vector2i _pos);
	static bool isHoveringText();
	static sf::Vector2i getSize();
	static void setMousePosAtCenter();
	static sf::Vector2i getMousePosWindowRelative();
	static float getRatio();
	static sf::Vector2f getRatioVec2();
	static bool hasFocus();
	inline static sf::RenderWindow* getWindow() { return &m_window; }
	static void setMouseCursorVisible(bool _value);
	static void setFullscreen(bool _isFullscreen);
	static void setVarFullscreen(bool _isFullscreen);
	static bool getFullScreen() { return m_fullScreen; }
	static void setLimitFPS(int _value);
	static void setVsync(bool _isVsync);
	static void setRenderTextView(sf::View);
	static inline sf::View& getView() { return m_view; }
	static inline float& getViewSize() { return m_viewSize; }
	static void setView(sf::Vector2f const& _centerPos, sf::Vector2f const& _size, sf::FloatRect const& _viewPort, float const& _angle);
	static void setView(bool _defaultView = false);
	static const sf::Texture* getRectangleTexture() { return m_rectangleGame.getTexture(); }
	static inline float getMouseWheelScrollDelta() { return m_mouseWheelScrollDelta.load(); }
	static inline void initIMGUI() { ImGui::SFML::Init(m_window); }
	static inline void setScaleEnable(bool _able) { m_enableScale = _able; }
private:
	static void centerText();
	static sf::RectangleShape m_rectangleGame;
	static sf::RenderWindow m_window;
	static sf::RenderTexture m_renderTexture;
	static sf::RectangleShape m_rectangleShape;
	static sf::Text m_text;
	static inline sf::Texture m_textureTransition{};
	static sf::Event m_event;
	static bool m_fullScreen;
	static sf::Vector2f m_ratio;
	static sf::Font m_font;
	static sf::View m_view;
	static std::atomic<float> m_mouseWheelScrollDelta;
	static std::atomic<bool> m_hasFocus;
	static inline float m_viewSize{ 1.f };
	static inline bool m_enableScale = false;
};


