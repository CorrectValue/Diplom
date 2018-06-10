#ifndef HUMAN
#define HUMAN
#include "Creature.h"
#include <vector>
#include <stdio.h>
//класс человека - наследует класс существа
using namespace std;
using namespace sf;
class human : public Creature
{
private:
	static int globalID;						//статичный общий id, от которого считаются все айди объектов
	static vector<goal> availibleGoals;			//доступные конкретному существу цели
	static vector<cell> houses;					//дома на карте
	static vector<String> maleNames;			//доступные для мужчин имена 
	static vector<String> femaleNames;			//доступные для женщин имена
	static vector<String> lastNames;			//доступные фамилии
	static vector<String> maleAppearances;		//вектор тайлсетов для персонажей, обликов мужчин
	static vector<String> femaleAppearances;	// для женщин
	static vector<action> availibleActions;		//список действий
	const int meanLifeTime = 70;
public:
	//навыки - то, что отличает человека от животного
	int strength; //1 - дохляк, 10 - атлант
	int intelligence; //1 - дебил, 10 - Эйнштейн
	int endurance; //1 - дохлая котлета, 10 - Форрест Гамп
	int agility; //1 - черепаха, 10 - Усэйн Болт
	
	int id; //идентификатор

	int gender; //пол

	//щас будет чорная магия
	bool hasWeapon;

	cell home; //домашняя клетка
	
	String name;
	String lastName;
		
	void generateName(); //генерирует имя персонажа
	static void prepareNames();//единовременно готовит список имён и фамилий
	static void prepareAppearances(); //единожды готовит списки обликов
	static void prepareHouses(world &wrld);
	static void prepareAvailibleActions(); //готовит список действий
	using Creature::die;
	void die();
	using Creature::respawn;
	void respawn();
	void generateNewHuman();
	using Creature::checkDeathDate;
	void checkDeathDate();
	using Creature::goalPlanner;
	void goalPlanner(int &time, int &weather);
	static void prepareAvailibleGoals();
	void actionPlanner();
	String getHumanData();

	human();

};

#endif