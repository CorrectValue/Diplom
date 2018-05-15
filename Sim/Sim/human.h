#ifndef HUMAN
#define HUMAN
#include "Creature.h"
//класс человека - наследует класс существа
class human : public Creature
{
public:
	//навыки - то, что отличает человека от животного
	int strength; //1 - дохл€к, 10 - атлант
	int intelligence; //1 - дебил, 10 - Ёйнштейн

	int approximateLifeTime; // предположительное врем€ жизни
	char name[15];
	char lastName[20];
	//комментарий!

};

#endif