#ifndef _PLAYER_H_
#define _PLAYER_H_


#include <d3d9.h>
#include <d3dx9.h>

#define SPEED (2)	//1�`...	��ԍő���1
#define RUNNING_NUM (10)
#define MOVE (6.0f)

enum Direction {
	RIGHT,
	LEFT,
	UP,
	DOWN,
};

typedef struct
{
	D3DXVECTOR4 position;	//�ʒu
	float width;			//����
	float height;			//����
	float velocity;			//�����x
	bool move;		//�ړ��l
	D3DCOLOR color;			//�F
	D3DXVECTOR2 uv;			//uv
	Direction direction;	//����
}PLAYER;


void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
PLAYER *GetPlayer();

int GetFlame();



#endif // !_PLAYER_H_
