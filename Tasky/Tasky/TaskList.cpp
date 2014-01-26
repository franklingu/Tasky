//@author A0096760W
#include "TaskList.h"
#include <assert.h>
#include <algorithm>

static const int FLOATING_TASK = 0;
static const int DEADLINE_TASK = 1;
static const int NORMAL_TASK = 2;
static const string STRING_DONE = "Done";
static const string STRING_FLOATING = "Floating task";
static const string STRING_DEADLINE = "Deadline task";
static const string STRING_TIMED = "Timed task";
static const string STRING_NON = "None";

bool keywordsFlag;
bool statusFlag;
bool typeFlag;

TaskList::TaskList(){
}

int TaskList::add(Task toAdd, vector<Task>& _temp){

	_temp.clear();

	if(isExisting(toAdd))
		return ERROR_ADD_DUPLICATE;

	if(toAdd.getType() == NORMAL_TASK)
		pushClashing(toAdd, _temp);

	addTask(toAdd);

	if(!_temp.empty())
		return WARNING_ADD_CLASH;
	else	
		return SUCCESS_ADD;

	return ERROR_ADD;
}

int TaskList::remove(Task toRemove){

	if(isSuccessfullyRemoved(toRemove))
		return SUCCESS_REMOVE;
	else
		return ERROR_REMOVE;
}

int TaskList::update(Task existingTask, Task newTask, vector<Task>& _temp){

	if(existingTask.isEqualTo(newTask))
		return WARNING_UPDATE_SAME;

	remove(existingTask);

	add(newTask, _temp);

	if(!_temp.empty())
		return WARNING_UPDATE_CLASH;
	else
		return SUCCESS_UPDATE;

	return ERROR_UPDATE;
}

int TaskList::mark(bool mark, Task task){

	if(task.getDone() == mark)
		return WARNING_MARK_NO_CHANGE;

	if(isSuccessfullyMarked(mark, task))
		return SUCCESS_MARK;
	else
		return ERROR_MARK;
}

int TaskList::displayAll(vector<Task>& _temp){

	_temp.clear();

	appendVectors(_temp);

	if(!_temp.empty())
		return SUCCESS_DISPLAY;
	else
		return WARNING_DISPLAY_NO_RESULT;

	return ERROR_DISPLAY;
}

int TaskList::displayToday(vector<Task>& _temp){

	BasicDateTime start;
	BasicDateTime end;

	setToday(start, end);

	return searchInRange(start, end, _temp);
}

int TaskList::displayStatus(bool done, vector<Task>& _temp){

	_temp.clear();

	pushStatus(done, _temp);

	if(!_temp.empty())
		return SUCCESS_DISPLAY;
	else
		return WARNING_DISPLAY_NO_RESULT;

	return ERROR_DISPLAY;
}

int TaskList::searchTasks(vector<string> keywords, int statusPresent, int type, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	setFlags(keywords, statusPresent, type);

	bool done;

	if(statusFlag && statusPresent == 1)
		done = true;
	if(statusFlag && statusPresent == -1)
		done = false;

	if(keywordsFlag == false && statusFlag == false && typeFlag == true)
		return searchInRange(start, end, _temp);
	else if(keywordsFlag == false && statusFlag == true && typeFlag == false)
		return displayStatus(done, _temp);
	else if(keywordsFlag == false && statusFlag == true && typeFlag == true)
		return searchStatusInRange(done, start, end, _temp);
	else if(keywordsFlag == true && statusFlag == false && typeFlag == false)
		return searchKeywords(keywords, _temp);
	else if(keywordsFlag == true && statusFlag == false && typeFlag == true)
		return searchKeywordsInRange(keywords, start, end, _temp);
	else if(keywordsFlag == true && statusFlag == true && typeFlag == false)
		return searchKeywordsWithStatus(keywords, done, _temp);
	else if(keywordsFlag == true && statusFlag == true && typeFlag == true)
		return searchKeywordsWithRangeAndStatus(keywords, start, end, done, _temp);

	return ERROR_SEARCH;
}

int TaskList::searchEmptySlots(BasicDateTime start, BasicDateTime end, vector<BasicDateTime>& _temp){

	_temp.clear();

	if(isEmptySlotsPresent(start, end)){
		pushEmptySlots(start, end, _temp);
		return SUCCESS_SEARCH;
	}
	else
		return WARNING_SEARCH_NO_SLOTS;

	return ERROR_SEARCH;
}

