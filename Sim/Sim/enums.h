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
	fallout, //осадки: дождь либо снег
	cloudy,	//облачно
	clear,	//ясно
	storm,	//буря
	gray	//пасмурно
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
	Sleep = 0,	//поспать
	Eat,		//поесть
	Drink,		//пить
	Run,		//убегать
	Idle,		//лень, фактическое отсутствие цели
	Hide,		//прятаться от дождя или бури
	Rest		//отдых
};

struct goal
{
	int Goal;
	int priority;
};

//enum items
//{};

#endif