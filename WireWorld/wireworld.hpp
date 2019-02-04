#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Engine/toggleKey.hpp"

enum class SimulationState
{
	Pause,
	Running
};

class WireWorld
{
public:
    WireWorld(sf::Vector2u winSize);
    ~WireWorld() = default;

    void HandleInput(sf::RenderWindow& window);
    void Update();
    void Render(sf::RenderWindow* window, SimulationState simState);

private:
    enum class STATE
    {
        EMPTY,
        ELECTRON_HEAD,
        ELECTRON_TAIL,
        CONDUCTOR
    };

    struct Cell
    {
        Cell()
        : quad(sf::Quads, 4)
        , state(STATE::EMPTY)
        {}

        void Colour(sf::Color c)
        {
            for (int i = 0; i < 4; i++)
            {
                quad[i].color = c;
            }
        }

        sf::VertexArray quad;
        STATE state;
    };

    int m_nBlockSize;
    std::vector<Cell> m_vecOutput;
    std::vector<Cell> m_vecState;

    sf::Vector2i m_QuadCount;
    sf::Vector2u m_screenSize;

	// Pause Screen Drawing Grid
	sf::RenderTexture m_grid;

	// Type Menu Buttons
	sf::Sprite m_TypeMenu[3];
	sf::Texture m_TexMenu;
	bool m_bDrawMenu;

	ToggleKey m_toggleKey;

    // For selecting Cell types in input
    STATE m_type;

    void Setup();
    int ElectronHeadNeighbour(int x, int y);
};