#include <iostream>

#include "Engine/game.h"

int main()
{
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