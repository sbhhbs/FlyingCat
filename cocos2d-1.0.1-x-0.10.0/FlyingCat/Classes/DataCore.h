#ifndef __DATA_CORE_H__
#define __DATA_CORE_H__

#include "cocos2d.h"

USING_NS_CC;

typedef enum
{
	kWorldRect,
	kWorldRound,
	kWorldUnKnown
}WorldType;

typedef enum
{
	kClassic,
	kTimeTrial,
	kSurvial,
	kModeunknown
}GameMode;

typedef enum
{
	kKitty1,
	kKitty2,
	kKitty3,
	kKitty4,
	kKittyUnknown
}KittyType;



class DataCore
{
public:
	                           
	static DataCore* sharedCore();

	//Call this before sharedCore to check first run status!
	static bool firstRun();

	//this can be call during gameplay
	//thus, achievement will be real-time
	void addTotalTime(int timeInMinute);
	int getTotalTime();

	//this can be call during gameplay
	//thus, achievement will be real-time
	void addTotalDistance(int distance);
	int getTotoalDistance();

	//this can be call during gameplay
	//thus, achievement will be real-time
	void addTotalStar(int starCount);
	int getTotalStar();
	
	//return true if it is a new best!
	bool finishAGameWithScore(int score, WorldType world, GameMode mode);
	int getBestScoreFor(WorldType world, GameMode mode);
	    


	//////////////////////////////////////////////////////////////////////////
	//Settings
	bool getSFX();
	void setSFX(bool status);
	void switchSFX();

	bool getBGM();
	void setBGM(bool status);
	void switchBGM();

	void resetGame();

	
	void save();
	void load();
	

	void setCurrent(WorldType world, KittyType kitty, GameMode mode);

	void getCurrent(WorldType & world, KittyType &kitty, GameMode &mode);




	//For Achievement
	//You can set your own bool attributes here.
	//if not exist, will return false
	void setBoolKey(string str,bool value);
	bool getBoolKey(string str);

private:
	DataCore();
	static DataCore *instance;

	string getWorldModeString(WorldType world, GameMode mode);

	WorldType currentWorld;
	KittyType currentKitty;
	GameMode currentMode;
};

#endif //__DATA_CORE_H__