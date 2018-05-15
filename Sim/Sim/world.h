#ifndef WORLD
#define WORLD
#include <cstdlib>
#include <ctime>
#include "enums.h"
#include <SFML\Graphics.hpp>



using namespace sf;

const int width = 64;
const int height = 48;

class world
{
	//����� ����


public:
	int curTimeOfDay; //������� ����� ����� � ��������� ������� - ������ enum
	int currentTimeHours; //���� �������� �������
	int currentTimeMinutes; //������
	int currentTimeSeconds; //�������
	int curWeather; //������� ������ - ������ enum
	int season;
	int day; //���� ������
	int month; //�����
	int year; //���
	int dayOfWeek; //���� ������?
	double curTemperature; //����������� � ���� - ����� ����� � ����������

	float speed; //

	//����� ������ � �������� �� ����� ������� �������������
	int riseTimeWinterH, riseTimeWinterM, setTimeWinterH, setTimeWinterM;

	//����� ������ � �������� �� ����� ������� �������������
	int riseTimeSummerH, riseTimeSummerM, setTimeSummerH, setTimeSummerM;

	//����� �������� � ������ (�������)
	int riseTimeM, setTimeM, riseTimeH, setTimeH; 

	int daysPastPeaque; //���������� ���� � ���������� �������������
	int deltaMinutesRise;
	int deltaMinutesSet;
	int stepRise;
	int stepSet;
	int dayOfYear;
	int daysInMonth[12];

	int minutesPastMidnight, MinutesRiseTime, MinutesSetTime; //����� ����� ��������
	
	int riseSetDuration; //����������������� �������� � �������� ������� � �������

	float stepRiseSetAlpha; //��� ����������/���������� ������� �������

	bool minutePassed; //������ ������

	int blueAlphaColor; //������������ ����

	int darkestAlpha; //������������ ���� � ����� ����� �����

	Image mapImg;//����������� �����

	sf::Texture mapTex;//�������� �����

	Sprite mapSpr;

	String TileMap[height][width];


	void draw(RenderWindow& window);
	world(String tileset);

	void timeManipulation(float time); //��� ���� ����� �������: ������� ������, �����, ����, ����� � ��� �����
	void weatherManipulation(); //����������� �������
	void envManipulation(RenderWindow& window);
	void changeWeather();
	void update(RenderWindow& window, float time);
	void displayInfo(); //������� ���������� � ������� ��������� �����
	int placeNineBlock(int x, int y, char c); //���������� ���� 3�3 ������ �������� ��������

	void generateSimpleMap();

	void world::makePreGenMap();
	
	void generateMap(); //����������� ��������� �����
};

#endif
