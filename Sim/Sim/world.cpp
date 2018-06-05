#include "world.h"
#include <iostream>

vector<cell> world::validCells;

void world::timeManipulation(float time)
{
	//управляет временем в мире
	//как бох

	//получили время, прошедшее с момента последнего обновления, надо каким-то образом прирастить его к имеющемуся
	currentTimeSeconds += time * speed; //СКОРОСТЬ ПОЧЕМУ-ТО НЕ РАБОТАЕТ

	//время прошло - таймер погоды сбиваем
	weatherTimer -= time * speed;

	//переброс на минуту
	if (currentTimeSeconds > 59)
	{
		currentTimeMinutes += 1;
		currentTimeSeconds -= 60;
		minutePassed = true;
	}

	//переброс на час
	if (currentTimeMinutes > 59)
	{
		currentTimeHours += 1;
		currentTimeMinutes -= 60;
	}

	//переброс на день
	if (currentTimeHours > 23)
	{
		day += 1;
		currentTimeHours = 0;
		dayOfWeek++;
		dayOfYear++;
		//переопределение времени заката и рассвета
		if (dayOfYear < 174 || dayOfYear > 357)
		{
			//весеннее полугодие
			MinutesRiseTime -= stepRise;
			MinutesSetTime += stepSet;
		}

		if (dayOfYear == 174)
		{
			//летнее солнцестояние
			MinutesRiseTime = riseTimeSummerH * 60 + riseTimeSummerM;
			MinutesSetTime = setTimeSummerH * 60 + setTimeSummerM;
		}

		if (dayOfYear > 174 && dayOfYear < 357)
		{
			//осеннее полугодие
			MinutesRiseTime += stepRise;
			MinutesSetTime -= stepSet;
		}

		if (dayOfYear == 357)
		{
			//зимнее солнцестояние
			MinutesRiseTime = riseTimeWinterH * 60 + riseTimeWinterM;
			MinutesSetTime = setTimeWinterH * 60 + setTimeWinterM;
		}
	}

	//переброс дней недели
	if (dayOfWeek > 7)
		dayOfWeek = 1;

	//переброс месяца

	

	//теперь вроде всё как надо
	if (day > daysInMonth[month-1])
	{
		day = 1;
		month++;
	}

	//переброс лет
	if (month > 12)
	{
		month = 1;
		year++;
	}

	//переопределение сезона
	if (month > 2 && month < 6)
		season = Spring;
	if (month > 5 && month < 9)
		season = Summer;
	if (month > 8 && month < 12)
		season = Fall;
	if (month == 12 || month < 3)
		season = Winter;

	//переопределение времени суток
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
	//управляет погодой в мире
	if (weatherTimer <= 0)
	{
		//одна погода закончилась, заряжай другую
		changeWeather();
	}
}

void world::changeWeather()
{
	//пора менять погоду! кидаем кубик
	//думай, из всех ли погодных условий может быть осуществлён переход во все остальные
	//из всех
	curWeather = rand() % 5;
	//вариант погоды выбран, установим таймер
	//погода может быть одного типа от двух часов до пары суток, рандомно
	//В СЕКУНДАХ
	weatherTimer = 7200 + rand() % 165600; //итого таймер устанавливается рандомно в диапазоне от 7200 до 165600+7200 секунд

}

