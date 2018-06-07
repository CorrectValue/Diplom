#include "Animal.h"

using namespace sf;
using namespace std;

int animal::globalID = 0;


animal::animal()
{
	//�������� id
	id = globalID;
	//��������� ���������� ��
	globalID++;

	//������ �������� ���������
	satiety = 100;
	thirst = 100;
	stamina = 100;
	hp = 100;

	w = 16;
	h = 16;
	//��������� ����� �����
	estLifeTime = meanLifeTime / 2 + rand() % meanLifeTime;
	//���������, ������ ��� ��������, �������� ��������������� ��� ������
	respawnPause = 0;
	currentPause = 0;

	running = false;

	//������ �����. ��������� � ��� �� ��������� ���� ������ ������, ����� � ���� ����
	tileset = "Images/CreatureTilesets/Animal/pig.png";
	image.loadFromFile(tileset);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));

	//�������� ��������
	speed = 0.2;
	runningSpeed = 0.3;

	dir = rand() % 4;

	//������� � ����
	cell tmp = validCells[rand() % validCells.size()];
	x = tmp.x;
	y = tmp.y;
	sprite.setPosition(x*w, y*h);
}

