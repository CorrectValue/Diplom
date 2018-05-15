#ifndef CREATURE
#define CREATURE
#include <SFML/Graphics.hpp>

using namespace sf;

class Creature
{
public:
	float x, y, w, h, dx, dy, speed;
	int dir; //����������� ��������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������

	float satiety; //�������, ����� 100 - ���, 0 - �������
	float thirst; //������� �����, 100 - �� ��, 0 - �������� �� �����
	float stamina; //����� ���, 100 - ���� ��������, 0 - ��� ��� ���
	float hp; //��������, ����� 100 - ������ ��� ���, 0 - ����

	static int meanLifeTime; //������� ����� ����� ����������� ���� �������
	int estLifeTime; //�������������� ����� �����. �� ��������� - ������.
	int age; //������� ������� ��������

	
	Creature(); 
};


#endif