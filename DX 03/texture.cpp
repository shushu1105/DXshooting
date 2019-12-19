/**********************************************

			texture
						�e�N�X�`���[�ǂݍ��ݏ���

***********************************************/

#include "texture.h"
#include "direct3d.h"
#include "Fujino.h"

//�e�N�X�`���Ǘ����W���[���̏�����
void InitTexture() {
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		g_TextureDate[i].filename[0] = 0;
		g_TextureDate[i].pTexture = NULL;
		g_TextureDate[i].width = 0;
		g_TextureDate[i].height = 0;
	}
}

//�e�N�X�`���̖��O �� ����
int TextureSetLoadFile(const char* pFileName) {

	Size size = {};
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		//���łɓo�^����Ă��Ȃ�������
		if (strcmp(g_TextureDate[i].filename, pFileName) == 0) {
			return i;	//�Ǘ��ԍ�
		}

		//�f�[�^�x�[�X�̎g�p����Ă��Ȃ��������������o�^
		if (g_TextureDate[i].filename[0] != 0) {
			continue;	//�g�p�ς݂Ȃ̂Ŏ�������
		}

		strcpy_s(g_TextureDate[i].filename, sizeof(g_TextureDate[i].filename), pFileName);

		GetImageSize(g_TextureDate[i].filename, &size);
		g_TextureDate[i].width = size.w;
		g_TextureDate[i].height = size.h;

		return i;

	}
	return -1;
}


//�߂�l = �G���[��		�d�����ČĂ�ł����Ȃ�
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



//�����J���\
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

//�S�J��
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


