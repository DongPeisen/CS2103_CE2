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
const string TextBuddy::MESSAGE_SEARCH_NO_RESULT = "there is no line in %s containing the word %s";
const string TextBuddy::MESSAGE_SORT = "all content in %s sorted alphabetically";
const string TextBuddy::MESSAGE_EMPTY = "%s is empty";
const string TextBuddy::MESSAGE_INVALID = "Invalid command";

list<string> TextBuddy::textList;
string TextBuddy::fileName;
char TextBuddy::buffer[255];
bool TextBuddy::userExit;
ofstream TextBuddy::outFile;



/*********highest level of abstraction*********/
void TextBuddy::main(string filename) {
	fileName = filename;
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), fileName.c_str());
	cout << buffer << endl;
	
	userExit = false;
	string firstWord;
	string feedback;
	while(!userExit) {
		cout << "command: ";		
		cin >> firstWord;	//first word of command is used to determine which kind of executions will be done.
		feedback = executeCommand(firstWord);
		showToUser(feedback);
	}
	
	textToFile();	//to write content into file right before exit.

	return;
}



/*********second level of abstraction*********/

//to print the feedback message shown to user
void TextBuddy::showToUser(string text) {
	cout << text << endl;
}

//to write all content from textList into a file.
void TextBuddy::textToFile() {
	if(isEmpty()) {
		outFile.close();
		return;
	}
	outFile << displayTextProcess();
	outFile.close();
	return;
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
		case SEARCH:
			getline(cin, restOfCommand);
			return searchText(restOfCommand);
		case SORT:
			return sortText();
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



/*********third level of abstraction*********/

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

//to add a new line of content to the back of textList.
string TextBuddy::addText(string text) {
	return addTextProcess(text);
}

//to delete a line based on the number of the line.
string TextBuddy::deleteText(int textNumber) {
	if(isEmpty()) {
		return bufferEmptyProcess();
	}
	if(textNumber==0 || textNumber<0 || textNumber>int(textList.size())) {
		return bufferInvalidProcess();
	}

	return deleteTextProcess(textNumber);
}

//to delete all content in textList.
string TextBuddy::clearText() {
	if(isEmpty()) {
		return bufferEmptyProcess();
	}

	return clearTextProcess();
}

//to search for all content containing a certain keyword.
string TextBuddy::searchText(string keyword) {	
	if(isEmpty()) {
		return bufferEmptyProcess();
	}

	return searchTextProcess(keyword);
}

//to sort all content in alphabetical order.
string TextBuddy::sortText() {
	if(isEmpty()) {
		return bufferEmptyProcess();
	}
	
	return sortTextProcess();
}

//to display all content. The actual arrangement and processing of content is done by toString() function.
string TextBuddy::displayText() {
	if(isEmpty()) {
		return bufferEmptyProcess();
	}

	return displayTextProcess();
}

//to exit the programme by turning userExit to true so that the while loop in TextBuddy::main() function terminates.
//exitProgramme() function has a string return type because executeCommand() function must return a string.
string TextBuddy::exitProgramme() {
	userExit = true;
	string empty;
	return empty;
}



/*********lowerest level of abstraction*********/

//to check if textList is empty.
bool TextBuddy::isEmpty() {
	return textList.empty();
}

//message for an empty textList.
string TextBuddy::bufferEmptyProcess() {
	sprintf_s(buffer, MESSAGE_EMPTY.c_str(), fileName.c_str());
	return buffer;
}

//message for an invalid user command.
string TextBuddy::bufferInvalidProcess() {
	sprintf_s(buffer, MESSAGE_INVALID.c_str());
	return buffer;
}

//the actual text-adding process.
string TextBuddy::addTextProcess(string text) {
	textList.push_back(text);
	sprintf_s(buffer, MESSAGE_ADD.c_str(), fileName.c_str(), text.c_str());
	return buffer;
}

//the actual text-deleting process when the list is not empty and the user command is valid.
string TextBuddy::deleteTextProcess(int textNumber) {
	list<string>::iterator iter = textList.begin();
	for(int i=1; i<textNumber; ++i) {
		iter++;
	}
	string tempText = *iter;
	sprintf_s(buffer, MESSAGE_DELETE.c_str(), fileName.c_str(), tempText.c_str());
	textList.erase(iter);
	return buffer;
}

//the actual list-clearing process when it is not empty.
string TextBuddy::clearTextProcess() {
	textList.clear();
	sprintf_s(buffer, MESSAGE_CLEAR.c_str(), fileName.c_str());
	return buffer;
}

//the actual list searching process when it is not empty.
string TextBuddy::searchTextProcess(string keyword) {
	int searchResult = 0;
	
	ostringstream out;
	list<string>::iterator iter = textList.begin();
	while(iter != textList.end()) {
		size_t found = (*iter).find(keyword);
		if(found != string::npos) {
			out << ++searchResult << ". " << *iter << endl;
		}
		iter++;
	}

	if(searchResult != 0) {
		return out.str();
	}
	sprintf_s(buffer, MESSAGE_SEARCH_NO_RESULT.c_str(), fileName.c_str(), keyword.c_str());
	return buffer;
}

////the actual list sorting process when it is not empty.
string TextBuddy::sortTextProcess() {
	textList.sort();
	sprintf_s(buffer, MESSAGE_SORT.c_str(), fileName.c_str());
	return buffer;
}

//to return all content in textList as a stringstream.
string TextBuddy::displayTextProcess() {
	int Number = 1;
	ostringstream oss; 
	list<string>::iterator iter = textList.begin();
	while(iter!=textList.end()) {
		oss << Number++ << ". " << *iter << endl;
		iter++;
	}
	return oss.str();
}
