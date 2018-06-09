
#include "Creature.h"

int Creature::globalID = 0;
vector<cell> Creature::validCells;

//оставленные здесь методы справедливы для всех наследников. Вроде.
Creature::Creature()
{
	
}

void Creature::update(float time, world &wrld)
{
	//обновляет состояние существа в каждом тике
	//если существо живо:
	if (alive)
	{
		//движение:
		switch (dir)
		{
		case down:
			//вниз
			sprite.setTextureRect(IntRect(0, 0, 16, 16));//повернуть перса по направлению движения
			dy = currentSpeed;
			dx = 0;
			break;
		case up:
			//вверх
			sprite.setTextureRect(IntRect(0, 17, 16, 16));
			dy = - currentSpeed;
			dx = 0;
			break;
		case dleft:
			//влево
			sprite.setTextureRect(IntRect(17, 17, 16, 16));
			dx = - currentSpeed;
			dy = 0;
			break;
		case dright:
			//вправо
			sprite.setTextureRect(IntRect(17, 0, 16, 16));
			dx = currentSpeed;
			dy = 0;
			break;
		default:
			break;
		}
		//прирастить координату
		if (x + dx*time < wrld.getWidth() * 16 && x + dx*time > 0)
			x += dx*time;
		if (y + dy*time < wrld.getHeight() * 16 && y + dy*time > 0)
			y += dy*time;
		sprite.setPosition(x*w, y*h);
	}
	else
	{
		//существо мертво, считаем его респавн тайм
		currentPause -= time;
		if (currentPause <= 0)
		{
			//время пришло, пора воскресать
			respawn();
		}
	}
}

void Creature::prepareValidCellsList(world wrld)
{
	//пробегаем все клетки 
	//уже ПОСЛЕ генерации объектов на карте, что значит, что клеток будет меньше и их придётся искать заново
	for (int i = 0; i < wrld.getHeight(); i++)
	{
		for (int j = 0; j < wrld.getWidth(); j++)
		{
			if (wrld.TileMap[i][j] == ' ')
			{
				//подходящая клетка
				cell temp = { j, i };
				validCells.insert(validCells.end(), temp);
			}
		}
	}
}

void Creature::mapInteraction(world wrld)
{
	//взаимодействие существа с отдельными частями карты
	//проверяем каждую точку спрайта существа на соприкосновение с неприкасаемыми частями карты
	for (int i = y / 16; i < (y + h) / 16; i++)
	{
		for (int j = x / 16; j < (x + w) / 16; j++)
		{
			if (wrld.TileMap[i][j] == 'r')//булыжник, наступать нельзя
			{
				if (dx > 0)
					x = j * 16 - w;
				if (dx < 0)
					x = j * 16 + 16;
			}
			if (wrld.TileMap[i][j] == 'v')//вода, наступать нельзя
			{
				if (dx > 0)
					x = j * 16 - w;
				if (dx < 0)
					x = j * 16 + 16;
			}
			if (wrld.TileMap[i][j] == 'B')//куст, наступать нельзя
			{
				if (dx > 0)
					x = j * 16 - w;
				if (dx < 0)
					x = j * 16 + 16;
			}
			if (wrld.TileMap[i][j] == 'T')//дерево, наступать нельзя
			{
				if (dx > 0)
					x = j * 16 - w;
				if (dx < 0)
					x = j * 16 + 16;
			}
			//пропасти: существо может случайно упасть в пропасть и погибнуть
			if (wrld.TileMap[i][j] == '=')//пропасть верхняя, наступил - умер
			{
				//тут надо подумать, как округлить координату
			}
			if (wrld.TileMap[i][j] == '_')//пропасть нижняя, наступил - умер
			{
				//тут надо подумать, как округлить координату
			}
			if (wrld.TileMap[i][j] == '/')//пропасть левая, наступил - умер
			{
				//тут надо подумать, как округлить координату
			}
			if (wrld.TileMap[i][j] == '\\')//пропасть правая, наступил - умер
			{
				//тут надо подумать, как округлить координату
			}
		}
	}
}

//void Creature::operator=(const Creature &other)
//{
//	x = other.x;
//	y = other.x;
//	age = other.age;
//	estLifeTime = other.estLifeTime;
//
//	satiety = other.satiety;
//	thirst = other.thirst;
//	stamina = other.stamina;
//	hp = other.hp;
//
//	w = other.w;
//	h = other.h;
//
//	alive = other.alive;
//	id = other.id;
//	dir = other.dir;
//	speed = other.speed;
//	runningSpeed = other.runningSpeed;
//	running = other.running;
//	tileset = other.tileset;
//	image.loadFromFile(tileset);
//	texture.loadFromImage(image);
//	sprite.setTexture(texture);
//	sprite.setTextureRect(IntRect(0, 0, w, h));
//	/*image = other.image;
//	texture = other.texture;
//	sprite = other.sprite;*/
//	
//	respawnPause = other.respawnPause;
//	currentPause = other.currentPause;
//
//}

void Creature::generateDeathDate()
{
	//есть текущий возраст, есть предполагаемое время жизни
	int diff = estLifeTime - age; //сколько лет осталось до смерти

}

void Creature::respawn()
{

}

void Creature::goalPlanner()
{

}

void Creature::moveTo(int X, int Y)
{
	//метод передвижения в заданную точку карты
	//сравнить координаты текущие и требуемые
	int diffX, diffY; //разница координат по осям Х и Y соответственно
	diffX = x - X; //текущие минус требуемые
	diffY = y - Y;
	//сначала выравниваем координату Х
	if (diffX > 0)
	{
		//текущая координата больше требуемой
		dir = dleft; //идём влево
	}
	else
	{
		//текущая координата меньше требуемой
		dir = dright;
	}
	if (diffX == 0)
	{
		//по иксу выровнялись, выравниваем игрек
		if (diffY > 0)
		{
			//находимся выше цели
			dir = down;
		}
		else
		{
			//находимся ниже
			dir = up;
		}
	}
}

void Creature::searchFor(String map)
{
	//поиск чего-либо
	//в режиме поиска существо не знает, где ему искать то, что нужно
	//поэтому выбирается случайная клетка карты
}