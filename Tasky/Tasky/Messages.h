#ifndef _Messages_H_
#define _Messages_H_

/**
*this class contains messages for feedback from different components
*/
//@author A0103516U

#include "Essential.h"

class Messages{
public:
	Messages();
	~Messages();
	string getMessage(int index);

private:

	static const string MESSAGE_OVERALL_SUCCESS;
	static const string MESSAGE_OVERALL_WARNING;
	static const string MESSAGE_OVERALL_ERROR;
	static const string MESSAGE_OVERALL_PROMPT;
	static const string MESSAGE_OVERALL_EXIT;

	static const string MESSAGE_SUCCESS_ADD;
	static const string MESSAGE_SUCCESS_REMOVE;
	static const string MESSAGE_SUCCESS_DISPLAY;
	static const string MESSAGE_SUCCESS_UPDATE;
	static const string MESSAGE_SUCCESS_RESHCEDULE;
	static const string MESSAGE_SUCCESS_MARK;
	static const string MESSAGE_SUCCESS_SEARCH;
	static const string MESSAGE_SUCCESS_LOAD;
	static const string MESSAGE_SUCCESS_SAVE;
	static const string MESSAGE_SUCCESS_UNDO;
	static const string MESSAGE_SUCCESS_REDO;
	static const string MESSAGE_SUCCESS_HELP;
	static const string MESSAGE_SUCCESS_RECORD;
	static const string MESSAGE_SUCCESS_INTERPRET_SEARCH_RENAME;
	static const string MESSAGE_SUCCESS_INTERPRET_SEARCH_RESCHEDULE;
	static const string MESSAGE_SUCCESS_INTERPRET_SEARCH_MARK;
	static const string MESSAGE_SUCCESS_INTERPRET_ADD;
	static const string MESSAGE_SUCCESS_INTERPRET_REMOVE;
	static const string MESSAGE_SUCCESS_INTERPRET_DISPLAY;
	static const string MESSAGE_SUCCESS_INTERPRET_RENAME;
	static const string MESSAGE_SUCCESS_INTERPRET_RESCHEDULE;	
	static const string MESSAGE_SUCCESS_INTERPRET_MARK;
	static const string MESSAGE_SUCCESS_INTERPRET_SEARCH;

	static const string MESSAGE_WARNING_ADD_CLASH;	
	static const string MESSAGE_WARNING_DISPLAY_NO_RESULT;
	static const string MESSAGE_WARNING_UPDATE_SAME;	
	static const string MESSAGE_WARNING_UPDATE_CLASH;
	static const string MESSAGE_WARNING_MARK_NO_CHANGE;
	static const string MESSAGE_WARNING_SEARCH_NO_RESULT;
	static const string MESSAGE_WARNING_SEARCH_NO_SLOTS;
	static const string MESSAGE_WARNING_UNDO_NO_TASKS;
	static const string MESSAGE_WARNING_REDO_NO_TASKS;
	static const string MESSAGE_WARNING_LOAD_EMPTY_FILE;	
	static const string MESSAGE_WARNING_INTERPRET_ADDITIONAL_USELESS_STUFF;
	static const string MESSAGE_WARNING_WRONG_INPUT;

	static const string MESSAGE_ERROR_ADD;
	static const string MESSAGE_ERROR_ADD_DUPLICATE;
	static const string MESSAGE_ERROR_REMOVE;
	static const string MESSAGE_ERROR_DISPLAY;
	static const string MESSAGE_ERROR_UPDATE;
	static const string MESSAGE_ERROR_MARK;
	static const string MESSAGE_ERROR_SEARCH;
	static const string MESSAGE_ERROR_UNDO;
	static const string MESSAGE_ERROR_REDO;
	static const string MESSAGE_ERROR_LOAD_OPENFILE;
	static const string MESSAGE_ERROR_LOAD_CORRUPTED_DATA;
	static const string MESSAGE_ERROR_SAVE_SAVEFILE;
	static const string MESSAGE_ERROR_RECORD;
	static const string MESSAGE_ERROR_INVALID_CHOICE;
	static const string MESSAGE_ERROR_NO_SEARCH_ACTION;
	static const string MESSAGE_ERROR_INTERPRET_SEARCH_RENAME;
	static const string MESSAGE_ERROR_INTERPRET_SEARCH_RESCHEDULE;
	static const string MESSAGE_ERROR_INTERPRET_SEARCH_MARK;
	static const string MESSAGE_ERROR_INTERPRET_EMPTY_INPUT;
	static const string MESSAGE_ERROR_INTERPRET_TITLE_FORMAT;
	static const string MESSAGE_ERROR_INTERPRET_DATETIME_FORMAT;
	static const string MESSAGE_ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND;
	static const string MESSAGE_ERROR_INTERPRET_MIXED_UP_INPUT;
	static const string MESSAGE_ERROR_INTERPRET_ADD;
	static const string MESSAGE_ERROR_INTERPRET_REMOVE;
	static const string MESSAGE_ERROR_INTERPRET_DISPLAY;
	static const string MESSAGE_ERROR_INTERPRET_RENAME;	
	static const string MESSAGE_ERROR_INTERPRET_RESCHEDULE;
	static const string MESSAGE_ERROR_INTERPRET_MARK;
	static const string MESSAGE_ERROR_INTERPRET_POWER_SEARCH;

	static const string MESSAGE_PROMPT_REMOVE_CHOOSE;
	static const string MESSAGE_PROMPT_RENAME_CHOOSE;
	static const string MESSAGE_PROMPT_RESCHEDULE_CHOOSE;
	static const string MESSAGE_PROMPT_MARK_CHOOSE;

	static const int MAX_MESSAGES = 100;
	static const string MESSAGE_ARRAY [MAX_MESSAGES];

};

#endif _Messages_H_