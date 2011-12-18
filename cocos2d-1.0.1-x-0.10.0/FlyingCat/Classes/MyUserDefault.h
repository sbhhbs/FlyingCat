#ifndef __MyUD_H__
#define __MyUD_H__
#include <string>
#include <map>

using namespace std;

class  MyUserDefault
{
public:
	// get value methods

	/**
	@brief Get bool value by key, if the key doesn't exist, a default value will return.
	 You can set the default value, or it is false.
	*/
	bool	getBoolForKey(const char* pKey, bool defaultValue = false);
	/**
	@brief Get integer value by key, if the key doesn't exist, a default value will return.
	 You can set the default value, or it is 0.
	*/
	int		getIntegerForKey(const char* pKey, int defaultValue = 0);
	/**
	@brief Get float value by key, if the key doesn't exist, a default value will return.
	 You can set the default value, or it is 0.0f.
	*/
	float	getFloatForKey(const char* pKey, float defaultValue=0.0f);
	/**
	@brief Get double value by key, if the key doesn't exist, a default value will return.
	 You can set the default value, or it is 0.0.
	*/
	double  getDoubleForKey(const char* pKey, double defaultValue=0.0);
	/**
	@brief Get string value by key, if the key doesn't exist, a default value will return.
	You can set the default value, or it is "".
	*/
	std::string getStringForKey(const char* pKey, const std::string & defaultValue = "");

	// set value methods

	/**
	@brief Set bool value by key.
	*/
	void	setBoolForKey(const char* pKey, bool value);
	/**
	@brief Set integer value by key.
	*/
	void	setIntegerForKey(const char* pKey, int value);
	/**
	@brief Set float value by key.
	*/
	void	setFloatForKey(const char* pKey, float value);
	/**
	@brief Set double value by key.
	*/
	void	setDoubleForKey(const char* pKey, double value);
	/**
	@brief Set string value by key.
	*/
	void	setStringForKey(const char* pKey, const std::string & value);

	static MyUserDefault* sharedUserDefault();

	void setAutoSave(bool status);
	void load();
	void save();
	void clear();
private:
	MyUserDefault();
	
	map<string,bool> boolLib;
	map<string,string> stringLib;
	map<string,int> intLib;
	map<string,float> floatLib;
	map<string,double> doubleLib;
	static MyUserDefault* instance;
	static std::string m_sFilePath;
	bool autosave;
};


#endif  // __MyUD_H__