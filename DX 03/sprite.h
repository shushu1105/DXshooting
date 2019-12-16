#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>


//	�X�v���C�g�`��
//	
//	����:textureId	�Ώۂ̃e�N�X�`���n���h��
//		:position	D3DXVECTOR2�^�̈ʒu���W
void spriteDraw(int textureId, D3DXVECTOR2 position, float width, float height, D3DCOLOR color);

//	�X�v���C�g�`��
//	
//	����:textureId	�Ώۂ̃e�N�X�`���n���h��
//		:position	D3DXVECTOR2�^�̈ʒu���W
void spriteDraw(int textureId, D3DXVECTOR2 position, float sizeX, float sizeY, int cut_x, int cut_y, int cut_w, int cut_h, D3DCOLOR color);


//	�X�v���C�g�`��
//	
//	����:textureId	�Ώۂ̃e�N�X�`���n���h��
//		:position	D3DXVECTOR2�^�̈ʒu���W
void spriteDraw(int textureId, D3DXVECTOR2 position, int sizeX, int sizeY, int cut_x, int cut_y, int cut_w, int cut_h, D3DXVECTOR2 center, float angle, D3DCOLOR color);

//	�X�v���C�g�`��
//	
//	����:textureId	�Ώۂ̃e�N�X�`���n���h��
//		:position	D3DXVECTOR2�^�̈ʒu���W
void spriteDraw(int textureId, D3DXVECTOR2 position, int cut_x, int cut_y, int cut_w, int cut_h, float scaleX, float scaleY, float scaleZ, D3DCOLOR color);

//	�X�v���C�g�`��
//	
//	����:textureId	�Ώۂ̃e�N�X�`���n���h��
//		:position	D3DXVECTOR2�^�̈ʒu���W
void spriteDivDraw(int textureId, D3DXVECTOR2 position, float width, float height, int numX, int numY, int Number, D3DCOLOR color);

//	�X�v���C�g�`��
//	
//	����:textureId	�Ώۂ̃e�N�X�`���n���h��
//		:position	D3DXVECTOR2�^�̈ʒu���W
void spriteDrawDivAnim(int textureId, D3DXVECTOR2 position, float width, float height, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim, D3DCOLOR color);


//	�X�v���C�g�`��
//	
//	����:textureId	�Ώۂ̃e�N�X�`���n���h��
//		:position	D3DXVECTOR2�^�̈ʒu���W
void spriteDrawDivAnim(int textureId, D3DXVECTOR2 position, float width, float height, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim, int _flameCounter, D3DCOLOR color);




#endif // !_SPRITE_H_


void SetSpriteColor(D3DCOLOR color);