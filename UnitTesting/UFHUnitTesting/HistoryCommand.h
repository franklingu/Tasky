#include "Task.h"

enum COMMAND_TYPES{
	ADD,
	REMOVE,
	UPDATE
};

class HistoryCommand{
private:
	COMMAND_TYPES _commandType;
	Task _oldTask;
	Task _newTask;
public:
	HistoryCommand(COMMAND_TYPES commandType, Task oldTask, Task newTask){
		_commandType = commandType;
		_newTask = newTask;
		_oldTask = oldTask;
	}
	 COMMAND_TYPES getCommandType();
	 Task getOld();
	 Task getNew();

	 COMMAND_TYPES getCommandTypeUndo();
	 COMMAND_TYPES getCommandTypeRedo();
};