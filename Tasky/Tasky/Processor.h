#ifndef _Processor_H_
#define _Processor_H_

/**
*This class is the central controlling unit. It will take string from UI and process it, acknowledge UI
*if input format is not suitable or it will go ahead and extract command out of input string and call methods
*in TaskList/history/FileProcessing to carry out the command.
*
*Main role: string processing, central logic unit, front wall of logic.
*
*Additional notice: this class will take the pointer of the _itemList in TaskList class to ease the cost of
*displaying. But the author of this class will only read from _itemList. This method is more like data-binding
*with only programmers' protection.
*@author A0103516U
*/

#include <sstream>
#include "Task.h"
#include "BasicDateTime.h"
#include "History.h"
#include "FileProcessing.h"
#include "TaskList.h"
#include "Interpreter.h"
#include "Essential.h"
#include "Messages.h"
#include "HelpUser.h"

class Processor{

private:
	///enum STATUSES contains various statuses of the program can be in at a given time
	enum STATUSES{
		NOTHING_PENDING,
		REMOVE_PENDING,
		RENAME_PENDING,
		RESCHEDULE_PENDING,
		MARK_PENDING,
	};
	
	vector<Task> _tempTaskList;			//<a list containing previously shown tasks
	vector<string> _tempStringList;		//<a list to give feedback in strings to IU
	STATUSES _statusFlag;				//<status flag for the status of the program
	bool _searched;						//<flag to check if the previous action was search

	string _tempTitle;					//<temporary title to be put in a task being modified
	string _tempComment;				//<temporary comment to be put in a task being modified
	bool _tempStatus;					//<temporary status to be put in a task being modified
	int _tempType;						//<temporary type to be put in a task being modified
	BasicDateTime _tempStart;			//<temporary start date to be put in a task being modified
	BasicDateTime _tempEnd;				//<temporary end date to be put in a task being modified

	TaskList _taskList;					//<object of the TaskList class
	History _history;					//<object of the History class
	Interpreter _interpreter;			//<object of the Interpreter class
	FileProcessing _fileProcessing;		//<object of the FileProcessing class
	Messages _messages;					//<object of the Messages class
	HelpUser _help;						//<object of the HelpUser class

private:

	///chars for use in string creation and processing
	static const char NEW_LINE;
	static const char SLASH;
	static const char BACK_SLASH;
	static const char DOT;
	static const char COLON;
	static const char DASH;
	static const char ZERO;
	static const char NINE;
	static const char SPACE;
	static const string EMPTY_STRING;
	static const string NEW_LINE_STRING;
	static const string NONE;

	///strings of the command types available
	static const string COMMAND_ADD;
	static const string COMMAND_REMOVE;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_RENAME;
	static const string COMMAND_RESCHEDULE;
	static const string COMMAND_MARK;
	static const string COMMAND_SEARCH;
	static const string COMMAND_UNDO;
	static const string COMMAND_REDO;
	static const string COMMAND_HELP;
	static const string COMMAND_EXIT;

	///strings for feedbacks specific to Processor
	static const string TASK_ADDED;
	static const string TASK_ADD_ERROR;
	static const string CLASHES;
	static const string TASKS_REMOVED;
	static const string TASKS_REMOVING_ERROR;
	static const string UPDATED_TO;
	static const string TASK_RENAMED;
	static const string TASK_RENAME_ERROR;
	static const string TASK_RESCHEDULED;
	static const string TASK_RESCHEDULED_ERROR;
	static const string TASKS_MARKED;
	static const string TASKS_MARKING_ERROR;
	static const string UNDO_TASK_ADDED;
	static const string UNDO_TASK_ADDING_ERROR;
	static const string UNDO_TASK_REMOVED;
	static const string UNDO_TASK_REMOVING_ERROR;
	static const string UNDO_TASK_UPDATED;
	static const string UNDO_TASK_UPDATING_ERROR;
	static const string REDO_TASK_ADDED;
	static const string REDO_TASK_ADDING_ERROR;
	static const string REDO_TASK_REMOVED;
	static const string REDO_TASK_REMOVING_ERROR;
	static const string REDO_TASK_UPDATED;
	static const string REDO_TASK_UPDATING_ERROR;
	static const string EMPTY_SLOTS;
	static const string SLOT_FROM;
	static const string SLOT_TO;
	static const string PROCESSOR_LOG_FILE;

public:
	Processor();
	/**
	* Purpose:
	* Handle user input based on first keyword
	* and call appropriate functions to handle the command
	*
	* @param input the raw user input passed in from the UI
	* @param message the feedback message to be passed to the UI
	* @param list the list of tasks to be displayed by the UI
	* @return overall status code
	*/
	int UImainProcessor(string input, string& message, vector<string>& list);

	~Processor();

private:
	/************************************************************************/
	/* Level 1 abstraction                                                  */
	/************************************************************************/

