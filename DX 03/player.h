#ifndef _PLAYER_H_
#define _PLAYER_H_


#include <d3d9.h>
#include <d3dx9.h>


#define SPEED (5)	//1～...	一番最速が1

enum Direction {
	RIGHT,
	LEFT,
	UP,
	DOWN,
};

typedef struct
{
	int texture;		//テクスチャハンドル
	D3DXVECTOR2 position;	//位置
	float width;			//横幅
	float height;			//高さ
	float velocity;			//加速度
	D3DXVECTOR2 move;		//移動値
	D3DCOLOR color;			//色
	D3DXVECTOR2 uv;			//uv
}PLAYER;


void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

PLAYER *GetPlayer();




#endif // !_PLAYER_H_
