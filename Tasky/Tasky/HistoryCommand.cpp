#include "HistoryCommand.h"

//@author A0103516U

COMMAND_TYPES HistoryCommand::getCommandType(){
	return _commandType;
}
Task HistoryCommand::getOld(){
	return _oldTask;
}
Task HistoryCommand::getNew(){
	return _newTask;
}
COMMAND_TYPES HistoryCommand::getCommandTypeUndo(){
	switch (_commandType){
	case ADD:
		return COMMAND_TYPES::REMOVE;
		break;
	case REMOVE:
		return COMMAND_TYPES::ADD;
		break;
	case UPDATE:
		return COMMAND_TYPES::UPDATE;
		break;
	default:
		return COMMAND_TYPES::NONE;
	}
}

COMMAND_TYPES HistoryCommand::getCommandTypeRedo(){
	return getCommandType();
}