#ifndef CREATURE
#define CREATURE
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "world.h"
#include <sstream>

using namespace sf;
using namespace std;

class Creature
{
private:
	static int globalID;
public:
	
	static vector<cell> validCells; //доступные для респауна клетки

	float x, y, w, h, dx, dy, currentSpeed, speed, runningSpeed;
	int dir; //направление движения
	Image image;//сфмл изображение
	sf::Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	String tileset; //строка, в которой лежит тайлсет
	int id;
	bool alive; //живо ли существо

	goal currentGoal; //текущая цель

	float respawnPause; //для респауна существ, причём респаун людей идёт медленнее
	float currentPause; //текущее время до респавна существа

	float satiety; //сытость, здесь 100 - сыт, 0 - голоден
	float thirst; //обратно жажде, 100 - всё ок, 0 - помирает от жажды
	float maxStamina, curStamina; //запас сил, 100 - хоть отбавляй, 0 - пал без сил
	float maxHp, curHp; //здоровье, здесь 100 - здоров как бык, 0 - мёртв

	
	int estLifeTime; //предполагаемое время жизни. По истечении - смерть.
	int age; //текущий возраст существа

	bool running; //бежит ли существо
	bool tookDamage; //получен урон от другого существа

	Creature(); 
	void update(float time, world &wrld);
	void respawn();
	void die(); //смерть существа по естественным или не очень естественным причинам
	static void prepareValidCellsList(world &wrld); //подготовить список клеток, в которые можно респауниться
	void mapInteraction(world wrld);
	void checkDeathDate();
	void generateDeathDate();//генерирует день смерти персонажа
	void goalPlanner(int &time, int &weather); //планировщик целей
	void moveTo(int X, int Y);
	void searchFor(String map);

	//void operator=(const Creature &other);
};


#endif