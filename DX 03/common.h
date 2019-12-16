#ifndef _COMMON_H_
#define _COMMON_H_

#include <d3d9.h>
#include <d3dx9.h>
/*
ヘッダファイルのルール
定数,列挙型(enum),構造体(struct),共用体(uninon)...などの宣言
関数のプロトタイプ宣言
#includeはヘッダに書かない ※必要なものを的確に書く
他のファイルで使用するものを書く(cpp内でおさまるものはcpp内で書けばいい)
*/
/*--------------------------------------------------------------------
		定数定義
---------------------------------------------------------------------*/

#define CLASS_NAME	"GameWindow"
#define WINDOW_CAPTION	""
#define SCREEN_WIDTH (1080.0f)
#define SCREEN_HEIGHT (640.0f)
#define WINDOW_STYLE WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)


typedef struct Vertex2d_tag {
	//x,y,z,w		座標変換済み頂点の利用　->　RHWに1.0fを設定
	D3DXVECTOR4 position;	//座標
	D3DCOLOR color;
	D3DXVECTOR2 uv;	//texcord
	//	u = 画像のx座標 / 画像の幅
	//	v = 画像のy画像 / 画像の高さ 
}Vertex2d;
#define FVF_VERTEX2D ((D3DFVF_XYZRHW)|(D3DFVF_DIFFUSE)|D3DFVF_TEX1)
//頂点の形を表現する頂点構造体を宣言する

//デバイスに頂点の形を伝えるためのFVFを宣言する




#endif // !_COMMON_H_

