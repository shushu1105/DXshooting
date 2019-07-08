

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

//	ID	�`��̍��W	�F	�J�b�g�J�n �P��pixel	�J�b�g�� �P��pixel
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h) {

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
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}

// �e�N�X�`���Ǘ��ԍ�	�ʒu	�F	�J�b�g�n�_(pixel)	�J�b�g��(pixel)	��]���S�ʒu	��]�̑傫��(radian)
void spriteDraw(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, D3DXVECTOR2 center, float angle) {

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
		{ D3DXVECTOR4(-cut_w / 2, -cut_h / 2,position.z,position.w),color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(+cut_w / 2, -cut_h / 2,position.z,position.w),color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(-cut_w / 2, +cut_h / 2,position.z,position.w),color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(+cut_w / 2, +cut_h / 2,position.z,position.w),color,D3DXVECTOR2(u1,v1) },
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

void spriteDrawRS(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int cut_x, int cut_y, int cut_w, int cut_h, float scaleX, float scaleY, float scaleZ, D3DXVECTOR2 center, float angle) {

	D3DXMATRIX mtxT;
	D3DXMATRIX mtxR;
	D3DXMATRIX mtxS;
	D3DXMATRIX mtxIT;


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

	D3DXMatrixTranslation(&mtxT, -center.x, -center.y, 0.0f);
	D3DXMatrixRotationZ(&mtxR, D3DXToRadian(angle));
	D3DXMatrixScaling(&mtxS, scaleX, scaleY, scaleZ);
	D3DXMatrixTranslation(&mtxIT, center.x + position.x, center.y + position.y, 0.0f);


	D3DXMATRIX mtxW = mtxT * mtxR *mtxS* mtxIT;

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


//	ID	�ʒu	�F	�p�^�[��	�e�N�X�`�����̏c���̌�	�`�悷��c���̒���
void spriteDrawAnimation(int textureId, D3DXVECTOR4 position, D3DCOLOR color, int speed, int animation_max, int numX, int numY, int width, int height) {

	int tw = TextureGetWidth(textureId);
	int th = TextureGetHeight(textureId);

	int pattern = GetFrameCounter() / speed % animation_max;

	//cut_x = pattern % numX * w/numX
//cut_y = pattern / numX * h/numY
//cut_w = w/numX
//cut_h = h/numY

	float u0 = (pattern % numX) * (tw / numX) / (float)tw;
	float v0 = (pattern / numX) * (th / numY) / (float)th;
	float u1 = ((pattern % numX) * (tw / numX) + (tw / numX)) / (float)tw;
	float v1 = ((pattern / numX) * (th / numY) + (th / numY)) / (float)th;

	Vertex2d v[] = {
		{ D3DXVECTOR4(position.x - width / 2,position.y - height / 2,position.z,position.w),color,D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(position.x + width / 2,position.y - height / 2,position.z,position.w),color,D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(position.x - width / 2,position.y + height / 2,position.z,position.w),color,D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(position.x + width / 2,position.y + height / 2,position.z,position.w),color,D3DXVECTOR2(u1,v1) },
	};

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	if (!pDevice) { return; }
	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureId));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}



LPDIRECT3DDEVICE9 pDevice = NULL;
//				vertexbuffer�𗘗p����spriteDraw
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
//				index�𗘗p����spriteDraw
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

//WORD index[] = {
//	0,1,2,
//	1,3,2
//};

void Sprite_Init() {

	pDevice = getDevice();

	pDevice->CreateVertexBuffer(sizeof(Vertex2d) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX2D,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);

	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 1;
	pIndex[4] = 3;
	pIndex[5] = 2;
	g_pIndexBuffer->Unlock();

}
void Sprite_Uninit(void) {
	if (g_pVertexBuffer) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}

void Sprite_Draw(int textureID, float dx, float dy) {
	//LPDIRECT3DDEVICE9 pDevice = getDevice();

	Vertex2d v[] = {
		{ D3DXVECTOR4(dx,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
		{ D3DXVECTOR4(dx,dy+0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
		{ D3DXVECTOR4(dx+0.5f,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
		{ D3DXVECTOR4(dx+0.5f,dy+0.1f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},

	};
	Vertex2d *pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	//							�S��			0�ł�����

	memcpy(pV, v, sizeof(v));
	g_pVertexBuffer->Unlock();



	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, TextureGetTexture(textureID));
	pDevice->SetIndices(g_pIndexBuffer);

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2d));
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}


