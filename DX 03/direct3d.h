/******************************************

			direct3d.h

						directXの設定処理

*******************************************/
#ifndef _DIRECT3D_H_
#define _DIRECT3D_H_

enum RENDERSTATE
{
	RENDER_DEFAULT,	//不透明
	RENDER_ALPHA,	//透明
	RENDER_HALFADD,	//半透明加算
	RENDER_ADD,		//加算
	RENDER_NORMALBLEND,	//テスト
	RENDER_ADDBLEND		//テスト
};

bool InitDirect3d(HWND hWnd);
bool UninitDirect3d();
LPDIRECT3DDEVICE9 getDevice();

void SetRender(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState);


#endif // !_DIRECT3D_H_

