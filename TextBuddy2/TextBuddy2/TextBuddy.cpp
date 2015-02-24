//Implementation file
//TextBuddy.cpp executes user commands and stores content in a string list named textList.
//It transfers all content into a file right before exiting the programme,
//so only the latest version of content will be stored into file.

#include "TextBuddy.h"
using namespace std;

const string TextBuddy::MESSAGE_WELCOME = "Welcome to TextBuddy. %s is ready for use";
const string TextBuddy::MESSAGE_ADD = "added to %s: \"%s\"";
const string TextBuddy::MESSAGE_DELETE = "deleted from %s: \"%s\"";
const string TextBuddy::MESSAGE_CLEAR = "all content deleted from %s";
const string TextBuddy::MESSAGE_EMPTY = "%s is empty";
const string TextBuddy::MESSAGE_INVALID = "Invalid command";

list<string> TextBuddy::textList;
string TextBuddy::fileName;
char TextBuddy::buffer[255];
bool TextBuddy::userExit;
ofstream TextBuddy::outFile;

void TextBuddy::main(string filename) {
	fileName = filename;
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), fileName.c_str());
	cout << buffer << endl;
	
	userExit = false;
	string firstWord;
	string feedback;

	while(!userExit) {
		cout << "command: ";		
		cin >> firstWord;	//only first word because it is used to determine which kind of executions will be done.
		feedback = executeCommand(firstWord);
		showToUser(feedback);
	}
	
	textToFile();	//to write content into file right before exit.

	return;
}

void TextBuddy::showToUser(string text) {
	cout << text << endl;
}

//to decipher the user command by converting it to the corresponding COMMAND_TYPE.
TextBuddy::COMMAND_TYPE TextBuddy::determineCommandType(string commandString) {
	if(commandString == "add") {
		return TextBuddy::ADD;
	} else if (commandString == "delete") {
		return TextBuddy::DELETE;
	} else if (commandString == "display") {
		return TextBuddy::DISPLAY;
	} else if (commandString == "clear") {
		return TextBuddy::CLEAR;
	} else if (commandString == "exit") {
		return TextBuddy::EXIT;
	} else if (commandString == "search") {
		return TextBuddy::SEARCH;
	} else if (commandString == "sort") {
		return TextBuddy::SORT;
	} else return TextBuddy::INVALID;
}

//to execute the user commands by making required changes to textList through respective functions.
string TextBuddy::executeCommand(string firstWord) {

	COMMAND_TYPE commandType = determineCommandType(firstWord);
	//for add and search commands, the rest of command after first word is also in string type.
	string restOfCommand;	
	//for delete command, where there is only an integer command following the first word.
	int textNumber;	

	switch (commandType) {
		case ADD:
			getline(cin, restOfCommand);
			return addText(restOfCommand);
		case DELETE:
			cin >> textNumber;
			return deleteText(textNumber);
		case CLEAR:
			return clearText();
		case DISPLAY: 
			return displayText();
		case EXIT:
			return exitProgramme();
		case INVALID:
			return MESSAGE_INVALID;
		default:
			return MESSAGE_INVALID;
	}
}

//to check if textList is empty.
bool TextBuddy::isEmpty() {
	return textList.empty();
}

//to add a new line of content to the back of textList.
string TextBuddy::addText(string text) {
	textList.push_back(text);
	sprintf_s(buffer, MESSAGE_ADD.c_str(), fileName.c_str(), text.c_str());
	return buffer;
}

//to delete a line based on the number of the line.
string TextBuddy::deleteText(int textNumber) {
	if(textNumber==0 || textNumber<0 || textNumber>textList.size()) {
		sprintf_s(buffer, MESSAGE_INVALID.c_str());
		return buffer;
	}

	if(isEmpty()) {
		sprintf_s(buffer, MESSAGE_EMPTY.c_str(), fileName.c_str());
		return buffer;
	}

	list<string>::iterator iter = textList.begin();
	for(int i=1; i<textNumber; ++i) {
		iter++;
	}
	string tempText = *iter;
	sprintf_s(buffer, MESSAGE_DELETE.c_str(), fileName.c_str(), tempText.c_str());
	textList.erase(iter);
	return buffer;
}

//to delete all content in textList.
string TextBuddy::clearText() {
	if(isEmpty()) {
		sprintf_s(buffer, MESSAGE_EMPTY.c_str(), fileName.c_str());
		return buffer;
	}

	textList.clear();
	sprintf_s(buffer, MESSAGE_CLEAR.c_str(), fileName.c_str());
	return buffer;
}

//to display all content. The actual arrangement and processing of content is done by toString() function.
string TextBuddy::displayText() {
	if(isEmpty()) {
		sprintf_s(buffer, MESSAGE_EMPTY.c_str(), fileName.c_str());
		return buffer;
	}
	return toString();
}

//to return all content in textList as a stringstream.
string TextBuddy::toString() {

	int Number = 1;
	ostringstream oss; 
	list<string>::iterator iter = textList.begin();
	while(iter!=textList.end()) {
		oss << Number++ << ". " << *iter << endl;
		iter++;
	}
	return oss.str();
}

//to write content from textList into a file.
void TextBuddy::textToFile() {
	if(isEmpty()) {
		outFile.close();
		return;
	}
	outFile << toString();
	outFile.close();
	return;
}

//to exit the programme by turning userExit to true so that the while loop in TextBuddy::main() function terminates.
//exitProgramme() function has a string return type because executeCommand() function must return a string.
string TextBuddy::exitProgramme() {
	userExit = true;
	string empty;
	return empty;
}