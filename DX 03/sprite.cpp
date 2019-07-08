

#include "texture.h"
#include "common.h"
#include "direct3d.h"
#include "spriteAnim.h"

void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color) {
	int w = TextureGetWidth(textureId);
	int h = TextureGetHeight(textureId);
	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - w * 0.5f,position.y - h * 0.5f,position.z,position.w),color,D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(position.x + w * 0.5f,position.y - h * 0.5f,position.z,position.w),color,D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(position.x - w * 0.5f,position.y + h * 0.5f,position.z,position.w),color,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(position.x + w * 0.5f,position.y + h * 0.5f,position.z,position.w),color,D3DXVECTOR2(1.0f,1.0f) },
	};
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}

//	ID	�`��̍��W	�T�C�Y	�F	�J�b�g�J�n �P��pixel	�J�b�g�� �P��pixel
void spriteDraw(int textureId, D3DXVECTOR4 position, float sizeX, float sizeY, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h) {

	int w = TextureGetWidth(textureId);
	int h = TextureGetHeight(textureId);
	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - sizeX / 2,position.y - sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(position.x + sizeX / 2,position.y - sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(position.x - sizeX / 2,position.y + sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(position.x + sizeX / 2,position.y + sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u1,v1) },
	};
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}

// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F	�J�b�g�n�_(pixel)	�J�b�g��(pixel)	��]���S�ʒu	��]�̑傫��(radian)
void spriteDraw(int textureId, D3DXVECTOR4 position, int sizeX, int sizeY, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, D3DXVECTOR2 center, float angle) {

	//�X�v���C�g�̉�] �x�N�g���̍��W�ϊ�
	//1,�ϐ��錾
	D3DXMATRIX mtxT;
	D3DXMATRIX mtxR;
	D3DXMATRIX mtxIT;
	//					���s->��]->���s�ړ�
	//float 16��
	//���ʂ̕ϐ��Ɠ����Ő錾�����Ă͂��ݓ���


	int w = TextureGetWidth(textureId);
	int h = TextureGetHeight(textureId);
	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	Vertex2d v[] = {
		{ D3DXVECTOR4((float)-sizeX / 2,(float)-sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4((float)+sizeX / 2,(float)-sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4((float)-sizeX / 2,(float)+sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4((float)+sizeX / 2,(float)+sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u1,v1) },
	};

	//2,�ϐ��Ɋ֐����g�p���Ēl��������
	D3DXMatrixTranslation(&mtxT, -center.x, -center.y, 0.0f);
	D3DXMatrixRotationZ(&mtxR, D3DXToRadian(angle));
	D3DXMatrixTranslation(&mtxIT, center.x + position.x, center.y + position.y, 0.0f);

	D3DXMATRIX mtxW = mtxT * mtxR * mtxIT;

	//3,���W�ϊ�����
	for (int i = 0; i < 4; i++) {
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);
	}

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}

// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F	�J�b�g�n�_(pixel)	�J�b�g��(pixel)	�g�啝(0�`1)
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, float scaleX, float scaleY, float scaleZ) {

	//�X�v���C�g�̉�] �x�N�g���̍��W�ϊ�
	//1,�ϐ��錾
	D3DXMATRIX mtxS;
	//					���s->��]->���s�ړ�
	//float 16��
	//���ʂ̕ϐ��Ɠ����Ő錾�����Ă͂��ݓ���


	int w = TextureGetWidth(textureId);
	int h = TextureGetHeight(textureId);
	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - cut_w / 2,position.y - cut_h / 2,position.z,position.w),color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(position.x + cut_w / 2,position.y - cut_h / 2,position.z,position.w),color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(position.x - cut_w / 2,position.y + cut_h / 2,position.z,position.w),color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(position.x + cut_w / 2,position.y + cut_h / 2,position.z,position.w),color,D3DXVECTOR2(u1,v1) },
	};

	//2,�ϐ��Ɋ֐����g�p���Ēl��������
	D3DXMatrixScaling(&mtxS, scaleX, scaleY, scaleZ);


	//3,���W�ϊ�����
	for (int i = 0; i < 4; i++) {
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxS);
	}

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}

//	ID	�ʒu	�`�悷��c���̒���	�F	�e�N�X�`�����̏c���̌�	����	(�����0�Ƃ��A�E�ɏ��X�Ɛ�����)���߂ƏI���
void spriteDrawDivAnim(int textureId, D3DXVECTOR4 position, int sizeX, int sizeY, D3DCOLOR color, int numX, int numY, int animation_max, int speed, int startAnim, int endAnim) {

	int tw = TextureGetWidth(textureId);
	int th = TextureGetHeight(textureId);

	int pattern = GetFrameCounter() / speed % animation_max;
	pattern = pattern % (endAnim - startAnim + 1) + startAnim;


	float u0 = (pattern % numX) * (tw / numX) / (float)tw;
	float v0 = (pattern / numX) * (th / numY) / (float)th;
	float u1 = ((pattern % numX) * (tw / numX) + (tw / numX)) / (float)tw;
	float v1 = ((pattern / numX) * (th / numY) + (th / numY)) / (float)th;

	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - sizeX / 2,position.y - sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(position.x + sizeX / 2,position.y - sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(position.x - sizeX / 2,position.y + sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(position.x + sizeX / 2,position.y + sizeY / 2,position.z,position.w),color,D3DXVECTOR2(u1,v1) },
	};

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}