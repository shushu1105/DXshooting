#ifndef _COMMON_H_
#define _COMMON_H_


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
#define SCREEN_WIDTH (960)
#define SCREEN_HEIGHT (540)
#define WINDOW_STYLE WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)
#define CIRCLE_COUNTER (600)

#define FPS_MEASUREMENT_TIME (1.0)	//この秒数毎に更新

typedef struct Vertex2d_tag {
	//x,y,z,w		座標変換済み頂点の利用　->　RHWに1.0fを設定
	D3DXVECTOR4 position;	//座標
	D3DCOLOR color;
	D3DXVECTOR2 uv;	//texcord
	//	u = 画像のx座標 / 画像の幅
	//	v = 画像のy画像 / 画像の高さ 
}Vertex2d;
#define FVF_VERTEX2D ((D3DFVF_XYZRHW)|(D3DFVF_DIFFUSE)|D3DFVF_TEX1)



typedef struct FLOAT2 {
public:
	FLOAT2(FLOAT x, FLOAT y);
	FLOAT x, y;
}FLOAT2;

typedef struct FLOAT3 {
public:
	FLOAT3(FLOAT x, FLOAT y, FLOAT z);
	FLOAT x, y, z;
}FLOAT3;

typedef struct FLOAT4 {
public:
	FLOAT4(FLOAT x, FLOAT y, FLOAT z, FLOAT w);
	FLOAT x, y, z, w;
}FLOAT4;


#endif // !_COMMON_H_

