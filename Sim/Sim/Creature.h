#ifndef CREATURE
#define CREATURE
#include <SFML/Graphics.hpp>
#include "enums.h"

using namespace sf;

class Creature
{
private:
	static int globalID;
public:
	
	const int meanLifeTime = 13; //среднее время жизни конкретного типа существ в годах
	
	float x, y, w, h, dx, dy, speed, runningSpeed;
	int dir; //направление движения
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	String tileset; //строка, в которой лежит тайлсет
	int id;
	bool alive; //живо ли существо

	int respawnTimer; //для респауна существ, причём респаун людей идёт медленнее

	float satiety; //сытость, здесь 100 - сыт, 0 - голоден
	float thirst; //обратно жажде, 100 - всё ок, 0 - помирает от жажды
	float stamina; //запас сил, 100 - хоть отбавляй, 0 - пал без сил
	float hp; //здоровье, здесь 100 - здоров как бык, 0 - мёртв

	
	int estLifeTime; //предполагаемое время жизни. По истечении - смерть.
	int age; //текущий возраст существа


	
	Creature(); 
	void update(float time);
	void respawn();
};


#endif