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
public:
	//������ - ��, ��� �������� �������� �� ���������
	int strength; //1 - ������, 10 - ������
	int intelligence; //1 - �����, 10 - ��������
	
	int gender; //���
	int meanLifeTime; //������� ����������������� �����

	int approximateLifeTime; // ����������������� ����� �����
	String name;
	String lastName;
	
	static vector<String> maleNames; //��������� ��� ������ ����� 
	static vector<String> femaleNames; //��������� ��� ������ �����
	static vector<String> lastNames; //��������� �������

	
	void generateName(); //���������� ��� ���������
	void generateDeathDate();//���������� ���� ������ ���������
	static void prepareNames();//������������� ������� ������ ��� � �������


	human();

};

#endif