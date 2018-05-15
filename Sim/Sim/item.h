#ifndef ITEM
#define ITEM

#include <SFML\Graphics.hpp>


using namespace sf;

//класс предмета
class item
{
public:
	float durability; //прочность предмета

	//отображение
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт

	//позиция в пространстве
	int x, y;

	//поглощаемость
	bool consumable;

	//проницаемость - можно ли столкнуться
	bool collidable;


	//обработка - предмет находится в инвентаре...

	void draw(int x, int y); //отрисовать спрайт предмета поверх клетки

};

#endif