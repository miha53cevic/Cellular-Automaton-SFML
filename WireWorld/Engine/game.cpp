#include "game.h"

#include <iostream>

Game::Game(const sf::Vector2u& l_size, const std::string& l_name)
	: m_window(l_size, l_name)
	, m_wireworld(m_window.getSize())
	, m_toggleKey(sf::Keyboard::Space)
	, m_speedToggleKey(sf::Keyboard::Y)
{
	m_SimulationState = SimulationState::Pause;
	m_updatesPerSecond = 4.0f;
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

	// Switch SimulationStates
	if (m_toggleKey.isKeyPressed())
	{
		if (m_SimulationState == SimulationState::Running)
		{
			m_SimulationState = SimulationState::Pause;
		}
		else
		{
			m_SimulationState = SimulationState::Running;
		}
	}

	// Change Tick Speed
	if (m_speedToggleKey.isKeyPressed())
	{
		std::cout << "Please enter how many updates per minute you would like: ";
		std::cin >> m_updatesPerSecond;

		// Check so that the value won't crash the program
		if (m_updatesPerSecond > 60.0f) m_updatesPerSecond = 60.0f;	// V-Sync is enabled in Window Class
		if (m_updatesPerSecond < 1.0f)  m_updatesPerSecond = 1.0f;	// No point in going any slower

		std::cout << "\n\n";
	}
}

void Game::Update()
{
	//Event System
	m_window.Update();

	if (m_SimulationState == SimulationState::Running)
	{
		float Tick = 1.0f / m_updatesPerSecond;

		if (m_elapsed.asSeconds() > Tick)
		{
			// Reset Elapsed & run simulation
			m_elapsed -= m_elapsed;

			m_wireworld.Update();
		}
	}
}

void Game::Render()
{
	//Draw something
	m_window.BeginDraw(sf::Color::Black);
	
	m_wireworld.Render(m_window.getWindow(), m_SimulationState);

	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed += m_clock.restart();
}