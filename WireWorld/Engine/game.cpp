#include "game.h"

Game::Game()
	: m_wireworld(m_window.getSize())
	, m_toggleKey(sf::Keyboard::Space)
{
	//Load Default settings && Textures
}
Game::Game(const sf::Vector2u& l_size, const std::string& l_name) : m_window(l_size, l_name), m_wireworld(m_window.getSize()), m_toggleKey(sf::Keyboard::Space)
{
	m_bRun = true;
}
Game::~Game() {}

Window* Game::getWindow()
{
	return &m_window;
}

void Game::HandleInput()
{
	//input
	m_wireworld.HandleInput(*m_window.getWindow());
}

void Game::Update()
{
	//Event System
	m_window.Update();

	// Switch States
	if (m_toggleKey.isKeyPressed())
	{
		if (m_bRun) m_bRun = false;
		else m_bRun = true;
	}

	// If running place colour background to black and update else state is PAUSE and colour background is gray
	if (m_bRun)
	{
		float Tick = 1.0f / 4.0f;

		if (m_elapsed.asSeconds() > Tick)
		{
			// Reset Elapsed
			m_elapsed -= m_elapsed;

			m_clearColour = sf::Color::Black;
			m_wireworld.Update();
		}
	}
	else m_clearColour = sf::Color(125, 125, 125);
}

void Game::Render()
{
	//Draw something
	m_window.BeginDraw(m_clearColour);
	
	m_wireworld.Render(m_window.getWindow());

	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed += m_clock.restart();
}