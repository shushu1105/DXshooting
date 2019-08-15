#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>


// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color);
//	ID	�`��̍��W	�T�C�Y	�F	�J�b�g�J�n �P��pixel	�J�b�g�� �P��pixel
void spriteDraw(int textureId, D3DXVECTOR4 position, float sizeX, float sizeY, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h);
// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F	�J�b�g�n�_(pixel)	�J�b�g��(pixel)	��]���S�ʒu	��]�̑傫��(radian)
void spriteDraw(int textureId, D3DXVECTOR4 position, int sizeX, int sizeY, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, D3DXVECTOR2 center, float angle);

// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F	�J�b�g�n�_(pixel)	�J�b�g��(pixel)	�g�啝(0�`1)	
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, float scaleX, float scaleY, float scaleZ);
//	ID	�ʒu	�`�悷��c���̒���	�F	�e�N�X�`�����̏c���̌�	����	(�����0�Ƃ��A�E�ɏ��X�Ɛ�����)���߂ƏI���
void spriteDrawDivAnim(int textureId, D3DXVECTOR4 position, int sizeX, int sizeY, D3DCOLOR color, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim);

void spriteDrawDivAnim(int textureId, D3DXVECTOR4 position, int sizeX, int sizeY, D3DCOLOR color, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim, int _flameCounter);




#endif // !_SPRITE_H_