world::world()
{
	//конструктор по умолчанию 
	//установить прочие важные и не очень данные
	//srand(time(0));
	//первое января первого года! Зима!
	//пока так, чуть позже будем получать из гуи
	year = 1;
	month = Jan;
	day = 1;
	dayOfWeek = Mon;
	season = Winter;

	//tileset = "Images/map-winter.png";
	switch (season)
	{
	case Winter:
		tileset = "Images/map-winter.png";
		break;
	case Summer:
		tileset = "Images/map-summer.png";
		break;
	case Spring:
		tileset = "Images/map-summer.png";
		break;
	case Fall:
		tileset = "Images/map-summer.png";
		break;
	}

	generateSimpleMap();
	//makePreGenMap();

	mapImg.loadFromFile(tileset);

	mapTex.loadFromImage(mapImg);

	mapSpr.setTexture(mapTex);

	minutePassed = false;


	//установить тайлсет для карты


	//
	curWeather = clear;
	//времечко шесть утра 
	currentTimeHours = 12;
	currentTimeMinutes = 0;
	currentTimeSeconds = 0;

	speed = 60; //для начала будем так считать ?????

	//22 декабря у нас зимнее солнцестояние - самая длинная ночь и самый короткий день.
	// восход 22 декабря - 7:55
	// заход 22 декабря - 16:07
	riseTimeWinterH = 7;
	riseTimeWinterM = 55;
	setTimeWinterH = 16;
	setTimeWinterM = 7;
	//22 июня - летнее солнцестояние
	// восход 22 июня - 3:59
	// заход 22 июня - 20:10
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

	//посчитать день года
	dayOfYear = 0;
	for (int i = 1; i < month; i++)
	{
		dayOfYear += daysInMonth[i - 1];
	}
	dayOfYear += day;

	//рассчитать время рассвета и заката в этот день
	if (dayOfYear < 174 || dayOfYear > 357)
	{
		//весеннее полугодие
		MinutesRiseTime = riseTimeWinterH * 60 + riseTimeWinterM;
		MinutesSetTime = setTimeWinterH * 60 + setTimeWinterM;
		MinutesRiseTime -= stepRise * (dayOfYear + 10);
		MinutesSetTime += stepSet * (dayOfYear + 10);
	}

	if (dayOfYear == 174)
	{
		//летнее солнцестояние
		MinutesRiseTime = riseTimeSummerH * 60 + riseTimeSummerM;
		MinutesSetTime = setTimeSummerH * 60 + setTimeSummerM;
	}

	if (dayOfYear > 174 && dayOfYear < 357)
	{
		//осеннее полугодие
		MinutesRiseTime = riseTimeSummerH * 60 + riseTimeSummerM;
		MinutesSetTime = setTimeSummerH * 60 + setTimeSummerM;
		MinutesRiseTime += stepRise * (dayOfYear - 174);
		MinutesSetTime -= stepSet * (dayOfYear - 174);
	}

	if (dayOfYear == 357)
	{
		//зимнее солнцестояние
		MinutesRiseTime = riseTimeWinterH * 60 + riseTimeWinterM;
		MinutesSetTime = setTimeWinterH * 60 + setTimeWinterM;
	}

	//указать продолжительность сумерек
	//зависит от широты
	riseSetDuration = 37; //примерно и условно

	darkestAlpha = 170;

	stepRiseSetAlpha = darkestAlpha / riseSetDuration;

	//рассчитать интенсивность сумерек в момент начала симуляции
	//днём и ночью не интересует, интересуют только сумерки
	minutesPastMidnight = currentTimeHours * 60 + currentTimeMinutes;

	if (minutesPastMidnight > MinutesSetTime - riseSetDuration && minutesPastMidnight < MinutesSetTime)
	{
		//закатные сумерки
		blueAlphaColor = stepRiseSetAlpha * (minutesPastMidnight - MinutesSetTime);
	}

	if (minutesPastMidnight > MinutesRiseTime - riseSetDuration && minutesPastMidnight < MinutesRiseTime)
	{
		//рассветные сумерки. с каждой минутой альфа синего экрана уменьшается
		blueAlphaColor = stepRiseSetAlpha * (minutesPastMidnight - MinutesRiseTime);
	}

	//набить мир
	makeWater();
	prepareValidCellsList();
	distributeObjects();

}

