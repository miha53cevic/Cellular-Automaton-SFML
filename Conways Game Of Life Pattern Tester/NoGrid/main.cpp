#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

//Stvara strukturu Cell koja ima bool da li je ziva i stvara kvadrat
struct Cell
{
	bool alive;
	sf::RectangleShape shape;
};

//Transformira 2D kordinate u 1D pomocu (ScreenWidth * y) + x formule
bool TransformCOORD(int x, int y, const int w, std::vector<Cell>& output)
{
	return output[(w * y) + x].alive;
}

int main()
{
	srand(time(0));

	//Variables
	const int nPixelSize = 8;
	const int nScreenWidth = 1280;
	const int nScreenHeight = 720;

	bool bSimulationStart = false;

	//Number of squares that are nPixelSize * nPixelSize in X and Y axis
	const int w = nScreenWidth / nPixelSize;
	const int h = nScreenHeight / nPixelSize;

	//Render Screen
	sf::RenderWindow window(sf::VideoMode(nScreenWidth, nScreenHeight), "Conways Game Of Life SFML");
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);

	//Cell Array - Kao 2D Mapa - Koriste se dva jer inace dok bi zamjenil jednog cela bi drugi gledal tog novog a nece se gledati novo napravljeni cellovi pa zato sluzi output i state
	std::vector<Cell>output(w*h);
	std::vector<Cell>state(w*h);

	//Po defaultu svaki cell je mrtav
	for (auto &i : output)
	{
		i.alive = false;
		i.shape.setFillColor(sf::Color::White);
		i.shape.setSize(sf::Vector2f(nPixelSize, nPixelSize));
	}

	//Declare position of squares

	//Dumy variable nezz kak bi drukcije
	int n = 0, m = 0; //n = x, m = y

	for (int i = 0; i < w*h; i++)
	{
		//Ako je dovrsil x os onda moram povecati za y os i resetirati x os na 0
		if (i % w == 0 && i != 0)
		{
			n += nPixelSize;
			m = 0;
		}

		output[i].shape.setPosition(m, n);
		m += nPixelSize;
	}

	//Na pocetku je state = output
	for (int i = 0; i < w * h; i++)
		state[i] = output[i];

	//Startup
	//for (int i = 0; i < w * h; i++)
		//state[i].alive = rand() % 2;

	//Time and Clock
	sf::Time elapsed;
	sf::Time limit;
	sf::Clock clock;

	//GAME LOOP
	while (window.isOpen())
	{
		elapsed = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				if (!bSimulationStart)
				{
					bSimulationStart = true;
				}
				else bSimulationStart = false;
			}
		}

		//Pattern Editor
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//Ako se pozicija misa nalazi u kvadratu stavi da je ziv ili mrtav ovisno o kliku
			for (auto &i : state)
			{
				sf::IntRect rect(i.shape.getGlobalBounds());
				if (rect.contains(sf::Mouse::getPosition(window)))
				{
					i.alive = true;
				}
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			for (auto &i : state)
			{
				sf::IntRect rect(i.shape.getGlobalBounds());
				if (rect.contains(sf::Mouse::getPosition(window)))
				{
					i.alive = false;
				}
			}
		}

		//Stavi state u output
		for (int i = 0; i < w * h; i++)
			output[i] = state[i];


		//Simulation Logic
		if (bSimulationStart)
		{
			if (limit.asMilliseconds() > 100) //AKO HOCES SMANJITI BRZINU MICANJA ZA ODREDENI BROJ
			{
				limit -= limit;

				//Get number of nSusjeda i promjeni prema pravilima
				for (int x = 0; x < w; x++)
					for (int y = 0; y < h; y++)
					{
						//Broj susjeda celije
						int nSusjed = 0;

						//Ako se celija nalazi na lijevom rubu treba gledati kordinate s druge strane ekrana za lijeve susjede, w - 1
						if (x == 0 && y != 0 && y != h - 1)	//Kod svakog if-a se ne provjeravaju rubne celije jer one ne vrijede
						{
							nSusjed = TransformCOORD(w - 1, y - 1, w, output) + TransformCOORD(x + 0, y - 1, w, output) + TransformCOORD(x + 1, y - 1, w, output) +
								TransformCOORD(w - 1, y + 0, w, output) + 0 + TransformCOORD(x + 1, y + 0, w, output) +
								TransformCOORD(w - 1, y + 1, w, output) + TransformCOORD(x + 0, y + 1, w, output) + TransformCOORD(x + 1, y + 1, w, output);
						}
						//Ako se celija nalazi na desnom rubu treba gledati kordinate s druge strane ekrana za desne susjede, 0
						else if (x == w - 1 && y != 0 && y != h - 1) //Kod svakog if-a se ne provjeravaju rubne celije jer one ne vrijede
						{
							nSusjed = TransformCOORD(x - 1, y - 1, w, output) + TransformCOORD(x + 0, y - 1, w, output) + TransformCOORD(0 + 0, y - 1, w, output) +
								TransformCOORD(x - 1, y + 0, w, output) + 0 + TransformCOORD(0 + 0, y + 0, w, output) +
								TransformCOORD(x - 1, y + 1, w, output) + TransformCOORD(x + 0, y + 1, w, output) + TransformCOORD(0 + 0, y + 1, w, output);
						}
						//Ako se celija nalazi na gornjem rubu treba gledati kordinate s druge strane ekrana za gornje susjede, h - 1
						else if (y == 0 && x != 0 && x != w - 1) //Kod svakog if-a se ne provjeravaju rubne celije jer one ne vrijede
						{
							nSusjed = TransformCOORD(x - 1, h - 1, w, output) + TransformCOORD(x + 0, h - 1, w, output) + TransformCOORD(x + 1, h - 1, w, output) +
								TransformCOORD(x - 1, y + 0, w, output) + 0 + TransformCOORD(x + 1, y + 0, w, output) +
								TransformCOORD(x - 1, y + 1, w, output) + TransformCOORD(x + 0, y + 1, w, output) + TransformCOORD(x + 1, y + 1, w, output);
						}
						//Ako se celija nalazi na doljnjem rubu treba gledati kordinate s druge strane ekrana za doljne susjede, 0
						else if (y == h - 1 && x != 0 && x != w - 1) //Kod svakog if-a se ne provjeravaju rubne celije jer one ne vrijede
						{
							nSusjed = TransformCOORD(x - 1, y - 1, w, output) + TransformCOORD(x + 0, y - 1, w, output) + TransformCOORD(x + 1, y - 1, w, output) +
								TransformCOORD(x - 1, y + 0, w, output) + 0 + TransformCOORD(x + 1, y + 0, w, output) +
								TransformCOORD(x - 1, 0 + 0, w, output) + TransformCOORD(x + 0, 0 + 0, w, output) + TransformCOORD(x + 1, 0 + 0, w, output);
						}

						//Ako celija nije na rubu ekrana i ako nije na rubnim tockima provjeravaj normalno susjede
						else if (x != 0 && y != 0 && x != w - 1 && y != h - 1)
						{
							nSusjed = TransformCOORD(x - 1, y - 1, w, output) + TransformCOORD(x + 0, y - 1, w, output) + TransformCOORD(x + 1, y - 1, w, output) +
								TransformCOORD(x - 1, y + 0, w, output) + 0 + TransformCOORD(x + 1, y + 0, w, output) +
								TransformCOORD(x - 1, y + 1, w, output) + TransformCOORD(x + 0, y + 1, w, output) + TransformCOORD(x + 1, y + 1, w, output);
						}

						//Cell Logic
						if (TransformCOORD(x, y, w, output) == 1)
						{
							if (nSusjed != 2 && nSusjed != 3) { state[(w * y) + x].alive = 0; }
						}
						else if (nSusjed == 3) { state[(w * y) + x].alive = 1; }
					}
			}
			else limit += elapsed;
		}

		for (auto &i : state)
		{
			if (i.alive) i.shape.setFillColor(sf::Color::White);
			else i.shape.setFillColor(sf::Color::Black);
		}

		window.clear(sf::Color::Black);

		//Draw Squares / Cells
		for (auto &i : output)
		{
			window.draw(i.shape);
		}

		window.display();
	}

	return 0;
}