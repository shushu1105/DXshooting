/**********************************************

		fade
				フェードイン・アウト処理

***********************************************/
#ifndef _FADE_H_
#define _FADE_H_

#include <d3d9.h>
#include <d3dx9.h>

void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();

void Fade_Start(int _frame, D3DCOLOR _color, bool bOut);
bool Fade_IsFade();

#endif // !_FADE_H_
