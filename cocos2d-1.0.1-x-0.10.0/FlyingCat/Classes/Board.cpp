#include "Board.h"

using namespace cocos2d;

bool Board :: init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CC_BREAK_IF(! CCLayer::init());

		CCSprite *back = CCSprite::spriteWithFile("back.png");

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		back->setPosition(ccp(winSize.width / 2, winSize.height / 2));

		this->addChild(back);

		//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);

		_delegate = NULL;

		_item1 = CCLabelBMFont::labelWithString("100","Bigfnt.fnt");
		_item1->setScale(0.5);
		_item2 = CCLabelBMFont::labelWithString("100","Bigfnt.fnt");
		_item2->setScale(0.5);
		_title = CCLabelBMFont::labelWithString("Pause", "Bigfnt.fnt");
		_title->setScale(0.5);
		_item1Descriptor = CCLabelBMFont::labelWithString("Distance : ", "Bigfnt.fnt");
		_item1Descriptor->setScale(0.5);
		_item2Descriptor = CCLabelBMFont::labelWithString("Star gathered : ", "Bigfnt.fnt");
		_item2Descriptor->setScale(0.5);
		_button1 = CCLabelBMFont::labelWithString("Restart", "Bigfnt.fnt");
		_button1->setScale(0.5);
		_button2 = CCLabelBMFont::labelWithString("Main Menu", "Bigfnt.fnt");
		_button2->setScale(0.5);


		CCMenuItemLabel *button1 = CCMenuItemLabel::itemWithLabel(_button1, this, menu_selector(Board::button1Func));	
		CCMenuItemLabel *button2 = CCMenuItemLabel::itemWithLabel(_button2, this, menu_selector(Board::button2Func));

		_title->setPosition(ccp(winSize.width / 2,winSize.height / 2 + back->getContentSize().height / 2 - _item2Descriptor->getContentSize().height / 2 - 100));

		_item1->setPosition(ccp(winSize.width / 2 - back->getContentSize().width / 2 + _item1->getContentSize().width + 40, 
			_title->getPosition().y - _title->getContentSize().height / 2 -  _item1->getContentSize().height / 2 ));

		_item1Descriptor->setPosition(ccp(back->getPosition().x +  back->getContentSize().width / 2 - _item1Descriptor->getContentSize().width / 2, 
			_title->getPosition().y - _title->getContentSize().height / 2 -  _item1->getContentSize().height / 2));

		_item2->setPosition(ccp(winSize.width / 2 - back->getContentSize().width / 2 + _item2->getContentSize().width + 10, 
			_item1Descriptor->getPosition().y - _item1Descriptor->getContentSize().height / 2 -  _item2->getContentSize().height / 2 + 10));

		_item2Descriptor->setPosition(ccp(back->getPosition().x + back->getContentSize().width / 2  - _item1Descriptor->getContentSize().width / 2, 
			_item1Descriptor->getPosition().y - _item1Descriptor->getContentSize().height / 2 -  _item2->getContentSize().height / 2 + 10));

		/*_button1->setPosition(ccp(winSize.width / 2 - back->getContentSize().width / 4 + _item2->getContentSize().width / 2 , 
			_item2Descriptor->getPosition().y - _item2Descriptor->getContentSize().height / 2 - 3 * _button1->getContentSize().height / 2 + 50));

		_button2->setPosition(ccp(back->getPosition().x + back->getContentSize().width / 2 - 80,
			_item2Descriptor->getPosition().y - _item2Descriptor->getContentSize().height / 2 - 3 * _button1->getContentSize().height / 2 + 50));
*/
		/*_button1->setPosition(ccp(100,100));
		_button2->setPosition(ccp(200,100));
*/
		CCMenu *buttonMenu = CCMenu::menuWithItems(button1, button2, NULL);
		buttonMenu->alignItemsHorizontally();
		//buttonMenu->setPosition(CCPointZero);
		buttonMenu->setPosition(ccpAdd(buttonMenu->getPosition(),ccp(100,-100)));
		
		buttonMenu->setTag(1);

		this->addChild(_item1);
		this->addChild(_item1Descriptor);
		this->addChild(_title);
		this->addChild(_item2);
		this->addChild(_item2Descriptor);
		this->addChild(buttonMenu);

		//this->setAnchorPoint(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2 ));

		bRet = true;
	} while (0);

	return bRet;
}

CCScene* Board::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Board *layer = Board::node();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

void Board :: setItem1Text(std::string text)
{
	_item1->setString(text.c_str());
}

void Board :: setItem2Text(std::string text)
{
	_item2->setString(text.c_str());
}

void Board :: button1Func(CCObject* object)
{
	//_button1Func(object);
	_boardParent->button1Func(object);
}

void Board :: button2Func(CCObject* object)
{
	//_button2Func(object);
	_boardParent->button2Func(object);
}

// To Be used

void Board :: setButton1Func(void( *buttonFunc)(CCObject *object))
{
	_button1Func = buttonFunc;
}

void Board :: setButton2Func(void( *buttonFunc)(CCObject *object))
{
	_button2Func = buttonFunc;
}

//

void Board ::setScale(int scale)
{
	_item1->setScale(0.5f);
	_item2->setScale(0.5f);
	_item1Descriptor->setScale(0.5f);
	_item2Descriptor->setScale(0.5f);
	_button1->setScale(0.5f);
	_button2->setScale(0.5f);
}

void Board :: setItem1Descritor(std::string text)
{
	_item1Descriptor->setString(text.c_str());
}

void Board :: setItem2Descriptor(std::string text)
{
	_item2Descriptor->setString(text.c_str());
}

void Board :: setTitle(std::string text)
{
	_title->setString(text.c_str());
}

void Board :: setButton1Text(std::string text)
{
	_button1->setString(text.c_str());
}

void Board :: setButton2Text(std::string text)
{
	_button2->setString(text.c_str());
}

void Board :: setBoardParent(BoardParent* parent)
{
	_boardParent = parent;                
}

void Board::ccTouchEnded( CCTouch*, CCEvent* )
{

}

bool Board::ccTouchBegan( CCTouch*, CCEvent* )
{
	return true;
}
