#ifndef L_UPLOADER_H
#define L_UPLOADER_H

#define DEFAULT_BUFLEN 512

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>


class LUploader {
	
	private:
		SOCKET Cs = INVALID_SOCKET;
		std::ifstream mfile;
		std::string host;
		std::string port;
		std::string fileName;
		long logTime;
		bool canLog;
		
	public:
		LUploader(const char *,const char *, const char *);
		WSADATA wsd;
		void initConnection();
		int uploadIt();
		void sendIt(const char*);
			void sendHttp();
				void lExit(){
		exit(1);
	};
	
		~LUploader();
};


#endif
