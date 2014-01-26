//@author A0096760W
#include "Task.h"

const string Task::TITLE_KEY_WORD =			"Title:      ";
const string Task::TYPE_KEY_WORD =			"Type:       ";
const string Task::STATUS_KEY_WORD =		"Status:     ";
const string Task::START_KEY_WORD =			"Start time: ";
const string Task::END_KEY_WORD =			"End time:   ";
const string Task::COMMENT_KEY_WORD =		"Comment:    ";
const string Task::DONE_KEY_WORD =			"Done";
const string Task::PENDING_KEY_WORD =		"Pending";
const string Task::NONE_KEY_WORD =			"None";
const string Task::TIMED_TASK_KEY_WORD =	"Timed task";
const string Task::DEADLINE_TASK_KEY_WORD = "Deadline task";
const string Task::FLOATING_TASK_KEY_WORD = "Floating task" ;
const string Task::EMPTY_STRING = "";
const string Task::NEW_LINE = "\n";

string Task::getTitle(){
	return _title;
}

BasicDateTime Task::getStart(){
	return _start;
}

BasicDateTime Task::getEnd(){
	return _end;
}

int Task::getType(){
	return _type;
}

bool Task::getDone(){
	return _done;
}

string Task::getComment(){
	return _comment;
}

void Task::toggleDone(){
	_done=!_done;
}

Task::Task(){
}


Task::Task(string title, BasicDateTime start, BasicDateTime end, int type, bool done, string comment){
	_title = title;
	_start = start;
	_end = end;
	_type = type;
	_done = done;
	_comment = comment;
}

Task::~Task(){
}

bool Task::isEqualTo(Task another){
	if (another.getDone() != _done){
		return false;
	}	
	switch(another.getType()){

	case FLOATING_TASK:
		return another.getTitle() == _title
			&& another.getType() == _type;
		break;
	case DEADLINE_TASK:
		return another.getTitle() == _title
			&& another.getEnd().compareTo(_end) == 0
			&& another.getType() == _type;
		break;
	case TIMED_TASK:
		return another.getTitle() == _title
			&& another.getStart().compareTo(_start) == 0
			&& another.getEnd().compareTo(_end) == 0
			&& another.getType() == _type;
		break;
	default:
		return false;
		break;
	}
	return false;
}


bool Task::isClashingWith(Task another){
	bool startClash = false;
	bool endClash = false;
	bool spanClash = false;

	if(another.getStart().compareTo(_start) >= 0 && another.getStart().compareTo(_end) < 0)
		startClash = true;

	if(another.getEnd().compareTo(_start) > 0 && another.getEnd().compareTo(_end) <= 0)
		endClash = true;

	if(another.getStart().compareTo(_start) <= 0 && another.getEnd().compareTo(_end) >= 0)
		spanClash = true;

	return startClash || endClash || spanClash;
}

string Task::toString(){
	string outputString;
	//outputString = TYPE_KEY_WORD + typeToString() + NEW_LINE;
	outputString = TITLE_KEY_WORD + _title + NEW_LINE;
	outputString += STATUS_KEY_WORD + statusToString() + NEW_LINE;
	outputString += START_KEY_WORD + startToString() + NEW_LINE;
	outputString += END_KEY_WORD + endToString() + NEW_LINE;
	outputString += COMMENT_KEY_WORD + _comment;

	return outputString;
}

vector<string> Task::toStringVector(){
	vector<string> stringVector;
	string s[6] = {"Type: " + typeToString(),
		"Title: " + _title, 
		"Status: " + statusToString(), 
		"Start: " + startToString(), 
		"End: " + endToString(), 
		"Comment: " + _comment};

	for(unsigned int i = 0; i < 6; i++){
		stringVector.push_back(s[i]);
	}

	return stringVector;
}


string Task::statusToString(){
	if(_done){
		return DONE_KEY_WORD;
	}else{
		return PENDING_KEY_WORD;
	}
}

string Task::typeToString(){
	switch (_type){
	case 0:
		return FLOATING_TASK_KEY_WORD;
		break;
	case 1:
		return DEADLINE_TASK_KEY_WORD;
		break;
	case 2:
		return TIMED_TASK_KEY_WORD;
		break;
	default:
		return EMPTY_STRING;
		break;
	}
}

string Task::startToString(){
	switch (_type){
	case 0:  case 1:
		return NONE_KEY_WORD;
		break;
	case 2:
		return _start.getDateTimeString();
		break;
	default:
		return EMPTY_STRING;
		break;
	}
}
string Task::endToString(){
	switch (_type){
	case 0:
		return NONE_KEY_WORD;
		break;
	case 1:	case 2:
		return _end.getDateTimeString();
		break;
	default:
		return EMPTY_STRING;
		break;
	}
}

void Task::setTitle(string title){
	_title = title;
}

void Task::setComment(string comment){
	_comment = comment;
}

void Task::setStartDate(BasicDateTime start){
	_start = start;
}

void Task::setEndDate(BasicDateTime end){
	_end = end;
}

void Task::setType(int type){
	_type = type;
}

bool Task::operator<(Task& a){
	
	if(a.getType() == TIMED_TASK)
		return (_start.compareTo(a.getStart()) < 0);
	else if(a.getType() == DEADLINE_TASK)
		return (_end.compareTo(a.getEnd()) < 0);
	else
		return false;
}