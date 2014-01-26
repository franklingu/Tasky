//@author A0099016B
#include "History.h"


History::History() {
	_undoRecord.clear();
	_redoRecord.clear();
}


int History::undo(HistoryCommand& hist) {
	int currentSize = _undoRecord.size();
	if(currentSize > 0) {
		hist = _undoRecord.back();
		_redoRecord.push_back(_undoRecord.back());
		_undoRecord.pop_back();
		if (currentSize - _undoRecord.size() == CHANGE_IN_HISTORY_SIZE){
			return STATUS_CODE_SET_SUCCESS::SUCCESS_UNDO;
		}
	} else {
		return STATUS_CODE_SET_WARNING::WARNING_UNDO_NO_TASKS;
	}
	return STATUS_CODE_SET_ERROR::ERROR_UNDO;
}


int History::record(HistoryCommand hist) {
	int currentSize = _undoRecord.size();
	_undoRecord.push_back(hist);
	while (_undoRecord.size() > HISTORY_MAX_SIZE) {
		_undoRecord.erase(_undoRecord.begin());
	}
	if (_undoRecord.size() <= HISTORY_MAX_SIZE){
		return STATUS_CODE_SET_SUCCESS::SUCCESS_RECORD;
	}
	return STATUS_CODE_SET_ERROR::ERROR_RECORD;
}

int History::redo(HistoryCommand& hist) {
	int currentSize = _redoRecord.size();
	if(currentSize > 0) {
		hist = _redoRecord.back();
		_undoRecord.push_back(_redoRecord.back());
		_redoRecord.pop_back();
		return STATUS_CODE_SET_SUCCESS::SUCCESS_REDO;
	} else {
		return STATUS_CODE_SET_WARNING::WARNING_REDO_NO_TASKS;
	}
	return STATUS_CODE_SET_ERROR::ERROR_REDO;
}
