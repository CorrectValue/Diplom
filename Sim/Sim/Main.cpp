#include <SFML/Graphics.hpp>

#include <conio.h>
#include "world.h"
#include "UI.h"

using namespace sf;



int main()
{
	//UI::drawStartWindow();
	//UI::drawLoadWindow();
	//UI::drawSaveWindow();

	View view(FloatRect(200, 200, 300, 200));
	RenderWindow window(sf::VideoMode(1024, 768), "GETTING STARTED");
	view.reset(sf::FloatRect(0, 0, 640, 480));
	Clock clock;
	//String levelString[height][width];
	//
	////наполнить левел хламом
	//for (int i = 0; i < height; i++)
	//{
	//	for (int j = 0; j < width; j++)
	//	{	
	//		levelString[i][j] = ' ';
	//	}
	//}
	//for (int i = 0; i < width; i++)
	//{
	//	levelString[0][i] = '-';
	//	levelString[height - 1][i] = '-';
	//}
	//for (int i = 0; i < height; i++)
	//{
	//	levelString[i][0] = 'i';
	//	levelString[i][width - 1] = 'i';
	//}


	//String path1 = "Images/tileset2.png";

	world level;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000; //было 800, не понравится - вернём

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
		sf::Vector2i localPosition = Mouse::getPosition(); //пихаем сюда координаты курсора

		
		if (localPosition.x < 3 && view.getCenter().x >= 150)
		{
			view.move(-0.2 * time, 0);
		}
		if (localPosition.x > window.getSize().x - 3 && view.getCenter().x <= 876)
		{
			view.move(0.2 * time, 0);
		}
		if (localPosition.y < 3 && view.getCenter().y >= 150)
		{
			view.move(0, -0.2 * time);
		}
		if (localPosition.y > window.getSize().y - 3 && view.getCenter().y <= 618)
		{
			view.move(0, 0.2 * time);
		}

		window.setView(view);
		window.clear();
		level.timeManipulation(time);
		level.draw(window);
		level.envManipulation(window);
		level.displayInfo();
		window.display();
	}

	return 0;
}