/*================================================================
		DXshooting[texture.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#ifndef  _TEXTURE_H_
#define  _TEXTURE_H_

// Direct3Dの各種ヘッダーのインクルードが必要なため
// すでにまとめてあるヘッダーをインクルードする
#include "direct3d.h"


// テクスチャクラス
class Texture
{
public:
	// コンストラクタ
	Texture();
	// デストラクタ
	~Texture();
	// 画像データ読み込み
	static bool Load(IDirect3DDevice9* pDevice3D, const char* FileName);

	static IDirect3DTexture9* GetTexture();

private:

	static	IDirect3DTexture9* pTexture;
};


#endif // ! _TEXTURE_H_
