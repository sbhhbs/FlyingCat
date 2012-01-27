#include "Hero.h"


void Hero::createBody()
{
	float radius = 32.0f;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int screenH = size.height;

	CCPoint startPosition = ccp(0, screenH/2+radius);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.linearDamping = 0.1f;
	bd.fixedRotation = true;
	bd.position.Set(startPosition.x/PTM_RATIO, startPosition.y/PTM_RATIO);
	_body = _world->CreateBody(&bd);

	b2CircleShape shape;
	shape.m_radius = radius/PTM_RATIO;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 0.5f;
	fd.restitution = 0.0f;
	fd.friction = 0.1;

	_body->CreateFixture(&fd);
}

void Hero::update()
{
	this->setPosition(ccp(_body->GetPosition().x*PTM_RATIO, _body->GetPosition().y*PTM_RATIO));
	b2Vec2 vel = _body->GetLinearVelocity();
	b2Vec2 weightedVel = vel;

	for(int i = 0; i < NUM_PREV_VELS; ++i) {
		weightedVel += _prevVels[i];
	}
	weightedVel = b2Vec2(weightedVel.x/NUM_PREV_VELS, weightedVel.y/NUM_PREV_VELS);    
	_prevVels[_nextVel++] = vel;
	if (_nextVel >= NUM_PREV_VELS) _nextVel = 0;

	float angle = ccpToAngle(ccp(vel.x, vel.y));  
	if (_awake) {  
		this->setRotation(-1 * CC_RADIANS_TO_DEGREES(angle));
	}
}

bool Hero::initWithWorld( b2World * world )
{
	
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCSprite::init());
		
		cat = Cat1::node();
		
		this->addChild(cat);

		_nextVel = 0;
		this->_world = world;
		this->createBody();

		bRet = true;
	} while (0);

	return bRet;
	

}

void Hero::wake()
{
	_awake = true;
	_body->SetActive(true);
	_body->ApplyLinearImpulse(b2Vec2(2,4), _body->GetPosition());
}

void Hero::dive()
{
	_body->ApplyForce(b2Vec2(10,-100),_body->GetPosition());
}

void Hero::limitVelocity()
{
	if (!_awake) return;

	const float minVelocityX = 5;
	const float minVelocityY = -40;
	b2Vec2 vel = _body->GetLinearVelocity();
	if (vel.x < minVelocityX) {
		vel.x = minVelocityX;
	}
	if (vel.y < minVelocityY) {
		vel.y = minVelocityY;
	}
	_body->SetLinearVelocity(vel);
}
