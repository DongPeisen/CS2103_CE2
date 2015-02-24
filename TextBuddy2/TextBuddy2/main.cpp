//Note: credit to my teammate Yeo Teck Kian's CE1 as it served as a reference for me.

//Assumptions:
//All commands must start accurately with the supported command words.
//The first word of every command must be in lowercase and spelled correctly.

#include "TextBuddy.h"
using namespace std;

//main function takes in a string of the file name in the form of argv[1].
//this name is passed to TextBuddy::main function for opening of the file.
void main(int argc, char* argv[]) {
	string filename(argv[1]);
	TextBuddy::main(filename);
	return;
}