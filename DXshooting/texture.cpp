/*================================================================
		DXshooting[texture.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#include "texture.h"

Texture::Texture() {
	pTexture = NULL;
}
Texture::~Texture()
{
	// 読み込まれていたら破棄
	if (pTexture != NULL)
		pTexture->Release();
}
bool Texture::Load(IDirect3DDevice9* pDevice3D, const char* FileName)
{
	// 画像読み込み
	// DirextXやWindowsAPIの関数はHRESULTを結果に返す関数が多い
	// FAILEDマクロで関数が失敗したかわかる
	// SUCEEDEDマクロで関数が成功したかわかる
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName, &pTexture)))
		return false;	// 画像読み込み失敗（ファイルがない可能性あり）

	// 画像読み込み成功
	return true;
}