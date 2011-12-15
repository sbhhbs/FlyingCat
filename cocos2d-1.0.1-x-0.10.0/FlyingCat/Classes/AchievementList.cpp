#include "AchievementList.h"



BaseAchivement::BaseAchivement()
{
	done = false;
	storename = "";
}

bool BaseAchivement::isDone()
{
	return done;
}

std::string BaseAchivement::getLockTitle()
{
	return string("Locked");
}

std::string BaseAchivement::getLockImagePath()
{
	return string("ac_unlock.png");
}

void BaseAchivement::forceLock()
{
	done = false;
}
