#ifndef HUMAN
#define HUMAN
#include "Creature.h"
#include <vector>
#include <stdio.h>
//����� �������� - ��������� ����� ��������
using namespace std;
using namespace sf;
class human : public Creature
{
private:
	static int globalID;						//��������� ����� id, �� �������� ��������� ��� ���� ��������
	static vector<goal> availibleGoals;			//��������� ����������� �������� ����
	static vector<cell> houses;					//���� �� �����
	static vector<String> maleNames;			//��������� ��� ������ ����� 
	static vector<String> femaleNames;			//��������� ��� ������ �����
	static vector<String> lastNames;			//��������� �������
	static vector<String> maleAppearances;		//������ ��������� ��� ����������, ������� ������
	static vector<String> femaleAppearances;	// ��� ������
	static vector<action> availibleActions;		//������ ��������
	const int meanLifeTime = 70;
public:
	//������ - ��, ��� �������� �������� �� ���������
	int strength; //1 - ������, 10 - ������
	int intelligence; //1 - �����, 10 - ��������
	int endurance; //1 - ������ �������, 10 - ������� ����
	int agility; //1 - ��������, 10 - ����� ����
	
	int id; //�������������

	int gender; //���

	//��� ����� ������ �����
	bool hasWeapon;

	cell home; //�������� ������
	
	String name;
	String lastName;
		
	void generateName(); //���������� ��� ���������
	static void prepareNames();//������������� ������� ������ ��� � �������
	static void prepareAppearances(); //�������� ������� ������ �������
	static void prepareHouses(world &wrld);
	static void prepareAvailibleActions(); //������� ������ ��������
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