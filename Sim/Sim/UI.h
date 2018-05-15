#ifndef UInterface
#define UInterface

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

#include "enums.h"
using namespace sf;
using namespace std;
using namespace tgui;
//Определяет класс пользовательского интерфейса программы
class UI
{
public:
	//UI(int type);

	//конкретные методы загрузки разных окон
	//загрузка стартового окна
	static void drawStartWindow();
	//загрузка главного окна
	static void drawMainWindow();
	//загрузка окна загрузки
	static void drawLoadWindow();
	//загрузка окна сохранения
	static void drawSaveWindow();
};
#endif