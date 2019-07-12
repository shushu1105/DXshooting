#ifndef _PLAYER_H_
#define _PLAYER_H_


#include <d3d9.h>
#include <d3dx9.h>

#define SPEED (2)	//1～...	一番最速が1
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
	D3DXVECTOR4 position;	//位置
	float width;			//横幅
	float height;			//高さ
	float velocity;			//加速度
	bool move;		//移動値
	D3DCOLOR color;			//色
	D3DXVECTOR2 uv;			//uv
	Direction direction;	//方向
}PLAYER;


void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
PLAYER *GetPlayer();

int GetFlame();



#endif // !_PLAYER_H_
