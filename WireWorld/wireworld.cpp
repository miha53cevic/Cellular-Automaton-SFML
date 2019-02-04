#include "wireworld.hpp"

WireWorld::WireWorld(sf::Vector2u winSize)
	: m_nBlockSize(8)
	, m_type(STATE::CONDUCTOR)
	, m_toggleKey(sf::Keyboard::X)
{
    m_screenSize = winSize;
    Setup();
}

void WireWorld::HandleInput(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	// Show Type Menu or Hide it with X
	if (m_toggleKey.isKeyPressed())
	{
		if (!m_bDrawMenu)
		{
			m_bDrawMenu = true;
		}
		else m_bDrawMenu = false;
	}

    // Change Cell Type with Type Menu
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_bDrawMenu)
	{
		sf::FloatRect MenuButtonC = m_TypeMenu[0].getGlobalBounds();
		sf::FloatRect MenuButtonE = m_TypeMenu[1].getGlobalBounds();
		sf::FloatRect MenuButtonX = m_TypeMenu[2].getGlobalBounds();

		if (MenuButtonC.contains(mousePos.x, mousePos.y))
		{
			m_type = STATE::CONDUCTOR;
		}
		else if (MenuButtonE.contains(mousePos.x, mousePos.y))
		{
			m_type = STATE::ELECTRON_HEAD;
		}
		else if (MenuButtonX.contains(mousePos.x, mousePos.y))
		{
			m_type = STATE::EMPTY;
		}
	}

	// Place Cells with Right Mouse Click
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        int x = mousePos.x / m_nBlockSize;
        int y = mousePos.y / m_nBlockSize;

        m_vecOutput[(y * m_QuadCount.x) + x].state = m_type;

        m_vecState = m_vecOutput;
    }
}

void WireWorld::Update()
{
    // Get Neighbours
    for (int y = 0; y < m_QuadCount.y; y++)
		for (int x = 0; x < m_QuadCount.x; x++)
		{
            // AKo je Celija CONDUCTOR treba gledati susjede
			if (m_vecOutput[(y * m_QuadCount.x) + x].state == STATE::CONDUCTOR)
            {
                int Neighbours = 0;

			    //Normalno - nije blizu ruba ekrana celija
			    if (x != 0 && x != m_QuadCount.x - 1 && y != 0 && y != m_QuadCount.y - 1)
			    {
				    Neighbours =	ElectronHeadNeighbour(x - 1, y - 1) + ElectronHeadNeighbour(x + 0, y - 1) + ElectronHeadNeighbour(x + 1, y - 1) +
					    			ElectronHeadNeighbour(x - 1, y + 0) +				0				      + ElectronHeadNeighbour(x + 1, y + 0) +
						    		ElectronHeadNeighbour(x - 1, y + 1) + ElectronHeadNeighbour(x + 0, y + 1) + ElectronHeadNeighbour(x + 1, y + 1);
			    }
			
			    // Ako ima 1 ili 2 susjeda CONDUCTOR pretvori ga u ELECTRON HEAD inace je dalje CONDUCTOR
                if (Neighbours == 1 || Neighbours == 2)
                {
                    m_vecState[(y * m_QuadCount.x) + x].state = STATE::ELECTRON_HEAD;
                }
            }

            // Electron Head -> Electron Tail
            else if (m_vecOutput[(y * m_QuadCount.x) + x].state == STATE::ELECTRON_HEAD)
            {
                m_vecState[(y * m_QuadCount.x) + x].state = STATE::ELECTRON_TAIL;
            }

            // Electron Tail -> Conductor
            else if (m_vecOutput[(y * m_QuadCount.x) + x].state == STATE::ELECTRON_TAIL)
            {
                m_vecState[(y * m_QuadCount.x) + x].state = STATE::CONDUCTOR;
            }
		}

        // Output becomes STATE
        m_vecOutput = m_vecState;
}

void WireWorld::Render(sf::RenderWindow* window, SimulationState simState)
{
	// If simulation is paused draw grid for easier drawing
	if (simState == SimulationState::Pause)
	{
		sf::Sprite grid(m_grid.getTexture());

		window->draw(grid);
	}

	// Draw Menu
	if (m_bDrawMenu)
	{
		for (int i = 0; i < 3; i++)
		{
			window->draw(m_TypeMenu[i]);
		}
	}

    for (auto &i : m_vecOutput)
    {
        if (i.state == STATE::EMPTY)
        {
            // No point in drawing empty
        }
        else if (i.state == STATE::ELECTRON_HEAD)
        {
            i.Colour(sf::Color::Blue);
            window->draw(i.quad);
        }
        else if (i.state == STATE::ELECTRON_TAIL)
        {
            i.Colour(sf::Color::Red);
            window->draw(i.quad);
        }
        else if (i.state == STATE::CONDUCTOR)
        {
            i.Colour(sf::Color::Yellow);
            window->draw(i.quad);
        }
    }
}

// Private Methods
void WireWorld::Setup()
{
	// Create Grid
	m_grid.create(m_screenSize.x, m_screenSize.y);
	m_grid.clear(sf::Color::Black);

	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(125, 125, 125));
	rect.setSize(sf::Vector2f(m_nBlockSize - 1, m_nBlockSize - 1));

    // Get Number of Quads in X and Y direction
    m_QuadCount.x = m_screenSize.x / m_nBlockSize;
    m_QuadCount.y = m_screenSize.y / m_nBlockSize;

    for (int y = 0; y < m_QuadCount.y; y++)
    {
        for (int x = 0; x < m_QuadCount.x; x++)
        {
            int realX = x * m_nBlockSize;
            int realY = y * m_nBlockSize;

            Cell temp;
            temp.quad[0].position = sf::Vector2f(realX, realY);
            temp.quad[1].position = sf::Vector2f(realX + m_nBlockSize, realY);
            temp.quad[2].position = sf::Vector2f(realX + m_nBlockSize, realY + m_nBlockSize);
            temp.quad[3].position = sf::Vector2f(realX, realY + m_nBlockSize);

            // Set Default Colour to Black
            temp.Colour(sf::Color::Black);

            m_vecOutput.push_back(temp);



			// Fill in grid
			rect.setPosition(sf::Vector2f(realX, realY));
			m_grid.draw(rect);
			m_grid.display();
        }
    }

    // Both output and state are the same
    m_vecState = m_vecOutput;

	// Load Menu Buttons
	if (!m_TexMenu.loadFromFile("MenuButtons.png")) { /* Error */ }

	m_TypeMenu[0].setTexture(m_TexMenu);
	m_TypeMenu[1].setTexture(m_TexMenu);
	m_TypeMenu[2].setTexture(m_TexMenu);

	m_TypeMenu[0].setTextureRect({ 0, 0, 64, 64 });
	m_TypeMenu[1].setTextureRect({ 64, 0, 64, 64 });
	m_TypeMenu[2].setTextureRect({ 128, 0, 64, 64 });

	m_TypeMenu[0].setPosition(0, 0);
	m_TypeMenu[1].setPosition(64, 0);
	m_TypeMenu[2].setPosition(128, 0);

	m_bDrawMenu = true;
}

int WireWorld::ElectronHeadNeighbour(int x, int y)
{
    if (m_vecOutput[(y * m_QuadCount.x) + x].state == STATE::ELECTRON_HEAD)
    {
        return true;
    }

    return false;
}