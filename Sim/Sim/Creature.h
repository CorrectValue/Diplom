#ifndef CREATURE
#define CREATURE
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "world.h"
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

const int mapH = 48;
const int mapW = 64;

class Creature
{
private:
	static int globalID;
public:
	
	static vector<cell> validCells; //��������� ��� �������� ������

	float x, y, w, h, dx, dy, currentSpeed, speed, runningSpeed;
	int X, Y; //���������� � ������������ �����
	int dir; //����������� ��������
	Image image;//���� �����������
	sf::Texture texture;//���� ��������
	Sprite sprite;//���� ������
	String tileset; //������, � ������� ����� �������
	int id;
	bool alive; //���� �� ��������
	bool sleeping; //���� ��� ����������

	cell dest; //����� ���������� ��������


	goal currentGoal; //������� ����

	float respawnPause; //��� �������� �������, ������ ������� ����� ��� ���������
	float currentPause; //������� ����� �� �������� ��������

	float satiety; //�������, ����� 100 - ���, 0 - �������
	float thirst; //������� �����, 100 - �� ��, 0 - �������� �� �����
	float maxStamina, curStamina; //����� ���, 100 - ���� ��������, 0 - ��� ��� ���
	float maxHp, curHp; //��������, ����� 100 - ������ ��� ���, 0 - ����

	
	int estLifeTime; //�������������� ����� �����. �� ��������� - ������.
	int age; //������� ������� ��������

	bool running; //����� �� ��������
	bool tookDamage; //������� ���� �� ������� ��������
	bool hidden; //���������

	Creature(); 
	void update(float time, world &wrld);
	void respawn();
	void die(); //������ �������� �� ������������ ��� �� ����� ������������ ��������
	static void prepareValidCellsList(world &wrld); //����������� ������ ������, � ������� ����� ������������
	void mapInteraction(world wrld);
	void checkDeathDate();
	void generateDeathDate();//���������� ���� ������ ���������
	virtual void goalPlanner(int &time, int &weather); //����������� �����
	virtual void actionPlanner(world &wrld);
	void moveTo(int X, int Y);
	void searchFor(String map[][mapW], int thing);

	virtual void eat();
	virtual void drink();

	//void operator=(const Creature &other);
};


#endif