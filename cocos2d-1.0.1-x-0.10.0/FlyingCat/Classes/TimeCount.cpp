#include "TimeCount.h"

TimeCount :: TimeCount()
{
	_time = 0;
	_stop = true;
}



void TimeCount :: setDelegate(BtnProtocal *delegate)
{
	_delegate = delegate;
}


bool TimeCount :: init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////


		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		this->schedule(schedule_selector(TimeCount::increaseTime, 1.0f));

		bRet = true;
	} while (0);

	return bRet;

}


void TimeCount ::increaseTime(ccTime dt)
{
	if (!_stop)
		_time++;
}

long TimeCount :: getTime()
{
	return _time;
}

void TimeCount :: continueCount()
{
	_stop = false;
}

void TimeCount ::stopCount()
{
	_stop = true;
}