int TaskList::search(string searchLine, vector<Task>& _temp){

	_temp.clear();

	searchTitle(searchLine, _temp);

	if(!_temp.empty())
		return SUCCESS_SEARCH;
	else
		return WARNING_SEARCH_NO_RESULT;

	return ERROR_SEARCH;
}

int TaskList::saveFile(){

	vector<Task> allTasks;

	appendVectors(allTasks);

	vector<string> allTasksString = taskVecToStringVec(allTasks);

	return _fileProcessing.save(allTasksString);
}

int TaskList::loadFile(){

	vector<string> stringsFromFile;
	int statusCode;

	statusCode = _fileProcessing.load(stringsFromFile);

	if(statusCode == SUCCESS_LOAD)
		loadTasksFromVector(stringsFromFile);

	return statusCode;
}

void TaskList::pushClashing(Task task, vector<Task>& _temp){

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(_normalTask[i].isClashingWith(task)){
			_temp.push_back(_normalTask[i]);
		}
	}
}

void TaskList::addTask(Task toAdd){

	switch(toAdd.getType()){

	case FLOATING_TASK:
		_floatingTask.push_back(toAdd);
		break;
	case DEADLINE_TASK:
		_deadlineTask.push_back(toAdd);
		break;
	case NORMAL_TASK:
		_normalTask.push_back(toAdd);
		break;
	}
}

bool TaskList::isExisting(Task task){

	switch(task.getType()){

	case FLOATING_TASK:
		for(unsigned int i = 0; i < _floatingTask.size(); i++){

			if(task.isEqualTo(_floatingTask[i])){
				return true;
			}
		}
		break;
	case DEADLINE_TASK:
		for(unsigned int i = 0; i < _deadlineTask.size(); i++){

			if(task.isEqualTo(_deadlineTask[i])){
				return true;
			}
		}
		break;
	case NORMAL_TASK:
		for(unsigned int i = 0; i < _normalTask.size(); i++){

			if(task.isEqualTo(_normalTask[i])){
				return true;
			}
		}
		break;
	}
	return false;
}

bool TaskList::isSuccessfullyRemoved(Task task){

	switch(task.getType()){

	case FLOATING_TASK:
		for(unsigned int i = 0; i < _floatingTask.size(); i++){

			if(task.isEqualTo(_floatingTask[i])){
				_floatingTask.erase(_floatingTask.begin()+i);
				return true;
			}
		}
		break;
	case DEADLINE_TASK:
		for(unsigned int i = 0; i < _deadlineTask.size(); i++){

			if(task.isEqualTo(_deadlineTask[i])){
				_deadlineTask.erase(_deadlineTask.begin()+i);
				return true;
			}
		}
		break;
	case NORMAL_TASK:
		for(unsigned int i = 0; i < _normalTask.size(); i++){

			if(task.isEqualTo(_normalTask[i])){
				_normalTask.erase(_normalTask.begin()+i);
				return true;
			}
		}
		break;
	}
	return false;
}

bool TaskList::isSuccessfullyMarked(bool mark, Task task){

	switch(task.getType()){

	case FLOATING_TASK:
		for(unsigned int i = 0; i < _floatingTask.size(); i++){

			if(task.isEqualTo(_floatingTask[i])){
				_floatingTask[i].toggleDone();
				return true;
			}
		}
		break;
	case DEADLINE_TASK:
		for(unsigned int i = 0; i < _deadlineTask.size(); i++){

			if(task.isEqualTo(_deadlineTask[i])){
				_deadlineTask[i].toggleDone();
				return true;
			}
		}
		break;
	case NORMAL_TASK:
		for(unsigned int i = 0; i < _normalTask.size(); i++){

			if(task.isEqualTo(_normalTask[i])){
				_normalTask[i].toggleDone();
				return true;
			}
		}
		break;
	}
	return false;
}

void TaskList::appendVectors(vector<Task>& _temp){

	std::sort(_normalTask.begin(), _normalTask.end());
	std::sort(_deadlineTask.begin(), _deadlineTask.end());

	_temp = _normalTask;
	_temp.insert(_temp.end(), _deadlineTask.begin(), _deadlineTask.end());
	_temp.insert(_temp.end(), _floatingTask.begin(), _floatingTask.end());
}

