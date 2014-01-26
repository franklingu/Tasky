#ifndef _ProcessorStub_H_
#define _ProcessorStub_H_

/*
*This class is the central controlling unit. It will take string from UI and process it, acknowledge UI
*if input format is not suitable or it will go ahead and extract command out of input string and call methods
*in TaskList/history/FileProcessing to carry out the command.
*
*Main role: string processing, central logic unit, front wall of logic.
*
*Additional notice: this class will take the pointer of the _itemList in TaskList class to ease the cost of
*displaying. But the author of this class will only read from _itemList. This method is more like data-binding
*with only programmers' protection.
*
*Author: Akshat, Junchao
*/

#include <sstream>
#include <iostream>
#include <algorithm>
#include <msclr\marshal_cppstd.h>
#include "Task.h"
#include "BasicDateTime.h"
#include "History.h"
#include "FileProcessing.h"
#include "TaskList.h"
#include "Essential.h"

using namespace msclr::interop;

class ProcessorStub{
	
public:
	int UImainProcessor(string input, string& message, vector<string>& list);
};

#endif
