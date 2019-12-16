#ifndef  _TEXTURE_H_
#define  _TEXTURE_H_

#include <d3d9.h>
#include <d3dx9.h>

#define FILENAME_MAX (64) 
#define TEXTUREDATA_MAX (128)
//	�e�N�X�`���Ǘ����W���[���̏�����
void InitTexture();
//	�e�N�X�`���̖��O �� ����
int TextureSetLoadFile(const char* pFileName);
//	�d�����ČĂ�ł����Ȃ�
int TextureLoad();
//	�����J���\
int TextureRelease(int ids[], int count);
//	�S�J��
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
