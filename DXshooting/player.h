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
	D3DXVECTOR4 position;	//�ʒu
	float width;			//����
	float height;			//����
	float velocity;			//�����x
	int texture;			//texture handle
	D3DXVECTOR4 move;		//�ړ��l
	D3DXVECTOR2 uv;			//uv
	bool life;				//�����t���O
	float fsin[360], fcos[360];
	int angle;				//360�x�̕���
	Direction direction;	//4����
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