void TaskList::setToday(BasicDateTime& start, BasicDateTime& end){

	time_t time1=time(NULL);
	struct tm time2;
	localtime_s(&time2, &time1);

	int day, month, year;

	day = time2.tm_mday;
	month = time2.tm_mon + 1;
	year = time2.tm_year + 1900;

	start = BasicDateTime(year, month, day);
	end = BasicDateTime(year, month, day, 23, 59, 59);
}

void TaskList::setFlags(vector<string> keywords, int statusPresent, int type){

	if(keywords.empty())
		keywordsFlag = false;
	else
		keywordsFlag = true;

	if(statusPresent == 0)
		statusFlag = false;
	else if(statusPresent == -1 || statusPresent == 1)
		statusFlag = true;

	if(type == 0)
		typeFlag = false;
	else if(type == 2)
		typeFlag = true;
}

int TaskList::searchInRange(BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	_temp.clear();

	pushInRange(_temp, start, end);

	if(!_temp.empty())
		return SUCCESS_DISPLAY;
	else
		return WARNING_DISPLAY_NO_RESULT;

	return ERROR_DISPLAY;
}

int TaskList::searchStatusInRange(bool done, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	_temp.clear();

	pushStatusInRange(done, start, end, _temp);

	if(!_temp.empty())
		return SUCCESS_DISPLAY;
	else
		return WARNING_DISPLAY_NO_RESULT;

	return ERROR_DISPLAY;
}

int TaskList::searchKeywords(vector<string> keywords, vector<Task>& _temp){

	assert(!keywords.empty());

	_temp.clear();

	searchVectors(keywords, _temp);

	if(!_temp.empty())
		return SUCCESS_SEARCH;
	else
		return WARNING_SEARCH_NO_RESULT;

	return ERROR_SEARCH;
}

int TaskList::searchKeywordsInRange(vector<string> keywords, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	assert(!keywords.empty());

	_temp.clear();

	searchVectorsWithRange(keywords, start, end, _temp);

	if(!_temp.empty())
		return SUCCESS_SEARCH;
	else
		return WARNING_SEARCH_NO_RESULT;

	return ERROR_SEARCH;
}

int TaskList::searchKeywordsWithStatus(vector<string> keywords, bool done, vector<Task>& _temp){

	assert(!keywords.empty());

	_temp.clear();

	searchVectorsWithStatus(keywords, done, _temp);

	if(!_temp.empty())
		return SUCCESS_SEARCH;
	else
		return WARNING_SEARCH_NO_RESULT;

	return ERROR_SEARCH;
}

int TaskList::searchKeywordsWithRangeAndStatus(vector<string> keywords, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp){

	assert(!keywords.empty());

	_temp.clear();

	searchVectorsWithRangeAndStatus(keywords, start, end, done, _temp);

	if(!_temp.empty())
		return SUCCESS_SEARCH;
	else
		return WARNING_SEARCH_NO_RESULT;

	return ERROR_SEARCH;
}

bool TaskList::isEmptySlotsPresent(BasicDateTime start, BasicDateTime end){

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(_normalTask[i].getStart().compareTo(start) <= 0 && _normalTask[i].getEnd().compareTo(end) >= 0)
			return false;
	}

	return true;
}

void TaskList::pushEmptySlots(BasicDateTime& start, BasicDateTime& end, vector<BasicDateTime>& _temp){

	_duplicateNormal = _normalTask;

	cutRange(start, end);

	if(!_duplicateNormal.empty())
		std::sort(_duplicateNormal.begin(), _duplicateNormal.end());

	pushEmptySlotsToTemp(start, end, _temp);
}

void TaskList::searchTitle(string searchLine, vector<Task>& _temp){

	for(unsigned int i = 0; i < _floatingTask.size(); i++){

		if(_floatingTask[i].getTitle() == searchLine)
			_temp.push_back(_floatingTask[i]);
	}

	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		if(_deadlineTask[i].getTitle() == searchLine)
			_temp.push_back(_deadlineTask[i]);
	}

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(_normalTask[i].getTitle() == searchLine)
			_temp.push_back(_normalTask[i]);
	}
}

vector<string> TaskList::taskVecToStringVec(vector<Task>& allTasks){

	vector<string> taskLines;
	vector<string> temp;

	for (unsigned int i = 0; i < allTasks.size(); i++){
		temp = allTasks[i].toStringVector();
		taskLines.insert(taskLines.end(), temp.begin(), temp.end());
	}
	return taskLines;
}

