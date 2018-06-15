#include "human.h"

using namespace sf;
using namespace std;

vector<String> human::maleNames;
vector<String> human::femaleNames;
vector<String> human::lastNames;
vector<String> human::maleAppearances;
vector<String> human::femaleAppearances;
vector<goal> human::availibleGoals;
vector<cell> human::houses;
vector<action> human::availibleActions;
int human::globalID = 0;

human::human()
{
	//получить id
	id = globalID;
	//увеличить глобальный ид
	globalID++;

	home = houses[id]; //присваивается человеку дом на карте по его айди

	generateNewHuman();

	cell tmp = validCells[rand() % validCells.size()];
	X = tmp.x;
	Y = tmp.y;
	w = 16;
	h = 16;
	x = X*w;
	y = Y*h;



	sprite.setPosition(x, y);

}

void human::generateName()
{
	//сгенерировать имя человека
	name = (gender == male) ? maleNames[rand() % maleNames.size()] : femaleNames[rand() % femaleNames.size()]; //мужчинам - мужские имена, женщинам - женские, рабочим - заводы, крестьянам - поля
	lastName = lastNames[rand() % lastNames.size()]; //фамилии генерируются
}

void human::prepareNames()
{
	maleNames = {
		"Gary",
		"Antony",
		"John",
		"Andy",
		"Gregory",
		"Stephen",
		"Igor",
		"Alexander",
		"Oleg",
		"Vasily",
		"Nick",
		"Nikolas",
		"Alexey",
		"Konstantin",
		"Michael",
		"Josh",
		"Mattias",
		"Kirk",
		"Matthew",
		"James",
		"Billy",
		"Richard",
		"Robert",
		"Lars",
		"Ricardo",
		"Leeroy",
		"Henry",
		"Morgan",
		"Gordon"

	};

	femaleNames = {
		"Alice",
		"Ann",
		"Alexandra",
		"Emma",
		"Olivia",
		"Alex",
		"Ava",
		"Isabella",
		"Sophia",
		"Mia",
		"Charlotte",
		"Amelia",
		"Evelyn",
		"Emily",
		"Elizabeth",
		"Ella",
		"Aria",
		"Victoria",
		"Zoey",
		"Lily",
		"Nataly",
		"Helen",
		"Olga",
		"Helga",
		"Leah",
		"Stella",
		"Mila",
		"Bella",
		"Aurora",
		"Lucy",
		"Caroline",
		"Maya",
		"Maria",
		"Julia",
		"Piper",
		"Lydia",
		"Nova",
		"Vivian",
		"Anne-Marie",
		"Galina",
		"Linda",
		"Diana", 
		"Anastasia",
		"Jessica"
	};

	lastNames = {
		"Smith",
		"Tikhonov",
		"Hamilton",
		"Johnson",
		"Doe",
		"Example",
		"Bitte",
		"Garcia",
		"Ivanov",
		"Davis",
		"Williams",
		"Miller",
		"Rodriguez",
		"White",
		"Wilson",
		"Newell",
		"Taylor",
		"Thomas",
		"Moore",
		"Martin",
		"Lee",
		"Walker",
		"Novikov",
		"Soloviev",
		"Smirnov",
		"Petrov",
		"Saakyan",
		"Volkov",
		"Orlov",
		"Mikhailov",
		"Nosov",
		"Grigoriev",
		"Lebedev",
		"Kozlov",
		"Blinov",
		"Popov",
		"Anders",
		"Sokolov",
		"Scott",
		"Green",
		"Hill",
		"Adams",
		"Parker",
		"King",
		"Baker",
		"Evans",
		"Perkins",
		"Mitchell",
		"Edwards",
		"Stewart",
		"Morris",
		"Murphy",
		"Rivera",
		"Cook",
		"Rogers",
		"Diaz",
		"Watson",
		"Barnes",
		"Jenkins",
		"Ashes",
		"Kim",
		"West",
		"Hayes",
		"Ford",
		"Freeman"
	};
}

void human::prepareAppearances()
{
	maleAppearances = {
		"male01",
		"male02",
		"male03",
		"male04",
		"male05",
		"male06",
		"male07",
		"male08",
		"male09"
	};

	femaleAppearances = {
		"female01",
		"female02",
		"female03",
		"female04",
		"female05",
		"female06",
		"female07",
		"female08"
	};
}

