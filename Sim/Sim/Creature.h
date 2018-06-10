#ifndef CREATURE
#define CREATURE
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "world.h"
#include <sstream>

using namespace sf;
using namespace std;

class Creature
{
private:
	static int globalID;
public:
	
	static vector<cell> validCells; //��������� ��� �������� ������

	float x, y, w, h, dx, dy, currentSpeed, speed, runningSpeed;
	int dir; //����������� ��������
	Image image;//���� �����������
	sf::Texture texture;//���� ��������
	Sprite sprite;//���� ������
	String tileset; //������, � ������� ����� �������
	int id;
	bool alive; //���� �� ��������

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

	Creature(); 
	void update(float time, world &wrld);
	void respawn();
	void die(); //������ �������� �� ������������ ��� �� ����� ������������ ��������
	static void prepareValidCellsList(world &wrld); //����������� ������ ������, � ������� ����� ������������
	void mapInteraction(world wrld);
	void checkDeathDate();
	void generateDeathDate();//���������� ���� ������ ���������
	void goalPlanner(int &time, int &weather); //����������� �����
	void moveTo(int X, int Y);
	void searchFor(String map);

	//void operator=(const Creature &other);
};


#endif