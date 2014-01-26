// TestDriver.cpp : Defines the entry point for the console application.
//
//@author A0105750N

#include <string>
#include <vector>
#include <gtest\gtest.h>
#include "Interpreter.h"
#include "BasicDateTime.h"
#include "Essential.h"

using namespace std;

//test for add
TEST(AddTest, simpleTest1){
	Interpreter inter;
	string title, comment;
	int type;
	BasicDateTime start, end;

	//standard input without comment
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD, inter.interpretAdd("'this one' from 12/09/2012 12.05 to 12/12/2012 13.05", title, type, start, end, comment));  //-- passed
	EXPECT_EQ("this one", title);
	EXPECT_EQ(2, type);
	EXPECT_EQ(12, start.getDay());
	EXPECT_EQ(9, start.getMonth());
	EXPECT_EQ(2012, start.getYear());
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	//multiple single quote
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD, inter.interpretAdd("'this's one' from 12/12/12 12.00 to 13/12/13 13.00", title, type, start, end, comment));  //-- passed
	EXPECT_EQ(2, type);
	EXPECT_EQ(12, start.getDay());
	EXPECT_EQ(2012, start.getYear());
	EXPECT_EQ(2013, end.getYear());
	EXPECT_EQ(13, end.getHour());
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	//multiple single quotes with comment
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD, inter.interpretAdd("'this's one' from 12/12/12 12.00 to 13/12/13 13.00 -m this is comment", title, type, start, end, comment));  //-- passed
	EXPECT_EQ(2, type);
	EXPECT_EQ(12, start.getDay());
	EXPECT_EQ(2012, start.getYear());
	EXPECT_EQ(2013, end.getYear());
	EXPECT_EQ(13, end.getHour());
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	//time with seconds
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD, inter.interpretAdd("'this's one' from today 14.00 to tomorrow 15.00.05 -m this is comment", title, type, start, end, comment));  // -- passed
	EXPECT_EQ(2, type);
	EXPECT_EQ("this is comment", comment);
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	//special date input
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD, inter.interpretAdd("'this's one' from today 1500 to tomorrow 1600 -m this is comment", title, type, start, end, comment));  // -- passed
	EXPECT_EQ(2, type);
	EXPECT_EQ("this is comment", comment);
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	//special date input
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD, inter.interpretAdd("'this's one' by tomorrow 1500 -m this is comment", title, type, start, end, comment));  // -- passed
	EXPECT_EQ(1, type);
	EXPECT_EQ("this is comment", comment);
	cout<<end.getDateTimeString()<<endl;
	//special date input
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD, inter.interpretAdd("'this's one' by next mon 1600 -m this is comment2", title, type, start, end, comment));
	EXPECT_EQ(1, type);
	EXPECT_EQ("this is comment2", comment);
	cout<<end.getDateTimeString()<<endl;
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD, inter.interpretAdd("'this's one' by this sun 1600 -m this is comment3", title, type, start, end, comment));
	cout<<end.getDateTimeString()<<endl;
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD, inter.interpretAdd("'this' from today to tomorrow", title, type, start, end, comment));
	//time out of boundary
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DATETIME_FORMAT, inter.interpretAdd("'this's one' from 31/04/12 12.00 to 13/12/13 13.00", title, type, start, end, comment));
	//empty input
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT, inter.interpretAdd("", title, type, start, end, comment));
	//incomplete title
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT, inter.interpretAdd("' this from 30/04/12 to 20/05/13", title, type, start, end, comment));
	//empty title
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT, inter.interpretAdd(" '' -m this", title, type, start, end, comment));
	//boundary checking
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DATETIME_FORMAT, inter.interpretAdd("'this's one' from today 15.00.00 to today 15.00.00 -m this is comment", title, type, start, end, comment));
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
}

TEST(RenameTest, simpleTest1){
	Interpreter inter;
	string title1, title2 , comment;
	BasicDateTime start, end;

	//standard
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RENAME, inter.interpretRename(" 'this is old' to 'this is new'", title1, title2, comment));
	EXPECT_EQ("this is old", title1);
	EXPECT_EQ("this is new", title2);
	//multiple single quotes
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RENAME, inter.interpretRename(" 'this 'is' old' to 'this is' new'", title1, title2, comment));
	EXPECT_EQ("this 'is' old", title1);
	EXPECT_EQ("this is' new", title2);
	//return error code
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND,inter.interpretRename("'this is is is'", title1, title2, comment));
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND,inter.interpretRename("'this is is ' to '", title1, title2, comment));
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT,inter.interpretRename("'this is is is' to ''", title1, title2, comment));
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND,inter.interpretRename("'old title'to 'new title'", title1, title2, comment));
}

