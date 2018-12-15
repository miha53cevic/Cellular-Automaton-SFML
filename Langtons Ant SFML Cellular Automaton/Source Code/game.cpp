///////////////////////////////////////////////////
/*
	@Author: Mihael Petrièeviæ
*/
///////////////////////////////////////////////////

#include "game.h"

Game::Game()
	: m_langtonsAnt(m_window.getSize())
{
	//Load Default settings && Textures
}
Game::Game(const sf::Vector2u& l_size, const std::string& l_name) : m_window(l_size, l_name), m_langtonsAnt(m_window.getSize()) {}
Game::~Game() {}

Window* Game::getWindow()
{
	return &m_window;
}

LangtonsAnt* Game::getAnt()
{
	return &m_langtonsAnt;
}

void Game::HandleInput()
{
	//input
}

void Game::Update()
{
	//Event System
	m_window.Update();
	
	m_langtonsAnt.update();
}

void Game::Render()
{
	//Draw something
	m_window.BeginDraw(sf::Color::White);
	
	m_langtonsAnt.draw(m_window.getWindow());

	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}