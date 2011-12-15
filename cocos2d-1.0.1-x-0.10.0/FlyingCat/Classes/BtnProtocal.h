#ifndef __BtnProtocal__H__
#define __BtnProtocal__H__

#include "cocos2d.h"

USING_NS_CC;

class BtnProtocal
{
public:
	virtual void playPressed();
	virtual void creditPressed();
	virtual void settingPressed();

	virtual void settingSFXPressed();
	virtual void settingBGMPressed();
	virtual void settingBackPressed();

	virtual void creditBackPressed();

	virtual void pauseRestartPressed();
	virtual void pauseHomePressed();
	virtual void pauseResumePressed();

};

#endif //__BtnProtocal__H__