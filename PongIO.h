
#ifndef PongIO
#define PongIO

#include<windows.h>

#define CONSOLE_LOGGING
//#define BOX_LOGGING

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

inline void error(std::string text){
	#ifdef CONSOLE_LOGGING
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	std::cout<<"Error: ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout<<text<<"\n";
	#endif
	#ifdef BOX_LOGGING
	MessageBox(NULL, text.c_str(), "Error", MB_OK | MB_ICONERROR);
	#endif
	
}

inline void warn(std::string text){
	#ifdef CONSOLE_LOGGING
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout<<"Warning: ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout<<text<<"\n";
	#endif
	#ifdef BOX_LOGGING
	MessageBox(NULL, text.c_str(), "Warning", MB_OK | MB_ICONWARNING);
	#endif
}

inline void print(std::string text){
	#ifdef CONSOLE_LOGGING
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout<<"Message: ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout<<text<<"\n";
	#endif
	#ifdef BOX_LOGGING
	MessageBox(NULL, text.c_str(), "Message", MB_OK | MB_ICONINFORMATION);
	#endif
}

std::string readFile(std::string filename){
	std::ifstream ifs(filename);
	std::stringstream ss;
	ss<<ifs.rdbuf();
	return ss.str();
}


#ifdef CONSOLE_LOGGING
#undef CONSOLE_LOGGING
#endif

#ifdef BOX_LOGGING
#undef BOX_LOGGING
#endif

#endif