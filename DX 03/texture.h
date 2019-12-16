#ifndef  _TEXTURE_H_
#define  _TEXTURE_H_

#include <d3d9.h>
#include <d3dx9.h>

#define FILENAME_MAX (64) 
#define TEXTUREDATA_MAX (128)
//	テクスチャ管理モジュールの初期化
void InitTexture();
//	テクスチャの名前 幅 高さ
int TextureSetLoadFile(const char* pFileName);
//	重複して呼んでも問題なし
int TextureLoad();
//	部分開放可能
int TextureRelease(int ids[], int count);
//	全開放
void TextureRelease();

LPDIRECT3DTEXTURE9 TextureGetTexture(int id);
int TextureGetWidth(int id);
int TextureGetHeight(int id);


typedef struct TextureData_tag
{
	char filename[FILENAME_MAX];
	int width;
	int height;
	LPDIRECT3DTEXTURE9 pTexture;
}TextureData;

static TextureData g_TextureDate[TEXTUREDATA_MAX];





#endif // ! _TEXTURE_H_