void world::envManipulation(RenderWindow& window)
{
	//управляет окружением
	//конкретно интересует освещение в дневное и ночное время
	//погодные условия
	RectangleShape overlayBlue, overlayYellow, overlayGray; //синий - для ночи, жёлтый - для заката и рассвета, серый - для погоды
	overlayBlue.setPosition(0, 0);
	overlayGray.setPosition(0, 0);
	Vector2f size;
	
	//идея: как и ирл, есть дни солнцестояния. соответственно, меняются продолжительности дня и ночи, вот так-то, ёпта!
	//22 декабря у нас зимнее солнцестояние - самая длинная ночь и самый короткий день.
	// восход 22 декабря - 7:55
	// заход 22 декабря - 16:07
	//22 июня - летнее солнцестояние
	// восход 22 июня - 3:59
	// заход 22 июня - 20:10
	//соответственно, алгоритм должен это учитывать...

	size.x = window.getSize().x;
	size.y = window.getSize().y;
	overlayBlue.setSize(size);
	overlayYellow.setSize(size);
	overlayGray.setSize(size);

	minutesPastMidnight = currentTimeHours * 60 + currentTimeMinutes;
	

	//теперь вычисляем значение альфы в зависимости от времени суток %)
	//ночь - максимальная альфа у синего и нулевая у жёлтого
	if (minutesPastMidnight > MinutesSetTime - riseSetDuration && minutesPastMidnight < MinutesSetTime)
	{
		//закатные сумерки. с каждой минутой альфа синего экрана увеличивается
		if (minutePassed)
		{
			blueAlphaColor += stepRiseSetAlpha;
			minutePassed = false;
		}
	}
	else if (minutesPastMidnight > MinutesRiseTime - riseSetDuration && minutesPastMidnight < MinutesRiseTime)
	{
		//рассветные сумерки. с каждой минутой альфа синего экрана уменьшается
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
	overlayGray.setFillColor(Color(128, 128, 128, grayAlphaColor));
	//overlayYellow.setFillColor(Color(255, 232, 75, yellowAlphaColor));
	window.draw(overlayBlue);
	//window.draw(overlayYellow);

	//обработка погоды
	switch (curWeather)
	{
	case clear:
		//при ясной погоде ничего не меняется, всё ярко и красиво
		grayAlphaColor = 0;
		break;
	case cloudy:
		//при облачной погоде яркость мира чуть снижается, процентов на двадцать
		grayAlphaColor = 52;
		break;
	case fallout:
		//поскольку осадков при ясной погоде не бывает (редко), то яркость падает на 30%, добавляется серый цвет
		grayAlphaColor = 78;
		//стоит добавить эффект осадков вообще, но пока хз
		break;
	case storm:
		//во время бури вообще мало что видно, всё серое
		grayAlphaColor = 125;
		break;
	case gray:
		//просто пасмурная погода, серый цвет и тусклота
		grayAlphaColor = 65;
		break;
	}
	window.draw(overlayGray);
}

void world::update(RenderWindow& window, float time)
{
	//на вход должно поступать время

	
}

void world::draw(RenderWindow& window)
{
	window.clear();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//код обработки строки карты
			if (TileMap[i][j] == ' ')
				//трава
				mapSpr.setTextureRect(IntRect(32, 0, 16, 16));
			if (TileMap[i][j] == 'r')
				//булыжник
				mapSpr.setTextureRect(IntRect(16, 0, 16, 16));
			if (TileMap[i][j] == 'c')
				//камень
				mapSpr.setTextureRect(IntRect(16, 16, 16, 16));
			if (TileMap[i][j] == 'w')
				//древесина
				mapSpr.setTextureRect(IntRect(32, 16, 16, 16));
			if (TileMap[i][j] == 'v')
				//вода
				mapSpr.setTextureRect(IntRect(0, 16, 16, 16));
			if (TileMap[i][j] == 'd')
				//земля
				mapSpr.setTextureRect(IntRect(0, 0, 16, 16));
			if (TileMap[i][j] == 'i')
				//забор вертикальный
				mapSpr.setTextureRect(IntRect(48, 0, 16, 16));
			if (TileMap[i][j] == '-')
				//забор горизонтальный
				mapSpr.setTextureRect(IntRect(64, 16, 16, 16));
			if (TileMap[i][j] == 'J')
				//угол правый нижний
				mapSpr.setTextureRect(IntRect(80, 16, 16, 16));
			if (TileMap[i][j] == 'L')
				//угол левый нижний
				mapSpr.setTextureRect(IntRect(48, 16, 16, 16));
			if (TileMap[i][j] == '?')
				//угол правый верхний
				mapSpr.setTextureRect(IntRect(80, 0, 16, 16));
			if (TileMap[i][j] == '!')
				//угол левый верхний
				mapSpr.setTextureRect(IntRect(64, 0, 16, 16));
			if (TileMap[i][j] == '/')
				//пропасть левая
				mapSpr.setTextureRect(IntRect(112, 16, 16, 16));
			if (TileMap[i][j] == '\\')
				//пропасть правая
				mapSpr.setTextureRect(IntRect(96, 0, 16, 16));
			if (TileMap[i][j] == '_')
				//пропасть нижняя
				mapSpr.setTextureRect(IntRect(96, 16, 16, 16));
			if (TileMap[i][j] == '=')
				//пропасть верхняя
				mapSpr.setTextureRect(IntRect(112, 0, 16, 16));
			if (TileMap[i][j] == 'q')
				//угол левый верхний
				mapSpr.setTextureRect(IntRect(128, 32, 16, 16));
			if (TileMap[i][j] == ']')
				//угол правый верхний
				mapSpr.setTextureRect(IntRect(128, 16, 16, 16));
			if (TileMap[i][j] == 'z')
				//угол левый нижний
				mapSpr.setTextureRect(IntRect(128, 0, 16, 16));
			if (TileMap[i][j] == '.')
				//угол правый нижний
				mapSpr.setTextureRect(IntRect(112, 32, 16, 16));
			if (TileMap[i][j] == 'T')
				//дерево
				mapSpr.setTextureRect(IntRect(32, 32, 16, 16));
			if (TileMap[i][j] == 'B')
				//куст
				mapSpr.setTextureRect(IntRect(16, 32, 16, 16));

			mapSpr.setPosition(j * 16, i * 16);
			window.draw(mapSpr);
		}
	}
}

