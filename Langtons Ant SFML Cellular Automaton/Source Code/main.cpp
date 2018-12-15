///////////////////////////////////////////////////
/*
	@Author: Mihael Petrièeviæ
	Date: 15.12.2018. (1:58h)
*/
///////////////////////////////////////////////////

#include "game.h"

int main()
{
	int cellSize;
	int AntNum;

	printf_s("Odaberi velicinu celije: ");
	scanf_s("%d", &cellSize);
	printf_s("Odaberi broj mrava: ");
	scanf_s("%d", &AntNum);

	if (cellSize < 1 || AntNum < 1)
	{
		cellSize = 1;
		AntNum = 1;
	}

	Game game(sf::Vector2u(1280, 720), "Langton's Ant Cellular Automaton SFML");

	game.getAnt()->setCellSize(cellSize);
	game.getAnt()->setNumberOfAnts(AntNum);

	while (!game.getWindow() -> IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}