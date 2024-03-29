/*================================================================
		DXshooting[direct3d.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#ifndef _DIRECT3D_H
#define _DIRECT3D_H



#define D3D_DEBUG_INFO

#include <comdef.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>

enum RENDERSTATE
{
	RENDER_DEFAULT,	//不透明
	RENDER_ALPHA,	//透明
	RENDER_HALFADD,	//半透明加算
	RENDER_ADD		//加算
};

// Direct3D
class Direct3D
{
public:
	IDirect3D9*				pD3D9;			
	IDirect3DDevice9*		pDevice3D;		

	Direct3D();
	~Direct3D();

	bool Create(HWND hWnd, int Width, int Height);
};


void SetRender(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState);


#endif // !_DIRECT3D_H
