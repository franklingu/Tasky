#ifndef _TASK_H_
#define _TASK_H_

/**
*This class is mainly to model a task in the real world. It uses
*the BasicDateTime class for the date and time of a task.
*
*
*
*Main author: Kai Wen
*/

#include "Essential.h"
#include "BasicDateTime.h"


class Task{
private:
	string _title;
	BasicDateTime _start;
	BasicDateTime _end;
	int _type;
	bool _done;
	string _comment;

public:

	Task();
	Task(std::string title, BasicDateTime start, BasicDateTime end, int type, bool status, std::string comment);
	~Task();	
	string getTitle();
	BasicDateTime getStart();
	BasicDateTime getEnd();
	int getType();
	bool getDone();
	string getComment();
	/**
	* Purpose:
	* toggles the state of the task from pending to done or vice versa.
	*/
	void toggleDone();
	/**
	* Purpose:
	* checks if this Task is equal to argument Task
	* @param Task the task to be compared with
	* @return True - Tasks are equal, False - Tasks are not equal
	*/
	bool isEqualTo(Task another);
	/**
	* Purpose:
	* checks if argument Task clashes with this Task.
	* @param Task the task to be compared with
	* @return True - Tasks clash, False - No clash
	*/
	bool isClashingWith(Task another);
	void setTitle(string title);
	void setStartDate(BasicDateTime start);
	void setEndDate(BasicDateTime end);
	void setType(int type);
};

#endif
