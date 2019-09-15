/*================================================================
		DXshooting[texture.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#ifndef  _TEXTURE_H_
#define  _TEXTURE_H_

// Direct3D�̊e��w�b�_�[�̃C���N���[�h���K�v�Ȃ���
// ���łɂ܂Ƃ߂Ă���w�b�_�[���C���N���[�h����
#include "direct3d.h"


// �e�N�X�`���N���X
class Texture
{
public:
	// �R���X�g���N�^
	Texture();
	// �f�X�g���N�^
	~Texture();
	// �摜�f�[�^�ǂݍ���
	static bool Load(IDirect3DDevice9* pDevice3D, const char* FileName);

	static IDirect3DTexture9* GetTexture();

private:

	static	IDirect3DTexture9* pTexture;
};


#endif // ! _TEXTURE_H_