void TaskList::loadTasksFromVector(vector<string>& stringsFromFile){

	string title, comment, currStr;
	int type;
	bool status;
	BasicDateTime start, end;

	for (unsigned int i = 0; i < stringsFromFile.size(); i++){

		currStr = stringsFromFile[i];

		switch (i % 6){
		case 0:
			if (currStr.substr(6) == STRING_FLOATING){
				type = 0;
			}else if (currStr.substr(6) == STRING_DEADLINE){
				type = 1;
			}else if (currStr.substr(6) == STRING_TIMED){
				type = 2;			
			}
			break;
		case 1:
			title = currStr.substr(7);
			break;
		case 2:
			if (currStr.substr(8) == STRING_DONE){
				status = true;
			}else{
				status = false;
			}
			break;
		case 3:
			stringToBasicDateTime(currStr.substr(7), start);
			break;
		case 4:
			stringToBasicDateTime(currStr.substr(5), end);
			break;
		case 5:
			comment = currStr.substr(9);
			Task tempTask(title, start, end, type, status, comment);
			addTask(tempTask);
			break;
		}
	}
}

void TaskList::pushInRange(vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	Task tempTask;

	tempTask = Task("temp", start, end, 2, false, "comment");

	std::sort(_normalTask.begin(), _normalTask.end());
	std::sort(_deadlineTask.begin(), _deadlineTask.end());

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(tempTask.isClashingWith(_normalTask[i]))
			_temp.push_back(_normalTask[i]);
	}

	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		if(isInRange(_deadlineTask[i].getEnd(), start, end))
			_temp.push_back(_deadlineTask[i]);
	}
}

void TaskList::pushStatus(bool done, vector<Task>& _temp){

	std::sort(_normalTask.begin(), _normalTask.end());
	std::sort(_deadlineTask.begin(), _deadlineTask.end());

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(_normalTask[i].getDone() == done)
			_temp.push_back(_normalTask[i]);
	}
	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		if(_deadlineTask[i].getDone() == done)
			_temp.push_back(_deadlineTask[i]);
	}
	for(unsigned int i = 0; i < _floatingTask.size(); i++){

		if(_floatingTask[i].getDone() == done)
			_temp.push_back(_floatingTask[i]);
	}
}

void TaskList::pushStatusInRange(bool done, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	Task tempTask;

	tempTask = Task("temp", start, end, 2, false, "comment");

	std::sort(_normalTask.begin(), _normalTask.end());
	std::sort(_deadlineTask.begin(), _deadlineTask.end());

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(tempTask.isClashingWith(_normalTask[i]) && _normalTask[i].getDone() == done)
			_temp.push_back(_normalTask[i]);
	}

	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		if(isInRange(_deadlineTask[i].getEnd(), start, end) && _normalTask[i].getDone() == done)
			_temp.push_back(_deadlineTask[i]);
	}
}

void TaskList::searchVectors(vector<string> keywords, vector<Task>& _temp){

	std::sort(_normalTask.begin(), _normalTask.end());
	std::sort(_deadlineTask.begin(), _deadlineTask.end());

	_duplicateFloating = _floatingTask;
	_duplicateDeadline = _deadlineTask;
	_duplicateNormal = _normalTask;

	exactSearch(keywords[0], _temp);
	containingExactStringSearch(keywords[0], _temp);
	containingBreakdownStringSearch(keywords, _temp);
}

void TaskList::searchVectorsWithRange(vector<string> keywords, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	std::sort(_normalTask.begin(), _normalTask.end());
	std::sort(_deadlineTask.begin(), _deadlineTask.end());

	_duplicateDeadline = _deadlineTask;
	_duplicateNormal = _normalTask;

	exactSearchWithRange(keywords[0], start, end, _temp);
	containingExactStringSearchWithRange(keywords[0], start, end, _temp);
	containingBreakdownStringSearchWithRange(keywords, start, end, _temp);
}

void TaskList::searchVectorsWithStatus(vector<string> keywords, bool done, vector<Task>& _temp){

	std::sort(_normalTask.begin(), _normalTask.end());
	std::sort(_deadlineTask.begin(), _deadlineTask.end());

	_duplicateFloating = _floatingTask;
	_duplicateDeadline = _deadlineTask;
	_duplicateNormal = _normalTask;

	exactSearchWithStatus(keywords[0], done, _temp);
	containingExactStringSearchWithStatus(keywords[0], done, _temp);
	containingBreakdownStringSearchWithStatus(keywords, done, _temp);
}

