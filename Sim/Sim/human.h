#ifndef HUMAN
#define HUMAN
#include "Creature.h"
//����� �������� - ��������� ����� ��������
class human : public Creature
{
public:
	//������ - ��, ��� �������� �������� �� ���������
	int strength; //1 - ������, 10 - ������
	int intelligence; //1 - �����, 10 - ��������

	int approximateLifeTime; // ����������������� ����� �����
	char name[15];
	char lastName[20];
	//�����������!

};

#endif