void human::die() //перегрузить
{
	//добавить выбор мёртвого тайлсета
	tileset = "Images/CreatureTilesets/Human/dead.png";
	alive = false;
	//дописать респавн
	respawnPause = rand() % 30000 + 10000; //в тиках?
	currentPause = respawnPause; //текущее время до респавна равно сгенерированному
}

void human::respawn()
{
	//когда истекает пауза респавна, человек возрождается там же, где и умер, но это уже другой человек
	//генерируем нового человека на месте старого: координаты остаются прежние
	generateNewHuman();

	//вроде всё?
	sprite.setPosition(x*w, y*h);
}

void human::generateNewHuman()
{
	//вынесено в отдельный метод во избежание дублирования кода
	//выбрать пол человека
	gender = rand() % 2;

	//сгенерировать имя
	generateName();

	//приготовить статы персонажа
	//случайное число от 1 до 10
	intelligence = 1 + rand() % 10;
	strength = 1 + rand() % 10;
	endurance = 1 + rand() % 10;
	agility = 1 + rand() % 10;

	//хп и стамина рассчитываются, исходя из
	maxStamina = endurance * 87.5 + strength * 53.5; // ну просто формулка
	curStamina = maxStamina;
	maxHp = endurance * 75 + strength * 60;
	curHp = maxHp;

	//голод и жажда - по умолчанию в самом начале человек сыт и не мучим жаждой
	satiety = 100;
	thirst = 100;

	//возраст
	//ожидаемое время жизни
	estLifeTime = meanLifeTime / 2 + rand() % meanLifeTime;

	age = rand() % estLifeTime; //изначально возраст человека от 0 лет до ожидаемого, чтобы не было противоречий

	//подготовить дату смерти человека, не вечно же жить
	generateDeathDate();

	//далее подготовить внешний вид
	//случайный выбор внешнего вида
	if (gender == male)
		tileset = "Images/CreatureTilesets/Human/Male/" + maleAppearances[rand() % maleAppearances.size()] + ".png";
	else
		tileset = "Images/CreatureTilesets/Human/Female/" + femaleAppearances[rand() % femaleAppearances.size()] + ".png";
	//загрузка внешнего вида из файла
	image.loadFromFile(tileset);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 16, 16));

	//параметры для движения
	speed = 0.2; //скорость ходьбы фиксированно равна 0,2
	runningSpeed = 0.2 + agility / 2 * 33 / 200; //скорость бега выше
	currentSpeed = 0;
	//направление движения в начале
	dir = rand() % 4;

	//не бит, не спит, не бежит
	tookDamage = false;
	sleeping = false;
	running = false;

	//по умолчанию в кармане есть фляга с водой и бутерброд
	hasFood = true;
	hasWater = true;
	hasWeapon = true;

	//обнуление точки назначения
	dest.x = -1;
	dest.y = -1;

	currentGoal = availibleGoals[Idle];
}

void human::checkDeathDate()
{
	//проверка, уж не пора ли помереть
}

void human::goalPlanner(int &time, int &weather)
{
	//осуществляет планирование целей
	//проверить состояние существа и на основе этого выбрать новую цель
	//если никаких предпосылок что-либо делать нет, ленимся
	//если возникнут - цель переопределится
	currentGoal = availibleGoals[Idle];

	if (satiety < 20) //если голод
	{
		//голод, нужно найти пищу
		//только если приоритет выше, чем у текущей цели
		if (availibleGoals[Eat].priority > currentGoal.priority)
			currentGoal = availibleGoals[Eat]; //цель - поесть
	}
	if (thirst < 20) //если жажда
	{
		//новая цель - поиск питья, но только если приоритет выше
		if (availibleGoals[Drink].priority > currentGoal.priority)
			currentGoal = availibleGoals[Drink]; //цель - поиск питья
	}
	if (curStamina < 5) //если запас сил существенно снижен
	{
		//утомление, нужно отдохнуть
		if (availibleGoals[Rest].priority > currentGoal.priority)
			currentGoal = availibleGoals[Rest];
	}
	if (time > 20 || time < 7)//если время ночное (20:00 - 7:00)
	{
		//время ночное, пора баиньки
		if (availibleGoals[Sleep].priority > currentGoal.priority)
			currentGoal = availibleGoals[Sleep];
	}
	if (weather == fallout || weather == storm) //погода - осадки или буря
	{
		//погодные условия плохие, надо прятаться
		if (availibleGoals[Hide].priority > currentGoal.priority)
			currentGoal = availibleGoals[Hide];
	}
	if (tookDamage) //получаем люлей
	{
		//надо убегать
		//поскольку приоритет у сваливания наибольший, даже чекать не надо
		currentGoal = availibleGoals[Run];
	}
}

