#ifndef ITEM
#define ITEM

#include <SFML\Graphics.hpp>


using namespace sf;

//����� ��������
class item
{
public:
	float durability; //��������� ��������

	//�����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������

	//������� � ������������
	int x, y;

	//�������������
	bool consumable;

	//������������� - ����� �� �����������
	bool collidable;


	//��������� - ������� ��������� � ���������...

	void draw(int x, int y); //���������� ������ �������� ������ ������

};

#endif