#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class BrainsBrain
{
public:
	BrainsBrain(sf::Vector2u l_windowSize);
	~BrainsBrain();

	void update(bool& l_Resized, sf::Vector2u l_newScreenSize);
	void draw(sf::RenderWindow& l_window);
	void setQuadSize(int l_size);

	void ToggleGrid(bool l_grid);

private:
	sf::Vector2u m_windowSize;

	enum State
	{
		Off = 0,
		On = 1,
		Dying = 2
	};

	int m_QuadSize;

	int m_ScreenQuadWidth;
	int m_ScreenQuadHeight;

	bool m_grid;

	struct Cell
	{
		Cell() : quad(sf::Quads, 4), cell_state(State::Off) {}
		sf::VertexArray quad;

		State cell_state;
	};

	std::vector<Cell> m_vecOutput;
	std::vector<Cell> m_vecState;
	
	void Setup();

	int getCellIndex(int x, int y);
	void setCellColor(sf::Color l_colour, int CellIndex);
	int getNeighbourState(int x, int y);
};

