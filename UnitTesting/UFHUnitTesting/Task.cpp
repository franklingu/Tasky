#include "Task.h"

static const int FLOATING_TASK = 0;
static const int DEADLINE_TASK = 1;
static const int NORMAL_TASK = 2;

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

Task::~Task()
{

}

bool Task::isEqualTo(Task another){

	switch(another.getType()){

	case FLOATING_TASK:
		return another.getTitle() == _title
			&& another.getType() == _type;
		break;
	case DEADLINE_TASK:
		return another.getTitle() == _title
			&& another.getEnd().compareTo(_end) == 0;
		break;
	case NORMAL_TASK:
		return another.getTitle() == _title
			&& another.getStart().compareTo(_start) == 0
			&& another.getEnd().compareTo(_end) == 0;
		break;

	}
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

void Task::setTitle(string title){
	_title = title;
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