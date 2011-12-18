#include "MyUserDefault.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "cocos2d.h"

USING_NS_CC;

MyUserDefault* MyUserDefault::instance = NULL;

MyUserDefault* MyUserDefault::sharedUserDefault()
{
	if(!instance)
	{
		instance = new MyUserDefault();
		instance->load();
	}
	return instance;
}

MyUserDefault::MyUserDefault()
{
	string path(cocos2d::CCFileUtils::getWriteablePath());
	//string path;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	// In android, every programe has a director under /data/data.
//	// The path is /data/data/ + start activity package name.
//	// You can save application specific data here.
//	path.append("/data/data/cn.com.androidcontest.eightdiagram.EightDiagram/save.sav");
//#endif
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//	// You can save file in anywhere if you have the permision.
//	path.append("save.save");
//#endif
//#if (CC_TARGET_PLATFORM == CC_PLATFROM_IPHONE)
//	// You can save file in anywhere if you have the permision.
//    //path = 
//	path.append("save.save");
//#endif
    path.append("save.save");
	//path.append("/data/data/cn.com.androidcontest.taijipuzzle/taiji.sav");
	//CCLog("My UserDefault Construct: %s",path.c_str());
	autosave = false;
	m_sFilePath = path;
}

bool MyUserDefault::getBoolForKey( const char* pKey, bool defaultValue /*= false*/ )
{
	if(boolLib.count(pKey))
	{
		return boolLib[pKey];
	}
	return defaultValue;
}

int MyUserDefault::getIntegerForKey( const char* pKey, int defaultValue /*= 0*/ )
{
	if(intLib.count(pKey))
	{
		return intLib[pKey];
	}
	return defaultValue;
}

float MyUserDefault::getFloatForKey( const char* pKey, float defaultValue/*=0.0f*/ )
{
	if(floatLib.count(pKey))
	{
		return floatLib[pKey];
	}
	return defaultValue;
}

double MyUserDefault::getDoubleForKey( const char* pKey, double defaultValue/*=0.0*/ )
{
	if(doubleLib.count(pKey))
	{
		return doubleLib[pKey];
	}
	return defaultValue;
}

std::string MyUserDefault::getStringForKey( const char* pKey, const std::string & defaultValue /*= ""*/ )
{
	if(stringLib.count(pKey))
	{
		return stringLib[pKey];
	}
	return defaultValue;
}

void MyUserDefault::setBoolForKey( const char* pKey, bool value )
{
	boolLib[pKey] = value;
	if(autosave)
		save();
}

void MyUserDefault::setIntegerForKey( const char* pKey, int value )
{
	intLib[pKey] = value;
	if(autosave)
		save();
}

void MyUserDefault::setFloatForKey( const char* pKey, float value )
{
	floatLib[pKey] = value;
	if(autosave)
		save();
}

void MyUserDefault::setDoubleForKey( const char* pKey, double value )
{
	doubleLib[pKey] = value;
	if(autosave)
		save();
}

void MyUserDefault::setStringForKey( const char* pKey, const std::string & value )
{
	stringLib[pKey] = value;
	if(autosave)
		save();
}

void MyUserDefault::save()
{
	std::stringstream ss;
	
	ss<<boolLib.size()<<endl;
	map<string,bool>::iterator boolIt =  boolLib.begin();
	while(boolIt != boolLib.end())
	{
		ss<<boolIt->first<<endl;
		if(boolIt->second)
		{
			ss<<1<<endl;
		}
		else
		{
			ss<<0<<endl;
		}
		boolIt++;
	}


	ss<<stringLib.size()<<endl;
	map<string,string>::iterator stringIt = stringLib.begin();
	while(stringIt != stringLib.end())
	{
		ss<<stringIt->first<<endl;
		ss<<stringIt->second<<endl;
		stringIt++;
	}

	ss<<intLib.size()<<endl;
	map<string,int>::iterator intIt = intLib.begin();
	while(intIt != intLib.end())
	{
		ss<<intIt->first<<endl;
		ss<<intIt->second<<endl;
		intIt++;
	}

	ss<<floatLib.size()<<endl;
	map<string,float>::iterator floatIt = floatLib.begin();
	while(floatIt != floatLib.end())
	{
		ss<<floatIt->first<<endl;
		ss<<floatIt->second<<endl;
		floatIt++;
	}

	ss<<doubleLib.size()<<endl;
	map<string,double>::iterator doubleIt = doubleLib.begin();
	while(doubleIt != doubleLib.end())
	{
		ss<<doubleIt->first<<endl;
		ss<<doubleIt->second<<endl;
		doubleIt++;
	}
	CCLog("My UserDefault Save: %s",m_sFilePath.c_str());
	//CCLog("Data: %s",ss.str().c_str());
	std::ofstream ofs(m_sFilePath.c_str());
	if(ofs.bad())
	{
		CCLog("Saving: bad");
	}
	else
	{
		CCLog("Saving: good");
	}
	ofs << ss.str();
	ofs.close();
}

void MyUserDefault::load()
{
	ifstream ss(m_sFilePath.c_str());
	CCLog("My UserDefault load: %s",m_sFilePath.c_str());
	if(ss.bad())
	{
		CCLog("loading: bad");
	}
	else
	{
		CCLog("loading: good");
	}
	clear();

	int boolLibSize,intLibSize,floatLibSize,stringLibSize,doubleLibSize;



	ss>>boolLibSize;
	for(int i=0;i<boolLibSize;i++)
	{
		char key[256];
		int value;
		ss.getline(key,256);
		ss.getline(key,256);
		ss>>value;
		if(value)
		{
			boolLib[key] = true;
		}
		else
		{
			boolLib[key] = false;
		}
	}


	ss>>stringLibSize;
	for(int i=0;i<stringLibSize;i++)
	{
		char key[256];
		char value[256];
		ss.getline(key,256);
		ss.getline(key,256);
		ss.getline(value,256);
		stringLib[key] = value;
	}

	ss>>intLibSize;
	for(int i=0;i<intLibSize;i++)
	{
		char key[256];
		int value;
		ss.getline(key,256);
		ss.getline(key,256);
		ss>>value;
		intLib[key] = value;
	}

	ss>>floatLibSize;
	for(int i=0;i<floatLibSize;i++)
	{
		char key[256];
		float value;
		ss.getline(key,256);
		ss.getline(key,256);
		ss>>value;
		floatLib[key] = value;
	}

	ss>>doubleLibSize;
	for(int i=0;i<doubleLibSize;i++)
	{
		char key[256];
		double value;
		ss.getline(key,256);
		ss.getline(key,256);
		ss>>value;
		doubleLib[key] = value;
	}
	ss.close();
	CCLog("loading complete");
}

void MyUserDefault::setAutoSave( bool status )
{
	autosave = status;
}

void MyUserDefault::clear()
{
	boolLib.clear();
	intLib.clear();
	floatLib.clear();
	stringLib.clear();
	doubleLib.clear();
}

std::string MyUserDefault::m_sFilePath = "";