TEST(RenameAfterSearchTest, simpleTest1){
	Interpreter inter;
	string title1, title2 , comment;
	BasicDateTime start, end;
	int num;

	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH_RENAME, inter.interpretRenameAfterSearch(" 2 to 'this is new'", num, title1, comment));
	EXPECT_EQ(2, num);
	EXPECT_EQ("this is new", title1);
	EXPECT_EQ("", comment);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH_RENAME, inter.interpretRenameAfterSearch(" 12 to 'this is new'", num, title1, comment));
	EXPECT_EQ(12, num);
	EXPECT_EQ("this is new", title1);
	EXPECT_EQ("", comment);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH_RENAME, inter.interpretRenameAfterSearch(" 12 to 'this is new' -m comment", num, title1, comment));
	EXPECT_EQ(12, num);
	EXPECT_EQ("this is new", title1);
	EXPECT_EQ("comment", comment);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH_RENAME, inter.interpretRenameAfterSearch(" 12 to 'this is new' -m 'comment", num, title1, comment));
	EXPECT_EQ(12, num);
	EXPECT_EQ("this is new", title1);
	EXPECT_EQ("'comment", comment);
}

TEST(RemoveTest, simpleTest1){
	Interpreter inter;
	string title1;

	//extract title, not much to test
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_REMOVE, inter.interpretRemove("'this is old'", title1));
	EXPECT_EQ("this is old", title1);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_REMOVE, inter.interpretRemove(" 'this is' ' old'", title1)); 
	EXPECT_EQ("this is' ' old", title1);
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT, inter.interpretRemove(" 'this   ", title1));
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT, inter.interpretRemove(" this  ' ", title1));
}

TEST(MarkTest, simpleTest1){
	Interpreter inter;
	string title1;
	bool status;

	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_MARK, inter.interpretMark("'title' done", title1, status));  // -- passed
	EXPECT_EQ("title", title1);
	EXPECT_TRUE(status);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_MARK, inter.interpretMark("'title' pending", title1, status));  // -- passed
	EXPECT_EQ("title", title1);
	EXPECT_FALSE(status);
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND, inter.interpretMark("'title'", title1, status));
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT, inter.interpretMark("'title", title1, status));
}

TEST(PowerSearchTest, simpleTest1){
	Interpreter inter;
	string title1, title2 , comment;
	vector<string> vec;
	int type, searchStatus;
	bool slotEnabled;
	BasicDateTime start, end;
	//this method is not fully tested yet not all the situations have been covered
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH, inter.interpretPowerSearch("from 12/12/2013 to 14/12/13", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_TRUE(slotEnabled);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH, inter.interpretPowerSearch("'title1 title2'from 12/12/2013 to 14/12/13", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_FALSE(slotEnabled);
	EXPECT_EQ("title1", vec.at(1));
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH, inter.interpretPowerSearch(" slot from 12/12/2013 to 14/12/13", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_TRUE(slotEnabled);
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH, inter.interpretPowerSearch("'keyword1 keyword2'from 12/12/2013 to 14/12/13", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_EQ("keyword2", vec.at(2));
	EXPECT_FALSE(slotEnabled);
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH, inter.interpretPowerSearch("'keyword1 slot slot'from 12/12/2013 to 14/12/13", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_EQ("slot", vec.at(3));
	EXPECT_FALSE(slotEnabled);
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH, inter.interpretPowerSearch("by 12/12/2013 12:13:13", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_TRUE(slotEnabled);
	cout<<end.getDateTimeString()<<endl;
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH, inter.interpretPowerSearch("'title keyword'", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_EQ("title", vec.at(1));
	EXPECT_TRUE(!slotEnabled);
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND, inter.interpretPowerSearch("random string", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND, inter.interpretPowerSearch("'random string", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DATETIME_FORMAT, inter.interpretPowerSearch("from to ", slotEnabled, vec, searchStatus, type, start, end));
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DATETIME_FORMAT, inter.interpretPowerSearch("by ", slotEnabled, vec, searchStatus, type, start, end));
}

TEST(DisplayTest, simpleTest1){
	Interpreter inter;
	string title1, title2 , comment;
	int type;
	//simple for display as this is downgraded
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_DISPLAY, inter.interpretDisplay("all", type)); 
	EXPECT_EQ(0, type);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_DISPLAY, inter.interpretDisplay("pending", type)); 
	EXPECT_EQ(1, type);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_DISPLAY, inter.interpretDisplay(" done", type));
	EXPECT_EQ(2, type);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_DISPLAY, inter.interpretDisplay(" today", type));
	EXPECT_EQ(3, type);
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DISPLAY, inter.interpretDisplay(" tod", type));
}

TEST(RescheduleTest, simpleTest1){
	Interpreter inter;
	string title1, title2 , comment;
	int type;
	BasicDateTime start, end;

	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RESCHEDULE, inter.interpretReschedule("'this is title'", title1, type, start, end));  // -- passed
	EXPECT_EQ(0, type);
	EXPECT_EQ("this is title", title1);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RESCHEDULE, inter.interpretReschedule("'this is's title' from 12/12/12 12.00 to 12/12/12 13.00", title1, type, start, end));  // -- passed
	EXPECT_EQ(2, type);
	EXPECT_EQ("this is's title", title1);
	EXPECT_EQ(STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DATETIME_FORMAT, inter.interpretReschedule("'this is title' by 12/12/12 12.00", title1, type, start, end));
}

