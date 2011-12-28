#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_

#include "cocos2d.h"
#include "BtnProtocal.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Pause : public CCLayerColor
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend to return the exactly class pointer
	static cocos2d::CCScene* scene();

	void setDistance(long);

	void setStar(long);

	void gameResume(CCObject*);

	void mainMenu(CCObject*);

	void setDelegate(BtnProtocal *iamadelegate);
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Pause);
protected:
	CCLabelBMFont *_currentDistance;
	CCLabelBMFont *_currentStar;
	CCLabelBMFont *_title;
	CCLabelBMFont *_distanceLabel;
	CCLabelBMFont *_starLabel;
	CCLabelBMFont *_resume;
	CCLabelBMFont *_mainMenu;

	BtnProtocal   *_delegate;

};

#endif