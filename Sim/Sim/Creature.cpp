
#include "Creature.h"

int Creature::globalID = 0;
vector<cell> Creature::validCells;

//����������� ����� ������ ����������� ��� ���� �����������. �����.
Creature::Creature()
{
	
}

void Creature::update(float time, world &wrld)
{
	//��������� ��������� �������� � ������ ����
	//���� �������� ����:
	if (alive)
	{
		//��������:
		switch (dir)
		{
		case down:
			//����
			sprite.setTextureRect(IntRect(0, 0, 16, 16));//��������� ����� �� ����������� ��������
			dy = currentSpeed;
			dx = 0;
			break;
		case up:
			//�����
			sprite.setTextureRect(IntRect(0, 17, 16, 16));
			dy = - currentSpeed;
			dx = 0;
			break;
		case dleft:
			//�����
			sprite.setTextureRect(IntRect(17, 17, 16, 16));
			dx = - currentSpeed;
			dy = 0;
			break;
		case dright:
			//������
			sprite.setTextureRect(IntRect(17, 0, 16, 16));
			dx = currentSpeed;
			dy = 0;
			break;
		default:
			break;
		}
		//���������� ����������
		if (x + dx*time < wrld.getWidth() * 16 && x + dx*time > 0)
			x += dx*time;
		if (y + dy*time < wrld.getHeight() * 16 && y + dy*time > 0)
			y += dy*time;
		sprite.setPosition(x*w, y*h);
	}
	else
	{
		//�������� ������, ������� ��� ������� ����
		currentPause -= time;
		if (currentPause <= 0)
		{
			//����� ������, ���� ����������
			respawn();
		}
	}
}

void Creature::prepareValidCellsList(world wrld)
{
	//��������� ��� ������ 
	//��� ����� ��������� �������� �� �����, ��� ������, ��� ������ ����� ������ � �� ������� ������ ������
	for (int i = 0; i < wrld.getHeight(); i++)
	{
		for (int j = 0; j < wrld.getWidth(); j++)
		{
			if (wrld.TileMap[i][j] == ' ')
			{
				//���������� ������
				cell temp = { j, i };
				validCells.insert(validCells.end(), temp);
			}
		}
	}
}

void Creature::mapInteraction(world wrld)
{
	//�������������� �������� � ���������� ������� �����
	//��������� ������ ����� ������� �������� �� ��������������� � �������������� ������� �����
	for (int i = y / 16; i < (y + h) / 16; i++)
	{
		for (int j = x / 16; j < (x + w) / 16; j++)
		{
			if (wrld.TileMap[i][j] == 'r')//��������, ��������� ������
			{
				if (dx > 0)
					x = j * 16 - w;
				if (dx < 0)
					x = j * 16 + 16;
			}
			if (wrld.TileMap[i][j] == 'v')//����, ��������� ������
			{
				if (dx > 0)
					x = j * 16 - w;
				if (dx < 0)
					x = j * 16 + 16;
			}
			if (wrld.TileMap[i][j] == 'B')//����, ��������� ������
			{
				if (dx > 0)
					x = j * 16 - w;
				if (dx < 0)
					x = j * 16 + 16;
			}
			if (wrld.TileMap[i][j] == 'T')//������, ��������� ������
			{
				if (dx > 0)
					x = j * 16 - w;
				if (dx < 0)
					x = j * 16 + 16;
			}
			//��������: �������� ����� �������� ������ � �������� � ���������
			if (wrld.TileMap[i][j] == '=')//�������� �������, �������� - ����
			{
				//��� ���� ��������, ��� ��������� ����������
			}
			if (wrld.TileMap[i][j] == '_')//�������� ������, �������� - ����
			{
				//��� ���� ��������, ��� ��������� ����������
			}
			if (wrld.TileMap[i][j] == '/')//�������� �����, �������� - ����
			{
				//��� ���� ��������, ��� ��������� ����������
			}
			if (wrld.TileMap[i][j] == '\\')//�������� ������, �������� - ����
			{
				//��� ���� ��������, ��� ��������� ����������
			}
		}
	}
}

//void Creature::operator=(const Creature &other)
//{
//	x = other.x;
//	y = other.x;
//	age = other.age;
//	estLifeTime = other.estLifeTime;
//
//	satiety = other.satiety;
//	thirst = other.thirst;
//	stamina = other.stamina;
//	hp = other.hp;
//
//	w = other.w;
//	h = other.h;
//
//	alive = other.alive;
//	id = other.id;
//	dir = other.dir;
//	speed = other.speed;
//	runningSpeed = other.runningSpeed;
//	running = other.running;
//	tileset = other.tileset;
//	image.loadFromFile(tileset);
//	texture.loadFromImage(image);
//	sprite.setTexture(texture);
//	sprite.setTextureRect(IntRect(0, 0, w, h));
//	/*image = other.image;
//	texture = other.texture;
//	sprite = other.sprite;*/
//	
//	respawnPause = other.respawnPause;
//	currentPause = other.currentPause;
//
//}

void Creature::generateDeathDate()
{
	//���� ������� �������, ���� �������������� ����� �����
	int diff = estLifeTime - age; //������� ��� �������� �� ������

}

void Creature::respawn()
{

}

void Creature::goalPlanner()
{

}

void Creature::moveTo(int X, int Y)
{
	//����� ������������ � �������� ����� �����
	//�������� ���������� ������� � ���������
	int diffX, diffY; //������� ��������� �� ���� � � Y ��������������
	diffX = x - X; //������� ����� ���������
	diffY = y - Y;
	//������� ����������� ���������� �
	if (diffX > 0)
	{
		//������� ���������� ������ ���������
		dir = dleft; //��� �����
	}
	else
	{
		//������� ���������� ������ ���������
		dir = dright;
	}
	if (diffX == 0)
	{
		//�� ���� �����������, ����������� �����
		if (diffY > 0)
		{
			//��������� ���� ����
			dir = down;
		}
		else
		{
			//��������� ����
			dir = up;
		}
	}
}

void Creature::searchFor(String map)
{
	//����� ����-����
	//� ������ ������ �������� �� �����, ��� ��� ������ ��, ��� �����
	//������� ���������� ��������� ������ �����
}