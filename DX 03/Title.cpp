#include "Title.h"
#include "font.h"
#include "common.h"
#include "input.h"
#include "scene.h"
#include "texture.h"
#include "sprite.h"
#include "bg.h"
#include "fade.h"
#include "file.h"
#include "score.h"
#include "sound.h"

static bool endtitle;

void InitTitle()
{
	endtitle = false;
	Fade_Start(30, D3DCOLOR_RGBA(255, 255, 255, 255), false);

	InitBG();
	InitFont();
	InitScore();
	HighScore_Load();

	PlaySound(SOUND_LABEL_TITLE);
	TextureLoad();
}
void UninitTitle()
{
	StopSound(SOUND_LABEL_TITLE);
	TextureRelease();
}

void UpdateTitle()
{
	UpdateBG();
	if (!endtitle)
	{
		if (Keyboard_IsTrigger(DIK_SPACE) ||
			GamePad_IsTrigger(0, BUTTON_CIRCLE) ||
			GamePad_IsTrigger(0, BUTTON_CROSS) ||
			GamePad_IsTrigger(0, BUTTON_TRIANGLE) ||
			GamePad_IsTrigger(0, BUTTON_SQUARE))
		{
			Fade_Start(60, D3DCOLOR_RGBA(255, 255, 255, 255), true);
			endtitle = true;
		}
	}
	else
	{
		if (!Fade_IsFade())
			SceneChange(SCENE_GAME);
	}
}
void DrawTitle()
{
	int digit = digitCount(GetHighScore());
	DrawBG();

	numberDraw(GetHighScore(), { SCREEN_WIDTH * 1 / 2 + digit / 2 * 24.0f, SCREEN_HEIGHT * 1 / 2 }, 48.0f, 48.0f);

	SetFont(300.0f, SCREEN_HEIGHT * 1 / 2 - 48.0f, 24.0f, 24.0f, h);
	SetFont(330.0f, SCREEN_HEIGHT * 1 / 2 - 48.0f, 24.0f, 24.0f, i);
	SetFont(360.0f, SCREEN_HEIGHT * 1 / 2 - 48.0f, 24.0f, 24.0f, g);
	SetFont(390.0f, SCREEN_HEIGHT * 1 / 2 - 48.0f, 24.0f, 24.0f, h);

	SetFont(420.0f, SCREEN_HEIGHT * 1 / 2 - 48.0f, 24.0f, 24.0f, s);
	SetFont(450.0f, SCREEN_HEIGHT * 1 / 2 - 48.0f, 24.0f, 24.0f, c);
	SetFont(480.0f, SCREEN_HEIGHT * 1 / 2 - 48.0f, 24.0f, 24.0f, o);
	SetFont(510.0f, SCREEN_HEIGHT * 1 / 2 - 48.0f, 24.0f, 24.0f, r);
	SetFont(540.0f, SCREEN_HEIGHT * 1 / 2 - 48.0f, 24.0f, 24.0f, e);



	SetFont(300.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, p);
	SetFont(350.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, r);
	SetFont(400.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, e);
	SetFont(450.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, s);
	SetFont(500.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, s);

	SetFont(600.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, s);
	SetFont(650.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, p);
	SetFont(700.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, a);
	SetFont(750.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, c);
	SetFont(800.0f, SCREEN_HEIGHT * 3 / 4, 32.0f, 32.0f, e);


}