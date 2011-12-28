#pragma once
#include "cocos2d.h"
#include "tests\tests\Box2DTestBed\GLES-Render.h"

#define kMaxHillKeyPoints 1000

#define kHillSegmentWidth 20

#define kMaxHillVertices 4000
#define kMaxBorderVertices 800 

USING_NS_CC;

class Terrain : public CCLayer {
public:
	int _offsetX;
	CCPoint _hillKeyPoints[kMaxHillKeyPoints];
	CCSprite *_stripes;

	virtual bool initWithWorld(b2World * world );  

	void setOffsetX(float newOffsetX);
	void generateHills();
	void draw();

	int _fromKeyPointI;
	int _toKeyPointI;

	void resetHillVertices();

	//LAYER_NODE_FUNC(Terrain);

	b2World *_world;
	b2Body *_body;
	GLESDebugDraw * _debugDraw;

	int _nHillVertices;
	CCPoint _hillVertices[kMaxHillVertices];
	CCPoint _hillTexCoords[kMaxHillVertices];
	int _nBorderVertices;

	void resetBox2DBody();
	void setupDebugDraw();



	CCPoint _borderVertices[kMaxBorderVertices];
};