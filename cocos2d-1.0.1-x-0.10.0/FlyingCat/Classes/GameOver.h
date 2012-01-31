// @ Author: Trine
// @ Last Modified : 2012/1/30

#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_

#include "cocos2d.h"
#include "BtnProtocal.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GameOver : public CCLayerColor
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend to return the exactly class pointer
	static cocos2d::CCScene* scene();

	void setDistance(long);

	void setStar(long);

	void gameRestart(CCObject*);

	void mainMenu(CCObject*);

	void setDelegate(BtnProtocal *iamadelegate);
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(GameOver);
protected:
	CCLabelBMFont *_finalDistance;
	CCLabelBMFont *_finalStar;
	CCLabelBMFont *_title;
	CCLabelBMFont *_distanceLabel;
	CCLabelBMFont *_starLabel;
	CCLabelBMFont *_restart;
	CCLabelBMFont *_mainMenu;

	BtnProtocal   *_delegate;

};

#endif