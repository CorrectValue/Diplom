
#include "Creature.h"

int Creature::globalID = 0;
vector<cell> Creature::validCells;

Creature::Creature()
{
	//получить id
	id = globalID;
	//увеличить глобальный ид
	globalID++;


}

void Creature::update(float time)
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
			dy = running ? runningSpeed : speed;
			dx = 0;
			break;
		case up:
			//вверх
			sprite.setTextureRect(IntRect(0, 17, 16, 16));
			dy = running ? -runningSpeed : -speed;
			dx = 0;
			break;
		case dleft:
			//влево
			sprite.setTextureRect(IntRect(17, 17, 16, 16));
			dx = running ? -runningSpeed : -speed;
			dy = 0;
			break;
		case dright:
			//вправо
			sprite.setTextureRect(IntRect(17, 0, 16, 16));
			dx = running ? runningSpeed : speed;
			dy = 0;
			break;
		default:
			break;
		}
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

void Creature::respawn()
{
	//когда истекает пауза респавна, существо возрождается в случайной клетке карты
	//сгенерировать точку для респауна
	cell tmp = validCells[rand() % validCells.size()];
	x = tmp.x;
	y = tmp.y;
	//вроде всё?
}

void Creature::die()
{
	//существо умирает. такова жизнь.
	alive = false;
	respawnPause = rand() % 3000 + 1000; //в тиках?
	currentPause = respawnPause; //текущее время до респавна равно сгенерированному
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