void human::prepareAvailibleGoals()
{
	//подготавливает список достижимых целей
	//для человека цели могут быть:
	//питание
	//питьё
	//сон
	//лень
	//отдых
	//побег
	//прятки
	//порядок очень важен внутри вектора, очень, правда
	goal slp = { Sleep, 2 };
	goal et = { Eat, 3 };
	goal drk = { Drink, 4 };
	goal idl = { Idle, 0 };
	goal rst = { Rest, 1 };
	goal rn = { Run, 6 };
	goal hd = { Hide, 5 };
	
	availibleGoals = {
		slp,
		et,
		drk,
		rn,
		idl,
		hd,
		rst
	};
}

void human::prepareHouses(world &wrld)
{
	//подготавливает список домиков на карте
	for (int i = 0; i < wrld.getHeight(); i++)
	{
		for (int j = 0; j < wrld.getWidth(); j++)
		{
			if (wrld.TileMap[i][j] == 'H')
			{
				//подходящая клетка
				cell temp = { j, i };
				houses.insert(houses.end(), temp);
			}
		}
	}
}

void human::goalAnalyzer()
{
	//планировщик действий для достижения цели
	//в первую очередь очищаем магазин действий
	actionSequence.clear();
	switch (currentGoal.Goal)
	{
	case Run:
		//
		currentState = inDanger;
		desiredState = noDanger;
		break;
	case Sleep:
		//текущее состояние
		if (X == home.x && Y == home.y)
			currentState = atHome;
		else
			currentState = notAtHome;
		desiredState = slept;
		break;
	case Eat:
		//тут либо поиск пищи, либо, если она есть, поглощение
		if (hasFood)
			currentState = FoodInBag;
		else
			currentState = noFoodInBag;
		desiredState = ate;
		break;
	case Drink:
		//опять же, есть вода - пьём, нет вода - ищем
		if (hasWater)
			currentState = waterInBag;
		else
			currentState = noWaterInBag;
		desiredState = drunk;
		break;
	case Idle:
		//ленивое состояние - либо стоим на месте, либо ходим из угла в угол
		currentState = noPurpose;
		desiredState = noPurpose;
		break;
	case Rest:
		//всё просто, прям где стояли - там и остаёмся
		currentState = feelTired;
		desiredState = notTired;
		break;
	case Hide:
		//если персонаж дома, то требуемое состояние сразу достигнуто
		if (X == home.x && Y == home.y)
			currentState = atHome;
		else
			currentState = notAtHome;
		desiredState = atHome;
		break; 
	}
}

void human::prepareAvailibleActions()
{
	//готовит список доступных действий
	availibleActions = {
		{noFoodInBag, getFood, FoodInBag},
		{noWaterInBag, getWater, waterInBag},
		{FoodInBag, eatFood, ate},
		{waterInBag, drinkWater, drunk},
		{inDanger, runFromAttack, noDanger},
		{atHome, getSleep, slept},
		{feelTired, takeRest, notTired},
		{noPurpose, doNothing, noPurpose},
		{notAtHome, getHome, atHome}
	};
}

String human::getHumanData()
{
	//возвращает строку с информацией о человеке
	std::stringstream ss;
	string str;

	ss << id << "_" << name.toAnsiString() << "_" << lastName.toAnsiString() << "_hp=" << curHp << "/" << maxHp << "_st=" << curStamina << "/" << maxStamina << "_x=" << X << "_y=" << Y;
	switch (currentGoal.Goal)
	{
	case Eat:
		ss << "_Eat";
		break;
	case Sleep:
		ss << "_Sleep";
		break;
	case Run:
		ss << "_Run";
		break;
	case Idle:
		ss << "_Idle";
		break;
	case Rest:
		ss << "_Rest";
		break;
	case Hide:
		ss << "_Hide";
		break;
	case Drink:
		ss << "_Drink";
		break;
	}
	
	ss >> str;
	String Str(str);
	return Str;
}

void human::eat()
{
	//у человека сжирается запас еды
	hasFood = false;
	satiety += 40;
	//действие выполнено, переход в следующее состояние
	currentState = ate;
}

