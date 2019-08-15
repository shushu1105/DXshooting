#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>


// テクスチャ管理番号	位置	色
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color);
//	ID	描画の座標	サイズ	色	カット開始 単位pixel	カット幅 単位pixel
void spriteDraw(int textureId, D3DXVECTOR4 position, float sizeX, float sizeY, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h);
// テクスチャ管理番号	位置	色	カット始点(pixel)	カット幅(pixel)	回転中心位置	回転の大きさ(radian)
void spriteDraw(int textureId, D3DXVECTOR4 position, int sizeX, int sizeY, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, D3DXVECTOR2 center, float angle);

// テクスチャ管理番号	位置	色	カット始点(pixel)	カット幅(pixel)	拡大幅(0～1)	
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, float scaleX, float scaleY, float scaleZ);
//	ID	位置	描画する縦横の長さ	色	テクスチャ元の縦横の個数	速さ	(左上を0とし、右に順々と数える)初めと終わり
void spriteDrawDivAnim(int textureId, D3DXVECTOR4 position, int sizeX, int sizeY, D3DCOLOR color, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim);

void spriteDrawDivAnim(int textureId, D3DXVECTOR4 position, int sizeX, int sizeY, D3DCOLOR color, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim, int _flameCounter);




#endif // !_SPRITE_H_
