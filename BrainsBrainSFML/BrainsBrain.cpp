#include "BrainsBrain.h"

BrainsBrain::BrainsBrain(sf::Vector2u l_windowSize) : m_QuadSize(16), m_grid(false)
{
	m_windowSize = l_windowSize;

	//Stvara celije od vertex tocki
	Setup();
}
BrainsBrain::~BrainsBrain() {}

void BrainsBrain::update(bool& l_Resized, sf::Vector2u l_newScreenSize)
{
	if (l_Resized)
	{
		m_windowSize = l_newScreenSize;
		Setup();
		l_Resized = false;
	}

	//TODO Izvan ekrana susjedi s druge strane
	for (int y = 0; y < m_ScreenQuadHeight; y++)
		for (int x = 0; x < m_ScreenQuadWidth; x++)
		{
			int Neighbours = 0;

			//Lijeva strana ekrana
			if (x == 0 && y != 0 && y != m_ScreenQuadHeight - 1)	//Ne provjeravaju se rubne celije jer ne vrijede
			{
				Neighbours =	getNeighbourState(m_ScreenQuadWidth - 1, y - 1) + getNeighbourState(x + 0, y - 1) + getNeighbourState(x + 1, y - 1) +
								getNeighbourState(m_ScreenQuadWidth - 1, y + 0) +				0				  + getNeighbourState(x + 1, y + 0) +
								getNeighbourState(m_ScreenQuadWidth - 1, y + 1) + getNeighbourState(x + 0, y + 1) + getNeighbourState(x + 1, y + 1);
			}
			//Desna strana ekrana
			else if (x == m_ScreenQuadWidth - 1 && y != 0 && y != m_ScreenQuadHeight - 1)
			{
				Neighbours =	getNeighbourState(x - 1, y - 1) + getNeighbourState(x + 0, y - 1) + getNeighbourState(0, y - 1) +
								getNeighbourState(x - 1, y + 0) + 			0					  + getNeighbourState(0, y + 0) +
								getNeighbourState(x - 1, y + 1) + getNeighbourState(x + 0, y + 1) + getNeighbourState(0, y + 1);
			}
			//Gornja strana ekrana
			else if (y == 0 && x != 0 && x != m_ScreenQuadWidth - 1)
			{
				Neighbours =	getNeighbourState(x - 1, m_ScreenQuadHeight - 1) + getNeighbourState(x + 0, m_ScreenQuadHeight - 1) + getNeighbourState(x + 1, m_ScreenQuadHeight - 1) +
								getNeighbourState(x - 1, y + 0) +				0				  + getNeighbourState(x + 1, y + 0) +
								getNeighbourState(x - 1, y + 1) + getNeighbourState(x + 0, y + 1) + getNeighbourState(x + 1, y + 1);
			}
			//Donja strana ekrana
			else if (y == m_ScreenQuadHeight - 1 && x != 0 && x != m_ScreenQuadWidth - 1)
			{
				Neighbours =	getNeighbourState(x - 1, y - 1) + getNeighbourState(x + 0, y - 1) + getNeighbourState(x + 1, y - 1) +
								getNeighbourState(x - 1, y + 0) +				0				  + getNeighbourState(x + 1, y + 0) +
								getNeighbourState(x - 1, 0) + getNeighbourState(x + 0, 0) + getNeighbourState(x + 1, 0);
			}
			//Normalno - nije blizu ruba ekrana celija
			else if (x != 0 && x != m_ScreenQuadWidth - 1 && y != 0 && y != m_ScreenQuadHeight - 1)
			{
				Neighbours =	getNeighbourState(x - 1, y - 1) + getNeighbourState(x + 0, y - 1) + getNeighbourState(x + 1, y - 1) +
								getNeighbourState(x - 1, y + 0) +				0				  + getNeighbourState(x + 1, y + 0) +
								getNeighbourState(x - 1, y + 1) + getNeighbourState(x + 0, y + 1) + getNeighbourState(x + 1, y + 1);
			}
			
			if (Neighbours == 2 && m_vecOutput[getCellIndex(x, y)].cell_state == State::Off)
				m_vecState[getCellIndex(x, y)].cell_state = State::On;
			else if (m_vecOutput[getCellIndex(x, y)].cell_state == State::On)
				m_vecState[getCellIndex(x, y)].cell_state = State::Dying;
			else if (m_vecOutput[getCellIndex(x, y)].cell_state == State::Dying)
				m_vecState[getCellIndex(x, y)].cell_state = State::Off;
		}

	//S obzirom u cijem je stanju celija stavi njezinu boju
	for (auto &i : m_vecState)
	{
		//Nema state off jer ako je off ga ne crtamo
		switch (i.cell_state)
		{
		case State::Dying:
			for (int j = 0; j < 4; j++)
				i.quad[j].color = sf::Color::Blue;
			break;
		case State::On:
			for (int j = 0; j < 4; j++)
				i.quad[j].color = sf::Color::Color(125, 125, 125);
			break;
		}
	}

	m_vecOutput = m_vecState;
}

