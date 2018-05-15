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
public:
	//навыки - то, что отличает человека от животного
	int strength; //1 - дохляк, 10 - атлант
	int intelligence; //1 - дебил, 10 - Эйнштейн
	
	int gender; //пол
	int meanLifeTime; //средняя продолжительность жизни

	int approximateLifeTime; // предположительное время жизни
	String name;
	String lastName;
	
	static vector<String> maleNames; //доступные для мужчин имена 
	static vector<String> femaleNames; //доступные для женщин имена
	static vector<String> lastNames; //доступные фамилии

	
	void generateName(); //генерирует имя персонажа
	void generateDeathDate();//генерирует день смерти персонажа
	static void prepareNames();//единовременно готовит список имён и фамилий


	human();

};

#endif