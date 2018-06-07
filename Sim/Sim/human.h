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
	static int globalID; //��������� ����� id, �� �������� ��������� ��� ���� ��������
	const int meanLifeTime = 70;
public:
	//������ - ��, ��� �������� �������� �� ���������
	int strength; //1 - ������, 10 - ������
	int intelligence; //1 - �����, 10 - ��������
	int endurance; //1 - ������ �������, 10 - ������� ����
	int agility; //1 - ��������, 10 - ����� ����
	
	int id; //�������������

	int gender; //���

	//��� ����� ������ �����
	bool hasWeapon;


	
	String name;
	String lastName;
	
	static vector<String> maleNames; //��������� ��� ������ ����� 
	static vector<String> femaleNames; //��������� ��� ������ �����
	static vector<String> lastNames; //��������� �������
	static vector<String> maleAppearances; //������ ��������� ��� ����������, ������� ������
	static vector<String> femaleAppearances; // ��� ������

	
	void generateName(); //���������� ��� ���������
	void generateDeathDate();//���������� ���� ������ ���������
	static void prepareNames();//������������� ������� ������ ��� � �������
	static void prepareAppearances(); //�������� ������� ������ �������


	human();

};

#endif