void TaskList::searchVectorsWithRangeAndStatus(vector<string> keywords, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp){

	std::sort(_normalTask.begin(), _normalTask.end());
	std::sort(_deadlineTask.begin(), _deadlineTask.end());

	_duplicateDeadline = _deadlineTask;
	_duplicateNormal = _normalTask;

	exactSearchWithRangeAndStatus(keywords[0], start, end, done, _temp);
	containingExactStringSearchWithRangeAndStatus(keywords[0], start, end, done, _temp);
	containingBreakdownStringSearchWithRangeAndStatus(keywords, start, end, done, _temp);
}

void TaskList::cutRange(BasicDateTime& start, BasicDateTime& end){

	Task tempTask;

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		tempTask = Task("temp", start, end, 2, false, "comment");

		if(!tempTask.isClashingWith(_duplicateNormal[i])){
			_duplicateNormal.erase(_duplicateNormal.begin() + i);
			i--;
		}

		else if(_duplicateNormal[i].getStart().compareTo(start) <= 0 && isInRange(_duplicateNormal[i].getEnd(), start, end)){
			start = _duplicateNormal[i].getEnd();
			_duplicateNormal.erase(_duplicateNormal.begin() + i);
			i--;
		}

		else if(_duplicateNormal[i].getEnd().compareTo(end) >= 0 && isInRange(_duplicateNormal[i].getStart(), start, end)){
			end = _duplicateNormal[i].getStart();
			_duplicateNormal.erase(_duplicateNormal.begin() + i);
			i--;
		}
	}
}

void TaskList::pushEmptySlotsToTemp(BasicDateTime& start, BasicDateTime& end, vector<BasicDateTime>& _temp){

	_temp.push_back(start);

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		_temp.push_back(_duplicateNormal[i].getStart());

		while(1){
			if(i != _duplicateNormal.size() - 1){
				if(isInRange(_duplicateNormal[i].getEnd(), _duplicateNormal[i+1].getStart(), _duplicateNormal[i+1].getEnd()) && i+1 == _duplicateNormal.size() - 1){
					_temp.push_back(_duplicateNormal[i+1].getEnd());
					i++;
					break;
				}
				else if(isInRange(_duplicateNormal[i].getEnd(), _duplicateNormal[i+1].getStart(), _duplicateNormal[i+1].getEnd()) && i+1 != _duplicateNormal.size() - 1){
					i++;
				}
				else{
					_temp.push_back(_duplicateNormal[i].getEnd());
					break;
				}
			}
			else
			{
				_temp.push_back(_duplicateNormal[i].getEnd());
				break;
			}
		}
	}

	_temp.push_back(end);
}

void TaskList::stringToBasicDateTime(string dateTimeString, BasicDateTime& bdt){

	if(dateTimeString == STRING_NON)
		return;

	int day, month, year, hour, min, sec;

	setDay(day, dateTimeString);
	setMonth(month, dateTimeString);
	setYear(year, dateTimeString);
	setHour(hour, dateTimeString);
	setMin(min, dateTimeString);
	setSec(sec, dateTimeString);

	if(isValidDateTime(day, month, year, hour, min, sec))
		bdt = BasicDateTime(year, month, day, hour, min, sec);
	else
		return;
}

void TaskList::exactSearch(string exactString, vector<Task>& _temp){

	stringToLower(exactString);
	
	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString) == exactString){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}	

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString) == exactString){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateFloating.size(); i++){

		string tempString = _duplicateFloating[i].getTitle();

		if(stringToLower(tempString) == exactString){
			_temp.push_back(_duplicateFloating[i]);
			_duplicateFloating.erase(_duplicateFloating.begin()+i);
			i--;
		}
	}
}

void TaskList::containingExactStringSearch(string exactString, vector<Task>& _temp){

	stringToLower(exactString);

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateFloating.size(); i++){

		string tempString = _duplicateFloating[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos){
			_temp.push_back(_duplicateFloating[i]);
			_duplicateFloating.erase(_duplicateFloating.begin()+i);
			i--;
		}
	}
}

void TaskList::containingBreakdownStringSearch(vector<string> keywords, vector<Task>& _temp){

	for(unsigned int i = 1; i < keywords.size(); i++){

		containingExactStringSearch(keywords[i], _temp);
		if(i == 6)
			break;
	}
}

