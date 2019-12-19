/**************************************************

			player
				�v���C���[����

*************************************************/
#ifndef _PLAYER_H_
#define _PLAYER_H_


#include <d3d9.h>
#include <d3dx9.h>
#include "Fujino.h"


#define SPEED (8)	//1�`...	��ԍő���1

enum Direction {
	RIGHT,
	LEFT,
	UP,
	DOWN,
};

typedef struct
{
	int texture;		//�e�N�X�`���n���h��
	Vector2 position;	//�ʒu
	float width;			//����
	float height;			//����
	float velocity;			//�����x
	D3DXVECTOR2 move;		//�ړ��l
	D3DCOLOR color;			//�F
	D3DXVECTOR2 uv;			//uv
	Collision collision;	
	int hp;
	int damageTime;
}PLAYER;


void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

PLAYER *getPlayer();
void Damage(int damage);
bool isDead();
bool NoneStatus();


#endif // !_PLAYER_H_
