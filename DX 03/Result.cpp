/*********************************************

			result
				ƒŠƒUƒ‹ƒgˆ—

**********************************************/


#include "Result.h"
#include "bg.h"
#include "font.h"
#include "common.h"
#include "input.h"
#include "scene.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "fade.h"
#include "file.h"
#include "sound.h"

static bool endresult;

void InitResult()
{
	endresult = false;
	Fade_Start(0, D3DCOLOR_RGBA(255, 255, 255, 255), false);

	InitFont();
	InitBG();
	InitScore();

	PlaySound(SOUND_LABEL_RESULT_SE);
	TextureLoad();
}

void UninitResult()
{
	if (GetScore() > GetHighScore())
		HighScore_Save(GetScore());

	TextureRelease();
}

void UpdateResult()
{
	UpdateBG();
	UpdateScore();
	if (!endresult)
	{
		if (Keyboard_IsTrigger(DIK_SPACE) ||
			GamePad_IsTrigger(0, BUTTON_CIRCLE) ||
			GamePad_IsTrigger(0, BUTTON_CROSS) ||
			GamePad_IsTrigger(0, BUTTON_TRIANGLE) ||
			GamePad_IsTrigger(0, BUTTON_SQUARE))
		{
			Fade_Start(60, D3DCOLOR_RGBA(255, 255, 255, 255), true);
			endresult = true;
		}
	}
	else
	{
		if (!Fade_IsFade())
			SceneChange(SCENE_TITLE);
	}

}

void DrawResult()
{
	DrawBG();
	numberDraw(GetScore(), { SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 4 }, 64.0f, 64.0f);

	if (GetScore() > GetHighScore())
	{
		SetFont(300.0f, SCREEN_HEIGHT * 3 / 4 - 64.0f, 32.0f, 32.0f, n);
		SetFont(350.0f, SCREEN_HEIGHT * 3 / 4 - 64.0f, 32.0f, 32.0f, e);
		SetFont(400.0f, SCREEN_HEIGHT * 3 / 4 - 64.0f, 32.0f, 32.0f, w);

		SetFont(500.0f, SCREEN_HEIGHT * 3 / 4 - 64.0f, 32.0f, 32.0f, r);
		SetFont(550.0f, SCREEN_HEIGHT * 3 / 4 - 64.0f, 32.0f, 32.0f, e);
		SetFont(600.0f, SCREEN_HEIGHT * 3 / 4 - 64.0f, 32.0f, 32.0f, c);
		SetFont(650.0f, SCREEN_HEIGHT * 3 / 4 - 64.0f, 32.0f, 32.0f, o);
		SetFont(700.0f, SCREEN_HEIGHT * 3 / 4 - 64.0f, 32.0f, 32.0f, r);
		SetFont(750.0f, SCREEN_HEIGHT * 3 / 4 - 64.0f, 32.0f, 32.0f, d);
	}
}