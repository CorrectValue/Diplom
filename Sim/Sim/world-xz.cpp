#include "world.h"

void world::timeManipulation(float time)
{
	//��������� �������� � ����
	//��� ���

	//�������� �����, ��������� � ������� ���������� ����������, ���� �����-�� ������� ���������� ��� � ����������
	//� ������ �������� ������� �������
	currentTimeSeconds += time * speed; //�������� ������-�� �� ��������, ��� ���� �����

	//�������� �� ������
	if (currentTimeSeconds > 59)
	{
		currentTimeMinutes += 1;
		currentTimeSeconds -= 60;
		minutePassed = true;
	}

	//�������� �� ���
	if (currentTimeMinutes > 59)
	{
		currentTimeHours += 1;
		currentTimeMinutes -= 60;
	}

	//�������� �� ����
	if (currentTimeHours > 23)
	{
		day += 1;
		currentTimeHours = 0;
		dayOfWeek++;
		dayOfYear++;
		//��������������� ������� ������ � ��������
		if (dayOfYear < 174 || dayOfYear > 357)
		{
			//�������� ���������
			MinutesRiseTime -= stepRise;
			MinutesSetTime += stepSet;
		}

		if (dayOfYear == 174)
		{
			//������ �������������
			MinutesRiseTime = riseTimeSummerH * 60 + riseTimeSummerM;
			MinutesSetTime = setTimeSummerH * 60 + setTimeSummerM;
		}

		if (dayOfYear > 174 && dayOfYear < 357)
		{
			//������� ���������
			MinutesRiseTime += stepRise;
			MinutesSetTime -= stepSet;
		}

		if (dayOfYear == 357)
		{
			//������ �������������
			MinutesRiseTime = riseTimeWinterH * 60 + riseTimeWinterM;
			MinutesSetTime = setTimeWinterH * 60 + setTimeWinterM;
		}
	}

	//�������� ���� ������
	if (dayOfWeek > 7)
		dayOfWeek = 1;

	//�������� ������

	

	//������ ����� �� ��� ����
	if (day > daysInMonth[month-1])
	{
		day = 1;
		month++;
	}

	//�������� ���
	if (month > 12)
	{
		month = 1;
		year++;
	}

	//��������������� ������
	if (month > 2 && month < 6)
		season = Spring;
	if (month > 5 && month < 9)
		season = Summer;
	if (month > 8 && month < 12)
		season = Fall;
	if (month == 12 || month < 3)
		season = Winter;

	//��������������� ������� �����
	if (currentTimeHours > 22 || currentTimeHours < 5)
		curTimeOfDay = Night;
	if (currentTimeHours > 4 && currentTimeHours < 11)
		curTimeOfDay = Morning;
	if (currentTimeHours > 10 && currentTimeHours < 17)
		curTimeOfDay = Day;
	if (currentTimeHours > 16 && currentTimeHours < 23)
		curTimeOfDay = Evening;
}

void world::weatherManipulation()
{
	//��������� ������� � ����

}

void world::changeWeather()
{
	//���� ������ ������! ������ �����
	srand(time(0));
	//�����, �� ���� �� �������� ������� ����� ���� ���������� ������� �� ��� ���������
}

