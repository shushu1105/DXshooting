/*
*	@file	"Fujino.h"
*
*	@autor:	藤野 修優
*
*	@date	2019/09/05	制作開始
*/

#ifndef _FUJINO_H_
#define _FUJINO_H_

#include <minwindef.h>
#include <assert.h>



typedef struct {
public:
	float x;
	float y;
}Float2;

typedef struct {
public:
	float x;
	float y;
	float z;
}Float3;

typedef struct {
public:
	float x;
	float y;
	float z;
	float w;
}Float4;



//	データの領域制限
//
//	引数:n		制限したいデータ
//		:low	下限
//		:high	上限
template <typename T>
static void clamp(T &n, T low, T high)
{
	assert(low <= high);
	n = min(max(n, low), high);
}


//	オブジェクトの領域制限
//
//	引数:n		制限したいデータ
//		:width	オブジェクトの幅
//		:low	下限
//		:high	上限
template <typename T>
static void clamp(T &n, T width, T low, T high)
{
	assert(low <= high);
	n = min(max(n, width / 2 + low), high - width / 2);
}

//	ターンアラウンド関数
//
//	引数:x		繰り返したいデータ
//		:low	下限
//		:high	上限
template <typename T>
static void wrap(T &x, T low, T high)
{
	assert(low < high);
	const int n = fmod(x - low, high - low);
	x = ((n >= 0) ? (n + low) : (n + high));
}

//	データの領域内判定
//
//	引数:x		判定したいデータ
//		:low	下限
//		:high	上限
//
//	戻り値:bool	領域内かどうか
template <typename T>
static bool isInside(T &x, T low, T high)
{
	assert(low < high);
	return (low < x) && (x < high) ? true : false;
}

//	リバウンド関数
//
//	引数:
//enum
//{
//	Pass = 0,
//	CollisionX,
//	CollisionY,
//};
//static int rebound(Float2 objectPos, Float2 objectVel, Float2 Reference, float wOffset, float hOffset)
//{
//	Float2 returnVal = { objectVel.x,objectVel.y };
//
//	if (objectPos.y > Reference.y - hOffset &&
//		objectPos.y < Reference.y + hOffset)
//	{
//		if (objectPos.x > Reference.x - wOffset &&
//			objectPos.x < Reference.x + wOffset)
//		{
//			returnVal.y = returnVal.y*-1;
//			if (objectPos.y + returnVal.y<Reference.y + hOffset &&
//				objectPos.y + returnVal.y>Reference.y - hOffset)
//				return CollisionX;
//		}
//		return CollisionY;
//	}
//	return Pass;
//}

class Vector2
{
public:
	float x;
	float y;

	//	座標の位置移動
	//
	//	引数:_x	xの移動量
	//		:_y	yの移動量
	void move(float _x, float _y)
	{
		this->x += _x;
		this->y += _y;
	}

	//	座標同士の距離を求める関数
	//	
	//	引数:other	Vector2クラスの対象物
	//
	//	戻り値:float	対象物との距離
	float length(const Vector2 &other) const
	{
		return (float)(sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2)));
	}

	//	座標同士の距離を求める関数
	//
	//	引数:other	Vector2クラスの対象物
	//
	//	戻り値:float	対象物との距離の二乗
	float lengthSq(const Vector2 &other)const
	{
		return (float)(pow((this->x - other.x), 2) + pow((this->y - other.y), 2));
	}

};

//	Circleクラス
//
//	collisionのクラスで使う
//
//	※09/09現在アップデート中
class Collision :public Vector2
{
public:
	float radius;

	//	オブジェクト同士の当たり判定フラグ
	//
	//	引数:other	Circleクラスの対象物
	//
	//	戻り値:bool	対象物と当たっているかどうか
	bool isCollide(const Collision &other)const
	{
		return lengthSq(other) < pow((this->radius + other.radius), 2);
	}

	//	当たり判定の更新
	//
	//	引数:other	Vector2型の対象物
	void Update(const Vector2 &other)
	{
		this->x = other.x;
		this->y = other.y;
	}
};



#endif // !_FUJINO_H_