void TaskList::exactSearchWithRange(string exactString, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	stringToLower(exactString);

	Task tempTask;
	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString) == exactString  && tempTask.isClashingWith(_duplicateNormal[i])){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString) == exactString && isInRange(_duplicateDeadline[i].getEnd(), start, end)){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}
}

void TaskList::containingExactStringSearchWithRange(string exactString, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	stringToLower(exactString);

	Task tempTask;
	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos && tempTask.isClashingWith(_duplicateNormal[i])){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos && isInRange(_duplicateDeadline[i].getEnd(), start, end)){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}
}

void TaskList::containingBreakdownStringSearchWithRange(vector<string> keywords, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	for(unsigned int i = 1; i < keywords.size(); i++){

		containingExactStringSearchWithRange(keywords[i], start, end, _temp);
		if(i == 6)
			break;
	}
}

void TaskList::exactSearchWithStatus(string exactString, bool done, vector<Task>& _temp){

	stringToLower(exactString);

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString) == exactString && _duplicateNormal[i].getDone() == done){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString) == exactString && _duplicateDeadline[i].getDone() == done){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateFloating.size(); i++){

		string tempString = _duplicateFloating[i].getTitle();

		if(stringToLower(tempString) == exactString && _duplicateFloating[i].getDone() == done){
			_temp.push_back(_duplicateFloating[i]);
			_duplicateFloating.erase(_duplicateFloating.begin()+i);
			i--;
		}
	}
}

void TaskList::containingExactStringSearchWithStatus(string exactString, bool done, vector<Task>& _temp){

	stringToLower(exactString);

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos && _duplicateNormal[i].getDone() == done){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos && _duplicateDeadline[i].getDone() == done){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateFloating.size(); i++){

		string tempString = _duplicateFloating[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos && _duplicateFloating[i].getDone() == done){
			_temp.push_back(_duplicateFloating[i]);
			_duplicateFloating.erase(_duplicateFloating.begin()+i);
			i--;
		}
	}
}

void TaskList::containingBreakdownStringSearchWithStatus(vector<string> keywords, bool done, vector<Task>& _temp){

	for(unsigned int i = 1; i < keywords.size(); i++){

		containingExactStringSearchWithStatus(keywords[i], done, _temp);
		if(i == 6)
			break;
	}
}

void TaskList::exactSearchWithRangeAndStatus(string exactString, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp){

	stringToLower(exactString);

	Task tempTask;
	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString) == exactString  && tempTask.isClashingWith(_duplicateNormal[i])
			&& _duplicateNormal[i].getDone() == done){
				_temp.push_back(_duplicateNormal[i]);
				_duplicateNormal.erase(_duplicateNormal.begin()+i);
				i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString) == exactString && isInRange(_duplicateDeadline[i].getEnd(), start, end) 
			&& _duplicateDeadline[i].getDone() == done){
				_temp.push_back(_duplicateDeadline[i]);
				_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
				i--;
		}
	}
}

void TaskList::containingExactStringSearchWithRangeAndStatus(string exactString, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp){

	stringToLower(exactString);

	Task tempTask;
	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos && tempTask.isClashingWith(_duplicateNormal[i])
			&& _duplicateNormal[i].getDone() == done){
				_temp.push_back(_duplicateNormal[i]);
				_duplicateNormal.erase(_duplicateNormal.begin()+i);
				i--;
		}
	}

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos && isInRange(_duplicateDeadline[i].getEnd(), start, end)
			&& _duplicateDeadline[i].getDone() == done){
				_temp.push_back(_duplicateDeadline[i]);
				_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
				i--;
		}
	}
}

void TaskList::containingBreakdownStringSearchWithRangeAndStatus(vector<string> keywords, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp){

	for(unsigned int i = 1; i < keywords.size(); i++){

		containingExactStringSearchWithRangeAndStatus(keywords[i], start, end, done, _temp);
		if(i == 6)
			break;
	}
}

void TaskList::setDay(int& day, string& dateTimeString){

	if(dateTimeString.at(0) == '0')
		day = dateTimeString.at(1) - 48;
	else if(dateTimeString.at(0) == '1')
		day = dateTimeString.at(1) - 48 + 10;
	else if(dateTimeString.at(0) == '2')
		day = dateTimeString.at(1) - 48 + 20;
}