world::world(String tileset)
{
	//����������� �� ��������� ����� ������ ��� ������, � ���������� ����� ����������� �������������������

	generateSimpleMap();
	//makePreGenMap();

	mapImg.loadFromFile(tileset);

	mapTex.loadFromImage(mapImg);

	mapSpr.setTexture(mapTex);

	minutePassed = false;

	//���������� ������ ������ � �� ����� ������
	//������ ������ ������� ����! ����, �����!
	year = 1;
	month = Jan;
	day = 1;
	dayOfWeek = Mon;
	season = Winter;
	//
	curWeather = clear;
	//�������� ������
	//����� ���� �����, ����� ����� 
	currentTimeHours = 12;
	currentTimeMinutes = 0;
	currentTimeSeconds = 0;

	speed = 60; //��� ������ ����� ��� �������

	//22 ������� � ��� ������ ������������� - ����� ������� ���� � ����� �������� ����.
	// ������ 22 ������� - 7:55
	// ����� 22 ������� - 16:07
	riseTimeWinterH = 7;
	riseTimeWinterM = 55;
	setTimeWinterH = 16;
	setTimeWinterM = 7;
	//22 ���� - ������ �������������
	// ������ 22 ���� - 3:59
	// ����� 22 ���� - 20:10
	riseTimeSummerH = 3;
	riseTimeSummerM = 59;
	setTimeSummerH = 20;
	setTimeSummerM = 10;

	deltaMinutesSet = setTimeSummerH * 60 + setTimeSummerM - setTimeSummerH * 60 - setTimeWinterM;
	deltaMinutesRise = riseTimeWinterH * 60 + riseTimeWinterM - riseTimeSummerH * 60 - riseTimeSummerM;

	stepRise = deltaMinutesRise / 183;
	stepSet = deltaMinutesSet / 183;
	daysInMonth[0] = 31;
	daysInMonth[1] = 29;
	daysInMonth[2] = 31;
	daysInMonth[3] = 30;
	daysInMonth[4] = 31;
	daysInMonth[5] = 30;
	daysInMonth[6] = 31;
	daysInMonth[7] = 31;
	daysInMonth[8] = 30;
	daysInMonth[9] = 31;
	daysInMonth[10] = 30;
	daysInMonth[11] = 31;

	//��������� ���� ����
	dayOfYear = 0;
	for (int i = 1; i < month; i++)
	{
		dayOfYear += daysInMonth[i - 1];
	}
	dayOfYear += day;

	//���������� ����� �������� � ������ � ���� ����
	if (dayOfYear < 174 || dayOfYear > 357)
	{
		//�������� ���������
		MinutesRiseTime = riseTimeWinterH * 60 + riseTimeWinterM;
		MinutesSetTime = setTimeWinterH * 60 + setTimeWinterM;
		MinutesRiseTime -= stepRise * (dayOfYear + 10);
		MinutesSetTime += stepSet * (dayOfYear + 10);
	}

	if (dayOfYear == 174)
	{
		//������ �������������
		MinutesRiseTime = riseTimeSummerH * 60 + riseTimeSummerM;
		MinutesSetTime = setTimeSummerH * 60 + setTimeSummerM;
	}

	if (dayOfYear > 174 && dayOfYear < 357)
	{
		//������� ���������
		MinutesRiseTime = riseTimeSummerH * 60 + riseTimeSummerM;
		MinutesSetTime = setTimeSummerH * 60 + setTimeSummerM;
		MinutesRiseTime += stepRise * (dayOfYear - 174);
		MinutesSetTime -= stepSet * (dayOfYear - 174);
	}

	if (dayOfYear == 357)
	{
		//������ �������������
		MinutesRiseTime = riseTimeWinterH * 60 + riseTimeWinterM;
		MinutesSetTime = setTimeWinterH * 60 + setTimeWinterM;
	}

	//������� ����������������� �������
	//������� �� ������
	riseSetDuration = 37; //�������� � �������

	darkestAlpha = 170;

	stepRiseSetAlpha = darkestAlpha / riseSetDuration;

	//���������� ������������� ������� � ������ ������ ���������
	//��� � ����� �� ����������, ���������� ������ �������
	minutesPastMidnight = currentTimeHours * 60 + currentTimeMinutes;

	if (minutesPastMidnight > MinutesSetTime - riseSetDuration && minutesPastMidnight < MinutesSetTime)
	{
		//�������� �������
		blueAlphaColor = stepRiseSetAlpha * (minutesPastMidnight - MinutesSetTime);
	}

	if (minutesPastMidnight > MinutesRiseTime - riseSetDuration && minutesPastMidnight < MinutesRiseTime)
	{
		//���������� �������. � ������ ������� ����� ������ ������ �����������
		blueAlphaColor = stepRiseSetAlpha * (minutesPastMidnight - MinutesRiseTime);
	}

}

