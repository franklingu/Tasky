#ifndef _HISTORY_H_
#define _HISTORY_H_

/*
 *This class is mainly to store previous successful operations. If undo is being called, undo will pop the latest
 *successful command to processor. And record will store the new command to _historyRecord
 *
 *Main author: Joan
*/

#include "Essential.h"
#include "HistoryCommand.h"
#include <assert.h>


///record past sucessful operations and pop the last one when undo called
class History{
private:
	static const int CHANGE_IN_HISTORY_SIZE = 1;
	static const int HISTORY_MAX_SIZE = 5;
	vector<HistoryCommand> _undoRecord;
	vector<HistoryCommand> _redoRecord;
	
public:
	/**
	* Purpose:
	*Clears the vector containing history actions upon start up
	*/
	History();
	/**
	* Purpose:
	* Retrieves the last action from vector of history records
	* @param hist - last action done will be passed back to calling function via this referenced string
	* @return Success in retrival; Empty records, nothing to be undone; Failure
	*/
	int undo(HistoryCommand& hist);
	/* Purpose:
	* saves the successful action into vectory of history records
	* @param hist - string containing successful user action preformed
	*@return Success in putting the record into history; Failure
	*/
	int record(HistoryCommand hist);
	/**
	* Retrieves the previously undone action
	* @param hist previously undone action will be stored here
	*/
	int redo(HistoryCommand& hist);
	
};

#endif
