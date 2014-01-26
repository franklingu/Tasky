#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

/*
 *This class is mainly for file-related operations. At the starting phase of the program, it will load existing 
 *tasks to processor and when the save method is being called, it will save the content in logic list to local file
 *
 *Main author: Joan
*/

#include <fstream>
#include "Essential.h"
//#include "LogLibrary\Log.h"

static const string _LOGNAME = "Tasky.txt";
static const int TASKLINES = 6;

class FileProcessing{
private:
	/**
	* Purpose:
	* Checks if the file Log is empty
	*@return True - File Log is empty, False - File Log not empty
	*/
	bool emptyFile();
	void readLines(ifstream& input, vector<string>& data);
	void writeLines(ofstream& output, vector<string>& data);
public:
	/**
	* Purpose:
	* Checks if file Log exists
	* If it exists, reads and load the tasks from file Log into vector<string> data
	* @param data - vector to be loaded with tasks from Log
	*@return Success in loading file; File Log does not exist; File Log is empty
	*/
	int load(vector<string>& data); 
	/**
	* Purpose:
	* Checks if file Log exist
	* If it exists, writes the task from vector<string> data into file Log
	* If it does not exist, create a file Log
	* @param data - vector containing all the tasks to be written
	* @return Success in writing file; failure in writing file
	*/
	int save(vector<string>& data); //reads vector, writes to text file
};

#endif
