#ifndef _TASKLIST_H_
#define _TASKLIST_H_

/*
 *This class is mainly to store tasks and manipulate tasks according to processor's command.
 *
 *Main author: Kai Wen
*/

#include "Essential.h"
#include "Task.h"

class TaskList{
private:
	vector<Task> _taskList;
	
public:
	TaskList();
	/**
	* Purpose:
	* adds the task to the taskList. Pushes any tasks that clashes into the referenced vector
	* @param toAdd the task to be added into _taskList
	* @param _temp for Logic to push in tasks that clash
	* @return status code
	*/
	int add(Task toAdd, vector<Task>& _temp);
	/**
	* Purpose:
	* finds a task in the vector that isEqual to the task to be removed and removes it.
	* @param toRemove task to be removed
	* @return status code
	*/
	int remove(Task toRemove);
	/**
	* Purpose:
	* pushes tasks that that has the same title as searchLine into temp.
	* @param searchLine title of task being searched
	* @param _temp for Logic to push in tasks that match
	* @return status code
	*/
	int search(string searchLine, vector<Task>& _temp); 
	/**
	* Purpose:
	* searches for tasks corresponding to the keywords and pushes those tasks by relevance into referenced vector.
	* @param keywords
	* @param _temp for Logic to push in tasks that match
	* @return status code
	*/
	int searchKeywords(vector<string> keywords, vector<Task>& _temp);
	/**
	* Purpose:
	* same as searchKeywords but only searches for tasks that are in range.
	* @param keywords
	* @param _temp for Logic to push in tasks that match
	* @param start
	* @param end
	* @return status code
	*/
	int searchKeywordsInRange(vector<string> keywords, vector<Task>& _temp, BasicDateTime start, BasicDateTime end);
	/**
	* Purpose:
	* pushes all tasks into referenced vector
	* @param _temp for Logic to put in all tasks
	* @return status code
	*/
	int displayAll(vector<Task>& _temp);
	/**
	* Purpose:
	* pushes tasks that are done/pending accordingly into referenced vector; done: true, pending:false;
	* @param done for Logic to search either done/pending tasks
	* @param _temp  for Logic to put in matching tasks
	* @return status code
	*/
	int displayStatus(bool done, vector<Task>& _temp);
	/**
	* Purpose:
	* pushes tasks in range into referenced vector
	* @param start
	* @param end
	* @param _temp for Logic to put in tasks within the range
	* @return status code
	*/
	int displayInRange(BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	/**
	* Purpose:
	* updates the existing task into the new task. any tasks that clashes will be pushed into referenced vector.
	* @param exisitngTask old task
	* @param newTask task with new details
	* @param _temp for Logic to put in tasks that clash
	* @return status code
	*/
	int update(Task existingTask, Task newTask, vector<Task>& _temp);
	/**
	* Purpose:
	* marks the task as done or pending
	* @param mark to mark the status of the task as
	* @param task task to be marked
	* @return status code
	*/
	int mark(bool mark, Task task);
	/**
	* Purpose:
	* pushes BasicDateTimes that are used into the referenced vector
	* @param vector<BasicDateTime> to push in the BasicDateTimes that are used
	*/
	void getOccupiedDates(vector<BasicDateTime>& usedDates);
};

#endif
