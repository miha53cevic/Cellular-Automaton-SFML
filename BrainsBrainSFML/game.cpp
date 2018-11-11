#include "game.h"

Game::Game()
	:	m_BrainsBrain(m_window.getSize())
{
	//Load Default settings && Textures
}
Game::Game(const sf::Vector2u& l_size, const std::string& l_name)
	:	m_window(l_size, l_name)
	,	m_BrainsBrain(m_window.getSize())
{

}
Game::~Game() {}

Window* Game::getWindow()
{
	return &m_window;
}

BrainsBrain* Game::getBrainsBrain()
{
	return &m_BrainsBrain;
}

void Game::HandleInput()
{
	//input
}

void Game::Update()
{
	//Event System
	m_window.Update();

	//TickRate
	float fFrameTime = 1.0f / 24.0f;

	if (m_elapsed.asSeconds() >= fFrameTime)
	{
		m_BrainsBrain.update(*m_window.isResized(), m_window.getSize());

		m_elapsed -= sf::seconds(fFrameTime);
	}
	
}

void Game::Render()
{
	//Draw something
	m_window.BeginDraw(sf::Color::White);
	
	m_BrainsBrain.draw(*m_window.getWindow());

	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed += m_clock.restart();
}