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
	const int meanLifeTime = 13; //среднее время жизни конкретного типа существ в годах
public:
	animal();
};

#endif