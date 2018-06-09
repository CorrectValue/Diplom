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
	//�������� id
	id = globalID;
	//��������� ���������� ��
	globalID++;

	home = houses[id]; //������������� �������� ��� �� ����� �� ��� ����

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
	//������������� ��� ��������
	name = (gender == male) ? maleNames[rand() % maleNames.size()] : femaleNames[rand() % femaleNames.size()]; //�������� - ������� �����, �������� - �������, ������� - ������, ���������� - ����
	lastName = lastNames[rand() % lastNames.size()]; //������� ������������
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

void human::die() //�����������
{
	//�������� ����� ������� ��������
	tileset = "Images/CreatureTilesets/Human/dead.png";
	alive = false;
	//�������� �������
	respawnPause = rand() % 30000 + 10000; //� �����?
	currentPause = respawnPause; //������� ����� �� �������� ����� ����������������
}

void human::respawn()
{
	//����� �������� ����� ��������, ������� ������������ ��� ��, ��� � ����, �� ��� ��� ������ �������
	//���������� ������ �������� �� ����� �������: ���������� �������� �������
	generateNewHuman();

	//����� ��?
	sprite.setPosition(x*w, y*h);
}

void human::generateNewHuman()
{
	//�������� � ��������� ����� �� ��������� ������������ ����
	//������� ��� ��������
	gender = rand() % 2;

	//������������� ���
	generateName();

	//����������� ����� ���������
	//��������� ����� �� 1 �� 10
	intelligence = 1 + rand() % 10;
	strength = 1 + rand() % 10;
	endurance = 1 + rand() % 10;

	//�� � ������� ��������������, ������ ��
	stamina = endurance * 87.5 + strength * 53.5; // �� ������ ��������
	hp = endurance * 75 + strength * 60;

	//����� � ����� - �� ��������� � ����� ������ ������� ��� � �� ����� ������
	satiety = 100;
	thirst = 100;

	//�������
	//��������� ����� �����
	estLifeTime = meanLifeTime / 2 + rand() % meanLifeTime;

	age = rand() % estLifeTime; //���������� ������� �������� �� 0 ��� �� ����������, ����� �� ���� ������������

	//����������� ���� ������ ��������, �� ����� �� ����
	generateDeathDate();

	//����� ����������� ������� ���
	//��������� ����� �������� ����
	if (gender == male)
		tileset = "Images/CreatureTilesets/Human/Male/" + maleAppearances[rand() % maleAppearances.size()] + ".png";
	else
		tileset = "Images/CreatureTilesets/Human/Female/" + femaleAppearances[rand() % femaleAppearances.size()] + ".png";
	//�������� �������� ���� �� �����
	image.loadFromFile(tileset);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 16, 16));

	//��������� ��� ��������
	speed = 0.2; //�������� ������ ������������ ����� 0,2
	runningSpeed = 0.2 + agility / 2 * 33 / 200; //�������� ���� ����
	currentSpeed = 0;
	//����������� �������� � ������
	dir = rand() % 4;


}

void human::checkDeathDate()
{
	//��������, �� �� ���� �� ��������
}

void human::goalPlanner()
{
	//������������ ������������ �����
	//��������� ��������� �������� � �� ������ ����� ������� ����� ����
	if (satiety < 20) //���� �����
	{
		//�����, ����� ����� ����
		//������ ���� ��������� ����, ��� � ������� ����
		if (availibleGoals[Eat].priority > currentGoal.priority)
			currentGoal = availibleGoals[Eat]; //���� - ������
	}
	else if (thirst < 20) //���� �����
	{
		//����� ���� - ����� �����, �� ������ ���� ��������� ����
		if (availibleGoals[Drink].priority > currentGoal.priority)
			currentGoal = availibleGoals[Drink]; //���� - ����� �����
	}
	else if (stamina < 5) //���� ����� ��� ����������� ������
	{
		//���������, ����� ���������
		if (availibleGoals[Rest].priority > currentGoal.priority)
			currentGoal = availibleGoals[Rest];
	}
	else if ()//���� ����� ������ (22:00 - 6:00)
	{
		//����� ������, ���� �������
		if (availibleGoals[Sleep].priority > currentGoal.priority)
			currentGoal = availibleGoals[Sleep];
	}
	else if () //������ - ������ ��� ����
	{
		//�������� ������� ������, ���� ���������
		if (availibleGoals[Hide].priority > currentGoal.priority)
			currentGoal = availibleGoals[Hide];
	}
	else if () //�������� �����
	{
		//���� �������
		//��������� ��������� � ���������� ����������, ���� ������ �� ����
		currentGoal = availibleGoals[Run];
	}
	else
	{
		//������� ����������� ���-���� ������ ���, �������
		currentGoal = availibleGoals[Idle];
	}



}

void human::prepareAvailibleGoals()
{
	//�������������� ������ ���������� �����
	//��� �������� ���� ����� ����:
	//�������
	//�����
	//���
	//����
	//�����
	//�����
	//������
	//������� ����� ����� ������ �������, �����, ������
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
	//�������������� ������ ������� �� �����
	for (int i = 0; i < wrld.getHeight(); i++)
	{
		for (int j = 0; j < wrld.getWidth(); j++)
		{
			if (wrld.TileMap[i][j] == 'H')
			{
				//���������� ������
				cell temp = { j, i };
				houses.insert(houses.end(), temp);
			}
		}
	}
}

void human::actionPlanner()
{
	//����������� �������� ��� ���������� ����
	switch (currentGoal.Goal)
	{
	case Run:
		//� ������ ���������� ������������ ��������� �����
		//� ����� � ��
		break;
	case Sleep:
		//��� ��� ����� ��������� �����
		moveTo(home.x, home.y);
		break;
	case Eat:
		//��� ���� ����� ����, ����, ���� ��� ����, ����������
		break;
	case Drink:
		//����� ��, ���� ���� - ����, ��� ���� - ����
		break;
	case Idle:
		//������� ��������� - ���� ����� �� �����, ���� ����� �� ���� � ����
		break;
	case Rest:
		//�� ������, ���� ��� ������ - ��� � �������
		break;
	case Hide:
		//����� �����
		moveTo(home.x, home.y);
		break; 
	}
}