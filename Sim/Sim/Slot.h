#ifndef SLOT
#define SLOT

//Класс слота в инвентаре персонажа
#include "item.h"
class slot
{
	//
	//как много экземпляров объекта находится в слоте
	int amount;
	//что конкретно лежит в слоте
	item &Item;

};
#endif