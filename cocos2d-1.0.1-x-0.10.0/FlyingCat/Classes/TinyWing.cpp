#include "TinyWing.h"
#include "Terrain.h"

using namespace cocos2d;

CCScene* TinyWing::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        TinyWing *layer = TinyWing::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TinyWing::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

		this->setupWorld();

		terrain = new Terrain();
		terrain->autorelease();
		terrain->initWithWorld(_world);
		
		
		CCSprite *stripes = CCSprite::spriteWithFile("board.png");
		ccTexParams tp2 = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};
		stripes->getTexture()->setTexParameters(&tp2);
		stripes->retain();
		terrain->_stripes = stripes;

		//terrain->setScale(0.25);


		this->addChild(terrain);

		_hero = new Hero();
		_hero->autorelease();
		_hero->initWithWorld(_world);
		terrain->addChild(_hero);


		this->scheduleUpdate();

		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
        bRet = true;
    } while (0);

    return bRet;
}

void TinyWing::update( ccTime dt )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float scale = (winSize.height*3/4) / _hero->getPosition().y;
	if (scale > 1) scale = 1;
	terrain->setScale(scale);


	if (_tapDown) {
		if (!_hero->_awake) {
			_hero->wake();
			_tapDown = false;
		} else {
			_hero->dive();
		}
	}
	_hero->limitVelocity();
//	[_hero limitVelocity];

	static double UPDATE_INTERVAL = 1.0f/60.0f;
	static double MAX_CYCLES_PER_FRAME = 5;
	static double timeAccumulator = 0;

	timeAccumulator += dt;    
	if (timeAccumulator > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
		timeAccumulator = UPDATE_INTERVAL;
	}    

	int32 velocityIterations = 3;
	int32 positionIterations = 2;
	while (timeAccumulator >= UPDATE_INTERVAL) {        
		timeAccumulator -= UPDATE_INTERVAL;        
		_world->Step(UPDATE_INTERVAL, 
			velocityIterations, positionIterations);        
		_world->ClearForces();

	}

	_hero->update();
	float offset = _hero->getPosition().x;

	/*static float offset = 0;
	static float distance = 500;
	offset += distance * dt;*/

	terrain->setOffsetX(offset);

	
}

void TinyWing::setupWorld()
{
	b2Vec2 gravity = b2Vec2(0.0f, -7.0f);
	bool doSleep = true;
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
}

void TinyWing::createTestBodyAtPostition( CCPoint position )
{
	b2BodyDef testBodyDef;
	testBodyDef.type = b2_dynamicBody;
	testBodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
	b2Body * testBody = _world->CreateBody(&testBodyDef);

	b2CircleShape testBodyShape;
	b2FixtureDef testFixtureDef;
	testBodyShape.m_radius = 25.0/PTM_RATIO;
	testFixtureDef.shape = &testBodyShape;
	testFixtureDef.density = 1.0;
	testFixtureDef.friction = 0.2;
	testFixtureDef.restitution = 0.5;
	testBody->CreateFixture(&testFixtureDef);
}

bool TinyWing::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	 _tapDown = true; 
	 return true;
}

void TinyWing::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	_tapDown = false; 
}

