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
	x = tmp.x;
	y = tmp.y;
	w = 16;
	h = 16;
	sprite.setPosition(x*w, y*h);

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

	//хп и стамина рассчитываются, исходя из
	stamina = endurance * 87.5 + strength * 53.5; // ну просто формулка
	hp = endurance * 75 + strength * 60;

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


}

void human::checkDeathDate()
{
	//проверка, уж не пора ли помереть
}

void human::goalPlanner()
{
	//осуществляет планирование целей
	//проверить состояние существа и на основе этого выбрать новую цель
	if (satiety < 20) //если голод
	{
		//голод, нужно найти пищу
		//только если приоритет выше, чем у текущей цели
		if (availibleGoals[Eat].priority > currentGoal.priority)
			currentGoal = availibleGoals[Eat]; //цель - поесть
	}
	else if (thirst < 20) //если жажда
	{
		//новая цель - поиск питья, но только если приоритет выше
		if (availibleGoals[Drink].priority > currentGoal.priority)
			currentGoal = availibleGoals[Drink]; //цель - поиск питья
	}
	else if (stamina < 5) //если запас сил существенно снижен
	{
		//утомление, нужно отдохнуть
		if (availibleGoals[Rest].priority > currentGoal.priority)
			currentGoal = availibleGoals[Rest];
	}
	else if ()//если время ночное (22:00 - 6:00)
	{
		//время ночное, пора баиньки
		if (availibleGoals[Sleep].priority > currentGoal.priority)
			currentGoal = availibleGoals[Sleep];
	}
	else if () //погода - осадки или буря
	{
		//погодные условия плохие, надо прятаться
		if (availibleGoals[Hide].priority > currentGoal.priority)
			currentGoal = availibleGoals[Hide];
	}
	else if () //получаем люлей
	{
		//надо убегать
		//поскольку приоритет у сваливания наибольший, даже чекать не надо
		currentGoal = availibleGoals[Run];
	}
	else
	{
		//никаких предпосылок что-либо делать нет, ленимся
		currentGoal = availibleGoals[Idle];
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
	goal drk = { Drink, 5 };
	goal idl = { Idle, 0 };
	goal rst = { Rest, 1 };
	goal rn = { Run, 7 };
	goal hd = { Hide, 6 };
	
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

void human::actionPlanner()
{
	//планировщик действий для достижения цели
	switch (currentGoal.Goal)
	{
	case Run:
		//в случае сваливания генерируется рандомная точка
		//и мувту в неё
		break;
	case Sleep:
		//для сна нужно добраться домой
		moveTo(home.x, home.y);
		break;
	case Eat:
		//тут либо поиск пищи, либо, если она есть, поглощение
		break;
	case Drink:
		//опять же, есть вода - пьём, нет вода - ищем
		break;
	case Idle:
		//ленивое состояние - либо стоим на месте, либо ходим из угла в угол
		break;
	case Rest:
		//всё просто, прям где стояли - там и остаёмся
		break;
	case Hide:
		//бежим домой
		moveTo(home.x, home.y);
		break; 
	}
}