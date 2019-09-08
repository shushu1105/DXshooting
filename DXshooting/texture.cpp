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
	// �ǂݍ��܂�Ă�����j��
	if (pTexture != NULL)
		pTexture->Release();
}
bool Texture::Load(IDirect3DDevice9* pDevice3D, const char* FileName)
{
	// �摜�ǂݍ���
	// DirextX��WindowsAPI�̊֐���HRESULT�����ʂɕԂ��֐�������
	// FAILED�}�N���Ŋ֐������s�������킩��
	// SUCEEDED�}�N���Ŋ֐��������������킩��
	if (FAILED(D3DXCreateTextureFromFile(pDevice3D, FileName, &pTexture)))
		return false;	// �摜�ǂݍ��ݎ��s�i�t�@�C�����Ȃ��\������j

	// �摜�ǂݍ��ݐ���
	return true;
}