TEST(RescheduleAfterSearchTest, simpleTest1){
	Interpreter inter;
	string title1, title2 , comment;
	int type;
	BasicDateTime start, end;
	int num;

	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH_RESCHEDULE, inter.interpretRescheduleAfterSearch(" 2 from tdy to tmr", num, type, start, end));
	EXPECT_EQ(2, num);
	EXPECT_EQ(2, type);
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH_RESCHEDULE, inter.interpretRescheduleAfterSearch(" 2 by tmr", num, type, start, end));
	EXPECT_EQ(2, num);
	EXPECT_EQ(1, type);
	cout<<start.getDateTimeString()<<endl;
	cout<<end.getDateTimeString()<<endl;
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH_RESCHEDULE, inter.interpretRescheduleAfterSearch(" 2", num, type, start, end));
	EXPECT_EQ(2, num);
	EXPECT_EQ(0, type);
	EXPECT_EQ(STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH_RESCHEDULE, inter.interpretRescheduleAfterSearch(" 12", num, type, start, end));
	EXPECT_EQ(12, num);
	EXPECT_EQ(0, type);
}

TEST(StringToIntTest, simpleTes1){
	Interpreter inter;
	EXPECT_EQ(-1, inter.stringToInt("1/1"));
	EXPECT_EQ(12, inter.stringToInt("12"));
	EXPECT_EQ(-1, inter.stringToInt("this"));
	EXPECT_EQ(2012, inter.stringToInt("2012"));
	EXPECT_EQ(-1, inter.stringToInt("20a12"));
}

TEST(StringToIntVecTest, simpleTest1){
	Interpreter inter;
	vector<int> vec;
	//simple method. not many tests here
	vec=inter.stringToIntVec("1,2,3");
	EXPECT_EQ(3, vec.size());
	EXPECT_EQ(1, vec.at(0));
	EXPECT_EQ(2, vec.at(1));
	EXPECT_EQ(3, vec.at(2));
	vec=inter.stringToIntVec("1-3");
	EXPECT_EQ(3, vec.size());
	EXPECT_EQ(1, vec.at(0));
	EXPECT_EQ(2, vec.at(1));
	EXPECT_EQ(3, vec.at(2));
	vec=inter.stringToIntVec("12-13");
	EXPECT_EQ(2, vec.size());
	EXPECT_EQ(12, vec.at(0));
	EXPECT_EQ(13, vec.at(1));
	vec=inter.stringToIntVec("12");
	EXPECT_EQ(1, vec.size());
	EXPECT_EQ(12, vec.at(0));
	vec=inter.stringToIntVec("1,1-1");
	EXPECT_EQ(0, vec.size());
	vec=inter.stringToIntVec("1-12a");
	EXPECT_EQ(0, vec.size());
}
