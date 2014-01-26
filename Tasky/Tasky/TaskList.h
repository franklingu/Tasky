#ifndef _TASKLIST_H_
#define _TASKLIST_H_

/*
*This class is mainly to store tasks and manipulate tasks according to processor's command.
*
*Main author: Kai Wen
*/
//@author A0096760W

#include "Essential.h"
#include "Task.h"
#include "FileProcessing.h"
#include <ctime>

class TaskList{
private:
	vector<Task> _floatingTask;
	vector<Task> _deadlineTask;
	vector<Task> _normalTask;

	vector<Task> _duplicateFloating;
	vector<Task> _duplicateDeadline;
	vector<Task> _duplicateNormal;

	FileProcessing _fileProcessing;

public:
	/** Abstraction Level 1 */
	TaskList();
	/**
	* Purpose:
	* adds the task to the taskList. Pushes any tasks that clashes into the referenced vector
	* @param toAdd the task to be added into _taskList
	* @param _temp for TaskList to push in tasks that clash
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
	* updates the existing task into the new task. any tasks that clashes will be pushed into referenced vector.
	* @param exisitngTask old task
	* @param newTask task with new details
	* @param _temp for TaskList to put in tasks that clash
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
	* pushes all tasks into referenced vector
	* @param _temp for TaskList to put in all tasks
	* @return status code
	*/
	int displayAll(vector<Task>& _temp);
	/**
	* Purpose:
	* pushes tasks that are pending today into referenced vector
	* @param done for TaskList to search either done/pending tasks
	* @param _temp  for TaskList to put in matching tasks
	* @return status code
	*/
	int displayToday(vector<Task>& _temp);
	/**
	* Purpose:
	* pushes tasks that are done/pending accordingly into referenced vector
	* @param done for TaskList to search either done/pending tasks; done: true, pending:false;
	* @param _temp  for TaskList to put in matching tasks
	* @return status code
	*/
	int displayStatus(bool done, vector<Task>& _temp);
	/**
	* Purpose:
	* does different types of searches according to the parameters that are supplied
	* @param keywords
	* @param statusPresent indicates whether to include status in search; 0 - none, 1 - done, -1 - pending
	* @param type indicates whether to include range in search; 0 - false, 2 - true
	* @param start
	* @param end
	* @param _temp to store search results
	* @return status code
	*/
	int searchTasks(vector<string> keywords, int statusPresent, int type, BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	/**
	* Purpose:
	* searches for empty slots between the start time and end time
	* @param start
	* @param end
	* @param _temp for TaskList to push in the slots that are empty in pairs of BasicDateTime
	* @return status code
	*/
	int searchEmptySlots(BasicDateTime start, BasicDateTime end, vector<BasicDateTime>& _temp);
	/**
	* Purpose:
	* pushes tasks that that has the same title as searchLine into temp.
	* @param searchLine title of task being searched
	* @param _temp for TaskList to push in tasks that match
	* @return status code
	*/
	int search(string searchLine, vector<Task>& _temp);
	/**
	* Purpose:
	* Collates all the tasks, puts them into a vector and pass to FileProcessing
	* @return status code
	*/
	int saveFile();
	/**
	* Purpose:
	* Retrieves the data of tasks and by reading vector of string from FileProcessing
	* @return status code
	*/
	int loadFile();

private:
	//** Abstraction Level 2 */
	void pushClashing(Task task, vector<Task>& _temp);
	void addTask(Task toAdd);
	bool isExisting(Task task);
	bool isSuccessfullyRemoved(Task task);
	bool isSuccessfullyMarked(bool mark, Task task);
	void appendVectors(vector<Task>& _temp);
	void setToday(BasicDateTime& start, BasicDateTime& end);
	void setFlags(vector<string> keywords, int statusPresent, int type);
	/**
	* Purpose:
	* pushes tasks in range into referenced vector
	* @param start
	* @param end
	* @param _temp for TaskList to put in tasks within the range
	* @return status code
	*/
	int searchInRange(BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	/**
	* Purpose:
	* pushes tasks with matching status and in range to referenced vector
	* @param done
	* @param start
	* @param end
	* @param _temp for TaskList to put in tasks within the range
	* @return status code
	*/
	int searchStatusInRange(bool done, BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	/**
	* Purpose:
	* searches for tasks corresponding to the keywords and pushes those tasks by relevance into referenced vector.
	* @param keywords
	* @param _temp for TaskList to push in tasks that match
	* @return status code
	*/
	int searchKeywords(vector<string> keywords, vector<Task>& _temp);
	/**
	* Purpose:
	* same as searchKeywords but only searches for tasks that are in range.
	* @param keywords
	* @param _temp for TaskList to push in tasks that match
	* @param start
	* @param end
	* @return status code
	*/
	int searchKeywordsInRange(vector<string> keywords, BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	/**
	* Purpose:
	* same as searchKeywords but only searches for tasks that matches the status.
	* @param keywords
	* @param done status of task to search for
	* @param _temp for TaskList to push in tasks that match
	* @return status code
	*/
	int searchKeywordsWithStatus(vector<string> keywords, bool done, vector<Task>& _temp);
	/**
	* Purpose:
	* same as searchKeywords but searches for tasks that matches both status and range
	* @param keywords
	* @param start
	* @param end
	* @param done status of task to search for
	* @param _temp for TaskList to push in tasks that match
	* @return status code
	*/
	int searchKeywordsWithRangeAndStatus(vector<string> keywords, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp);
	bool isEmptySlotsPresent(BasicDateTime start, BasicDateTime end);
	void pushEmptySlots(BasicDateTime& start, BasicDateTime& end, vector<BasicDateTime>& _temp);
	void searchTitle(string searchLine, vector<Task>& _temp);
	vector<string> taskVecToStringVec(vector<Task>& allTasks);
	void loadTasksFromVector(vector<string>& stringsFromFile);

	/** Abstraction Level 3 */
	void pushInRange(vector<Task>& _temp, BasicDateTime start, BasicDateTime end);
	void pushStatus(bool done, vector<Task>& _temp);
	void pushStatusInRange(bool done, BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	void searchVectors(vector<string> keywords, vector<Task>& _temp);
	void searchVectorsWithRange(vector<string> keywords, BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	void searchVectorsWithStatus(vector<string> keywords, bool done, vector<Task>& _temp);
	void searchVectorsWithRangeAndStatus(vector<string> keywords, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp);
	void cutRange(BasicDateTime& start, BasicDateTime& end);
	void pushEmptySlotsToTemp(BasicDateTime& start, BasicDateTime& end, vector<BasicDateTime>& _temp);
	void stringToBasicDateTime(string, BasicDateTime&);

	/** Abstraction Level 4 */
	void exactSearch(string exactString, vector<Task>& _temp);
	void containingExactStringSearch(string exactString, vector<Task>& _temp);
	void containingBreakdownStringSearch(vector<string> keywords, vector<Task>& _temp);

	void exactSearchWithRange(string exactString, BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	void containingExactStringSearchWithRange(string exactString, BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	void containingBreakdownStringSearchWithRange(vector<string> keywords, BasicDateTime start, BasicDateTime end, vector<Task>& _temp);

	void exactSearchWithStatus(string exactString, bool done, vector<Task>& _temp);
	void containingExactStringSearchWithStatus(string exactString, bool done, vector<Task>& _temp);
	void containingBreakdownStringSearchWithStatus(vector<string> keywords, bool done, vector<Task>& _temp);

	void exactSearchWithRangeAndStatus(string exactString, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp);
	void containingExactStringSearchWithRangeAndStatus(string exactString, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp);
	void containingBreakdownStringSearchWithRangeAndStatus(vector<string> keywords, BasicDateTime start, BasicDateTime end, bool done, vector<Task>& _temp);

	void setDay(int& day, string& dateTimeString);
	void setMonth(int& month, string& dateTimeString);
	void setYear(int& year, string& dateTimeString);
	void setHour(int& hour, string& dateTimeString);
	void setMin(int& min, string& dateTimeString);
	void setSec(int& sec, string& dateTimeString);
	bool isValidDateTime(int day, int month, int year, int hour, int minute, int sec);

	bool isInRange(BasicDateTime time, BasicDateTime start, BasicDateTime end);

	/** Abstraction Level 5 */
	string stringToLower(string& toLowerString);
};

#endif