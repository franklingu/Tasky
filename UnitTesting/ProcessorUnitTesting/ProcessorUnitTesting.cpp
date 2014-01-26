/*
* ProcessorUnitTesting.cpp
* @author A0103516U
* Unit tests for the Processor task
* tests using actual classes, not stubs
* as stubs would be pointless due to high coupling
*/

#include "gtest/gtest.h"
#include "Processor.h"
#include <string>

const string NEWLINE = "\n";

string message, expected, actual;
vector<string> outStrings;
int statusCode;

/*add a normal task with all parameters*/
TEST(message_addSingle, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 08.00 to 22/11/2020 09.00", message, outStrings);
	EXPECT_EQ("Success! Task added",message);
}

TEST(outStrings_addSingleNormal, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 08.00 to 22/11/2020 09.00 -m Adding comment", message, outStrings);
	expected = 
		"Task Added:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 08:00:00\n"
		"End time:   22/11/2020 09:00:00\n"
		"Comment:    Adding comment";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outStrings_addSingleDeadline, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' by 21/11/2020 08.00", message, outStrings);
	expected = 
		"Task Added:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   21/11/2020 08:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outStrings_addSingleFloating, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1'", message, outStrings);
	expected = 
		"Task Added:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   None\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

/* add existing task */
TEST(message_addExisting, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 08.00 to 22/11/2020 09.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 08.00 to 22/11/2020 09.00", message, outStrings);
	EXPECT_EQ("Error! Task already exists. Task not added",message);
}

/*add a normal task which clashes*/
TEST(message_addClash, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 08.00 to 22/11/2020 09.00", message, outStrings);

	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 21/11/2020 to 22/11/2020", message, outStrings);
	EXPECT_EQ("Warning! Task clashes with existing ones",message);
}

TEST(outStrings_addClash1, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 08.00 to 22/11/2020 09.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 21/11/2020 08.00 to 22/11/2020 12.00", message, outStrings);
	expected = 
		"Task Added:"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 08:00:00\n"
		"End time:   22/11/2020 12:00:00\n"
		"Comment:    "
		"Clashes:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 08:00:00\n"
		"End time:   22/11/2020 09:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected,actual);
}

TEST(outStrings_addClash2, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 08.00 to 22/11/2020 09.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 21/11/2020 08.00 to 22/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 20/11/2020 to 23/11/2020", message, outStrings);
	expected = 
		"Task Added:"
		"Title:      test case 3\n"
		"Status:     Pending\n"
		"Start time: 20/11/2020 00:00:00\n"
		"End time:   23/11/2020 23:59:59\n"
		"Comment:    "
		"Clashes:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 08:00:00\n"
		"End time:   22/11/2020 09:00:00\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 08:00:00\n"
		"End time:   22/11/2020 12:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3]+outStrings[4];
	EXPECT_EQ(expected, actual);
}

/*border case for task clash, SHOULD be identified as clashing*/

TEST(outStrings_addBorderClashPlus, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 11.59 to 24/11/2020", message, outStrings);
	expected = 
		"Task Added:"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 22/11/2020 11:59:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    "
		"Clashes:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 12:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);
}