void world::displayInfo()
{
	// пока выводит в консоль
	//чистим консоль дедовским методом
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
	cout << "\n";

	//cout << tileset.toAnsiString() << "\n";

	//for (int i = 0; i < height; i++)
	//{
	//	for (int j = 0; j < width; j++)
	//	{
	//		cout << TileMap[i][j].toAnsiString();
	//	}
	//	cout << "\n";
	//}
}

//функция не будет использована в рамках выполнения дипломной работы
void world::generateMap()
{
	//осуществляет процедурную генерацию карты
	//задать тип водоёма!
	srand(time(0));
	int reservoirType = rand() % 3;
	reservoirType = 2; // ТЕСТИРУЕМ ОКЕАН
	//сперва забивает карту "стандартными" блоками
	//если водоём - океан, всё сложнее
	if (reservoirType != ocean)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				TileMap[i][j] = ' ';
			}
		}
		//затем строит границу - каким способом?? горы? Пропасть? весело было бы сделать пропасть
		for (int i = 0; i < width; i++)
		{
			TileMap[0][i] = 'a'; // от abyss - пропасть. НАПИСАТЬ ОБРАБОТЧИК
			TileMap[height - 1][i] = 'a';
		}
		for (int i = 0; i < height; i++)
		{
			TileMap[i][0] = 'e'; //похоже на перевернутую а, "боковая пропасть"
			TileMap[i][width - 1] = 'e';
		}
		//углы
		TileMap[0][0] = '1'; //левый верхний
		TileMap[0][width - 1] = '2'; // правый верхний
		TileMap[height - 1][0] = '3'; //левый нижний
		TileMap[height - 1][width - 1] = '4'; //правый нижний
	}

	//наполнение мира. обязательно должны быть деревья, водоёмы и горы
	int nextSpot;//пригодится потом
	switch (reservoirType)
	{
	case river:
		break;
	case lake:
		//аналогично случаю с океаном, но наоборот
		break;
	case ocean:
		//самый забавный случай: сделаем остров в океане!
		//заливаем карту водой
		for (int i = 1; i < height - 1; i++)
		{
			for (int j = 1; j < width - 1; j++)
			{
				TileMap[i][j] = 'v';
			}
		}
		//делаем остров
		int square = 1000; //площадь острова
		//идея в том, чтобы остров был окружён океаном со всех сторон!
		//рандомится начальная точка, от неё будут идти в разные стороны другие клетки, посмотрим, что выйдет)
		srand(time(0));
		int x = rand() % width/2 + width/4;
		int y = rand() % height / 2 + height / 4;
		TileMap[y][x] = ' ';
		int blocksPlaced = 1;
		blocksPlaced += placeNineBlock(x, y, ' ');
		while (blocksPlaced < square)
		{
			//выбрать в окрестности имеющейся точки другую точку
			srand(time(0));
			nextSpot = rand() % 8;
			//очень хитро
			switch (nextSpot)
			{
			case 0:
				//слева сверху от центра НАЙН-блока
				x -= 1;
				y -= 1;
				break;
			case 1:
				//сверху от центра
				y -= 1;
				break;
			case 2:
				//справа-сверху
				y -= 1;
				x++;
				break;
			case 3:
				//справа
				x += 1;
				break;
			case 4:
				//справа-снизу
				x += 1;
				y += 1;
				break;
			case 5:
				//снизу
				y += 1;
				break;
			case 6:
				//слева-снизу
				y += 1;
				x -= 1;
				break; 
			case 7:
				//слева
				x -= 1;
				break;
			}
			//плейсим НАЙН-блок!
			blocksPlaced += placeNineBlock(x, y, ' ');
		}
		break;
	}

}

