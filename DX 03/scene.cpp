#include "scene.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "texture.h"

static SCENE_INDEX g_SceneIndex;
static SCENE_INDEX g_SceneNextIndex;

typedef void(*SceneFunc)();

//関数ポインタ
static const SceneFunc Init[] =
{
	InitTitle,
	InitGame,
	InitResult,
};


void InitScene(SCENE_INDEX index)
{
	g_SceneNextIndex = g_SceneIndex = index;

	Init[g_SceneIndex]();

}

void UninitScene()
{
	switch (g_SceneIndex) {

	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_GAME:
		UninitGame();
		break;

	case SCENE_RESULT:
		UninitResult();
		break;
	}
}

void UpdateScene()
{
	switch (g_SceneIndex) {

	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_GAME:
		UpdateGame();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;
	}
}

void DrawScene()
{
	switch (g_SceneIndex) {

	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_GAME:
		DrawGame();
		break;

	case SCENE_RESULT:
		DrawResult();
		break;
	}
}

void SceneCheck()
{
	if (g_SceneIndex != g_SceneNextIndex)
	{
		UninitScene();
		InitScene(g_SceneNextIndex);
	}
}

void SceneChange(SCENE_INDEX index)
{
	g_SceneNextIndex = index;
}

SCENE_INDEX GetScene()
{
	return g_SceneIndex;
}

//関数ポインタ
//
//typedef void *Func();
//
//static const Func SCENE_INIT[] = {
//		SCENE_NONE,
//	SCENE_TITLE,
//	SCENE_GAME,
//	SCENE_HIGHSCORE,
//	SCENE_MAX,
//	SCENE_END
//}

//SCENE_INIT[g_NextScene]();