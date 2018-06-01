#ifndef CREATURE
#define CREATURE
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "world.h"

using namespace sf;
using namespace std;

class Creature
{
private:
	static int globalID;
public:
	
	static vector<cell> validCells; //��������� ��� �������� ������

	const int meanLifeTime = 13; //������� ����� ����� ����������� ���� ������� � �����
	
	float x, y, w, h, dx, dy, speed, runningSpeed;
	int dir; //����������� ��������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������
	String tileset; //������, � ������� ����� �������
	int id;
	bool alive; //���� �� ��������

	float respawnPause; //��� �������� �������, ������ ������� ����� ��� ���������
	float currentPause; //������� ����� �� �������� ��������

	float satiety; //�������, ����� 100 - ���, 0 - �������
	float thirst; //������� �����, 100 - �� ��, 0 - �������� �� �����
	float stamina; //����� ���, 100 - ���� ��������, 0 - ��� ��� ���
	float hp; //��������, ����� 100 - ������ ��� ���, 0 - ����

	
	int estLifeTime; //�������������� ����� �����. �� ��������� - ������.
	int age; //������� ������� ��������

	bool running; //����� �� ��������

	
	
	Creature(); 
	void update(float time);
	void respawn();
	void die(); //������ �������� �� ������������ ��� �� ����� ������������ ��������
	static void prepareValidCellsList(world wrld); //����������� ������ ������, � ������� ����� ������������
	void mapInteraction(world wrld);
};


#endif