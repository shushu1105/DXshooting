/**************************************************

			player
				プレイヤー処理

*************************************************/
#ifndef _PLAYER_H_
#define _PLAYER_H_


#include <d3d9.h>
#include <d3dx9.h>
#include "Fujino.h"


#define SPEED (8)	//1～...	一番最速が1

enum Direction {
	RIGHT,
	LEFT,
	UP,
	DOWN,
};

typedef struct
{
	int texture;		//テクスチャハンドル
	Vector2 position;	//位置
	float width;			//横幅
	float height;			//高さ
	float velocity;			//加速度
	D3DXVECTOR2 move;		//移動値
	D3DCOLOR color;			//色
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
