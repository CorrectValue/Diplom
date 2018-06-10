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
//���������� ����� ����������������� ���������� ���������
class UI
{
public:
	//UI(int type);

	//�������� ��������� ����������, � ������� ����� �������� ������ �� ���������� ����
	static int count; //����� �������
	static int hours; //���� �� 0 �� 23
	static int minutes; //������ �� 0 �� 59, ���������� ��� ����
	static int season;
	static int weather;

	//���������� ������ �������� ������ ����
	//�������� ���������� ����
	static void drawStartWindow();
	//�������� �������� ����
	static void drawMainWindow(RenderWindow &window, vector<animal> &animals, vector<human> &humans, world &wrld);
	//�������� ���� ��������
	static void drawLoadWindow();
	//�������� ���� ����������
	static void drawSaveWindow();

	static void getData(EditBox::Ptr &ebCount, ComboBox::Ptr &cbSeason, ComboBox::Ptr &cbWeather, EditBox::Ptr &ebHours, EditBox::Ptr &ebMinutes, RenderWindow &window);
	static void makeRandom(RenderWindow &window);
};
#endif