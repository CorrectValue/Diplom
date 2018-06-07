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

