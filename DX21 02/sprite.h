#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>

// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color);
// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F	�J�b�g�n�_(pixel)	�J�b�g��(pixel)	
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h);
// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F	�J�b�g�n�_(pixel)	�J�b�g��(pixel)	��]���S�ʒu	��]�̑傫��(radian)
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, D3DXVECTOR2 center, float angle);
// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F	�J�b�g�n�_(pixel)	�J�b�g��(pixel)	�g�啝(0�`1)	
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, float scaleX, float scaleY, float scaleZ);
//	ID	�ʒu	�F	�p�^�[��	�e�N�X�`�����̏c���̌�	�`�悷��c���̒���
void spriteDrawAnimation(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int speed, int animation_max, int numX, int numY, int width, int height);

#endif // !_SPRITE_H_
