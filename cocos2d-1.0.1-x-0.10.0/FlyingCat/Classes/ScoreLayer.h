#pragma once


#include "cocos2d.h"

USING_NS_CC;

class ScoreLayer : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	void setBest(long bestScore);

	void setCurrentStar(long star);

	void setCurrentDistance(long distance);

	
	void appear();

	void disappear();


	// implement the "static node()" method manually
	LAYER_NODE_FUNC(ScoreLayer);
protected:
	long best;
	long currentStar;
	long currentDistance;
	CCLabelBMFont *bestLabel;
	CCLabelBMFont *starLabel;
	CCLabelBMFont *distanceLabel;
};