//в рамках дипломной работы не использована
int world::placeNineBlock(int x, int y, char c)
{
	//данные координаты x и y - центр блока
	int X = x;
	int Y = y;
	int retVal = 0;
	X++;
	Y--;
	//ставит две вертикальные полосы слева и справа от центра
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
	//доставляет оставшиеся две клетки сверху и снизу
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

//простой генератор простой карты
void world::generateSimpleMap()
{
	//забиваем всю карту травой по умолчанию
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			TileMap[i][j] = ' ';
		}
	}
	//рисуем границы карты
	//левая
	for (int i = 0; i < height; i++)
	{
		TileMap[i][0] = '/';
	}
	//правая
	for (int i = 0; i < height; i++)
	{
		TileMap[i][width-1] = '\\';
	}
	//нижняя
	for (int i = 0; i < width; i++)
	{
		TileMap[0][i] = '_';
	}
	//верхняя
	for (int i = 0; i < width; i++)
	{
		TileMap[height-1][i] = '=';
	}

	//углы карты
	TileMap[0][0] = 'q';
	TileMap[0][width - 1] = ']';
	TileMap[height - 1][0] = 'z';
	TileMap[height - 1][width - 1] = '.';

	//края карты у границ
	//левая
	for (int i = 1; i < height-1; i++)
	{
		TileMap[i][1] = 'd';
	}
	//правая
	for (int i = 1; i < height-1; i++)
	{
		TileMap[i][width - 2] = 'd';
	}
	//нижняя
	for (int i = 1; i < width-1; i++)
	{
		TileMap[1][i] = 'd';
	}
	//верхняя
	for (int i = 1; i < width-1; i++)
	{
		TileMap[height - 2][i] = 'd';
	}

	//нарисовать водоёмы
	//makeWater();
	////распределить объекты
	//distributeObjects();


}

