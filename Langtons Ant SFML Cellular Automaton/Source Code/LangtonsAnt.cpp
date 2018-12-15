///////////////////////////////////////////////////
/*
	@Author: Mihael Petrièeviæ
	Date: 15.12.2018. (1:58h)
*/
///////////////////////////////////////////////////

#include "LangtonsAnt.h"

LangtonsAnt::LangtonsAnt(sf::Vector2u l_winSize)
	: m_QuadSize(8)
	, m_numberOfAnts(1)
{
	m_windowSize = l_winSize;

	Setup();
}

void LangtonsAnt::update()
{
	for (int i = 0; i < m_numberOfAnts; i++)
	{
		m_vecGrid[COORDConvert(vecAnts[i].ant.x, vecAnts[i].ant.y)].changeColour(sf::Color::Black);

		if (m_vecGrid[COORDConvert(vecAnts[i].ant.x, vecAnts[i].ant.y)].CellState == Of)
		{
			m_vecGrid[COORDConvert(vecAnts[i].ant.x, vecAnts[i].ant.y)].CellState = On;

			if (vecAnts[i].antDir == LEFT)			vecAnts[i].antDir = UP;
			else if (vecAnts[i].antDir == RIGHT)	vecAnts[i].antDir = DOWN;
			else if (vecAnts[i].antDir == UP)		vecAnts[i].antDir = RIGHT;
			else if (vecAnts[i].antDir == DOWN)		vecAnts[i].antDir = LEFT;

			vecAnts[i].moveForward();
		}
		else if (m_vecGrid[COORDConvert(vecAnts[i].ant.x, vecAnts[i].ant.y)].CellState == On)
		{
			m_vecGrid[COORDConvert(vecAnts[i].ant.x, vecAnts[i].ant.y)].CellState = Of;

			if (vecAnts[i].antDir == LEFT)			vecAnts[i].antDir = DOWN;
			else if (vecAnts[i].antDir == RIGHT)	vecAnts[i].antDir = UP;
			else if (vecAnts[i].antDir == UP)		vecAnts[i].antDir = LEFT;
			else if (vecAnts[i].antDir == DOWN)		vecAnts[i].antDir = RIGHT;

			vecAnts[i].moveForward();
		}

		//	Provjera je li mrav izvan ekrana i prebacuje ga na drugu stranu
		if (vecAnts[i].ant.x >= m_QuadRows)		vecAnts[i].ant.x = 0;
		if (vecAnts[i].ant.x < 0)				vecAnts[i].ant.x = m_QuadRows - 1;
		if (vecAnts[i].ant.y >= m_QuadColumns)	vecAnts[i].ant.y = 0;
		if (vecAnts[i].ant.y < 0)				vecAnts[i].ant.y = m_QuadColumns - 1;

		m_vecGrid[COORDConvert(vecAnts[i].ant.x, vecAnts[i].ant.y)].changeColour(sf::Color::Red);
	}
}

void LangtonsAnt::draw(sf::RenderWindow* l_window)
{
	for (auto i : m_vecGrid)
	{
		//	Crtam samo one celije koje su On ili crne a pozadina je bijela tako da bi program brze radio
		if (i.CellState == On || i.quad[0].color == sf::Color::Red)
			l_window->draw(i.quad);
	}
}

void LangtonsAnt::Setup()
{
	m_QuadRows		= (int)m_windowSize.x / m_QuadSize;
	m_QuadColumns	= (int)m_windowSize.y / m_QuadSize;

	//	Clear Vector in case of calling setup later
	m_vecGrid.clear();
	vecAnts.clear();

	for (int y = 0; y < m_QuadColumns; y++)
	{
		for (int x = 0; x < m_QuadRows; x++)
		{
			int pixelX = x * m_QuadSize;
			int pixelY = y * m_QuadSize;

			Cell cell;
			cell.quad[0].position = sf::Vector2f(pixelX,					pixelY);
			cell.quad[1].position = sf::Vector2f(pixelX + m_QuadSize,		pixelY);
			cell.quad[2].position = sf::Vector2f(pixelX + m_QuadSize,		pixelY + m_QuadSize);
			cell.quad[3].position = sf::Vector2f(pixelX,					pixelY + m_QuadSize);

			cell.changeColour(sf::Color::Black);

			m_vecGrid.push_back(cell);
		}
	}

	for (int i = 0; i < m_numberOfAnts; i++)
	{
		Ants ant;

		if (i == 0)
		{
			ant.ant.x = m_QuadRows / 2;
			ant.ant.y = m_QuadColumns / 2;

			ant.antDir = LEFT;
		}
		else
		{
			ant.ant.x = rand() % m_QuadRows;
			ant.ant.y = rand() % m_QuadColumns;

			ant.antDir = Direction(rand() % 4);
		}

		vecAnts.push_back(ant);
	}
}

int LangtonsAnt::COORDConvert(int x, int y)
{
	return (y * m_QuadRows) + x;
}

void LangtonsAnt::setNumberOfAnts(int l_numberOfAnts)
{
	m_numberOfAnts = l_numberOfAnts;
	Setup();
}

void LangtonsAnt::setCellSize(int l_cellSize)
{
	m_QuadSize = l_cellSize;
	Setup();
}