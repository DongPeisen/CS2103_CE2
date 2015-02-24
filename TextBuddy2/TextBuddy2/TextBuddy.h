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
		ADD, DELETE, CLEAR, DISPLAY, INVALID, EXIT
	};

private:
	//all feedback messages
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_ADD;
	static const string MESSAGE_DELETE;
	static const string MESSAGE_CLEAR;
	static const string MESSAGE_EMPTY;
	static const string MESSAGE_INVALID;

	//all global variables
	static list<string> textList; //a string list to store all the text content from user.
	static string fileName;
	static char buffer[255];
	static bool userExit; //to trigger the condition of exiting the programme.
	static ofstream outFile;

	//all private functions
	static void showToUser(string text);
	static COMMAND_TYPE determineCommandType(string commandString);
	static string executeCommand(string firstWord);
	static bool isEmpty();
	static string addText(string text);
	static string deleteText(int textNumber);
	static string clearText();
	static string displayText();

	static string toString();
	static void textToFile();
	static string exitProgramme();

public:
	static void main(string filename);
};

#endif
