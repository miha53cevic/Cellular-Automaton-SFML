#pragma once
#include "window.h"
#include "BrainsBrain.h"

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
	BrainsBrain* getBrainsBrain();

	void RestartClock();

private:
	Window m_window;

	BrainsBrain m_BrainsBrain;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};