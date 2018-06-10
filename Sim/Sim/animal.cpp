#include "Animal.h"

using namespace sf;
using namespace std;

int animal::globalID = 0;
vector<goal> animal::availibleGoals;


animal::animal()
{
	//�������� id
	id = globalID;
	//��������� ���������� ��
	globalID++;

	//������ �������� ���������
	satiety = 100;
	thirst = 100;
	maxStamina = 100;
	maxHp = 100;
	curStamina = 100;
	curHp = 100;

	w = 16;
	h = 16;
	//��������� ����� �����
	estLifeTime = meanLifeTime / 2 + rand() % meanLifeTime;
	//���������, ������ ��� ��������, �������� ��������������� ��� ������
	respawnPause = 0;
	currentPause = 0;

	running = false;

	//������ �����. ��������� � ��� �� ��������� ���� ������ ������, ����� � ���� ����
	tileset = "Images/CreatureTilesets/Animal/pig.png";
	image.loadFromFile(tileset);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));

	//�������� ��������
	speed = 0.2;
	runningSpeed = 0.3;
	currentSpeed = 0;

	dir = rand() % 4;

	//������� � ����
	cell tmp = validCells[rand() % validCells.size()];
	x = tmp.x;
	y = tmp.y;
	sprite.setPosition(x*w, y*h);
}

void animal::die()
{
	//�������� �������. ������ �����.
	alive = false;
	respawnPause = rand() % 3000 + 1000; //� �����?
	currentPause = respawnPause; //������� ����� �� �������� ����� ����������������
}

void animal::respawn()
{
	//����� �������� ����� ��������, �������� ������������ � ��������� ������ �����
	//������������� ����� ��� ��������
	cell tmp = validCells[rand() % validCells.size()];
	x = tmp.x;
	y = tmp.y;
	//����� ��?
	sprite.setPosition(x*w, y*h);
}

String animal::getAnimalData()
{
	//����� ������ ����� �������� � ������?
	std::stringstream ss;
	string str;

	ss << id << "_hp=" << curHp << "/" << maxHp << "_st=" << curStamina << "/" << maxStamina << "_x=" << x << "_y=" << y;

	ss >> str;
	String Str(str);
	return Str;
}

void animal::goalPlanner(int &time, int &weather)
{
	//������������ ������������ �����
	//��������� ��������� �������� � �� ������ ����� ������� ����� ����
	//���� ������� ����������� ���-���� ������ ���, �������
	// �����, ���� ���� ���-�� ������, ���� ������ ���������������
	currentGoal = availibleGoals[Idle];

	if (satiety < 20)
	{
		//�����, ����� ����� ����
		//������ ���� ��������� ����, ��� � ������� ����
		if (availibleGoals[Eat].priority > currentGoal.priority)
			currentGoal = availibleGoals[Eat]; //���� - ������
	}
	if (thirst < 20)
	{
		//����� ���� - ����� �����, �� ������ ���� ��������� ����
		if (availibleGoals[Drink].priority > currentGoal.priority)
			currentGoal = availibleGoals[Drink]; //���� - ����� �����
	}
	if (curStamina < 5 || (time > 20 || time < 7)) //��� ����� ������� ���
	{
		//���������, ����� �������
		if (availibleGoals[Sleep].priority > currentGoal.priority)
			currentGoal = availibleGoals[Sleep];
	}
	if (weather == fallout || weather == storm) //������ - ������ ��� ����
	{
		//�������� ������� ������, ���� ���������
		if (availibleGoals[Hide].priority > currentGoal.priority)
			currentGoal = availibleGoals[Hide];
	}
	if (tookDamage) //�������� �����
	{
		//���� �������
		//��������� ��������� � ���������� ����������, ���� ������ �� ����
		currentGoal = availibleGoals[Run];
	}
}

void animal::prepareAvailibleGoals()
{
	//�������������� ������ ���������� �����
	//��� ��������� ���� ����� ����:
	//�������
	//�����
	//���
	//����
	goal slp = { Sleep, 1 };
	goal et = { Eat, 3 };
	goal drk = { Drink, 5 };
	goal idl = { Idle, 0 };
	goal hd = { Hide, 6 };
	goal rn = { Run, 7 };
	availibleGoals = {
		slp,
		et,
		drk,
		rn,
		idl,
		hd
	};
}

void animal::actionPlanner()
{
	//��������� ��������������� ��������, ������������ �� ���������� ����
	switch (currentGoal.Goal)
	{
	case Sleep:
		//�������� ����� ����� ��� ������, ����������� ������������
		break;
	case Eat:
		//�������� �������� ������, ������� ������������.. ����� �� ���� �������. ����� ������ � ������
		break;
	case Idle:
		//���� ���� - ����������, �� �������� ���� ����� �� �����, ���� ����� �� ���� � ����
		break;
	case Run:
		//� ��������� ���������� �� ������� �������� ����� � ��������� ����� �����
		running = true;
		//������������� �����-�� ����� �����

		break;
	}
}
