#include "TimeLayer.h"

TimeLayer :: TimeLayer()
{
	_initialTime = 60;
	_collisionUnitTime = 10;
	_restTime = _initialTime;
}

bool TimeLayer :: decreaseRestTime()
{
	char buffer[64];

	if (_restTime - 1 < 0)
		_restTime = 0;
	else
		_restTime--;

	sprintf(buffer,"Time Left : %d",_restTime);

	_timeLabel->setString(buffer);

	_clockTick = true;

	if (_restTime == 0)
		return true;
	else
		return false;
}


bool TimeLayer ::decreaseCollisionTime()
{
	if (_clockTick)
	{
		char buffer[64];

		if (_restTime - _collisionUnitTime < 0)
			_restTime = 0;
		else
			_restTime -= _collisionUnitTime;

		sprintf(buffer,"Time Left : %d",_restTime);

		_timeLabel->setString(buffer);

		_clockTick = false;
	}

	if (_restTime == 0)
		return true;
	else
		return false;

}

void TimeLayer :: setInitalTime(long time)
{
	char buffer[64];

	_initialTime = time;

	sprintf(buffer,"Time Left : %d",_initialTime);

	_timeLabel->setString(buffer);
}

bool TimeLayer :: init()
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

		_timeLabel = CCLabelBMFont::labelWithString("Time Left : 60","Bigfnt.fnt");

		_timeLabel->setPosition(ccp(winSize.width / 2, winSize.height - _timeLabel->getContentSize().height / 2));

		_timeLabel->setScale(0.5f);

		this->addChild(_timeLabel);

		bRet = true;
	} while (0);

	return bRet;

}