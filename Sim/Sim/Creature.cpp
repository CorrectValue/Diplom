
#include "Creature.h"

int Creature::globalID = 0;

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
	//движение:
	switch (dir)
	{
	case down:
		//вниз
		sprite.setTextureRect(IntRect(0, 0, 16, 16));//повернуть перса по направлению движения
		dy = speed;
		dx = 0;
		break;
	case up:
		//вверх
		sprite.setTextureRect(IntRect(0, 17, 16, 16));
		dy = -speed;
		dx = 0;
		break;
	case dleft:
		//влево
		sprite.setTextureRect(IntRect(17, 17, 16, 16));
		dx = -speed;
		dy = 0;
		break;
	case dright:
		//вправо
		sprite.setTextureRect(IntRect(17, 0, 16, 16));
		dx = speed;
		dy = 0;
		break;
	default:
		break;
	}
}

void respawn()
{
	//когда истекает пауза респавна, существо возрождается в случайной клетке карты

}