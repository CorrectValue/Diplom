#ifndef CREATURE
#define CREATURE
#include <SFML/Graphics.hpp>
#include "enums.h"

using namespace sf;

class Creature
{
public:
	float x, y, w, h, dx, dy, speed, runningSpeed;
	int dir; //направление движения
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	String tileset; //строка, в которой лежит тайлсет

	float satiety; //сытость, здесь 100 - сыт, 0 - голоден
	float thirst; //обратно жажде, 100 - всё ок, 0 - помирает от жажды
	float stamina; //запас сил, 100 - хоть отбавляй, 0 - пал без сил
	float hp; //здоровье, здесь 100 - здоров как бык, 0 - мёртв

	static int meanLifeTime; //среднее время жизни конкретного типа существ
	int estLifeTime; //предполагаемое время жизни. По истечении - смерть.
	int age; //текущий возраст существа


	
	Creature(); 
};


#endif