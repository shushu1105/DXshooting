
#include "fade.h"
#include "common.h"
#include "direct3d.h"

typedef struct FadeVertex_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}FadeVertex;
#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

D3DCOLOR g_FadeColor = 0;
bool g_isFadeOut = false;		//フェードアウト処理をするかどうか
bool g_isFade = false;			//フェード中であるかどうか
int g_FadeFrame = 0;
int g_FadeFrameCount = 0;
int g_FadeStartFrame = 0;

void InitFade()
{
	g_isFade = false;
	g_FadeFrameCount = 0;
}

void UninitFade()
{

}

void UpdateFade()
{
	if (g_isFade)
	{
		int elapsedFrame = g_FadeFrameCount - g_FadeStartFrame;

		float percentage = (float)elapsedFrame / g_FadeFrame;

		if (percentage >= 1.0f)
		{
			percentage = 1.0f;
			g_isFade = false;
		}

		float alpha = g_isFadeOut ? percentage : 1.0f - percentage;


		D3DXCOLOR color = g_FadeColor;
		color.a = alpha;
		g_FadeColor = color;		//D3DCOLOR型をD3DXCOLOR型に変換

	}
	g_FadeFrameCount++;
}

void DrawFade()
{
	D3DXCOLOR color = g_FadeColor;
	if (color.a <= 0.0001f)return;

	FadeVertex v[] =
	{
		{D3DXVECTOR4(0.0f,			0.0f,			0.0f,1.0f),g_FadeColor},
		{D3DXVECTOR4(SCREEN_WIDTH,	0.0f,			0.0f,1.0f),g_FadeColor},
		{D3DXVECTOR4(0.0f,			SCREEN_HEIGHT,	0.0f,1.0f),g_FadeColor},
		{D3DXVECTOR4(SCREEN_WIDTH,	SCREEN_HEIGHT,	0.0f,1.0f),g_FadeColor},
	};

	LPDIRECT3DDEVICE9 pDevice = getDevice();
	pDevice->SetFVF(FVF_FADE_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FadeVertex));
}

void Fade_Start(int _frame, D3DCOLOR _color, bool isOut)
{
	g_FadeFrame = _frame;
	g_FadeColor = _color;
	g_FadeStartFrame = g_FadeFrameCount;
	g_isFadeOut = isOut;
	g_isFade = true;
}

bool Fade_IsFade()
{
	return g_isFade;
}