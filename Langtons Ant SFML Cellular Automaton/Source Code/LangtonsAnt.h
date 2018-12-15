///////////////////////////////////////////////////
/*
	@Author: Mihael Petrièeviæ
	Date: 15.12.2018. (1:58h)
*/
///////////////////////////////////////////////////

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class LangtonsAnt
{
public:
	LangtonsAnt(sf::Vector2u l_winSize);
	~LangtonsAnt() = default;

	void update();
	void draw(sf::RenderWindow* l_window);

	void setNumberOfAnts(int l_numberOfAnts);
	void setCellSize(int l_cellSize);

private:
	enum Direction
	{
		UP, DOWN, RIGHT, LEFT
	};

	struct Ants
	{
		sf::Vector2i ant;
		Direction antDir;

		void moveForward()
		{
			if (antDir == LEFT)			ant.x--;
			else if (antDir == RIGHT)	ant.x++;
			else if (antDir == UP)		ant.y--;
			else if (antDir == DOWN)	ant.y++;
		}
	};

	std::vector<Ants> vecAnts;
	int m_numberOfAnts;

	int m_QuadSize;

	int m_QuadColumns;
	int m_QuadRows;
	
	enum State
	{
		On,
		Of
	};

	struct Cell
	{
		Cell() : quad(sf::PrimitiveType::Quads, 4), CellState(Of) {}
		
		sf::VertexArray quad;
		State CellState;

		void changeColour(sf::Color l_colour)
		{
			for (int i = 0; i < 4; i++)
			{
				quad[i].color = l_colour;
			}
		}
	};

	std::vector<Cell> m_vecGrid;

	sf::Vector2u m_windowSize;

	void Setup();
	int COORDConvert(int x, int y);
};