void world::envManipulation(RenderWindow& window)
{
	//��������� ����������
	//��������� ���������� ��������� � ������� � ������ �����
	//�������� �������
	RectangleShape overlayBlue, overlayYellow; //����� - ��� ����, ����� - ��� ������ � ��������
	overlayBlue.setPosition(0, 0);
	Vector2f size;
	
	//����: ��� � ���, ���� ��� �������������. ��������������, �������� ����������������� ��� � ����, ��� ���-��, ����!
	//22 ������� � ��� ������ ������������� - ����� ������� ���� � ����� �������� ����.
	// ������ 22 ������� - 7:55
	// ����� 22 ������� - 16:07
	//22 ���� - ������ �������������
	// ������ 22 ���� - 3:59
	// ����� 22 ���� - 20:10
	//��������������, �������� ������ ��� ���������...

	size.x = window.getSize().x;
	size.y = window.getSize().y;
	overlayBlue.setSize(size);
	overlayYellow.setSize(size);

	minutesPastMidnight = currentTimeHours * 60 + currentTimeMinutes;
	

	//������ ��������� �������� ����� � ����������� �� ������� ����� %)
	//���� - ������������ ����� � ������ � ������� � ������
	if (minutesPastMidnight > MinutesSetTime - riseSetDuration && minutesPastMidnight < MinutesSetTime)
	{
		//�������� �������. � ������ ������� ����� ������ ������ �������������
		if (minutePassed)
		{
			blueAlphaColor += stepRiseSetAlpha;
			minutePassed = false;
		}
	}
	else if (minutesPastMidnight > MinutesRiseTime - riseSetDuration && minutesPastMidnight < MinutesRiseTime)
	{
		//���������� �������. � ������ ������� ����� ������ ������ �����������
		if (minutePassed)
		{
			blueAlphaColor -= stepRiseSetAlpha;
			minutePassed = false;
		}
	}
	else if (minutesPastMidnight > MinutesSetTime || minutesPastMidnight < MinutesRiseTime)
	{
		blueAlphaColor = darkestAlpha;
	}

	else if (minutesPastMidnight > MinutesRiseTime && minutesPastMidnight < MinutesSetTime)
	{
		blueAlphaColor = 0;
	}
	overlayBlue.setFillColor(Color(0, 0, 55, blueAlphaColor)); 
	//overlayYellow.setFillColor(Color(255, 232, 75, yellowAlphaColor));
	window.draw(overlayBlue);
	//window.draw(overlayYellow);
	
}

void world::update(RenderWindow& window, float time)
{
	//�� ���� ������ ��������� �����

	
}

void world::draw(RenderWindow& window)
{
	window.clear();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//��� ��������� ������ �����: ���� ������ ����
			if (TileMap[i][j] == ' ')
				//�����
				mapSpr.setTextureRect(IntRect(32, 0, 16, 16));
			if (TileMap[i][j] == 'r')
				//��������
				mapSpr.setTextureRect(IntRect(16, 0, 16, 16));
			if (TileMap[i][j] == 'c')
				//������
				mapSpr.setTextureRect(IntRect(16, 16, 16, 16));
			if (TileMap[i][j] == 'w')
				//���������
				mapSpr.setTextureRect(IntRect(32, 16, 16, 16));
			if (TileMap[i][j] == 'v')
				//����
				mapSpr.setTextureRect(IntRect(0, 16, 16, 16));
			if (TileMap[i][j] == 'd')
				//�����
				mapSpr.setTextureRect(IntRect(0, 0, 16, 16));
			if (TileMap[i][j] == 'i')
				//����� ������������
				mapSpr.setTextureRect(IntRect(48, 0, 16, 16));
			if (TileMap[i][j] == '-')
				//����� ��������������
				mapSpr.setTextureRect(IntRect(64, 16, 16, 16));
			if (TileMap[i][j] == 'J')
				//���� ������ ������
				mapSpr.setTextureRect(IntRect(80, 16, 16, 16));
			if (TileMap[i][j] == 'L')
				//���� ����� ������
				mapSpr.setTextureRect(IntRect(48, 16, 16, 16));
			if (TileMap[i][j] == '?')
				//���� ������ �������
				mapSpr.setTextureRect(IntRect(80, 0, 16, 16));
			if (TileMap[i][j] == '!')
				//���� ����� �������
				mapSpr.setTextureRect(IntRect(64, 0, 16, 16));
			if (TileMap[i][j] == '/')
				//�������� �����
				mapSpr.setTextureRect(IntRect(112, 16, 16, 16));
			if (TileMap[i][j] == '\\')
				//�������� ������
				mapSpr.setTextureRect(IntRect(96, 0, 16, 16));
			if (TileMap[i][j] == '_')
				//�������� ������
				mapSpr.setTextureRect(IntRect(96, 16, 16, 16));
			if (TileMap[i][j] == '=')
				//�������� �������
				mapSpr.setTextureRect(IntRect(112, 0, 16, 16));
			if (TileMap[i][j] == 'q')
				//���� ����� �������
				mapSpr.setTextureRect(IntRect(128, 32, 16, 16));
			if (TileMap[i][j] == ']')
				//���� ������ �������
				mapSpr.setTextureRect(IntRect(128, 16, 16, 16));
			if (TileMap[i][j] == 'z')
				//���� ����� ������
				mapSpr.setTextureRect(IntRect(128, 0, 16, 16));
			if (TileMap[i][j] == '.')
				//���� ������ ������
				mapSpr.setTextureRect(IntRect(112, 32, 16, 16));

			mapSpr.setPosition(j * 16, i * 16);
			window.draw(mapSpr);
		}
	}
}

