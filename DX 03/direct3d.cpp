/******************************************

			direct3d.cpp
						
						directXの設定処理
					
*******************************************/
#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"
#include "direct3d.h"

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pDevive = NULL;	//Direct3Dデバイスの取得


bool InitDirect3d(HWND hWnd) {

	D3DPRESENT_PARAMETERS d3dpp = {};
	HRESULT hr;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {
		MessageBox(NULL, "Direct3DCreate9 is null", "", MB_OK);
		return false;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;	//バックバッファの幅
	d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;	//バックバッファの高さ
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//バックバッファの種類
	d3dpp.BackBufferCount = 1;		//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//スワップ方法(基本コレ)
	d3dpp.Windowed = TRUE;	//ウィンドウモードの指定(true=ウィンドウモード false=フルスクリーン)
	d3dpp.EnableAutoDepthStencil = TRUE;	//DepthBufferを準備
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

	//FAILED(hr) hrが失敗だったら真 SUCCEEDED(hr) hrが成功だったら真
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
	//g_pDevive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);		//テクスチャの色を持ってくる
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
	case RENDER_NORMALBLEND:
		//通常ブレンド
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定(1.0 - SRC)
		break;
	case RENDER_ADDBLEND:
		//加算ブレンド
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// αデスティネーションカラーの指定(1.0)
		break;
	}
}
