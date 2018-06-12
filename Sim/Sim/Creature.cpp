
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
		sleeping = false; //�� ����, �� ���� ����, �� ����
		//���������� ���� �������������
		goalPlanner(wrld.currentTimeHours, wrld.curWeather);
		actionPlanner(wrld);
		if (curStamina < 0)
		{
			curStamina = 0;
			currentSpeed = 0;
		}
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
		if (time > 10)
			time = 10.0;
		//���������� ����������
		if (x + dx*time < wrld.getWidth() * 16 && x + dx*time > 0)
		{
			x += dx*time;
			X = (x+w/2) / w;//����� �������
		}
		if (y + dy*time < wrld.getHeight() * 16 && y + dy*time > 0)
		{
			y += dy*time;
			Y = (y+h/2) / h;
		}

		mapInteraction(wrld);

		//����������� ���������� ��������, �������, ����� � ������
		//����� � �����
		if (satiety > 0)
			satiety -= 0.1; //���� ������������ ���: ������ ������� ��������� � �� �� ���� �� �������
		if (thirst > 0)
		{
			if (sleeping)
				thirst -= (wrld.season == Winter) ? 0.05 : 0.15; //����� ������ �������� ����, ��� �����
			else
				thirst -= (wrld.season == Winter) ? 0.1 : 0.3; //����� ������ �������� ����, ��� �����
		}
		//������ ������� ������� �� ����, ��������� ���������� ��������� ��������
		
		if (currentSpeed > 0)
		{
			if (running)
				curStamina -= 0.5;
			else
				curStamina -= 0.2;
		}
		else
			if (curStamina < maxStamina) //���� �� ���������, �� ����� ��� �� �����, ������� ���
				if (sleeping)
					curStamina += 0.5; //�� ��� ����������� ������ ��� ������������
				else
					curStamina += 0.1;
		//��, ���� �������� ������� ��� ������� �� �����, ��������
		if (satiety == 0 || thirst == 0)
			if (sleeping)
				curHp -= 0.05;
			else
				curHp -= 0.1;
		else
			if (curHp < maxHp)
				if (sleeping)
					curHp += 0.2;//�� ��� ����������� ���������
				else
					curHp += 0.1;
		if (curHp <= 0)
		{
			//YOU DIED
			die();
		}
		sprite.setPosition(x, y);
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

void Creature::prepareValidCellsList(world &wrld)
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
			if (wrld.TileMap[i][j] == 'B')//����, ����� ����������
			{
				hidden = true;
			}
			if (wrld.TileMap[i][j] == 'T')//������, ��� ��� ����� ����������
			{
				hidden = true;
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

void Creature::goalPlanner(int &time, int &weather)
{
	
}

void Creature::actionPlanner(world &wrld)
{

}

void Creature::moveTo(int destX, int destY)
{
	//����� ������������ � �������� ����� �����
	//�������� ���������� ������� � ���������
	int diffX, diffY; //������� ��������� �� ���� � � Y ��������������
	diffX = X - destX; //������� ����� ���������
	diffY = Y - destY;

	currentSpeed = running ? runningSpeed : speed;
	//������� ����������� ���������� �
	if (diffX > 0)
	{
		//������� ���������� ������ ���������
		dir = dleft; //��� �����
	}
	else if (diffX < 0)
	{
		//������� ���������� ������ ���������
		dir = dright;
	}
	else if (diffX == 0)
	{
		//�� ���� �����������, ����������� �����
		if (diffY > 0)
		{
			//��������� ���� ����
			dir = up;
		}
		else
		{
			//��������� ����
			dir = down;
		}
	}
	currentSpeed = running ? runningSpeed : speed; //����� ��� ��� � ����
	if (diffX == 0 && diffY == 0)
	{
		//�������� ����� ����������, �������� 
		dest.x = -1;
		dest.y = -1;
	}
}

void Creature::searchFor(String map[][mapW], int thing)
{
	//����� ����-����
	switch (thing)
	{
	case Water:
		//���� ������ ������
		//���� ������ ����
		for (int i = X - 2; i < X + 2 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 2; j < Y + 2 && j > -1 && j <mapH; j++)
			{
				if (map[j][i] == 'v')
				{
					//���� ������� ����� � ���������
					dest.x = i;
					dest.y = j;
				}
			}
		}
		
		break;
	case Food:
		//���� ���� ��� ������ 
		for (int i = X - 2; i < X + 2 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 2; j < Y + 2 && j > -1 && j < mapH; j++)
			{
				if (map[j][i] == 'T' || map[j][i] == 'B')
				{
					//���� ������� ����� � ���������
					dest.x = i;
					dest.y = j;
				}
			}
		}
		break;
	case Cover:
		//���� �������. �������� �������� ���� ��� ������
		for (int i = X - 2; i < X + 2 && i > -1 && i < mapW; i++)
		{
			for (int j = Y - 2; j < Y + 2 && j > -1 && j < mapH; j++)
			{
				if (map[j][i] == 'T' || map[j][i] == 'B')
				{
					//���� ������� ����� � ���������
					dest.x = i;
					dest.y = j;
				}
				cout << map[j][i].toAnsiString();
			}
		}
		break;
	}
	//���� ����� ���� �� �����, ��
	if (dest.x == -1) //����� �� ���������
	{
		dest = validCells[rand() % validCells.size()];
	}
	moveTo(dest.x, dest.y);
}

void Creature::die()
{

}

void Creature::eat()
{

}

void Creature::drink()
{

}