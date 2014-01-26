#include "Task.h"

/**
*This class contains the HistoryCommand class, which is a container
*for the commands to be stored by the History class and retrieved
*by the Processor class
*/
//@author A0103516U
enum COMMAND_TYPES{
	ADD,
	REMOVE,
	UPDATE,
	NONE,
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