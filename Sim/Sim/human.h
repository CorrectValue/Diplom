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

	//������� ���������� �� ��������� ������������ ������ ����
	bool hasWeapon;	//���� ������
	bool hasWater;	//���� ����� ����
	bool hasFood;	//���� ����� ����

	cell home; //�������� ������

	cell attacked; //������, ������ ������� �������
	
	String name;
	String lastName;

	int currentState; //������� ��������� ������
	int desiredState; //��������� ��������� ������
	int currentAction; //������� ��������
	vector<action> actionSequence; //������� ��������
		
	void generateName(); //���������� ��� ���������
	static void prepareNames();//������������� ������� ������ ��� � �������
	static void prepareAppearances(); //�������� ������� ������ �������
	static void prepareHouses(world &wrld);
	static void prepareAvailibleActions(); //������� ������ ��������
	static void prepareAvailibleGoals();
	using Creature::die;
	void die();
	using Creature::respawn;
	void respawn();
	void generateNewHuman();
	using Creature::checkDeathDate;
	void checkDeathDate();
	using Creature::goalPlanner;
	void goalPlanner(int &time, int &weather);

	void goalAnalyzer();
	String getHumanData();
	using Creature::eat;
	void eat();
	using Creature::drink;
	void drink();
	using Creature::actionPlanner;
	void actionPlanner(world &wrld);
	void makeSequence(); //��������� ������������������ ��������
	void performSequence(); //��������� ������������������ ��������
	void performAction(world &wrld); //��������� ���� ��������
	void slack(); //������ ������

	human();

};

#endif