TEST(outStrings_addBorderClashMinus, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 16.00 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 20/11/2020 to 21/11/2020 16.01", message, outStrings);
	expected = 
		"Task Added:"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 20/11/2020 00:00:00\n"
		"End time:   21/11/2020 16:01:00\n"
		"Comment:    "
		"Clashes:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 16:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);}

/*border case for task clash, SHOULD NOT be identified as clashing*/
TEST(message_addBorderNoClash, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020", message, outStrings);
	EXPECT_EQ("Success! Task added",message);
}

TEST(outStrings_addBorderNoClash, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020", message, outStrings);
	expected =
		"Task Added:"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 23/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

/*test cases for remove*/
/* single remove*/
TEST(message_remove, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	EXPECT_EQ("Success! Task removed",message);
}

TEST(outStrings_remove, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	expected = 
		"Tasks removed:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

/*invalid remove*/
TEST(message_removeInvalid, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 3'", message, outStrings);
	EXPECT_EQ("Warning! No such task",message);
}

/*remove with choices*/
TEST(message_removeChoose, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	EXPECT_EQ("Enter task number to remove:", message);
}

TEST(prompt_removeChoose, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 22/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outstrings_removeChoose, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("2", message, outStrings);
	expected = 
		"Tasks removed:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 22/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];

	EXPECT_EQ(expected, actual);
}

/*remove with multiple choices*/
TEST(outstrings_removeChooseMultiple, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' by 20/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("1-2", message, outStrings);
	expected = 
		"Tasks removed:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   20/12/2020 23:59:59\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2];
	EXPECT_EQ(expected, actual);
}

/*test cases for display*/
TEST(message_display, display){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 2' pending", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("display all", message, outStrings);
	EXPECT_EQ("Success! Tasks displayed",message);
}

TEST(outstrings_displayAll, display){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 2' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("display all", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test case 2\n"
		"Status:     Done\n"
		"Start time: 22/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outstrings_displayDone, display){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 2' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("display done", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 2\n"
		"Status:     Done\n"
		"Start time: 22/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0];
	EXPECT_EQ(expected, actual);
}

TEST(outstrings_displayPending, display){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 2' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("display pending", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0];
	EXPECT_EQ(expected, actual);
}

/*test cases for rename*/
TEST(message_rename, rename){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("rename 'test case 1' to 'test case 3'", message, outStrings);
	EXPECT_EQ("Success! Task updated",message);
}

TEST(outStrings_rename, rename){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020 -m A comment", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("rename 'test case 1' to 'test case 3'", message, outStrings);
	expected = 
		"Task renamed:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    A comment"
		"Updated to:"
		"Title:      test case 3\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    A comment";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);
}

TEST(outStrings_renameComment, rename){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("rename 'test case 1' to 'test case 3' -m A comment", message, outStrings);
	expected = 
		"Task renamed:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Updated to:"
		"Title:      test case 3\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    A comment";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);
}

TEST(message_renameInvalid, rename){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("rename 'test case 3' to 'test case 1'", message, outStrings);
	EXPECT_EQ("Warning! No such task",message);
}

TEST(message_renameChoose, rename){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("rename 'test case 1' to 'test case 3'", message, outStrings);
	EXPECT_EQ("Enter task number to rename:", message);
}

TEST(prompt_renameChoose, rename){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("rename 'test case 1' to 'test case 3'", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 22/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outstrings_renameChoose, rename){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("rename 'test case 1' to 'test case 3'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("1", message, outStrings);
	expected = 
		"Task renamed:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Updated to:"
		"Title:      test case 3\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);
}

/*test cases for reschedule*/
TEST(message_reschedule, reschedule){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 1' by 22/12/2020", message, outStrings);
	EXPECT_EQ("Success! Task updated",message);
}

TEST(outStrings_reschedule, reschedule){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 1' by 22/12/2020", message, outStrings);
	expected = 
		"Task rescheduled:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Updated to:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   22/12/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);
}

TEST(message_rescheduleInvalid, reschedule){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 3' by 22/12/2020", message, outStrings);
	EXPECT_EQ("Warning! No such task",message);
}

TEST(message_rescheduleChoose, reschedule){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 1' by 22/12/2020", message, outStrings);
	EXPECT_EQ("Enter task number to reschedule:", message);
}

TEST(prompt_rescheduleChoose, reschedule){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 1' by 22/12/2020", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 22/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outstrings_rescheduleChoose, reschedule){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 1' by 22/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("1", message, outStrings);
	expected = 
		"Task rescheduled:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Updated to:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   22/12/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);
}

/*test cases for mark*/
/* single mark*/
TEST(message_mark, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	EXPECT_EQ("Success! Task(s) marked",message);
}

TEST(outStrings_mark, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	expected = 
		"Tasks marked:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Done\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

/*invalid mark*/
TEST(message_markInvalid, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 3' Done", message, outStrings);
	EXPECT_EQ("Warning! No such task",message);
}

/*mark with choices*/
TEST(message_markChoose, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	EXPECT_EQ("Enter task number to mark:", message);
}

TEST(prompt_markChoose, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 22/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outstrings_markChoose, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("2", message, outStrings);
	expected = 
		"Tasks marked:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Done\n"
		"Start time: 22/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];

	EXPECT_EQ(expected, actual);
}

/*mark with multiple choices*/
TEST(outstrings_markChooseMultiple, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' by 20/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("1-2", message, outStrings);
	expected = 
		"Tasks marked:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Done\n"
		"Start time: None\n"
		"End time:   20/12/2020 23:59:59\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test case 1\n"
		"Status:     Done\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2];
	EXPECT_EQ(expected, actual);
}

/*test a mark toggle*/
TEST(outstrings_markToggle, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' pending", message, outStrings);
	expected = 
		"Tasks marked:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

/* test mark same status*/ 
TEST(message_markSame, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	EXPECT_EQ("Warning! There is no change for the status", message);
}

TEST(outstrings_markSame, mark){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 1' done", message, outStrings);
	expected = 
		"Tasks marking error:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Done\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

/*test cases for search
* not every possible scenario is tested as
* some testing from the tasklist class for all those cases is assumed
*/
/* simple keyword search*/
TEST(message_searchKeywords, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1 keyword1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test nocase 1 keyword2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest nocase 1 keyword3' by 20/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest case 2 keyword4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search 'test case keyword3'", message, outStrings);
	EXPECT_EQ("Success! Search successful", message);
}

TEST(outstrings_searchKeywords, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1 keyword1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test nocase 1 keyword2' from 22/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest nocase 1 keyword3' by 20/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest case 2 keyword4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search 'test case keyword3'", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 1 keyword1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test nocase 1 keyword2\n"
		"Status:     Pending\n"
		"Start time: 22/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    "
		"Task no:    3\n"
		"Title:      notest case 2 keyword4\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    "
		"Task no:    4\n"
		"Title:      notest nocase 1 keyword3\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   20/12/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);
}

TEST(outstrings_searchKeywordsRange, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1 keyword1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1 keyword2' from 23/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest nocase 1 keyword3' by 20/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest case 2 keyword4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest case 2 keyword5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search 'case' from 23/11/2020 to 25/11/2020", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 1 keyword2\n"
		"Status:     Pending\n"
		"Start time: 23/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      notest case 2 keyword4\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outstrings_searchKeywordsRangeStatus, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1 keyword1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1 keyword2' from 23/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest nocase 1 keyword3' by 20/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest case 2 keyword4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest case 2 keyword5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'notest case 2 keyword4' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search 'case' pending from 23/11/2020 to 25/11/2020", message, outStrings);
	expected = 
		"Task no:    1\n"
		"Title:      test case 1 keyword2\n"
		"Status:     Pending\n"
		"Start time: 23/11/2020 00:00:00\n"
		"End time:   24/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0];
	EXPECT_EQ(expected, actual);
}

TEST(message_searchInvalid, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1 keyword1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1 keyword2' from 23/11/2020 to 24/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest nocase 1 keyword3' by 20/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest case 2 keyword4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'notest case 2 keyword5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'notest case 2 keyword4' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search 'invalid' pending from 22/11/2020 to 25/11/2020", message, outStrings);

	EXPECT_EQ("Warning! No such task", message);
}

TEST(message_searchSlots, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search slots from 20/11/2020 to 25/11/2020", message, outStrings);

	EXPECT_EQ("Success! Search successful", message);
}

TEST(outstrings_searchSlots, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search slots from 20/11/2020 to 25/11/2020", message, outStrings);
	expected =
		"Following empty slots found:"
		"1:From: 20/11/2020 00:00:00 To: 21/11/2020 00:00:00"
		"2:From: 22/11/2020 23:59:59 To: 23/11/2020 00:00:00"
		"3:From: 24/11/2020 12:00:00 To: 24/11/2020 13:00:00";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);
}

TEST(message_searchSlotsInvalid, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search slots from 21/11/2020 to 22/11/2020", message, outStrings);

	EXPECT_EQ("Warning! No slots found", message);
}

TEST(outstrings_searchSlotsMinus, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search slots from 20/11/2020 to 21/11/2020", message, outStrings);
	expected =
		"Following empty slots found:"
		"1:From: 20/11/2020 00:00:00 To: 21/11/2020 00:00:00";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outstrings_searchSlotsPlus, search){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("search slots from 25/11/2020 to 26/11/2020", message, outStrings);
	expected =
		"Following empty slots found:"
		"1:From: 25/11/2020 23:59:59 To: 26/11/2020 23:59:59";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}


/* test cases for undo */
TEST(message_undo, undo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("undo", message, outStrings);

	EXPECT_EQ("Success! Undo successful", message);
}

TEST(outstrings_undo, undo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("undo", message, outStrings);
	expected = 
		"Undo Tasks removed:"
		"Title:      test case 5\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   None\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(message_undoMultiple, undo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 4' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 1' by 15/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("undo 4", message, outStrings);

	EXPECT_EQ("Success! Undo successful", message);
}

TEST(outstrings_undoMultiple, undo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 4' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 1' by 15/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("undo 4", message, outStrings);
	expected = 
		"Undo Tasks added:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2020 00:00:00\n"
		"End time:   22/11/2020 23:59:59\n"
		"Comment:    "
		"Undo Tasks updated:"
		"Title:      test case 4\n"
		"Status:     Done\n"
		"Start time: None\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    "
		"Title:      test case 4\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    "
		"Undo Tasks removed:"
		"Title:      test case 4\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    "
		"Undo Tasks removed:"
		"Title:      test case 3\n"
		"Status:     Pending\n"
		"Start time: 24/11/2020 13:00:00\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3]+outStrings[4]+outStrings[5]+outStrings[6]+outStrings[7]+outStrings[8];
	EXPECT_EQ(expected, actual);
}

TEST(message_undoInvalid, undo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("undo", message, outStrings);
	EXPECT_EQ("Warning! There is nothing to undo", message);
}

/* test cases for redo */
TEST(message_redo, redo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("undo", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("redo", message, outStrings);

	EXPECT_EQ("Success! Redo successful", message);
}

TEST(outstrings_redo, redo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 5'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("undo", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("redo", message, outStrings);
	expected = 
		"Redo Tasks added:"
		"Title:      test case 5\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   None\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(message_redoMultiple, redo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 4' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 1' by 15/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("undo 4", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("redo 3", message, outStrings);

	EXPECT_EQ("Success! Redo successful", message);
}

TEST(outstrings_redoMultiple, redo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 23/11/2020 to 24/11/2020 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 24/11/2020 13.00 to 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 4' by 25/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("mark 'test case 4' done", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("reschedule 'test case 1' by 15/12/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("undo 4", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("redo 3", message, outStrings);
	expected = 

		"Redo Tasks added:"
		"Title:      test case 3\n"
		"Status:     Pending\n"
		"Start time: 24/11/2020 13:00:00\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    "
		"Redo Tasks added:"
		"Title:      test case 4\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    "
		"Redo Tasks updated:"
		"Title:      test case 4\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    "
		"Title:      test case 4\n"
		"Status:     Done\n"
		"Start time: None\n"
		"End time:   25/11/2020 23:59:59\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3]+outStrings[4]+outStrings[5]+outStrings[6];
	EXPECT_EQ(expected, actual);
}

TEST(message_redoInvalid, redo){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2020 to 22/11/2020", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("redo", message, outStrings);
	EXPECT_EQ("Warning! There is nothing to redo", message);
}
