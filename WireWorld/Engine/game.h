#pragma once
#include "window.h"

#include "../wireworld.hpp"
#include "toggleKey.hpp"

class Game
{
public:
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

	ToggleKey m_toggleKey;
	ToggleKey m_speedToggleKey;

	float m_updatesPerSecond;

	sf::Clock m_clock;
	sf::Time m_elapsed;

	SimulationState m_SimulationState;
};