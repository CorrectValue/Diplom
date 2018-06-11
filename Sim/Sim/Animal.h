#ifndef ANIMAL
#define ANIMAL
#include "Creature.h"
#include <vector>
#include <stdio.h>

//класс человека - наследует класс существа
using namespace std;
using namespace sf;
class animal : public Creature
{
private:
	static int globalID;
	static vector<goal> availibleGoals; //доступные конкретному существу цели
	const int meanLifeTime = 13; //среднее время жизни конкретного типа существ в годах
public:
	animal();
	using Creature::die;
	void die();
	using Creature::respawn;
	void respawn();
	String getAnimalData(); //возвращает строку данных о животном
	using Creature::goalPlanner;
	void goalPlanner(int &time, int &weather);
	static void prepareAvailibleGoals();
	using Creature::actionPlanner;
	void actionPlanner(world &wrld);
	using Creature::eat;
	void eat();
	using Creature::drink;
	void drink();
};

#endif