#include "human.h"

using namespace sf;
using namespace std;

vector<String> human::maleNames;
vector<String> human::femaleNames;
vector<String> human::lastNames;
vector<String> human::maleAppearances;
vector<String> human::femaleAppearances;
int human::globalID = 0;

human::human()
{
	//�������� id
	id = globalID;
	//��������� ���������� ��
	globalID++;

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
	//� ��������� ������������ �� ������ �������� ���������� ��������, ��� �������� ������ �������� ����� ��������� �������
	age = rand() % meanLifeTime; //���������� ������� �������� �� 0 ��� �� ��������

	//����������� ���� ������ ��������, �� ����� �� ����
	generateDeathDate();

	//����� ����������� ������� ���
	//��������� ����� �������� ����
	if (gender == male)
		tileset = "Images/CreatureTilesets/Human/Male" + maleAppearances[rand() % maleAppearances.size()];
	else
		tileset = "Images/CreatureTilesets/Human/Female" + femaleAppearances[rand() % femaleAppearances.size()];
	//�������� �������� ���� �� �����
	image.loadFromFile(tileset);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 16, 16));

	//��������� ��� ��������
	speed = 0.2; //�������� ������ ������������ ����� 0,2
	runningSpeed = 0.2 + agility / 2 * 33 / 200; //�������� ���� ����
	//����������� �������� � ������
	dir = rand() % 4;

	

}

void human::generateDeathDate()
{
	//���������� �������������� ���� ������ ��������, �� ����� +-
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