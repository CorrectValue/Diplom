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
	maxStamina = 100;
	maxHp = 100;
	curStamina = 100;
	curHp = 100;

	w = 16;
	h = 16;
	//ожидаемое время жизни
	estLifeTime = meanLifeTime / 2 + rand() % meanLifeTime;
	//параметры, нужные для респавна, задаются непосредственно при смерти
	respawnPause = 0;
	currentPause = 0;

	running = false;
	hidden = false;
	tookDamage = false;

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

	currentGoal = availibleGoals[Idle];

	//обнуление точки назначения
	dest.x = -1;
	dest.y = -1;

	//позиция в мире
	cell tmp = validCells[rand() % validCells.size()];
	X = tmp.x;
	Y = tmp.y;
	x = X*w;
	y = Y*h;
	sprite.setPosition(x, y);
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

	ss << id << "_hp=" << curHp << "_st=" << curStamina;
	switch (currentGoal.Goal)
	{
	case Eat:
		ss << "_Eat";
		break;
	case Sleep:
		ss << "_Sleep";
		break;
	case Run:
		ss << "_Run";
		break;
	case Idle:
		ss << "_Idle";
		break;
	case Rest:
		ss << "_Rest";
		break;
	case Hide:
		ss << "_Hide";
		break;
	case Drink:
		ss << "_Drink";
		break;
	}
	ss >> str;
	String Str(str);
	return Str;
}

void animal::goalPlanner(int &time, int &weather)
{
	//осуществляет планирование целей
	//проверить состояние существа и на основе этого выбрать новую цель
	//если никаких предпосылок что-либо делать нет, ленимся
	// далее, если есть что-то важнее, цель просто переопределится
	currentGoal = availibleGoals[Idle];

	if (satiety < 20)
	{
		//голод, нужно найти пищу
		//только если приоритет выше, чем у текущей цели
		if (availibleGoals[Eat].priority > currentGoal.priority)
			currentGoal = availibleGoals[Eat]; //цель - поесть
	}
	if (thirst < 20)
	{
		//новая цель - поиск питья, но только если приоритет выше
		if (availibleGoals[Drink].priority > currentGoal.priority)
			currentGoal = availibleGoals[Drink]; //цель - поиск питья
	}
	if (curStamina < 5 || (time > 20 || time < 7)) //или время позднее уже
	{
		//утомление, нужно поспать
		if (availibleGoals[Sleep].priority > currentGoal.priority)
			currentGoal = availibleGoals[Sleep];
	}
	if (weather == fallout || weather == storm) //погода - осадки или буря
	{
		//погодные условия плохие, надо прятаться
		if (availibleGoals[Hide].priority > currentGoal.priority)
			currentGoal = availibleGoals[Hide];
	}
	if (tookDamage) //получаем люлей
	{
		//надо убегать
		//поскольку приоритет у сваливания наибольший, даже чекать не надо
		currentGoal = availibleGoals[Run];
	}
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

void animal::actionPlanner(world &wrld)
{
	//планирует непосредственно действия, направленные на достижение цели
	switch (currentGoal.Goal)
	{
	case Sleep:
		//животные могут спать где угодно, максимально неприхотливы
		currentSpeed = 0;
		sleeping = true;
		break;
	case Eat:
		//животные питаются фруктами и ягодами с деревьев и кустов
		sleeping = false;
		searchFor(wrld.TileMap, Food);
		for (int i = X - 1; i < X + 1 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 1; j < Y + 1 && j > -1 && j < mapH; j++)
			{
				if (wrld.TileMap[j][j] == 'T' || wrld.TileMap[j][j] == 'B')
				{
					//рядом с текущей клеткой есть еда, жрём
					eat();
				}
			}
		}
		break;
	case Drink:
		//ищем водоём и пьём
		sleeping = false;
		searchFor(wrld.TileMap, Water);
		for (int i = X - 1; i < X + 1 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 1; j < Y + 1 && j > -1 && j < mapH; j++)
			{
				if (wrld.TileMap[j][j] == 'v')
				{
					//рядом с текущей клеткой есть вода, пьём
					drink();
				}
			}
		}
		break;
	case Idle:
		//если цель - полениться, то животное либо стоит на месте, либо ходит из угла в угол
		sleeping = false;
		if (dest.x == -1)
		{
			int randNum = rand() % 100;
			if (randNum > 79)
			{
				//стоим на месте
				currentSpeed = 0;
			}
			else
			{
				//идём куда-нибудь
				dest = validCells[rand() % validCells.size()];
			}
		}
		else
			moveTo(dest.x, dest.y);
		break;
	case Hide:
		//если цель - ныкаться, то ищем укрытие и нычемся!
		sleeping = false;
		searchFor(wrld.TileMap, Cover);
		break;
	case Run:
		//в состоянии сваливания от проблем животное бежит в случайную точку карты
		sleeping = false;
		running = true;
		//сгенерировать какую-то точку карты
		if (dest.x == -1)
		{
			//генерим новую точку, если никакой ещё не сгенерировано
			dest = validCells[rand() % validCells.size()];
		}
		//двинуться в неё
		moveTo(dest.x, dest.y);
		break;
	}
}

void animal::eat()
{
	//при еде просто повышается счётчик сытости
	satiety += 50;
}

void animal::drink()
{
	//у животного просто при питье жажда снижается
	thirst += 40;
}
