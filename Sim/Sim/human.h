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
	static int globalID; //статичный общий id, от которого считаются все айди объектов
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


	
	String name;
	String lastName;
	
	static vector<String> maleNames; //доступные для мужчин имена 
	static vector<String> femaleNames; //доступные для женщин имена
	static vector<String> lastNames; //доступные фамилии
	static vector<String> maleAppearances; //вектор тайлсетов для персонажей, обликов мужчин
	static vector<String> femaleAppearances; // для женщин

	
	void generateName(); //генерирует имя персонажа
	void generateDeathDate();//генерирует день смерти персонажа
	static void prepareNames();//единовременно готовит список имён и фамилий
	static void prepareAppearances(); //единожды готовит списки обликов


	human();

};

#endif