#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>

// テクスチャ管理番号	位置	色
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color);
// テクスチャ管理番号	位置	色	カット始点(pixel)	カット幅(pixel)	
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h);
// テクスチャ管理番号	位置	色	カット始点(pixel)	カット幅(pixel)	回転中心位置	回転の大きさ(radian)
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, D3DXVECTOR2 center, float angle);
// テクスチャ管理番号	位置	色	カット始点(pixel)	カット幅(pixel)	拡大幅(0～1)	
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, float scaleX, float scaleY, float scaleZ);
//	ID	位置	色	パターン	テクスチャ元の縦横の個数	描画する縦横の長さ
void spriteDrawAnimation(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int speed, int animation_max, int numX, int numY, int width, int height);

#endif // !_SPRITE_H_
