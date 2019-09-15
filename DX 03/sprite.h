#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>


//	スプライト描画
//	
//	引数:textureId	対象のテクスチャハンドル
//		:position	D3DXVECTOR2型の位置座標
void spriteDraw(int textureId, D3DXVECTOR2 position, float width, float height);

//	スプライト描画
//	
//	引数:textureId	対象のテクスチャハンドル
//		:position	D3DXVECTOR2型の位置座標
void spriteDraw(int textureId, D3DXVECTOR2 position, float sizeX, float sizeY, int cut_x, int cut_y, int cut_w, int cut_h);


//	スプライト描画
//	
//	引数:textureId	対象のテクスチャハンドル
//		:position	D3DXVECTOR2型の位置座標
void spriteDraw(int textureId, D3DXVECTOR2 position, int sizeX, int sizeY, int cut_x, int cut_y, int cut_w, int cut_h, D3DXVECTOR2 center, float angle);

//	スプライト描画
//	
//	引数:textureId	対象のテクスチャハンドル
//		:position	D3DXVECTOR2型の位置座標
void spriteDraw(int textureId, D3DXVECTOR2 position, int cut_x, int cut_y, int cut_w, int cut_h, float scaleX, float scaleY, float scaleZ);

//	スプライト描画
//	
//	引数:textureId	対象のテクスチャハンドル
//		:position	D3DXVECTOR2型の位置座標
void spriteDivDraw(int textureId, D3DXVECTOR2 position, float width, float height, int numX, int numY, int Number);

//	スプライト描画
//	
//	引数:textureId	対象のテクスチャハンドル
//		:position	D3DXVECTOR2型の位置座標
void spriteDrawDivAnim(int textureId, D3DXVECTOR2 position, float width, float height, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim);


//	スプライト描画
//	
//	引数:textureId	対象のテクスチャハンドル
//		:position	D3DXVECTOR2型の位置座標
void spriteDrawDivAnim(int textureId, D3DXVECTOR2 position, float width, float height, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim, int _flameCounter);




#endif // !_SPRITE_H_


void SetSpriteColor(D3DCOLOR color);