void world::distributeObjects()
{
	//нужно сгенерировать кучу различных типов объектов
	//это камень, куст, дерево
	//сгенерировать число камней, кустов, деревьев
	int rocksCount, bushesCount, treesCount, randNum;
	rocksCount = rand() % (width*height/100) + 1; //девятая часть карты должна быть занята камнями
	bushesCount = rand() % (width*height / 100) + 1; //кустов должно быть побольше, т.к. с них жители берут ягоды
	treesCount = rand() % (width*height / 100) + 1; //деревьев должно быть ещё больше, т.к. это не только еда, но и древесина
	//ну и разместить
	//камни
	for (int i = 0; i < rocksCount; i++)
	{
		randNum = rand() % validCells.size();
		cell tmp = validCells[randNum];
		//клетка более не считается доступной
		validCells.erase(validCells.begin() + randNum);
		//позиция выбрана, остаётся разместить
		TileMap[tmp.y][tmp.x] = 'r';
	}
	//кусты
	for (int i = 0; i < bushesCount; i++)
	{
		randNum = rand() % validCells.size();
		cell tmp = validCells[randNum];
		//клетка более не считается доступной
		validCells.erase(validCells.begin() + randNum);
		//позиция выбрана, остаётся разместить
		TileMap[tmp.y][tmp.x] = 'B';
	}
	//деревья
	for (int i = 0; i < treesCount; i++)
	{
		randNum = rand() % validCells.size();
		cell tmp = validCells[randNum];
		//клетка более не считается доступной
		validCells.erase(validCells.begin() + randNum);
		//позиция выбрана, остаётся разместить
		TileMap[tmp.y][tmp.x] = 'T';
	}
}

void world::makeWater()
{
	//нужно найти несколько соседних клеток и разместить на них водоём
	//генерируем число водоёмов
	int waterCount = rand() % 3 + 1; //на карте может быть от 1 до 4 водоёмов
	int waterSize, waterCenterX, waterCenterY;
	for (int i = 0; i < waterCount; i++)
	{
		//рандомно генерируем размер водоёма
		 waterSize = rand() % 10 + 2; //от 2 до 12 клеток
		//генерируем центр водоёма
		waterCenterX = rand() % (width - 2) + 1; //по идее, от 1 до width-1, чтобы не попадать на края
		waterCenterY = rand() % (height - 2) + 1; //аналогично
		//размещаем водоём
		TileMap[waterCenterY][waterCenterX] = 'v'; //клетка в центре
		waterSize--;
		int dr, pm, currentX, currentY;
		currentX = waterCenterX;
		currentY = waterCenterY;
		while (waterSize > 0)
		{
			dr = rand() % 1; //направление движения Х или Y
			pm = rand() % 1; // плюс или минус
			//это хрень
			//или нет? ещё не тестил
			switch (dr)
			{
			case 0:
				//координата меняется по X
				switch (pm)
				{
				case 0:
					//в положительную сторону
					if (TileMap[currentY][currentX + 1] == ' ')
					{
						currentX++;
						TileMap[currentY][currentX] = 'v';
						waterSize--;
					}
					break;
				case 1:
					//в отрицательную сторону
					if (TileMap[currentY][currentX - 1] == ' ')
					{
						currentX--;
						TileMap[currentY][currentX] = 'v';
						waterSize--;
					}
					break;	
				}
				break;
			case 1:
				//координата меняется по Y
				switch (pm)
				{
				case 0:
					//в положительную сторону
					if (TileMap[currentY + 1][currentX] == ' ')
					{
						currentY++;
						TileMap[currentY][currentX] = 'v';
						waterSize--;
					}
					break;
				case 1:
					//в отрицательную сторону
					if (TileMap[currentY - 1][currentX] == ' ')
					{
						currentY--;
						TileMap[currentY][currentX] = 'v';
						waterSize--;
					}
					break;
				}
				break;
			}
			
		}
	}

}

void world::prepareValidCellsList()
{
	//все клетки, где просто трава - доступные
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (TileMap[j][i] == ' ')
			{
				cell temp = { i, j };
				validCells.insert(validCells.end(), temp);
			}
		}
	}
}

int world::getHeight()
{
	return height;
}

int world::getWidth()
{
	return width;
}