#include "texture.h"
#include "sprite.h"

#define COCO_WALK_PATTERN_MAX (13)
#define MAN_RUNNING_PATTERN_MAX (10)

static int g_FrameCounter = 0;
static int g_cocoTexture;
static int g_runningTexture100;
static int g_runningTexture101;
static int g_runningTexture102;

void spriteAnimInit() {
	g_cocoTexture = TextureSetLoadFile("cocosozai.png", 512, 512);
	g_runningTexture100 = TextureSetLoadFile("runningman100.png", 350, 200);
	g_runningTexture101 = TextureSetLoadFile("runningman101.png", 350, 200);
	g_runningTexture102 = TextureSetLoadFile("runningman102.png", 350, 200);
}
void spriteAnimUninit() {

}
void spriteAnimUpdate() {
	g_FrameCounter++;
}
void spriteAnimDraw(float dx, float dy) {
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
	spriteDrawDivAnim(
		g_cocoTexture,
		{ 600.0f,200.0f,0.0f,1.0f },
		32, 32,
		D3DCOLOR_RGBA(255, 255, 255, 255),
		16, 16, 16 * 16,
		5,
		16, 28);

	spriteDrawDivAnim(
		g_runningTexture100,
		{ dx,dy,0.0f,1.0f },
		70,
		100,
		D3DCOLOR_RGBA(255, 255, 255, 255),
		5,
		2,
		10,
		5,
		0,
		9
	);
}

int GetFrameCounter() {
	return g_FrameCounter;
}