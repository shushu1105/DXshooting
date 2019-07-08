#include "texture.h"
#include "sprite.h"
#include "input.h"


static int g_FrameCounter = 0;




void spriteAnimInit() {


}
void spriteAnimUninit() {

}
void spriteAnimUpdate() {
	g_FrameCounter++;
}
void spriteAnimDraw() {

}

int GetFrameCounter() {
	return g_FrameCounter;
}