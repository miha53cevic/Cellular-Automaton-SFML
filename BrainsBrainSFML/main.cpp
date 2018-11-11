#include "game.h"
#include <iostream>

int main()
{
	Game game(sf::Vector2u(1280, 720), "Brian's Brain SFML");
	game.getBrainsBrain()->ToggleGrid(false);
	game.getBrainsBrain()->setQuadSize(1);

	while (!game.getWindow() -> IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}