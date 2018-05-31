
#include "Creature.h"

int Creature::globalID = 0;

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
	//��������:
	switch (dir)
	{
	case down:
		//����
		sprite.setTextureRect(IntRect(0, 0, 16, 16));//��������� ����� �� ����������� ��������
		dy = speed;
		dx = 0;
		break;
	case up:
		//�����
		sprite.setTextureRect(IntRect(0, 17, 16, 16));
		dy = -speed;
		dx = 0;
		break;
	case dleft:
		//�����
		sprite.setTextureRect(IntRect(17, 17, 16, 16));
		dx = -speed;
		dy = 0;
		break;
	case dright:
		//������
		sprite.setTextureRect(IntRect(17, 0, 16, 16));
		dx = speed;
		dy = 0;
		break;
	default:
		break;
	}
}

void respawn()
{
	//����� �������� ����� ��������, �������� ������������ � ��������� ������ �����

}