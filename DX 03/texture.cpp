/**********************************************

			texture
						テクスチャー読み込み処理

***********************************************/

#include "texture.h"
#include "direct3d.h"
#include "Fujino.h"

//テクスチャ管理モジュールの初期化
void InitTexture() {
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		g_TextureDate[i].filename[0] = 0;
		g_TextureDate[i].pTexture = NULL;
		g_TextureDate[i].width = 0;
		g_TextureDate[i].height = 0;
	}
}

//テクスチャの名前 幅 高さ
int TextureSetLoadFile(const char* pFileName) {

	Size size = {};
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		//すでに登録されていないか検索
		if (strcmp(g_TextureDate[i].filename, pFileName) == 0) {
			return i;	//管理番号
		}

		//データベースの使用されていない部分を検索し登録
		if (g_TextureDate[i].filename[0] != 0) {
			continue;	//使用済みなので次を検索
		}

		strcpy_s(g_TextureDate[i].filename, sizeof(g_TextureDate[i].filename), pFileName);

		GetImageSize(g_TextureDate[i].filename, &size);
		g_TextureDate[i].width = size.w;
		g_TextureDate[i].height = size.h;

		return i;

	}
	return -1;
}


//戻り値 = エラー数		重複して呼んでも問題なし
int TextureLoad() {
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	int error_count = 0;
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (g_TextureDate[i].filename[0] == 0) {
			continue;
		}
		if (g_TextureDate[i].pTexture != NULL) {
			continue;
		}
		HRESULT hr = D3DXCreateTextureFromFile(
			pDevice,
			g_TextureDate[i].filename,
			&g_TextureDate[i].pTexture
		);
		if (FAILED(hr)) {
			error_count++;
		}

	}
	return error_count;
}



//部分開放可能
int TextureRelease(int ids[], int count) {
	for (int i = 0; i < count; i++) {
		if (!g_TextureDate[ids[i]].pTexture) {
			continue;
		}
		g_TextureDate[ids[i]].pTexture->Release();
		g_TextureDate[ids[i]].pTexture = NULL;
		g_TextureDate[ids[i]].filename[0] = 0;
		g_TextureDate[ids[i]].width = 0;
		g_TextureDate[ids[i]].height = 0;
	}
	return 1;
}

//全開放
void TextureRelease() {
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (!g_TextureDate[i].pTexture) {
			continue;
		}
		g_TextureDate[i].pTexture->Release();
		g_TextureDate[i].pTexture = NULL;
		g_TextureDate[i].filename[0] = 0;
		g_TextureDate[i].width = 0;
		g_TextureDate[i].height = 0;
	}
}

LPDIRECT3DTEXTURE9 TextureGetTexture(int id) {
	return g_TextureDate[id].pTexture;
}
int TextureGetWidth(int id) {
	return g_TextureDate[id].width;
}

int TextureGetHeight(int id) {
	return g_TextureDate[id].height;
}


