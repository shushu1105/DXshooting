
#include "manage.h"

Manage::Manage()
{
	player = new Player;
}

Manage::~Manage()
{
	delete player;
}

void Manage::All()
{
	player->All();
}