	/**
	* Purpose: Handle add commands
	*
	* @param input the input passed in from the main processor without the add keyword
	* @return status code
	*/
	int addCommandProcessor(string input);

	/**
	* Purpose: Handle remove commands
	*
	* @param input the input passed in from the main processor without the remove keyword
	* @return status code
	*/
	int removeCommandProcessor(string input);

	/**
	* Purpose: Handle display commands
	*
	* @param input the input passed in from the main processor without the display keyword
	* @return status code
	*/
	int displayCommandProcessor(string input);

	/**
	* Purpose: Handle rename commands from update
	*
	* @param input the input passed in from the main processor without the update keyword
	* @return status code
	*/
	int renameCommandProcessor(string input);

	/**
	* Purpose: Handle reschedule commands from update
	*
	* @param input the input passed in from the main processor without the update keyword
	* @return status code
	*/
	int rescheduleCommandProcessor(string input);

	/**
	* Purpose: Handle mark commands
	*
	* @param input the input passed in from the main processor without the mark keyword
	* @return status code
	*/
	int markCommandProcessor(string input);

	/**
	* Purpose: Handle search commands
	*
	* @param input the input passed in from the main processor without the search keyword
	* @return status code
	*/
	int searchCommandProcessor(string input);

	/**
	* Purpose: Handle search actions
	*
	* @param input the input passed in from the main processor with the command
	* @return status code
	*/
	int searchActionProcessor(string command, string input);

	/**
	* Purpose: Handle undo commands
	*
	* @param input the input passed in from the main processor without the undo keyword
	* @return status code
	*/
	int undoCommandProcessor(string input);

	/**
	* Purpose: Handle redo commands
	*
	* @param input the input passed in from the main processor without the redo keyword
	* @return status code
	*/
	int redoCommandProcessor(string input);

	/**
	* Purpose: Handle help commands
	*
	* @param input the input passed in from the main processor without the help keyword
	* @return status code
	*/
	int helpCommandProcessor(string input);

	/**
	* Purpose: Handle wrong/invalid commands
	*
	* @param input the input passed in from the main processor
	* @return status code(always WARNING_WRONG_INPUT)
	*/
	int otherCommandProcessor();

	/**
	* Purpose: Handle save command
	*
	* @return status code
	*/
	int saveFile();

	/**
	* Purpose: Handle load command
	*
	* @return status code
	*/
	int loadFile();

	/**
	* Purpose: To return feedback to the user and give the overall status of the operation
	*
	* @param returnCode feedback from commandProcessors
	* @param message message to be passed to the UI
	* @param list the list of strings that need to be printed out with the message
	*
	* @return overall status code
	*/
	int feedbackToUI(int returnCode, string& message, vector<string>& list);

	/************************************************************************/
	/* Level 2 abstraction                                                  */
	/************************************************************************/
	
	int addTask(string title, int type, BasicDateTime start, BasicDateTime end, string comment);
	void recordAndFeedbackAdd( Task oldTask, Task newTask );
	int removeTask( Task newTask, Task oldTask, vector<Task>& removed, vector<Task>& error);
	int renameTask( Task &oldTask, Task &newTask );
	int recordAndFeedbackUpdate( Task &oldTask, Task &newTask, string success, string error );
	int rescheduleTask( Task &oldTask, Task &newTask );
	int markTask( Task &newTask, Task oldTask, vector<Task> &markedTasks, vector<Task> &errorTasks );
	
	///helper functions for undo
	int undoAdd( HistoryCommand command );
	int undoRemove( HistoryCommand command );
	int undoUpdate( HistoryCommand command );

	///helper functions for redo
	int redoAdd( HistoryCommand command );
	int redoRemove( HistoryCommand command );
	int redoUpdate( HistoryCommand command );

	///helper functions for searchActions
	void searchMark( vector<int> &choiceVec, int interReturn, Task &oldTask, int &returnCode, Task newTask, vector<Task> success, vector<Task> error );
	void searchReschedule( int choice, int interReturn, Task &newTask, int &returnCode, Task oldTask );
	void searchRename( int choice, int interReturn, Task &newTask, int &returnCode, Task oldTask );
	void searchRemove( vector<int> &choiceVec, Task &newTask, int &returnCode, Task oldTask, vector<Task> success, vector<Task> error );
	
	///other helper functions
	string getCommand(string& input);
	bool canProceed( string command, string input, int& returnCode );
	bool isEscape(string command);
	int recordCommand(COMMAND_TYPES commandType, Task oldTask, Task newTask);
	bool choiceIsValidVec(vector<int> choice);
	bool choiceIsValid(unsigned int choice);
	void taskVecToStringVec(vector<Task> taskList, vector<string>& stringList);
	void dateTimeVecToStringVec(vector<BasicDateTime>slots, vector<string>& stringList);
	bool commandIsNormal(string command);
	void pushFeedackToStringVec(vector<Task> taskVector, string message);
	void checkComment(Task task);
};

#endif
