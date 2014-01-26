#ifndef TASK_H
#define TASK_H

/**
 *This class is mainly to model a task in the real world. It uses
 *the BasicDateTime class for the date and time of a task.
 *
 *Main author: Kai Wen, Akshat, Junchao
 */
//@author A0096760W

#include "Essential.h"
#include "BasicDateTime.h"

class Task{
private:

private:
	string _title;
	BasicDateTime _start;
	BasicDateTime _end;
	int _type;
	bool _done;
	string _comment;

private:
	static const string TYPE_KEY_WORD;
	static const string TITLE_KEY_WORD;
	static const string STATUS_KEY_WORD;
	static const string START_KEY_WORD;
	static const string END_KEY_WORD;
	static const string COMMENT_KEY_WORD;
	static const string DONE_KEY_WORD;
	static const string PENDING_KEY_WORD;
	static const string NONE_KEY_WORD;
	static const string TIMED_TASK_KEY_WORD;
	static const string DEADLINE_TASK_KEY_WORD;
	static const string FLOATING_TASK_KEY_WORD;
	static const string EMPTY_STRING;
	static const string NEW_LINE;
	
    static const int FLOATING_TASK = 0;
    static const int DEADLINE_TASK = 1;
    static const int TIMED_TASK = 2;

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
	/**
	* Purpose:
	* converts the Task object to a string for saving and displaying,
	* returns that string
	*/
	string toString();
	vector<string> toStringVector();
	void setTitle(string title);
	void setComment(string comment);
	void setStartDate(BasicDateTime start);
	void setEndDate(BasicDateTime end);
	void setType(int type);
	bool operator<(Task& a);

private:
	string statusToString();
	string typeToString();
	string startToString();
	string endToString();
};

#endif
