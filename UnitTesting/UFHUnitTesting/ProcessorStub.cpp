//@author A0099016B
#include "ProcessorStub.h"

int ProcessorStub::UImainProcessor(string input, string& message, vector<string>& list) {
	message = "returning from stub"; 

	string list1 = "list1";
	string list2 = "list2";
	string list3 = "list3";

	list.push_back(list1);
	list.push_back(list2);
	list.push_back(list3);

	string yellow = "yellow";
	string red = "red";
	string green = "green";
	string blue = "blue";
	string exit = "exit";
	if (input.compare(yellow) == 0){
		return STATUS_CODE_SET_OVERALL::OVERALL_WARNING;
	}else if (input.compare(red) == 0){
		return STATUS_CODE_SET_OVERALL::OVERALL_ERROR;
	}else if (input.compare(blue) == 0){
		return STATUS_CODE_SET_OVERALL::OVERALL_PROMPT;
	}else if (input.compare(exit) == 0){
		return STATUS_CODE_SET_OVERALL::OVERALL_EXIT;
	}else{
		return STATUS_CODE_SET_OVERALL::OVERALL_SUCCESS;
	}
}