#include "Animal.h"

using namespace sf;
using namespace std;

int animal::globalID = 0;


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
