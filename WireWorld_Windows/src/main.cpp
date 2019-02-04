#include <iostream>

#include "Engine/game.h"

int main()
{
	std::cout << "Controls: X = SHOW / HIDE MENU, Y = CHANGE SIMULATION SPEED\n\n";

    Game app({640, 480}, "WireWorld");
    
    while(!app.getWindow()->IsDone())
    {
        app.HandleInput();
        app.Update();
        app.Render();
        app.RestartClock();
    }

    return 0; 
}