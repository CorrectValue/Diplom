#ifndef INVENTORY
#define INVENTORY
#include "slot.h"
//���������� ����� �������
class Inventory
{
public:
	//������ �������� ������������� �������� � ���� ����������
	//� ������������ ����� ������ ������
	//������� ���������
	int capacity;
	//������ ������
	std::vector<slot> slots;

	
	
};
#endif