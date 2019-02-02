#pragma once
#include "window.h"

#include "../wireworld.hpp"
#include "toggleKey.hpp"

class Game
{
public:
	Game();
	Game(const sf::Vector2u& l_size, const std::string& l_name);
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* getWindow();

	void RestartClock();

private:
	Window m_window;

	WireWorld m_wireworld;

	bool m_bRun;
	sf::Color m_clearColour;

	ToggleKey m_toggleKey;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};