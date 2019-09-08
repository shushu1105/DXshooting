/*================================================================
		DXshooting[sprite.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/

#include "sprite.h"


// コンストラクタ
Sprite::Sprite()
{
	pos.x = pos.y = 0.0f;
	width = 0;
	height = 0;
}
// デストラクタ
Sprite::~Sprite() {}

void Sprite::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}
void Sprite::SetLength(int Width, int Height)
{
	width = Width;
	height = Height;
}

void Sprite::Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture)
{
	// 頂点情報セット
	Vertex vtx[4] = {
		{ pos.x + width / 2, pos.y - height / 2, 0.0f, 1.0f, 1.0f, 0.0f},
		{ pos.x + width / 2, pos.y + height / 2, 0.0f, 1.0f, 1.0f, 1.0f},
		{ pos.x - width / 2, pos.y - height / 2, 0.0f, 1.0f, 0.0f, 0.0f},
		{ pos.x - width / 2, pos.y + height / 2, 0.0f, 1.0f, 0.0f, 1.0f}
	};

	// テクスチャセット
	pDevice3D->SetTexture(0, pTexture);
	// 頂点構造体宣言セット
	pDevice3D->SetFVF(SPRITE_FVF);
	// スプライト描画
	pDevice3D->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(Vertex));
}