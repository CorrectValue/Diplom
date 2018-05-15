#ifndef INVENTORY
#define INVENTORY
#include "slot.h"
//определяет класс рюкзака
class Inventory
{
public:
	//рюкзак обладает фиксированной ёмкостью у всех персонажей
	//и представляет собой вектор слотов
	//ёмкость инвентаря
	int capacity;
	//вектор слотов
	std::vector<slot> slots;

	
	
};
#endif