void human::drink()
{
	//убирается вода из рюкзака, снижается жажда
	hasWater = false;
	thirst += 40;
	//действие выполнено, переход в следующее состояние
	currentState = drunk;
}

void human::makeSequence()
{
	//построить последовательность действий, направленную на достижение какой-то цели
	//найти в списке доступных действий то, которое подходит для начала цепочки
	for (int i = 0; i < availibleActions.size(); i++)
	{
		if (availibleActions[i].precondition == currentState) //если предусловие действия равно текущему состоянию
			actionSequence.insert(actionSequence.end(), availibleActions[i]); //пхаем в начало цепочки
	}
	//строим оставшуюся цепочку
	while (actionSequence[actionSequence.size() - 1].result != desiredState)
	{
		for (int i = 0; i < availibleActions.size(); i++)
		{
			if (availibleActions[i].precondition == actionSequence[actionSequence.size() - 1].result)
			{
				actionSequence.insert(actionSequence.end(), availibleActions[i]); //помещаем новое действие в цепочку
			}
		}
	}
	//по идее, это должно работать...

}

void human::performSequence()
{
	//выполнить последовательность действий
	//есть вектор с действиями, нужно перебрать каждое
	//пробегаем последовательность и проверяем, какое действие нужно сейчас выполнять
	for (int i = 0; i < actionSequence.size(); i++)
	{
		if (actionSequence[i].precondition == currentState)
		{
			//если текущее состояние персонажа такое же, как предусловие действия, то его и выполняем
			currentAction = actionSequence[i].Action;
		}
	}

}

void human::performAction(world &wrld)
{
	//выполнить конкретное действие
	switch (currentAction)
	{
	case getFood:
		//поиск пищи. Пищи нет в инвентаре
		searchFor(wrld.TileMap, Food);
		for (int i = X - 1; i < X + 1 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 1; j < Y + 1 && j > -1 && j < mapH; j++)
			{
				if (wrld.TileMap[j][j] == 'T' || wrld.TileMap[j][j] == 'B')
				{
					//рядом с текущей клеткой есть еда, наполняем карманы
					hasFood = true;
				}
			}
		}
		if (hasFood)
			currentState = FoodInBag;
		break;
	case getWater:
		//воды нет в рюкзаке, надо найти
		searchFor(wrld.TileMap, Water);
		for (int i = X - 1; i < X + 1 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 1; j < Y + 1 && j > -1 && j < mapH; j++)
			{
				if (wrld.TileMap[j][j] == 'v' )
				{
					//рядом с текущей клеткой есть вода, наполняем флягу
					hasWater = true;
				}
			}
		}

		if (hasWater)
			currentState = waterInBag;
		break;
	case getHome:
		//идти домой
		moveTo(home.x, home.y);
		if (X == home.x && Y == home.y)
			currentState = atHome;
		break;
	case getSleep:
		//поспать
		currentSpeed = 0;
		sleeping = true;
		break;
	case eatFood:
		//съесть пищу из инвентаря
		eat();
		break;
	case drinkWater:
		//выпить воду из инвентаря
		drink();
		break;
	case runFromAttack:
		//убегать от атаки
		//сгенерировать точку и побежать в неё
		if (dest.x == -1 && X == attacked.x && Y == attacked.y) //если точка ещё не сгенерирована
		{
			dest = validCells[rand() % validCells.size()];
		}
		running = true;
		moveTo(dest.x, dest.y);
		//проверка: если достигли точки, то цель достигнута
		if (X != attacked.x && Y != attacked.y)
		{
			//из точки убежали
			currentState = noDanger;
		}
		break;
	case takeRest:
		//устал, присел отдохнуть
		currentSpeed = 0;
		break;
	case doNothing:
		//делаем ничего
		slack();
		break;
	}
}

void human::slack()
{
	//бездельничать
	sleeping = false;
	if (dest.x == -1)
	{
		int randNum = rand() % 100;
		if (randNum > 79)
		{
			//стоим на месте
			currentSpeed = 0;
		}
		else
		{
			//идём куда-нибудь
			dest = validCells[rand() % validCells.size()];
		}
	}
	else
		moveTo(dest.x, dest.y);
}

void human::actionPlanner(world &wrld)
{
	//проанализировать цель и текущее состояние агента
	goalAnalyzer();
	//сформировать последовательность действий
	makeSequence();
	//выполнить её
	performSequence();
	//выполнить действие
	performAction(wrld);
}