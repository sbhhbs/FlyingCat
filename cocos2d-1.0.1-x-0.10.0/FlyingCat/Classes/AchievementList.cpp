#include "AchievementList.h"
#include "DataCore.h"



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

Achievement_Flying10000 :: Achievement_Flying10000()
{
	storename = "ac_flying10000";
	done = DataCore::sharedCore()->getBoolKey(storename);
}

string Achievement_Flying10000 :: getLockInfo()
{
	return "Flying 10000 meters to unlock";
}

string Achievement_Flying10000 :: getUnlockInfo()
{
	return "You have flying 10000 meters";
}

string Achievement_Flying10000 :: getLockTitle()
{
	return "Fly For Fun";
}

string Achievement_Flying10000 :: getUnlockTitle()
{
	return "A Good Pilot";
}

// TODO : Add the path for the images

string Achievement_Flying10000 :: getUnlockImagePath()
{
	return "";
}

string Achievement_Flying10000 :: getLockImagePath()
{
	return "";
}

// End

void Achievement_Flying10000 :: check()
{
	if (done)
		return;
	if (DataCore::sharedCore()->getTotoalDistance() >= 10000)
	{
		done = true;
		DataCore::sharedCore()->setBoolKey(storename, true);	
		DataCore::sharedCore()->save();
	}
}


// Stars 100

Achievement_Stars100 :: Achievement_Stars100()
{
	storename = "ac_stars100";
	done = DataCore::sharedCore()->getBoolKey(storename);
}

string Achievement_Stars100 :: getLockInfo()
{
	return "Get 100 stars to unlock";
}

string Achievement_Stars100 :: getUnlockInfo()
{
	return "You got 100 stars";
}

string Achievement_Stars100 :: getLockTitle()
{
	return "Star lover";
}

string Achievement_Stars100 :: getUnlockTitle()
{
	return "Star lover";
}

// TODO : Add the path for the images

string Achievement_Stars100 :: getUnlockImagePath()
{
	return "";
}

string Achievement_Stars100 :: getLockImagePath()
{
	return "";
}

// End

void Achievement_Stars100 :: check()
{
	if (done)
		return;
	if (DataCore::sharedCore()->getTotalStar() >= 100)
	{
		done = true;
		DataCore::sharedCore()->setBoolKey(storename, true);	
		DataCore::sharedCore()->save();
	}
}