void TaskList::setMonth(int& month, string& dateTimeString){

	if(dateTimeString.at(3) == '0')
		month = dateTimeString.at(4) - 48;
	else if(dateTimeString.at(3) == '1')
		month = dateTimeString.at(4) - 48 + 10;
}

void TaskList::setYear(int& year, string& dateTimeString){

	if(dateTimeString.at(6) == '2')
		year = 2000;
	else if(dateTimeString.at(6) == '3')
		year = 3000;

	if(dateTimeString.at(7) == '1')
		year += 100;
	else if(dateTimeString.at(7) == '2')
		year += 200;
	else if(dateTimeString.at(7) == '3')
		year += 300;
	else if(dateTimeString.at(7) == '4')
		year += 400;
	else if(dateTimeString.at(7) == '5')
		year += 500;
	else if(dateTimeString.at(7) == '6')
		year += 600;
	else if(dateTimeString.at(7) == '7')
		year += 700;
	else if(dateTimeString.at(7) == '8')
		year += 800;
	else if(dateTimeString.at(7) == '9')
		year += 900;

	if(dateTimeString.at(8) == '1')
		year += 10;
	else if(dateTimeString.at(8) == '2')
		year += 20;
	else if(dateTimeString.at(8) == '3')
		year += 30;
	else if(dateTimeString.at(8) == '4')
		year += 40;
	else if(dateTimeString.at(8) == '5')
		year += 50;
	else if(dateTimeString.at(8) == '6')
		year += 60;
	else if(dateTimeString.at(8) == '7')
		year += 70;
	else if(dateTimeString.at(8) == '8')
		year += 80;
	else if(dateTimeString.at(8) == '9')
		year += 90;

	year += dateTimeString.at(9) - 48;
}

void TaskList::setHour(int& hour, string& dateTimeString){

	if(dateTimeString.at(11) == '0')
		hour = dateTimeString.at(12) - 48;
	else if(dateTimeString.at(11) == '1')
		hour = dateTimeString.at(12) - 48 + 10;
	else if(dateTimeString.at(11) == '2')
		hour = dateTimeString.at(12) - 48 + 20;
}

void TaskList::setMin(int& min, string& dateTimeString){

	if(dateTimeString.at(14) == '0')
		min = dateTimeString.at(15) - 48;
	else if(dateTimeString.at(14) == '1')
		min = dateTimeString.at(15) - 48 + 10;
	else if(dateTimeString.at(14) == '2')
		min = dateTimeString.at(15) - 48 + 20;
	else if(dateTimeString.at(14) == '3')
		min = dateTimeString.at(15) - 48 + 30;
	else if(dateTimeString.at(14) == '4')
		min = dateTimeString.at(15) - 48 + 40;
	else if(dateTimeString.at(14) == '5')
		min = dateTimeString.at(15) - 48 + 50;
}

void TaskList::setSec(int& sec, string& dateTimeString){

	if(dateTimeString.at(17) == '0')
		sec = dateTimeString.at(18) - 48;
	else if(dateTimeString.at(17) == '1')
		sec = dateTimeString.at(18) - 48 + 10;
	else if(dateTimeString.at(17) == '2')
		sec = dateTimeString.at(18) - 48 + 20;
	else if(dateTimeString.at(17) == '3')
		sec = dateTimeString.at(18) - 48 + 30;
	else if(dateTimeString.at(17) == '4')
		sec = dateTimeString.at(18) - 48 + 40;
	else if(dateTimeString.at(17) == '5')
		sec = dateTimeString.at(18) - 48 + 50;
}

bool TaskList::isValidDateTime(int day, int month, int year, int hour, int minute, int sec){

	if(day < 1 || day > 31)
		return false;
	if(month < 1 || month > 12)
		return false;
	if(year < 2000 || year > 3999)
		return false;
	if(hour < 0 || hour > 24)
		return false;
	if(minute < 0 || minute > 59)
		return false;
	if(sec < 0 || sec > 59)
		return false;

	return true;
}

bool TaskList::isInRange(BasicDateTime time, BasicDateTime start, BasicDateTime end){

	return time.compareTo(start) >= 0 && time.compareTo(end) <= 0;
}

string TaskList::stringToLower(string& toLowerString){

	std::transform(toLowerString.begin(), toLowerString.end(), toLowerString.begin(), ::tolower);

	return toLowerString;
}