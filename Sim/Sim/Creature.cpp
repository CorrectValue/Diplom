
#include "Creature.h"

int Creature::globalID = 0;
vector<cell> Creature::validCells;

Creature::Creature()
{
	//�������� id
	id = globalID;
	//��������� ���������� ��
	globalID++;


}

void Creature::update(float time)
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
			dy = running ? runningSpeed : speed;
			dx = 0;
			break;
		case up:
			//�����
			sprite.setTextureRect(IntRect(0, 17, 16, 16));
			dy = running ? -runningSpeed : -speed;
			dx = 0;
			break;
		case dleft:
			//�����
			sprite.setTextureRect(IntRect(17, 17, 16, 16));
			dx = running ? -runningSpeed : -speed;
			dy = 0;
			break;
		case dright:
			//������
			sprite.setTextureRect(IntRect(17, 0, 16, 16));
			dx = running ? runningSpeed : speed;
			dy = 0;
			break;
		default:
			break;
		}
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

void Creature::respawn()
{
	//����� �������� ����� ��������, �������� ������������ � ��������� ������ �����
	//������������� ����� ��� ��������
	cell tmp = validCells[rand() % validCells.size()];
	x = tmp.x;
	y = tmp.y;
	//����� ��?
}

void Creature::die()
{
	//�������� �������. ������ �����.
	alive = false;
	respawnPause = rand() % 3000 + 1000; //� �����?
	currentPause = respawnPause; //������� ����� �� �������� ����� ����������������
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