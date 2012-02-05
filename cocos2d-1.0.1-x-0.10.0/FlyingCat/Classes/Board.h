// @ Author: Trine
// @ Last Modified : 2012/1/30

#ifndef _BOARD_H_
#define _BOARD_H_

#include "cocos2d.h"
#include "BtnProtocal.h"
#include "BoardParent.h"

#include "SimpleAudioEngine.h"

extern class BoardParent;

using namespace cocos2d;

class Board : public CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend to return the exactly class pointer
	static cocos2d::CCScene* scene();

	void setItem1Text(std::string);

	void setItem2Text(std::string);

	void setItem1Descritor(std::string);

	void setItem2Descriptor(std::string);

	void button1Func(CCObject*);

	void button2Func(CCObject*);

	void setTitle(std::string);

	void setScale(int);

	void setButton1Func(void(*)(CCObject*));

	void setButton2Func(void(*)(CCObject*));

	void setButton1Text(std::string);
	
	void setButton2Text(std::string);

	void setBoardParent(BoardParent*);

	virtual void ccTouchEnded(CCTouch*, CCEvent*);

	virtual bool ccTouchBegan(CCTouch*, CCEvent*);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Board);
protected:
	CCLabelBMFont *_item1;
	CCLabelBMFont *_item2;
	CCLabelBMFont *_title;
	CCLabelBMFont *_item1Descriptor;
	CCLabelBMFont *_item2Descriptor;
	CCLabelBMFont *_button1;
	CCLabelBMFont *_button2;                                                                

	void (* _button1Func)(CCObject*);
	void (* _button2Func)(CCObject*);

	BoardParent *_boardParent;

	BtnProtocal   *_delegate;

};

#endif