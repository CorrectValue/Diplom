#ifndef UInterface
#define UInterface

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

#include "Animal.h"
#include "human.h"

#include "enums.h"
using namespace sf;
using namespace std;
using namespace tgui;
//Определяет класс пользовательского интерфейса программы
class UI
{
public:
	//UI(int type);

	//публично объявляем переменные, в которые будут записаны данные из стартового окна
	static int count; //число существ
	static int hours; //часы от 0 до 23
	static int minutes; //минуты от 0 до 59, валидаторы уже есть
	static int season;
	static int weather;

	//конкретные методы загрузки разных окон
	//загрузка стартового окна
	static void drawStartWindow();
	//загрузка главного окна
	static void drawMainWindow(RenderWindow &window, vector<animal> &animals, vector<human> &humans, world &wrld);
	//загрузка окна загрузки
	static void drawLoadWindow();
	//загрузка окна сохранения
	static void drawSaveWindow();

	static void getData(EditBox::Ptr &ebCount, ComboBox::Ptr &cbSeason, ComboBox::Ptr &cbWeather, EditBox::Ptr &ebHours, EditBox::Ptr &ebMinutes, RenderWindow &window);
	static void makeRandom(RenderWindow &window);
};
#endif