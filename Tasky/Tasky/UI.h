#ifndef UI_H
#define UI_H

//@author A0099016B

#include <iostream>
#include <Windows.h>
#include <assert.h>
#include "Processor.h"

using namespace std;
using namespace System;

static const string MESSAGE_WELCOME = "Welcome To Tasky! ";
static const string MESSAGE_TASKS_TODAY = "\nThe tasks for today are as follows:\n";
static const string MESSAGE_GOODBYE = "GoodBye!";
static const string MESSAGE_COMMAND = "Command: ";

static const string COMMAND_EXIT = "exit";
static string COMMAND_DISPLAY_TASK_TODAY = "display today";

class UI
{
private:
	Processor _processor;
	/**
	* Purpose:
	* Displays a welcome message to the user
	* Displays the tasks of the day/pending tasks
	*/
	void displayWelcomeMessage(HANDLE hConsole);
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
