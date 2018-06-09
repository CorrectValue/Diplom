#ifndef ENUMS
#define ENUMS
enum dayOfWeek
{
	Mon = 1,
	Tue,
	Wed,
	Thu,
	Fri,
	Sat,
	Sun
};

enum timeOfDay
{
	Morning,
	Day,
	Evening,
	Night
};

enum timeOfYear
{
	Summer,
	Fall,
	Winter,
	Spring
};

enum weather
{
	fallout, //������: ����� ���� ����
	cloudy,	//�������
	clear,	//����
	storm,	//����
	gray	//��������
};

enum month
{
	Jan = 1,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec
};

enum reservoir
{
	river,
	lake,
	ocean
};

enum items
{
	
};

enum creatures
{
	pig,
	sheep,
	horse,
};

enum humanz
{
	nigger,
	white,
	yellow
};

enum gender
{
	male,
	female,
	attackHelicopter
};

enum guiTypes
{
	startWindow,
	mainWindow,
	saveWindow,
	loadWindow
};

enum directions
{
	up,
	dright,
	down,
	dleft
};

struct cell
{
	int x;
	int y;
};

enum goals
{
	Sleep = 0,	//�������
	Eat,		//������
	Drink,		//����
	Run,		//�������
	Idle,		//����, ����������� ���������� ����
	Hide,		//��������� �� ����� ��� ����
	Rest		//�����
};

struct goal
{
	int Goal;
	int priority;
};

//enum items
//{};

#endif