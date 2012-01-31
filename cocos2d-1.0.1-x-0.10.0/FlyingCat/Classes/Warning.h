// @ Author : Trine
// @ Last Modified : 2012/1/30

#pragma once

#include "cocos2d.h"
#include "BtnProtocal.h"
#include <string>

using namespace cocos2d;


USING_NS_CC;

class Warning : public cocos2d::CCLayer
{
public:
	Warning();
	Warning(int, string);

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Warning);
protected: 
	std :: string _warningContent;
	int _angle;
	BtnProtocal   *_delegate;
	CCLabelBMFont *_warningLabel;
};
