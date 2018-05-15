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
	//класс мира


public:
	int curTimeOfDay; //текущее время суток в строковом формате - смотри enum
	int currentTimeHours; //часы текущего времени
	int currentTimeMinutes; //минуты
	int currentTimeSeconds; //секунды
	int curWeather; //текущая погода - смотри enum
	int season;
	int day; //день месяца
	int month; //месяц
	int year; //год
	int dayOfWeek; //день недели?
	double curTemperature; //температура в мире - авось когда и пригодится

	float speed; //

	//время заката и рассвета во время зимнего солнцестояния
	int riseTimeWinterH, riseTimeWinterM, setTimeWinterH, setTimeWinterM;

	//время заката и рассвета во время летнего солнцестояния
	int riseTimeSummerH, riseTimeSummerM, setTimeSummerH, setTimeSummerM;

	//время рассвета и заката (текущее)
	int riseTimeM, setTimeM, riseTimeH, setTimeH; 

	int daysPastPeaque; //количество дней с последнего солнцестояния
	int deltaMinutesRise;
	int deltaMinutesSet;
	int stepRise;
	int stepSet;
	int dayOfYear;
	int daysInMonth[12];

	int minutesPastMidnight, MinutesRiseTime, MinutesSetTime; //минут после полуночи
	
	int riseSetDuration; //продолжительность утренних и вечерних сумерек в минутах

	float stepRiseSetAlpha; //шаг увеличения/уменьшения густоты сумерек

	bool minutePassed; //прошла минута

	int blueAlphaColor; //прозрачность ночи

	int darkestAlpha; //прозрачность ночи в самое тёмное время

	Image mapImg;//изображение карты

	sf::Texture mapTex;//текстура карты

	Sprite mapSpr;

	String TileMap[height][width];


	void draw(RenderWindow& window);
	world(String tileset);

	void timeManipulation(float time); //для всей смены времени: прирост секунд, минут, дней, годов и так далее
	void weatherManipulation(); //манипуляция погодой
	void envManipulation(RenderWindow& window);
	void changeWeather();
	void update(RenderWindow& window, float time);
	void displayInfo(); //выводит информацию о текущем положении вещей
	int placeNineBlock(int x, int y, char c); //генерирует блок 3х3 клетки заданных символов

	void generateSimpleMap();

	void world::makePreGenMap();
	
	void generateMap(); //процедурная генерация карты
};

#endif
