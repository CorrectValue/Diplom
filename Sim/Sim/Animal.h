#ifndef ANIMAL
#define ANIMAL
#include "Creature.h"
#include <vector>
#include <stdio.h>

//����� �������� - ��������� ����� ��������
using namespace std;
using namespace sf;
class animal : public Creature
{
private:
	static int globalID;
	static vector<goal> availibleGoals; //��������� ����������� �������� ����
	const int meanLifeTime = 13; //������� ����� ����� ����������� ���� ������� � �����
public:
	animal();
	using Creature::die;
	void die();
	using Creature::respawn;
	void respawn();
	String getAnimalData(); //���������� ������ ������ � ��������
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