#include "texture.h"
#include "sprite.h"
#include "input.h"


static int g_FrameCounter = 0;




void spriteAnimInit() {


}
void spriteAnimUninit() {

}
void spriteAnimUpdate() {
	if (g_FrameCounter == 255)
		g_FrameCounter = 0;
	g_FrameCounter++;
}
void spriteAnimDraw() {

}

int GetFrameCounter() {
	return g_FrameCounter;
}