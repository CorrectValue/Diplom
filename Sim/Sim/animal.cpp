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
	hidden = false;
	tookDamage = false;

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

	currentGoal = availibleGoals[Idle];

	//��������� ����� ����������
	dest.x = -1;
	dest.y = -1;

	//������� � ����
	cell tmp = validCells[rand() % validCells.size()];
	X = tmp.x;
	Y = tmp.y;
	x = X*w;
	y = Y*h;
	sprite.setPosition(x, y);
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

	ss << id << "_hp=" << curHp << "_st=" << curStamina;
	switch (currentGoal.Goal)
	{
	case Eat:
		ss << "_Eat";
		break;
	case Sleep:
		ss << "_Sleep";
		break;
	case Run:
		ss << "_Run";
		break;
	case Idle:
		ss << "_Idle";
		break;
	case Rest:
		ss << "_Rest";
		break;
	case Hide:
		ss << "_Hide";
		break;
	case Drink:
		ss << "_Drink";
		break;
	}
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

void animal::actionPlanner(world &wrld)
{
	//��������� ��������������� ��������, ������������ �� ���������� ����
	switch (currentGoal.Goal)
	{
	case Sleep:
		//�������� ����� ����� ��� ������, ����������� ������������
		currentSpeed = 0;
		sleeping = true;
		break;
	case Eat:
		//�������� �������� �������� � ������� � �������� � ������
		sleeping = false;
		searchFor(wrld.TileMap, Food);
		for (int i = X - 1; i < X + 1 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 1; j < Y + 1 && j > -1 && j < mapH; j++)
			{
				if (wrld.TileMap[j][j] == 'T' || wrld.TileMap[j][j] == 'B')
				{
					//����� � ������� ������� ���� ���, ���
					eat();
				}
			}
		}
		break;
	case Drink:
		//���� ����� � ����
		sleeping = false;
		searchFor(wrld.TileMap, Water);
		for (int i = X - 1; i < X + 1 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 1; j < Y + 1 && j > -1 && j < mapH; j++)
			{
				if (wrld.TileMap[j][j] == 'v')
				{
					//����� � ������� ������� ���� ����, ����
					drink();
				}
			}
		}
		break;
	case Idle:
		//���� ���� - ����������, �� �������� ���� ����� �� �����, ���� ����� �� ���� � ����
		sleeping = false;
		if (dest.x == -1)
		{
			int randNum = rand() % 100;
			if (randNum > 79)
			{
				//����� �� �����
				currentSpeed = 0;
			}
			else
			{
				//��� ����-������
				dest = validCells[rand() % validCells.size()];
			}
		}
		else
			moveTo(dest.x, dest.y);
		break;
	case Hide:
		//���� ���� - ��������, �� ���� ������� � �������!
		sleeping = false;
		searchFor(wrld.TileMap, Cover);
		break;
	case Run:
		//� ��������� ���������� �� ������� �������� ����� � ��������� ����� �����
		sleeping = false;
		running = true;
		//������������� �����-�� ����� �����
		if (dest.x == -1)
		{
			//������� ����� �����, ���� ������� ��� �� �������������
			dest = validCells[rand() % validCells.size()];
		}
		//��������� � ��
		moveTo(dest.x, dest.y);
		break;
	}
}

void animal::eat()
{
	//��� ��� ������ ���������� ������� �������
	satiety += 50;
}

void animal::drink()
{
	//� ��������� ������ ��� ����� ����� ���������
	thirst += 40;
}
