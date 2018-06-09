#include "Animal.h"

using namespace sf;
using namespace std;

int animal::globalID = 0;
vector<goal> animal::availibleGoals;


animal::animal()
{
	//получить id
	id = globalID;
	//увеличить глобальный ид
	globalID++;

	//задать основные параметры
	satiety = 100;
	thirst = 100;
	stamina = 100;
	hp = 100;

	w = 16;
	h = 16;
	//ожидаемое время жизни
	estLifeTime = meanLifeTime / 2 + rand() % meanLifeTime;
	//параметры, нужные для респавна, задаются непосредственно при смерти
	respawnPause = 0;
	currentPause = 0;

	running = false;

	//задать облик. Поскольку у нас по умолчанию пока только свиньи, облик у всех один
	tileset = "Images/CreatureTilesets/Animal/pig.png";
	image.loadFromFile(tileset);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));

	//скорость движения
	speed = 0.2;
	runningSpeed = 0.3;
	currentSpeed = 0;

	dir = rand() % 4;

	//позиция в мире
	cell tmp = validCells[rand() % validCells.size()];
	x = tmp.x;
	y = tmp.y;
	sprite.setPosition(x*w, y*h);
}

void animal::die()
{
	//существо умирает. такова жизнь.
	alive = false;
	respawnPause = rand() % 3000 + 1000; //в тиках?
	currentPause = respawnPause; //текущее время до респавна равно сгенерированному
}

void animal::respawn()
{
	//когда истекает пауза респавна, существо возрождается в случайной клетке карты
	//сгенерировать точку для респауна
	cell tmp = validCells[rand() % validCells.size()];
	x = tmp.x;
	y = tmp.y;
	//вроде всё?
	sprite.setPosition(x*w, y*h);
}

String animal::getAnimalData()
{
	//какие данные нужно выводить в виджет?
	std::stringstream ss;
	string str;

	ss << id << " hp=" << hp << " st=" << stamina << "x=" << x << " y=" << y;

	ss >> str;
	String Str(str);
	return Str;
}

void animal::goalPlanner()
{
	//осуществляет планирование целей
	//проверить состояние существа и на основе этого выбрать новую цель
	if (satiety < 20)
	{
		//голод, нужно найти пищу
		//только если приоритет выше, чем у текущей цели
		if (availibleGoals[Eat].priority > currentGoal.priority)
			currentGoal = availibleGoals[Eat]; //цель - поесть
	}
	else if (thirst < 20)
	{
		//новая цель - поиск питья, но только если приоритет выше
		if (availibleGoals[Drink].priority > currentGoal.priority)
			currentGoal = availibleGoals[Drink]; //цель - поиск питья
	}
	else if (stamina < 5) //или время позднее уже
	{
		//утомление, нужно поспать
		if (availibleGoals[Sleep].priority > currentGoal.priority)
			currentGoal = availibleGoals[Sleep];
	}
	else
	{
		//никаких предпосылок что-либо делать нет, ленимся
		currentGoal = availibleGoals[Idle];
	}

	//условие убегания при атаке

}

void animal::prepareAvailibleGoals()
{
	//подготавливает список достижимых целей
	//для животного цели могут быть:
	//питание
	//питьё
	//сон
	//лень
	goal slp = { Sleep, 1 };
	goal et = { Eat, 3 };
	goal drk = { Drink, 5 };
	goal idl = { Idle, 0 };
	goal hd = { Hide, 6 };
	goal rn = { Run, 7 };
	availibleGoals = {
		slp,
		et,
		drk,
		rn,
		idl,
		hd
	};
}

void animal::actionPlanner()
{
	//планирует непосредственно действия, направленные на достижение цели
	switch (currentGoal.Goal)
	{
	case Sleep:
		//животные могут спать где угодно, максимально неприхотливы
		break;
	case Eat:
		//животные питаются травой, которая произрастает.. почти на всех клетках. Найти клетку и поесть
		break;
	case Idle:
		//если цель - полениться, то животное либо стоит на месте, либо ходит из угла в угол
		break;
	case Run:
		//в состоянии сваливания от проблем животное бежит в случайную точку карты
		running = true;
		//сгенерировать какую-то точку карты

		break;
	}
}


