/******************************************

			direct3d.cpp
						
						directX�̐ݒ菈��
					
*******************************************/
#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"
#include "direct3d.h"

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pDevive = NULL;	//Direct3D�f�o�C�X�̎擾


bool InitDirect3d(HWND hWnd) {

	D3DPRESENT_PARAMETERS d3dpp = {};
	HRESULT hr;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {
		MessageBox(NULL, "Direct3DCreate9 is null", "", MB_OK);
		return false;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;	//�o�b�N�o�b�t�@�̕�
	d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;	//�o�b�N�o�b�t�@�̍���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//�o�b�N�o�b�t�@�̎��
	d3dpp.BackBufferCount = 1;		//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�X���b�v���@(��{�R��)
	d3dpp.Windowed = TRUE;	//�E�B���h�E���[�h�̎w��(true=�E�B���h�E���[�h false=�t���X�N���[��)
	d3dpp.EnableAutoDepthStencil = TRUE;	//DepthBuffer������
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	hr = g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pDevive
	);

	//FAILED(hr) hr�����s��������^ SUCCEEDED(hr) hr��������������^
	if (FAILED(hr)) {
		MessageBox(hWnd, "Can't create device", "error", MB_OK);

		return false;
	}

	SetRender(g_pDevive, RENDER_NORMALBLEND);

	//g_pDevive->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//g_pDevive->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pDevive->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//
	g_pDevive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//g_pDevive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);		//�e�N�X�`���̐F�������Ă���
	//g_pDevive->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	return true;

}

bool UninitDirect3d() {
	if (g_pDevive != NULL)
		g_pDevive->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();

	return true;
}

LPDIRECT3DDEVICE9 getDevice() {
	return g_pDevive;
}

void SetRender(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState)
{
	switch (RenderState)
	{
	case RENDER_DEFAULT:
		//�s����
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		break;
	case RENDER_ALPHA:
		//����
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);		//�A���t�@�e�X�g�̗L����
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);			//�A���t�@�Q�ƒl
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//�A���t�@�e�X�g���i�
		break;

	case RENDER_HALFADD:
		//���������Z
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);			//�A���t�@�e�X�g�̖�����
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);			//�A���t�@�u�����f�B���O�̗L����
		pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);			//Z�o�b�t�@�ւ̏������݂𖳌��ɂ���B
		//pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );			//Z�e�X�g���s��Ȃ�			
		//pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );				//���C�e�B���O���Ȃ�
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		//�u�����f�B���O�I�v�V�������Z
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//SRC�̐ݒ�
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DEST�̐ݒ�
		break;

	case RENDER_ADD:
		//���Z
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);		//�A���t�@�u�����f�B���O�̗L����
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);	//�u�����f�B���O�I�v�V�������Z
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);		//SRC�̐ݒ�
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//DEST�̐ݒ�
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);		//�A���t�@�e�X�g�̖�����
		break;
	case RENDER_NORMALBLEND:
		//�ʏ�u�����h
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0 - SRC)
		break;
	case RENDER_ADDBLEND:
		//���Z�u�����h
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0)
		break;
	}
}
