/*================================================================
		DXshooting[player.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/19

==================================================================*/
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "sprite.h"
#include "texture.h"

enum Direction
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
};

typedef struct
{
	D3DXVECTOR4 position;	//位置
	float width;			//横幅
	float height;			//高さ
	float velocity;			//加速度
	int texture;			//texture handle
	D3DXVECTOR4 move;		//移動値
	D3DXVECTOR2 uv;			//uv
	bool life;				//生存フラグ
	float fsin[360], fcos[360];
	int angle;				//360度の方向
	Direction direction;	//4方向
}PlayerData;


class Player
{
private:
	PlayerData player;

	void Update();
	void Draw();

public:


	Player();
	~Player();

	void All();

	void SetPlayer(D3DXVECTOR4 _position,int _width,int _height);
	PlayerData* getPlayer();
};



#endif // !_PLAYER_H_