void world::displayInfo()
{
	// ���� ������� � �������
	//������ ������� ��������� �������
	system("cls");
	printf("====================================================\n");
	printf("Today is ");
	switch (dayOfWeek)
	{
	case Mon:
		printf("Mon");
		break;
	case Tue:
		printf("Tue");
		break;
	case Wed:
		printf("Wed");
		break;
	case Thu:
		printf("Thu");
		break;
	case Fri:
		printf("Fri");
		break;
	case Sat:
		printf("Sat");
		break;
	case Sun:
		printf("Sun");
		break;
	}
	printf(", %d ", day);
	switch (month)
	{
	case Jan:
		printf("Jan ");
		break;
	case Feb:
		printf("Feb ");
		break;
	case Mar:
		printf("Mar ");
		break;
	case Apr:
		printf("Apr ");
		break;
	case May:
		printf("May ");
		break;
	case Jun:
		printf("Jun ");
		break;
	case Jul:
		printf("Jul ");
		break;
	case Aug:
		printf("Aug ");
		break;
	case Sep:
		printf("Sep ");
		break;
	case Oct:
		printf("Oct ");
		break;
	case Nov:
		printf("Nov ");
		break;
	case Dec:
		printf("Dec ");
		break;
	}
	printf("%d\n", year);
	printf("The weather is ");
	switch (curWeather)
	{
	case clear:
		printf("clear");
		break;
	case fallout:
		printf("fallout");
		break;
	case storm:
		printf("storm");
		break;
	case cloudy:
		printf("cloudy");
		break;
	case gray:
		printf("gray");
		break;
	}
	printf("\n");
	
	printf("\t%d:", currentTimeHours);
	if (currentTimeMinutes < 10)
		printf("0");
	printf("%d", currentTimeMinutes);
}