void BrainsBrain::draw(sf::RenderWindow& l_window)
{
	for (auto &i : m_vecOutput)
		//Ako celija nije Off ili Mrtva prikaži ju na ekranu
		if (i.cell_state != State::Off)
			l_window.draw(i.quad);
}

void BrainsBrain::Setup()
{	
	//Broj celija koje stanu u širinu i visinu ekrana
	m_ScreenQuadWidth = m_windowSize.x / m_QuadSize;
	m_ScreenQuadHeight = m_windowSize.y / m_QuadSize;

	m_vecOutput.clear();
	m_vecState.clear();

	/*
		- Stvori kvadrate koji prezentiraju celije tako da podijeli velicinu celije sa velicinom prozora
		  te zna tada koliko ce biti celija u tom smjeru,
		- ukupan broj celija je umnozak tih dvaju brojeva u ovom slucaju ScreenQuadHeight * ScreenQuadWidth
	*/
	for (int y = 0; y < m_ScreenQuadHeight; y++)
		for (int x = 0; x < m_ScreenQuadWidth; x++)
		{
			float pixelX = x * m_QuadSize;
			float pixelY = y * m_QuadSize;

			int QuadWidth = m_QuadSize;

			if (m_grid)
				QuadWidth = m_QuadSize - 1;

			Cell cell;
			cell.quad[0].position = sf::Vector2f(pixelX,				pixelY);
			cell.quad[1].position = sf::Vector2f(pixelX + QuadWidth,	pixelY);
			cell.quad[2].position = sf::Vector2f(pixelX + QuadWidth,	pixelY + QuadWidth);
			cell.quad[3].position = sf::Vector2f(pixelX,				pixelY + QuadWidth);

			//Daj random vrijednosti celijama
			cell.cell_state = State(rand() % 3);

			m_vecOutput.push_back(cell);
		}

	//Stavlja da su na pocetku isti
	m_vecState = m_vecOutput;
}

int BrainsBrain::getCellIndex(int x, int y)
{
	//Nabavi index celije u 1D vec polju preko 2D kordinata
	return (y * m_ScreenQuadWidth) + x;
}

void BrainsBrain::setCellColor(sf::Color l_colour, int CellIndex)
{
	//Promjeni boju svakog vertexa kod celije
	for (int i = 0; i < 4; i++)
		m_vecOutput[CellIndex].quad[i].color = l_colour;
}

int BrainsBrain::getNeighbourState(int x, int y)
{
	if (m_vecOutput[(y * m_ScreenQuadWidth) + x].cell_state == State::On) return 1;
	else return 0;
}

void BrainsBrain::setQuadSize(int l_size) { m_QuadSize = l_size; Setup(); }
void BrainsBrain::ToggleGrid(bool l_grid) { m_grid = l_grid; Setup(); }
