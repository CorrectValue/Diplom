
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
		sleeping = false; //не спим, но если ночь, то спим
		//определить цель существования
		goalPlanner(wrld.currentTimeHours, wrld.curWeather);
		actionPlanner(wrld);
		if (curStamina < 0)
		{
			curStamina = 0;
			currentSpeed = 0;
		}
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
		if (time > 10)
			time = 10.0;
		//прирастить координату
		if (x + dx*time < wrld.getWidth() * 16 && x + dx*time > 0)
		{
			x += dx*time;
			X = (x+w/2) / w;//центр спрайта
		}
		if (y + dy*time < wrld.getHeight() * 16 && y + dy*time > 0)
		{
			y += dy*time;
			Y = (y+h/2) / h;
		}

		mapInteraction(wrld);

		//пересчитать показатели здоровья, стамины, жажды и голода
		//голод и жажда
		if (satiety > 0)
			satiety -= 0.1; //пока фиксированно так: расход сытости постоянен и ни от чего не зависит
		if (thirst > 0)
		{
			if (sleeping)
				thirst -= (wrld.season == Winter) ? 0.05 : 0.15; //летом расход жидкости выше, чем зимой
			else
				thirst -= (wrld.season == Winter) ? 0.1 : 0.3; //летом расход жидкости выше, чем зимой
		}
		//расход стамины зависит от того, насколько интенсивно двигается существо
		
		if (currentSpeed > 0)
		{
			if (running)
				curStamina -= 0.5;
			else
				curStamina -= 0.2;
		}
		else
			if (curStamina < maxStamina) //если не двигаемся, но запас сил не полон, регеним его
				if (sleeping)
					curStamina += 0.5; //во сне регенерация запаса сил существеннее
				else
					curStamina += 0.1;
		//хп, если персонаж голоден или умирает от жажды, тратится
		if (satiety == 0 || thirst == 0)
			if (sleeping)
				curHp -= 0.05;
			else
				curHp -= 0.1;
		else
			if (curHp < maxHp)
				if (sleeping)
					curHp += 0.2;//во сне регенерация усиленнее
				else
					curHp += 0.1;
		if (curHp <= 0)
		{
			//YOU DIED
			die();
		}
		sprite.setPosition(x, y);
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

void Creature::prepareValidCellsList(world &wrld)
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
			if (wrld.TileMap[i][j] == 'B')//куст, можно спрятаться
			{
				hidden = true;
			}
			if (wrld.TileMap[i][j] == 'T')//дерево, под ним можно спрятаться
			{
				hidden = true;
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

void Creature::goalPlanner(int &time, int &weather)
{
	
}

void Creature::actionPlanner(world &wrld)
{

}

void Creature::moveTo(int destX, int destY)
{
	//метод передвижения в заданную точку карты
	//сравнить координаты текущие и требуемые
	int diffX, diffY; //разница координат по осям Х и Y соответственно
	diffX = X - destX; //текущие минус требуемые
	diffY = Y - destY;

	currentSpeed = running ? runningSpeed : speed;
	//сначала выравниваем координату Х
	if (diffX > 0)
	{
		//текущая координата больше требуемой
		dir = dleft; //идём влево
	}
	else if (diffX < 0)
	{
		//текущая координата меньше требуемой
		dir = dright;
	}
	else if (diffX == 0)
	{
		//по иксу выровнялись, выравниваем игрек
		if (diffY > 0)
		{
			//находимся выше цели
			dir = up;
		}
		else
		{
			//находимся ниже
			dir = down;
		}
	}
	currentSpeed = running ? runningSpeed : speed; //бежим или идём к цели
	if (diffX == 0 && diffY == 0)
	{
		//достигли точки назначения, обнуляем 
		dest.x = -1;
		dest.y = -1;
	}
}

void Creature::searchFor(String map[][mapW], int thing)
{
	//поиск чего-либо
	switch (thing)
	{
	case Water:
		//ищем водную клетку
		//ищем вокруг себя
		for (int i = X - 2; i < X + 2 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 2; j < Y + 2 && j > -1 && j <mapH; j++)
			{
				if (map[j][i] == 'v')
				{
					//цель найдена рядом с существом
					dest.x = i;
					dest.y = j;
				}
			}
		}
		
		break;
	case Food:
		//ищем куст или дерево 
		for (int i = X - 2; i < X + 2 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 2; j < Y + 2 && j > -1 && j < mapH; j++)
			{
				if (map[j][i] == 'T' || map[j][i] == 'B')
				{
					//цель найдена рядом с существом
					dest.x = i;
					dest.y = j;
				}
			}
		}
		break;
	case Cover:
		//ищем укрытие. укрытием является куст или дерево
		for (int i = X - 2; i < X + 2 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 2; j < Y + 2 && j > -1 && j < mapH; j++)
			{
				if (map[j][i] == 'T' || map[j][i] == 'B')
				{
					//цель найдена рядом с существом
					dest.x = i;
					dest.y = j;
				}
				cout << map[j][i].toAnsiString();
			}
		}
		break;
	}
	//если около себя не нашли, то
	if (dest.x == -1) //точка не назначена
	{
		dest = validCells[rand() % validCells.size()];
	}
	moveTo(dest.x, dest.y);
}

void Creature::die()
{

}

void Creature::eat()
{

}

void Creature::drink()
{

}