#ifndef _SCENE_H_
#define _SCENE_H_

enum SCENE_INDEX
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_MAX,
};


void InitScene(SCENE_INDEX);
void UninitScene();
void UpdateScene();
void DrawScene();

void SceneCheck();

void SceneChange(SCENE_INDEX);
SCENE_INDEX GetScene();


#endif // !_SCENE_H_
