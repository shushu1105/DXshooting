
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"

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
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//バックバッファの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//バックバッファの高さ
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