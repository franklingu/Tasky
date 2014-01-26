#ifndef UI_H
#define UI_H

#include <iostream>
#include <assert.h>
//#include "Processor.h"
#include "ProcessorStub.h"

using namespace std;

static const string MESSAGE_WELCOME = "Welcome!";
static const string MESSAGE_GOODBYE = "GoodBye!";
static const string MESSAGE_COMMAND = "Command: ";

static const string COMMAND_EXIT = "exit";
static string COMMAND_DISPLAY_TASK_PENDING = "display pending";

class UI
{
private:
	ProcessorStub _processor;
	/**
	* Purpose:
	* Displays a welcome message to the user
	* Displays the tasks of the day/pending tasks
	*/
	void displayWelcomeMessage(HANDLE hConsole);	//should display welcome messages + task of the day
	/**
	* Purpose:
	* Takes in user command & put into string command
	* @param command - stores the user input 
	*/
	void displayCommandMessage(string& command, HANDLE hConsole);
	/**
	* Purpose:
	* Send the user's command to the Processor
	*@param command - user input to be passed to Processor
	*/
	void displayProcessorMessage(string command,HANDLE hConsole,bool& statusFlag);
public:
	/**
	* Purpose:
	* Function called when program is started up
	* Takes in user input/commands and passes to Processor
	*Checks if user wishes to exit the program
	*/
	void UI_interface(); //takes in user input
};

#endif
