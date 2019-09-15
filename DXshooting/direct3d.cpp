/*================================================================
		DXshooting[direct3d.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#include "direct3d.h"




Direct3D::Direct3D() {
	pD3D9 = NULL;
	pDevice3D = NULL;
}

Direct3D::~Direct3D() {

	if (pDevice3D != NULL)
		pDevice3D->Release();
	if (pD3D9 != NULL)
		pD3D9->Release();
}


bool Direct3D::Create(HWND hWnd, int Width, int Height) {


	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DDISPLAYMODE Display;
	pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Display);

	D3DPRESENT_PARAMETERS	D3DParam = {
		Width,
		Height,
		Display.Format,
		1,
		D3DMULTISAMPLE_NONE,
		0,
		D3DSWAPEFFECT_DISCARD,
		hWnd,
		TRUE,
		TRUE,
		D3DFMT_D24S8,
		0,
		0,
		D3DPRESENT_INTERVAL_DEFAULT
	};

	////////////////////////////////////////////
	////エラー処理
	if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))

		if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DParam.hDeviceWindow,
			D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))

			if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))

				if (FAILED(pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, D3DParam.hDeviceWindow,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &D3DParam, &pDevice3D)))
				{
					pD3D9->Release();
					return false;
				}
	////////////////////////////////////////////
	return true;
}

void SetRender(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState)
{
	switch (RenderState)
	{
	case RENDER_DEFAULT:
		//不透明
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		break;
	case RENDER_ALPHA:
		//透明
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);		//アルファテストの有効化
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);			//アルファ参照値
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//アルファテスト合格基準
		break;

	case RENDER_HALFADD:
		//半透明加算
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);			//アルファテストの無効化
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);			//アルファブレンディングの有効化
		pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);			//Zバッファへの書き込みを無効にする。
		//pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );			//Zテストを行わない			
		//pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );				//ライティングしない
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		//ブレンディングオプション加算
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//SRCの設定
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			//DESTの設定
		break;

	case RENDER_ADD:
		//加算
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);		//アルファブレンディングの有効化
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);	//ブレンディングオプション加算
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);		//SRCの設定
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//DESTの設定
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);		//アルファテストの無効化
		break;
	}
}
