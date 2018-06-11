#include <SFML/Graphics.hpp>

#include <conio.h>
#include "world.h"
#include "human.h"
#include "UI.h"
#include "Animal.h"

using namespace sf;



int main()
{
	UI::drawStartWindow();
	//UI::drawLoadWindow();
	//UI::drawSaveWindow();

	View view(FloatRect(200, 200, 300, 200));
	RenderWindow window(sf::VideoMode(1024, 768), "GETTING STARTED");
	view.reset(sf::FloatRect(0, 0, 640, 480));
	Clock clock;
	//мир теперь создаётся не абы какой, а параметризированный!
	//из стартового окна вынимается сезон, время и погода
	world level(UI::season, UI::weather, UI::hours, UI::minutes, UI::count);
	//задать вектора существ
	vector<animal> animals;
	vector<human> people;
	animal::prepareValidCellsList(level);
	animal::prepareAvailibleGoals();
	human::prepareAvailibleGoals();
	human::prepareValidCellsList(level);
	human::prepareAppearances();
	human::prepareNames();
	human::prepareAvailibleActions();
	human::prepareHouses(level);

	int animalsCount = UI::count / 4;
	int peopleCount = UI::count;
	
	//набить этот вектор ровно необходимым количеством людей
	animals.resize(animalsCount);
	people.resize(peopleCount);
	

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800; //было 800, не понравится - вернём

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
		//обработать
		for (int i = 0; i < animalsCount; i++)
		{
			animals[i].update(time, level); //левел передаётся теперь по ссылке, всё быстро и норм
			window.draw(animals[i].sprite);
		}
		//for (int i = 0; i < peopleCount; i++)
		//{
		//	window.draw(people[i].sprite);
		//}
		level.weatherManipulation();
		level.envManipulation(window);
		level.displayInfo();
		UI::drawMainWindow(window, animals, people, level);
		window.display();
	}

	return 0;
}