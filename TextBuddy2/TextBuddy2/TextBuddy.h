//Header file

#ifndef TEXTBUDDY_H_
#define TEXTBUDDY_H_
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>

using namespace std;

class TextBuddy {
public:
	//all types of commands supported
	enum COMMAND_TYPE {
		ADD, DELETE, CLEAR, SEARCH, SORT, DISPLAY, INVALID, EXIT
	};

private:
	//all feedback messages
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_ADD;
	static const string MESSAGE_DELETE;
	static const string MESSAGE_CLEAR;
	static const string MESSAGE_SEARCH_NO_RESULT;
	static const string MESSAGE_SORT;
	static const string MESSAGE_EMPTY;
	static const string MESSAGE_INVALID;

	//all global variables
	static list<string> textList; //a string list to store all the text content from user.
	static string fileName;
	static char buffer[255];
	static bool userExit; //to trigger the condition of exiting the programme.
	static ofstream outFile;

	//all private functions that is only used in TextBuddy.cpp
	static void showToUser(string text);
	static COMMAND_TYPE determineCommandType(string commandString);
	static bool isEmpty();
	static string bufferEmptyProcess();
	static string bufferInvalidProcess();
	static string addTextProcess(string text);
	static string deleteTextProcess(int textNumber);
	static string clearTextProcess();
	static string searchTextProcess(string keyword);
	static string sortTextProcess();
	static string displayTextProcess();

public:
	//all public functions that can be used in both TextBuddy.cpp and unit testing
	static void main(string filename);
	static void textToFile();
	static string executeCommand(string firstWord);
	static string addText(string text);
	static string deleteText(int textNumber);
	static string clearText();
	static string searchText(string keyword);
	static string sortText();
	static string displayText();
	static string exitProgramme();

	//wrapping methods below around #ifdef and #endif preprocessor directives 
	//to restrict the use of the methods for unit testing only
	#ifdef TESTMODE 
	
	void TextBuddy::addTextForTest(string text) {
		textList.push_back(text);
		return;
	}

	#endif
};

#endif


