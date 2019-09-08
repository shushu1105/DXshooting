/*================================================================
		DXshooting[directSound.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/

#ifndef _MANAGE_H_
#define _MANAGE_H_
#include "player.h"

class Manage
{

private:
	Player *player;

public:
	Manage();
	~Manage();

	void All();
};

#endif // !_MANAGE_H_
