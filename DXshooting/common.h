/*================================================================
		DXshooting[common.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#ifndef _COMMON_H_
#define _COMMON_H_

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define WINDOW_CAPTION "GAME"
#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE)
#define CLEAR_COLOR (D3DCOLOR_RGBA(20,30,40,0))
#define FONT_W (16)
#define FONT_H (32)


typedef	struct Vertex2d_tag {
	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
}Vertex2d;
#define FVF_VERTEX2D ((D3DFVF_XYZRHW) | (D3DFVF_DIFFUSE) | D3DFVF_TEX1)



#endif _COMMON_H_