#ifndef CREATURE
#define CREATURE
#include <SFML/Graphics.hpp>
#include "enums.h"

using namespace sf;

class Creature
{
private:
	static int globalID;
public:
	
	const int meanLifeTime = 13; //������� ����� ����� ����������� ���� ������� � �����
	
	float x, y, w, h, dx, dy, speed, runningSpeed;
	int dir; //����������� ��������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������
	String tileset; //������, � ������� ����� �������
	int id;
	bool alive; //���� �� ��������

	int respawnTimer; //��� �������� �������, ������ ������� ����� ��� ���������

	float satiety; //�������, ����� 100 - ���, 0 - �������
	float thirst; //������� �����, 100 - �� ��, 0 - �������� �� �����
	float stamina; //����� ���, 100 - ���� ��������, 0 - ��� ��� ���
	float hp; //��������, ����� 100 - ������ ��� ���, 0 - ����

	
	int estLifeTime; //�������������� ����� �����. �� ��������� - ������.
	int age; //������� ������� ��������


	
	Creature(); 
	void update(float time);
	void respawn();
};


#endif