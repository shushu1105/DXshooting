/*
*	@file	"Fujino.h"
*
*	@autor:	���� �C�D
*
*	@date	2019/09/05	����J�n
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



//	�f�[�^�̗̈搧��
//
//	����:n		�����������f�[�^
//		:low	����
//		:high	���
template <typename T>
static void clamp(T &n, T low, T high)
{
	assert(low <= high);
	n = min(max(n, low), high);
}


//	�I�u�W�F�N�g�̗̈搧��
//
//	����:n		�����������f�[�^
//		:width	�I�u�W�F�N�g�̕�
//		:low	����
//		:high	���
template <typename T>
static void clamp(T &n, T width, T low, T high)
{
	assert(low <= high);
	n = min(max(n, width / 2 + low), high - width / 2);
}

//	�^�[���A���E���h�֐�
//
//	����:x		�J��Ԃ������f�[�^
//		:low	����
//		:high	���
template <typename T>
static void wrap(T &x, T low, T high)
{
	assert(low < high);
	const int n = fmod(x - low, high - low);
	x = ((n >= 0) ? (n + low) : (n + high));
}

//	�f�[�^�̗̈������
//
//	����:x		���肵�����f�[�^
//		:low	����
//		:high	���
//
//	�߂�l:bool	�̈�����ǂ���
template <typename T>
static bool isInside(T &x, T low, T high)
{
	assert(low < high);
	return (low < x) && (x < high) ? true : false;
}

//	���o�E���h�֐�
//
//	����:
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

	//	���W���m�̋��������߂�֐�
	//	
	//	����:other	Vector2�N���X�̑Ώە�
	//
	//	�߂�l:float	�Ώە��Ƃ̋���
	float length(const Vector2 &other) const
	{
		return (float)(sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2)));
	}

	//	���W���m�̋��������߂�֐�
	//
	//	����:other	Vector2�N���X�̑Ώە�
	//
	//	�߂�l:float	�Ώە��Ƃ̋����̓��
	float lengthSq(const Vector2 &other)const
	{
		return (float)(pow((this->x - other.x), 2) + pow((this->y - other.y), 2));
	}
};

class Circle :public Vector2
{
public:
	float radius;

	//�I�u�W�F�N�g���m�̓����蔻��t���O
	//
	//	����:other	Circle�N���X�̑Ώە�
	//
	//	�߂�l:bool	�Ώە��Ɠ������Ă��邩�ǂ���
	bool isCollide(const Circle &other)const
	{
		return lengthSq(other) < pow((this->radius + other.radius), 2);
	}
};



#endif // !_FUJINO_H_
