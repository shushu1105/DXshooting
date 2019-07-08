#include "texture.h"
#include "sprite.h"
#include "input.h"


#define COCO_WALK_PATTERN_MAX (13)
#define MAN_RUNNING_PATTERN_MAX (10)

static int g_FrameCounter = 0;
static int g_cocoTexture;
static int g_runningTexture100;
static int g_runningTexture101;
static int g_runningTexture102;

D3DXVECTOR4 g_cocoPosition = { 0,0,0,0 };


void spriteAnimInit() {
	g_cocoTexture = TextureSetLoadFile("cocosozai.png", 512, 512);
	g_runningTexture100 = TextureSetLoadFile("runningman100.png", 350, 200);
	g_runningTexture101 = TextureSetLoadFile("runningman101.png", 350, 200);
	g_runningTexture102 = TextureSetLoadFile("runningman102.png", 350, 200);
	g_cocoPosition = { 300.0f,300.0f,0.0f,1.0f };

}
void spriteAnimUninit() {

}
void spriteAnimUpdate() {
	g_FrameCounter++;
}
void spriteAnimDraw() {
	int patternC = g_FrameCounter / 5 % COCO_WALK_PATTERN_MAX;
	int patternR = g_FrameCounter / 5 % MAN_RUNNING_PATTERN_MAX;


	//spriteDraw(
	//	g_cocoTexture,
	//	{ dx, dy,0.0f,1.0f },
	//	D3DCOLOR_RGBA(255, 255, 255, 255),
	//	patternC * 32,
	//	0,
	//	32,
	//	32);

	//spriteDraw(
	//	g_runningTexture100,
	//	{ dx,dy,0.0f,1.0f },
	//	D3DCOLOR_RGBA(255, 255, 255, 255),
	//	patternR % 5 * TextureGetWidth(g_runningTexture100) / 5,
	//	patternR / 5 * TextureGetHeight(g_runningTexture100) / 2,
	//	TextureGetWidth(g_runningTexture100) / 5,
	//	TextureGetHeight(g_runningTexture100) / 2
	//);

	if (Keyboard_IsPress(DIK_W) || Keyboard_IsPress(DIK_UP)) {
		g_cocoPosition.y -= 2.0f;

	}
	if (Keyboard_IsPress(DIK_S) || Keyboard_IsPress(DIK_DOWN)) {
		g_cocoPosition.y += 2.0f;
	}
	if (Keyboard_IsPress(DIK_A) || Keyboard_IsPress(DIK_LEFT)) {
		g_cocoPosition.x -= 2.0f;
	}
	if (Keyboard_IsPress(DIK_D) || Keyboard_IsPress(DIK_RIGHT)) {
		g_cocoPosition.x += 2.0f;
	}
	if (Keyboard_IsPress(DIK_R)) {
		g_cocoPosition = { 300.0f,300.0f,0.0f,1.0f };
	}
	spriteDrawAnimation(g_cocoTexture, g_cocoPosition, D3DCOLOR_RGBA(255, 255, 255, 255), 5, 13, 16, 16, 32, 32);
	spriteDrawAnimation(
		g_runningTexture100,
		{ 400.0f,200.0f,0.0f,1.0f },
		D3DCOLOR_RGBA(255, 255, 255, 255),
		5,
		5 * 2,
		5, 2,
		140, 200
	);
}

int GetFrameCounter() {
	return g_FrameCounter;
}