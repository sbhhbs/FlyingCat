#include "Terrain.h"

#include "HelloWorldScene.h"
#include "Hero.h"

void Terrain::generateHills()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();    
	float minDX = 160 * 2;
	float minDY = 60 * 2;
	int rangeDX = 80 * 2;
	int rangeDY = 40 * 2;

	float x = -minDX;
	float y = winSize.height/2-minDY;

	float dy, ny;
	float sign = 1; // +1 - going up, -1 - going  down
	float paddingTop = 20 * 2;
	float paddingBottom = 20 * 2;

	for (int i=0; i<kMaxHillKeyPoints; i++) {
		_hillKeyPoints[i] = ccp(x, y);
		if (i == 0) {
			x = 0;
			y = winSize.height/2;
		} else {
			x += rand()%rangeDX+minDX;
			while(true) {
				dy = rand()%rangeDY+minDY;
				ny = y + dy*sign;
				if(ny < winSize.height-paddingTop && ny > paddingBottom) {
					break;   
				}
			}
			y = ny;
		}
		sign *= -1;
	}
}

void Terrain::draw()
{
	if(!_stripes) return;
	glBindTexture(GL_TEXTURE_2D, _stripes->getTexture()->getName());
	glDisableClientState(GL_COLOR_ARRAY);

	glColor4f(1, 1, 1, 1);
	glVertexPointer(2, GL_FLOAT, 0, _hillVertices);
	glTexCoordPointer(2, GL_FLOAT, 0, _hillTexCoords);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nHillVertices);

	for(int i = MAX(_fromKeyPointI, 1); i <= _toKeyPointI; ++i) {
		glColor4f(1.0, 0, 0, 1.0); 
		//ccDrawLine(_hillKeyPoints[i-1], _hillKeyPoints[i]);    

		glColor4f(0.0, 0.0, 1.0, 1.0);

		CCPoint p0 = _hillKeyPoints[i-1];
		CCPoint p1 = _hillKeyPoints[i];
		int hSegments = floorf((p1.x-p0.x)/kHillSegmentWidth);
		float dx = (p1.x - p0.x) / hSegments;
		float da = M_PI / hSegments;
		float ymid = (p0.y + p1.y) / 2;
		float ampl = (p0.y - p1.y) / 2;

		CCPoint pt0, pt1;
		pt0 = p0;
		for (int j = 0; j < hSegments+1; ++j) {

			pt1.x = p0.x + j*dx;
			pt1.y = ymid + ampl * cosf(da*j);

			ccDrawLine(pt0, pt1);

			pt0 = pt1;

		}

	}

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//_world->DrawDebugData();

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

bool Terrain::initWithWorld(b2World * world )
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());
		_fromKeyPointI = 0;
		_toKeyPointI = 0;
		//_stripes = NULL;
		_body = NULL;
		_world = world;
		this->setupDebugDraw();
		this->generateHills();
		this->resetHillVertices();

		Hero *hero = new Hero();
		hero->autorelease();
		hero->initWithWorld(_world);

		this->addChild(hero);
		bRet = true;
	} while (0);

	return bRet;
}

void Terrain::setOffsetX( float newOffsetX )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_offsetX = newOffsetX;
	this->setPosition(ccp(winSize.width/8-_offsetX*this->getScale(), 0));
	this->resetHillVertices();
}

void Terrain::resetHillVertices()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();    
	static int prevFromKeyPointI = -1;
	static int prevToKeyPointI = -1;

	// key points interval for drawing
	while (_hillKeyPoints[_fromKeyPointI+1].x < _offsetX-winSize.width/8/this->getScale()) {
		_fromKeyPointI++;
	}
	while (_hillKeyPoints[_toKeyPointI].x < _offsetX+winSize.width*9/8/this->getScale()) {
		_toKeyPointI++;
	}
	
	_fromKeyPointI--;
	if(_fromKeyPointI < 0) _fromKeyPointI = 0;


	if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI) {

		// vertices for visible area
		_nHillVertices = 0;
		_nBorderVertices = 0;
		CCPoint p0, p1, pt0, pt1;
		p0 = _hillKeyPoints[_fromKeyPointI];
		for (int i=_fromKeyPointI+1; i<_toKeyPointI+1; i++) {
			p1 = _hillKeyPoints[i];

			// triangle strip between p0 and p1
			int hSegments = floorf((p1.x-p0.x)/kHillSegmentWidth);
			float dx = (p1.x - p0.x) / hSegments;
			float da = M_PI / hSegments;
			float ymid = (p0.y + p1.y) / 2;
			float ampl = (p0.y - p1.y) / 2;
			pt0 = p0;
			_borderVertices[_nBorderVertices++] = pt0;
			for (int j=1; j<hSegments+1; j++) {
				pt1.x = p0.x + j*dx;
				pt1.y = ymid + ampl * cosf(da*j);
				_borderVertices[_nBorderVertices++] = pt1;

				_hillVertices[_nHillVertices] = CCPointMake(pt0.x, 0);
				_hillTexCoords[_nHillVertices++] = CCPointMake(pt0.x/512, 1.0f);
				_hillVertices[_nHillVertices] = CCPointMake(pt1.x, 0);
				_hillTexCoords[_nHillVertices++] = CCPointMake(pt1.x/512, 1.0f);

				_hillVertices[_nHillVertices] = CCPointMake(pt0.x, pt0.y);
				_hillTexCoords[_nHillVertices++] = CCPointMake(pt0.x/512, 0);
				_hillVertices[_nHillVertices] = CCPointMake(pt1.x, pt1.y);
				_hillTexCoords[_nHillVertices++] = CCPointMake(pt1.x/512, 0);

				pt0 = pt1;
			}

			p0 = p1;
		}

		prevFromKeyPointI = _fromKeyPointI;
		prevToKeyPointI = _toKeyPointI;    
		this->resetBox2DBody();
	}
}

void Terrain::resetBox2DBody()
{

	if(_body) {
		_world->DestroyBody(_body);
	}

	b2BodyDef bd;
	bd.position.Set(0, 0);

	_body = _world->CreateBody(&bd);

	b2EdgeShape shape;

	b2Vec2 p1, p2;
	for (int i=0; i<_nBorderVertices-1; i++) {
		p1 = b2Vec2(_borderVertices[i].x/PTM_RATIO,_borderVertices[i].y/PTM_RATIO);
		p2 = b2Vec2(_borderVertices[i+1].x/PTM_RATIO,_borderVertices[i+1].y/PTM_RATIO);
		shape.Set(p1, p2);
		_body->CreateFixture(&shape, 0);
	}
}

void Terrain::setupDebugDraw()
{
	/*_debugDraw = new GLESDebugDraw(PTM_RATIO * CCDirector::sharedDirector()->getContentScaleFactor());
	_world->SetDebugDraw(_debugDraw);
	_debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);*/
}
