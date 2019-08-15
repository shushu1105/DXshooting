#ifndef _ENEMY_H_
#define _ENEMY_H_


#include <d3d9.h>
#include <d3dx9.h>
#include "collision.h"

#define ENEMY_MAX (64)

typedef struct
{
	D3DXVECTOR4 position;
	D3DXVECTOR4 move;
	float velocity;
	bool isUse;
	int flameCount;

}ENEMY;




void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();

void createEnemy(float x, float y);
ENEMY *getEnemy();
CIRCLE *getCollisionEnemy();



#endif // !_ENEMY_H_

