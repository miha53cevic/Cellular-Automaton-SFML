///////////////////////////////////////////////////
/*
	@Author: Mihael Petrièeviæ
*/
///////////////////////////////////////////////////

#pragma once
#include "window.h"
#include "LangtonsAnt.h"

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
	LangtonsAnt* getAnt();

	void RestartClock();

private:
	Window m_window;
	LangtonsAnt m_langtonsAnt;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};