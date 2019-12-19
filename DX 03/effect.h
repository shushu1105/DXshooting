/*******************************************

				effect
						エフェクト処理

********************************************/
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Fujino.h"


void InitEffect();
void UninitEffect();
void UpdateEffect();
void DrawEffect();

void createEffect(float x, float y, D3DCOLOR color, int life, float scale);


#endif // !_EFFECT_H_
