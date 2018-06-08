#ifndef ANIMAL
#define ANIMAL
#include "Creature.h"
#include <vector>
#include <stdio.h>
#include <sstream>
//����� �������� - ��������� ����� ��������
using namespace std;
using namespace sf;
class animal : public Creature
{
private:
	static int globalID;
	const int meanLifeTime = 13; //������� ����� ����� ����������� ���� ������� � �����
public:
	animal();
	using Creature::die;
	void die();
	using Creature::respawn;
	void respawn();
	String getAnimalData(); //���������� ������ ������ � ��������
};

#endif