/*================================================================
		DXshooting[sprite.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#ifndef _SPRITE_H_
#define _SPRITE_H_

// Direct3D�̊e��w�b�_�[�̃C���N���[�h���K�v�Ȃ���
// ���łɂ܂Ƃ߂Ă���w�b�_�[���C���N���[�h����
#include "direct3d.h"


// �X�v���C�g�N���X�i2D�|���S���j
class Sprite
{
public:
	// �|���S�����_���
	struct Vertex {
		float x, y, z;// 3�������W
		float rhw;	// 2D�ϊ��ς݃t���O
		float u, v;	// UV���W
	};
	// FVF�i�_��Ȓ��_�\���̐錾�j�t���O
	static const DWORD SPRITE_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

	// �X�v���C�g�ʒu
	D3DXVECTOR2 pos;
	// �X�v���C�g�T�C�Y
	int width;
	int height;

	// �R���X�g���N�^
	Sprite();
	// �f�X�g���N�^
	~Sprite();

	void SetPos(float x, float y);
	void SetLength(int Width, int Height);
	static void Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture);

};
#endif // !_SPRITE_H_
