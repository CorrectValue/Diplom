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
	//eeann ie?a


public:
	int curTimeOfDay; //oaeouaa a?aiy nooie a no?ieiaii oi?iaoa - niio?e enum
	int currentTimeHours; //?anu oaeouaai a?aiaie
	int currentTimeMinutes; //ieioou
	int currentTimeSeconds; //naeoiau
	int curWeather; //oaeouay iiaiaa - niio?e enum
	int season;
	int day; //aaiu ianyoa
	int month; //ianyo
	int year; //aia
	int dayOfWeek; //aaiu iaaaee?
	double curTemperature; //oaiia?aoo?a a ie?a - aainu eiaaa e i?eaiaeony

	float speed; //

	//a?aiy caeaoa e ?annaaoa ai a?aiy ceiiaai nieioanoiyiey
	int riseTimeWinterH, riseTimeWinterM, setTimeWinterH, setTimeWinterM;

	//a?aiy caeaoa e ?annaaoa ai a?aiy eaoiaai nieioanoiyiey
	int riseTimeSummerH, riseTimeSummerM, setTimeSummerH, setTimeSummerM;

	//a?aiy ?annaaoa e caeaoa (oaeouaa)
	int riseTimeM, setTimeM, riseTimeH, setTimeH; 

	int daysPastPeaque; //eiee?anoai aiae n iineaaiaai nieioanoiyiey
	int deltaMinutesRise;
	int deltaMinutesSet;
	int stepRise;
	int stepSet;
	int dayOfYear;
	int daysInMonth[12];

	int minutesPastMidnight, MinutesRiseTime, MinutesSetTime; //ieioo iinea iieoii?e
	
	int riseSetDuration; //i?iaie?eoaeuiinou oo?aiieo e aa?a?ieo noia?ae a ieiooao

	float stepRiseSetAlpha; //oaa oaaee?aiey/oiaiuoaiey aonoiou noia?ae

	bool minutePassed; //i?ioea ieiooa

	int blueAlphaColor; //i?ic?a?iinou ii?e

	int darkestAlpha; //i?ic?a?iinou ii?e a naiia o?iiia a?aiy

	Image mapImg;//ecia?a?aiea ea?ou

	sf::Texture mapTex;//oaenoo?a ea?ou

	Sprite mapSpr;

	String TileMap[height][width];


	void draw(RenderWindow& window);
	world(String tileset);

	void timeManipulation(float time); //aey anae niaiu a?aiaie: i?e?ino naeoia, ieioo, aiae, aiaia e oae aaeaa
	void weatherManipulation(); //iaieioeyoey iiaiaie
	void envManipulation(RenderWindow& window);
	void changeWeather();
	void update(RenderWindow& window, float time);
	void displayInfo(); //auaiaeo eioi?iaoe? i oaeouai iiei?aiee aauae
	int placeNineBlock(int x, int y, char c); //aaia?e?oao aeie 3o3 eeaoee caaaiiuo neiaieia

	void generateSimpleMap();

	void world::makePreGenMap();
	
	void generateMap(); //i?ioaao?iay aaia?aoey ea?ou
};

#endif