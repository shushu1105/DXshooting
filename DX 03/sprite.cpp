/********************************************

			sprite
				スプライト描画処理	

*********************************************/
#include "texture.h"
#include "common.h"
#include "direct3d.h"
#include "frameCounter.h"

D3DCOLOR g_color;
void SetSpriteColor(D3DCOLOR color);


void spriteDraw(int textureId, D3DXVECTOR2 position, float width, float height, D3DCOLOR color)
{
	//int w = TextureGetWidth(textureId);
	//int h = TextureGetHeight(textureId);
	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - width * 0.5f,position.y - height * 0.5f,0.0f,1.0f),color,D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(position.x + width * 0.5f,position.y - height * 0.5f,0.0f,1.0f),color,D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(position.x - width * 0.5f,position.y + height * 0.5f,0.0f,1.0f),color,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(position.x + width * 0.5f,position.y + height * 0.5f,0.0f,1.0f),color,D3DXVECTOR2(1.0f,1.0f) },
	};
	
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));

}

void spriteDraw(int textureId, D3DXVECTOR2 position, float width, float height, int cut_x, int cut_y, int cut_w, int cut_h, D3DCOLOR color)
{
	SetSpriteColor(color);

	int w = TextureGetWidth(textureId);
	int h = TextureGetHeight(textureId);
	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - width / 2,position.y - height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(position.x + width / 2,position.y - height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(position.x - width / 2,position.y + height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(position.x + width / 2,position.y + height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1) },
	};
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));

}

// テクスチャ管理番号	位置	色	カット始点(pixel)	カット幅(pixel)	回転中心位置	回転の大きさ(radian)
void spriteDraw(int textureId, D3DXVECTOR2 position, int width, int height, int cut_x, int cut_y, int cut_w, int cut_h, D3DXVECTOR2 center, float angle, D3DCOLOR color)
{
	SetSpriteColor(color);

	//スプライトの回転 ベクトルの座標変換
	//1,変数宣言
	D3DXMATRIX mtxT;
	D3DXMATRIX mtxR;
	D3DXMATRIX mtxIT;
	//					平行->回転->平行移動
	//float 16個
	//普通の変数と同じで宣言したてはごみ入り

	int w = TextureGetWidth(textureId);
	int h = TextureGetHeight(textureId);
	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	Vertex2d v[] = {
		{ D3DXVECTOR4((float)-width / 2,(float)-height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4((float)+width / 2,(float)-height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4((float)-width / 2,(float)+height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4((float)+width / 2,(float)+height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1) },
	};

	//2,変数に関数を使用して値を代入する
	D3DXMatrixTranslation(&mtxT, -center.x, -center.y, 0.0f);
	D3DXMatrixRotationZ(&mtxR, D3DXToRadian(angle));
	D3DXMatrixTranslation(&mtxIT, center.x + position.x, center.y + position.y, 0.0f);

	D3DXMATRIX mtxW = mtxT * mtxR * mtxIT;

	//3,座標変換する
	for (int i = 0; i < 4; i++) {
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);
	}

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));

}

// テクスチャ管理番号	位置	色	カット始点(pixel)	カット幅(pixel)	拡大幅(0～1)
void spriteDraw(int textureId, D3DXVECTOR2 position, int cut_x, int cut_y, int cut_w, int cut_h, float scaleX, float scaleY, float scaleZ, D3DCOLOR color)
{
	SetSpriteColor(color);

	//スプライトの回転 ベクトルの座標変換
	//1,変数宣言
	D3DXMATRIX mtxS;
	//					平行->回転->平行移動
	//float 16個
	//普通の変数と同じで宣言したてはごみ入り


	int w = TextureGetWidth(textureId);
	int h = TextureGetHeight(textureId);
	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - cut_w / 2,position.y - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(position.x + cut_w / 2,position.y - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(position.x - cut_w / 2,position.y + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(position.x + cut_w / 2,position.y + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1) },
	};

	//2,変数に関数を使用して値を代入する
	D3DXMatrixScaling(&mtxS, scaleX, scaleY, scaleZ);


	//3,座標変換する
	for (int i = 0; i < 4; i++) {
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxS);
	}

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));

}

//	ID	位置	描画する縦横の長さ	色	テクスチャ元の縦横の個数	速さ	(左上を0とし、右に順々と数える)表示したい画像
void spriteDivDraw(int textureId, D3DXVECTOR2 position, float width, float height, int numX, int numY, int Number, D3DCOLOR color)
{
	SetSpriteColor(color);

	int tw = TextureGetWidth(textureId);
	int th = TextureGetHeight(textureId);


	float u0 = (Number % numX) * (tw / numX) / (float)tw;
	float v0 = (Number / numX) * (th / numY) / (float)th;
	float u1 = ((Number % numX) * (tw / numX) + (tw / numX)) / (float)tw;
	float v1 = ((Number / numX) * (th / numY) + (th / numY)) / (float)th;

	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - width / 2,position.y - height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(position.x + width / 2,position.y - height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(position.x - width / 2,position.y + height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(position.x + width / 2,position.y + height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1) },
	};

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));

}



//	ID	位置	描画する縦横の長さ	色	テクスチャ元の縦横の個数	速さ	(左上を0とし、右に順々と数える)初めと終わり
void spriteDrawDivAnim(int textureId, D3DXVECTOR2 position, float width, float height, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim, D3DCOLOR color)
{
	SetSpriteColor(color);

	int tw = TextureGetWidth(textureId);
	int th = TextureGetHeight(textureId);

	int pattern = GetFrameCounter() / speed % animation_max;
	pattern = pattern % (endAnim - startAnim + 1) + startAnim;


	float u0 = (pattern % numX) * (tw / numX) / (float)tw;
	float v0 = (pattern / numX) * (th / numY) / (float)th;
	float u1 = ((pattern % numX) * (tw / numX) + (tw / numX)) / (float)tw;
	float v1 = ((pattern / numX) * (th / numY) + (th / numY)) / (float)th;

	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - width / 2,position.y - height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(position.x + width / 2,position.y - height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(position.x - width / 2,position.y + height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(position.x + width / 2,position.y + height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1) },
	};

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));

}



//	ID	位置	描画する縦横の長さ	色	テクスチャ元の縦横の個数	速さ	(左上を0とし、右に順々と数える)初めと終わり
void spriteDrawDivAnim(int textureId, D3DXVECTOR2 position, float width, float height, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim, int _flameCounter, D3DCOLOR color)
{
	SetSpriteColor(color);

	int tw = TextureGetWidth(textureId);
	int th = TextureGetHeight(textureId);

	int pattern = _flameCounter / speed % animation_max;
	pattern = pattern % (endAnim - startAnim + 1) + startAnim;


	float u0 = (pattern % numX) * (tw / numX) / (float)tw;
	float v0 = (pattern / numX) * (th / numY) / (float)th;
	float u1 = ((pattern % numX) * (tw / numX) + (tw / numX)) / (float)tw;
	float v1 = ((pattern / numX) * (th / numY) + (th / numY)) / (float)th;

	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - width / 2,position.y - height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(position.x + width / 2,position.y - height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(position.x - width / 2,position.y + height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(position.x + width / 2,position.y + height / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1) },
	};

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));

}

void SetSpriteColor(D3DCOLOR color)
{
	g_color = color;
}