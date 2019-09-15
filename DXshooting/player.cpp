/*================================================================
		DXshooting[player.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/08/19

==================================================================*/

#include "player.h"
#include "input.h"
#include "clamp.h"
#include "common.h"
#include "font.h"
#include "directX.h"

static int g_FrameCounter = 0;

Direct3D direct3d;

Player::Player()
{
	SetPlayer({ 120.0f,120.0f,0.0f,1.0f },256,256);
	Texture::Load(direct3d.pDevice3D, "cocosozai.png");	//Å©
}

Player::~Player()
{

}

void Player::All()
{
	Update();
	Draw();
}

void Player::Update()
{
	player.move.x *= player.velocity;
	player.move.y *= player.velocity;
	player.angle = -1;
	//[38]Å™ [40]Å´   [37]Å©   [39]Å®

	if (Keyboard_IsPress(DIK_RIGHT) && Keyboard_IsPress(DIK_UP))    //âEè„
	{
		player.angle = 315;
		player.direction = RIGHT;
	}
	else if (Keyboard_IsPress(DIK_LEFT) && Keyboard_IsPress(DIK_UP))    //ç∂è„
	{
		player.angle = 225;
		player.direction = LEFT;
	}
	else if (Keyboard_IsPress(DIK_LEFT) && Keyboard_IsPress(DIK_DOWN))    //ç∂â∫
	{
		player.angle = 135;
		player.direction = LEFT;

	}
	else if (Keyboard_IsPress(DIK_RIGHT) && Keyboard_IsPress(DIK_DOWN))    //âEâ∫
	{
		player.angle = 45;
		player.direction = RIGHT;

	}
	else if (Keyboard_IsPress(DIK_UP))    //Å™
	{
		player.angle = 270;
		player.direction = UP;
	}
	else if (Keyboard_IsPress(DIK_DOWN))    //Å´
	{
		player.angle = 90;
		player.direction = DOWN;
	}
	else if (Keyboard_IsPress(DIK_LEFT))    //Å©
	{
		player.angle = 180;
		player.direction = LEFT;
	}
	else if (Keyboard_IsPress(DIK_RIGHT))    //Å®
	{
		player.angle = 0;
		player.direction = RIGHT;
	}

	if (player.angle != -1) {
		player.move.x += player.fcos[player.angle] * player.velocity;
		player.move.y += player.fsin[player.angle] * player.velocity;
	}

	//if (Keyboard_IsTrigger(DIK_SPACE)) {
	//	createBullet(player.position.x, player.position.y, player.direction);
	//}

	Clamp(player.position, player.width, player.height, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	player.position += player.move;
	g_FrameCounter++;
}
void Player::Draw()
{
	Sprite::Draw(direct3d.pDevice3D, Texture::GetTexture());	//Å©Ç±ÇÃå`

}

void Player::SetPlayer(D3DXVECTOR4 position,int _width,int _height)
{
	player.position = { position.x,position.y,0.0f,1.0f };
	sprite.SetPos(position.x, position.y);
	sprite.SetLength(_width, _height);

}

PlayerData* Player::getPlayer()
{
	return &player;
}