//������� �� ����� ������������ � ������ ���������� ��������� ������
void world::generateMap()
{
	//������������ ����������� ��������� �����
	//������ ��� ������!
	srand(time(0));
	int reservoirType = rand() % 3;
	reservoirType = 2; // ��������� �����
	//������ �������� ����� "������������" �������
	//���� ����� - �����, �� �������
	if (reservoirType != ocean)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				TileMap[i][j] = ' ';
			}
		}
		//����� ������ ������� - ����� ��������?? ����? ��������? ������ ���� �� ������� ��������
		for (int i = 0; i < width; i++)
		{
			TileMap[0][i] = 'a'; // �� abyss - ��������. �������� ����������
			TileMap[height - 1][i] = 'a';
		}
		for (int i = 0; i < height; i++)
		{
			TileMap[i][0] = 'e'; //������ �� ������������ �, "������� ��������"
			TileMap[i][width - 1] = 'e';
		}
		//����
		TileMap[0][0] = '1'; //����� �������
		TileMap[0][width - 1] = '2'; // ������ �������
		TileMap[height - 1][0] = '3'; //����� ������
		TileMap[height - 1][width - 1] = '4'; //������ ������
	}

	//���������� ����. ����������� ������ ���� �������, ������ � ����
	int nextSpot;//���������� �����
	switch (reservoirType)
	{
	case river:
		break;
	case lake:
		//���������� ������ � �������, �� ��������
		break;
	case ocean:
		//����� �������� ������: ������� ������ � ������!
		//�������� ����� �����
		for (int i = 1; i < height - 1; i++)
		{
			for (int j = 1; j < width - 1; j++)
			{
				TileMap[i][j] = 'v';
			}
		}
		//������ ������
		int square = 1000; //������� �������
		//���� � ���, ����� ������ ��� ������ ������� �� ���� ������!
		//���������� ��������� �����, �� �� ����� ���� � ������ ������� ������ ������, ���������, ��� ������)
		srand(time(0));
		int x = rand() % width/2 + width/4;
		int y = rand() % height / 2 + height / 4;
		TileMap[y][x] = ' ';
		int blocksPlaced = 1;
		blocksPlaced += placeNineBlock(x, y, ' ');
		while (blocksPlaced < square)
		{
			//������� � ����������� ��������� ����� ������ �����
			srand(time(0));
			nextSpot = rand() % 8;
			//����� �����
			switch (nextSpot)
			{
			case 0:
				//����� ������ �� ������ ����-�����
				x -= 1;
				y -= 1;
				break;
			case 1:
				//������ �� ������
				y -= 1;
				break;
			case 2:
				//������-������
				y -= 1;
				x++;
				break;
			case 3:
				//������
				x += 1;
				break;
			case 4:
				//������-�����
				x += 1;
				y += 1;
				break;
			case 5:
				//�����
				y += 1;
				break;
			case 6:
				//�����-�����
				y += 1;
				x -= 1;
				break; 
			case 7:
				//�����
				x -= 1;
				break;
			}
			//������� ����-����!
			blocksPlaced += placeNineBlock(x, y, ' ');
		}
		break;
	}

}

//� ������ ��������� ������ �� ������������
int world::placeNineBlock(int x, int y, char c)
{
	//������ ���������� x � y - ����� �����
	int X = x;
	int Y = y;
	int retVal = 0;
	X++;
	Y--;
	//������ ��� ������������ ������ ����� � ������ �� ������
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!(X <= 0 && X >= width - 1 && Y <= 0 && Y >= height - 1) && TileMap[Y][X] != c)
			{
				TileMap[Y][X] = c;
				retVal++;
			}
			Y++;
		}
		X -= 2;
	}
	//���������� ���������� ��� ������ ������ � �����
	if (y - 1 > 0 && y - 1 < height - 1 && TileMap[Y][X] != c)
	{
		TileMap[y - 1][x] = c;
		retVal++;
	}
	if (y + 1 > 0 && y + 1 < height - 1 && TileMap[Y][X] != c)
	{
		TileMap[y + 1][x] = c;
		retVal++;
	}
	return retVal;
}


void world::makePreGenMap()
{
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			TileMap[i][j] = ' ';
		}
	}
}

//������� ��������� ������� �����
void world::generateSimpleMap()
{
	//�������� ��� ����� ������ �� ���������
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			TileMap[i][j] = ' ';
		}
	}
	//������ ������� �����
	//�����
	for (int i = 0; i < height; i++)
	{
		TileMap[i][0] = '/';
	}
	//������
	for (int i = 0; i < height; i++)
	{
		TileMap[i][width-1] = '\\';
	}
	//������
	for (int i = 0; i < width; i++)
	{
		TileMap[0][i] = '_';
	}
	//�������
	for (int i = 0; i < width; i++)
	{
		TileMap[height-1][i] = '=';
	}

	//���� �����
	TileMap[0][0] = 'q';
	TileMap[0][width - 1] = ']';
	TileMap[height - 1][0] = 'z';
	TileMap[height - 1][width - 1] = '.';

	//���� ����� � ������
	//�����
	for (int i = 1; i < height-1; i++)
	{
		TileMap[i][1] = 'd';
	}
	//������
	for (int i = 1; i < height-1; i++)
	{
		TileMap[i][width - 2] = 'd';
	}
	//������
	for (int i = 1; i < width-1; i++)
	{
		TileMap[1][i] = 'd';
	}
	//�������
	for (int i = 1; i < width-1; i++)
	{
		TileMap[height - 2][i] = 'd';
	}

	//������

	//�������

	//�����


}