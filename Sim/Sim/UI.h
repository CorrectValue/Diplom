#ifndef UInterface
#define UInterface

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

#include "enums.h"
using namespace sf;
using namespace std;
using namespace tgui;
//���������� ����� ����������������� ���������� ���������
class UI
{
public:
	//UI(int type);

	//���������� ������ �������� ������ ����
	//�������� ���������� ����
	static void drawStartWindow();
	//�������� �������� ����
	static void drawMainWindow();
	//�������� ���� ��������
	static void drawLoadWindow();
	//�������� ���� ����������
	static void drawSaveWindow();
};
#endif