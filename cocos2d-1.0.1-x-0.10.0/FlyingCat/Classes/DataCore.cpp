#include "DataCore.h"
#include "cocos2d.h"
#include "MyUserDefault.h"
#include <assert.h>
using namespace cocos2d;

#define DATACORE_VERSION 1

DataCore * DataCore::instance = NULL;

DataCore* DataCore::sharedCore()
{	
	if(!instance)
	{
		instance = new DataCore();

		if(firstRun())
		{
			instance->resetGame();
		}

		assert((MyUserDefault::sharedUserDefault()->getIntegerForKey("version",0)) == DATACORE_VERSION);
	}
	return instance;
}


bool DataCore::getSFX()
{
	return  MyUserDefault::sharedUserDefault()->getBoolForKey("SFX");
}

void DataCore::setSFX( bool status )
{
	MyUserDefault::sharedUserDefault()->setBoolForKey("SFX",status);
}

void DataCore::switchSFX()
{
	setSFX(!getSFX());
}

bool DataCore::getBGM()
{
	return MyUserDefault::sharedUserDefault()->getBoolForKey("BGM");
}

void DataCore::setBGM( bool status )
{
	MyUserDefault::sharedUserDefault()->setBoolForKey("BGM",status);
}

void DataCore::switchBGM()
{
	setBGM(!getBGM());
}

void DataCore::resetGame()
{
	MyUserDefault::sharedUserDefault()->clear();
	MyUserDefault::sharedUserDefault()->setAutoSave(false);
	CCLog("Entering ResetGame");
	MyUserDefault::sharedUserDefault()->setBoolForKey("FirstRun",false);
	MyUserDefault::sharedUserDefault()->setIntegerForKey("version",DATACORE_VERSION);
	char buffer[64];
	MyUserDefault::sharedUserDefault()->setBoolForKey("SFX",true);
	MyUserDefault::sharedUserDefault()->setBoolForKey("BGM",true);
	MyUserDefault::sharedUserDefault()->setIntegerForKey("TotalTime",0);
	MyUserDefault::sharedUserDefault()->setIntegerForKey("TotalDistance",0);
	MyUserDefault::sharedUserDefault()->setIntegerForKey("TotalStar",0);
	MyUserDefault::sharedUserDefault()->setIntegerForKey("BestStar",0);
	MyUserDefault::sharedUserDefault()->save();
}


DataCore::DataCore()
{
	currentKitty = kKittyUnknown;
	currentMode = kModeunknown;
	currentWorld = kWorldUnKnown;
}


void DataCore::addTotalTime( int timeInMinute )
{
	long total = timeInMinute + getTotalTime();
	if(total >= 60000) 
		total = 60000;
	MyUserDefault::sharedUserDefault()->setIntegerForKey("TotalTime",total);
}

int DataCore::getTotalTime()
{
	return MyUserDefault::sharedUserDefault()->getIntegerForKey("TotalTime",0);
}

bool DataCore::firstRun()
{
	return MyUserDefault::sharedUserDefault()->getBoolForKey("FirstRun",true);
}


void DataCore::save()
{
	MyUserDefault::sharedUserDefault()->save();
}

void DataCore::load()
{
	MyUserDefault::sharedUserDefault()->load();
}

void DataCore::setBoolKey( string str,bool value )
{
	MyUserDefault::sharedUserDefault()->setBoolForKey(str.c_str(),value);
}

bool DataCore::getBoolKey( string str )
{
	return MyUserDefault::sharedUserDefault()->getBoolForKey(str.c_str());
}

void DataCore::getCurrent( WorldType & world, KittyType &kitty, GameMode &mode )
{
	world = currentWorld;
	kitty = currentKitty;
	mode = currentMode;
}

void DataCore::addTotalDistance( int distance )
{
	long total = distance + getTotoalDistance();
	if(total >= 60000) 
		total = 60000;
	MyUserDefault::sharedUserDefault()->setIntegerForKey("TotalDistance",total);
}

void DataCore::addTotalStar( int starCount )
{
	long total = starCount + getTotalStar();
	if(total >= 60000) 
		total = 60000;
	MyUserDefault::sharedUserDefault()->setIntegerForKey("TotalStar",total);
}

int DataCore::getTotalStar()
{
	return MyUserDefault::sharedUserDefault()->getIntegerForKey("TotalStar",0);
}

int DataCore::getTotoalDistance()
{
	return MyUserDefault::sharedUserDefault()->getIntegerForKey("TotalDistance",0);
}

void DataCore::setCurrent( WorldType world, KittyType kitty, GameMode mode )
{
	currentKitty = kitty;
	currentMode = mode;
	currentWorld = world;
}

bool DataCore::finishAGameWithScore( int score, WorldType world, GameMode mode )
{
	if(score > getBestScoreFor(world,mode))
	{
		MyUserDefault::sharedUserDefault()->setIntegerForKey(getWorldModeString(world,mode).c_str(),score);
		return true;
	}
	return false;
}

int DataCore::getBestScoreFor( WorldType world, GameMode mode )
{	
	return MyUserDefault::sharedUserDefault()->getIntegerForKey(getWorldModeString(world,mode).c_str());
}

std::string DataCore::getWorldModeString( WorldType world, GameMode mode )
{
	string str = "";
	switch (world)
	{
	case kWorldRect:
		str += "rect_";
		break;
	case kWorldRound:
		str += "round_";
		break;
	}
	switch (mode)
	{
	case kSurvial:
		str += "survival";
		break;
	case kTimeTrial:
		str += "round";
		break;
	case kClassic:
		str += "classic";
		break;
	}
	str += "_best";
	return str;
}
