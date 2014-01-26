//@author A0096760W
#include "gtest\gtest.h"
#include "testTaskList.h"

TEST(TaskListTest, CheckAdd)
{
	TaskList taskList;

	vector<Task> _temp;

	Task t1float;
	Task t2deadline;
	Task t3normal;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, false, "comment");

	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);

	//EXPECT_EQ("hahaha boring...", taskList.getFloat()[0].getTitle());
	//EXPECT_EQ("Try again later", taskList.getDeadline()[0].getTitle());
	//EXPECT_EQ("la la lah", taskList.getNormal()[0].getTitle());
}

TEST(TaskListTest, CheckAddDuplicates)
{
	TaskList taskList;

	vector<Task> _temp;

	Task t1float;
	Task t2deadline;
	Task t3normal;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, false, "comment");

	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);
	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);

	//EXPECT_EQ(1, taskList.getFloat().size());
	//EXPECT_EQ(1, taskList.getDeadline().size());
	//EXPECT_EQ(1, taskList.getNormal().size());
}

TEST(TaskListTest, CheckAddClashes)
{
	TaskList taskList;

	vector<Task> _temp;

	Task t1normal;
	Task t2normal;
	Task t3normal;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1normal = Task("hahaha boring...", bdtstart1, bdtend3, 2, false, "comment");
	t2normal = Task("Try again later", bdtstart2, bdtend2, 2, false, "comment");
	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, false, "comment");

	taskList.add(t1normal, _temp);
	taskList.add(t2normal, _temp);

	EXPECT_EQ(1, _temp.size());
	EXPECT_EQ("hahaha boring...", _temp[0].getTitle());

	taskList.add(t3normal, _temp);

	EXPECT_EQ(1, _temp.size());
	EXPECT_EQ("hahaha boring...", _temp[0].getTitle());
}

TEST(TaskListTest, CheckRemove)
{
	TaskList taskList;

	vector<Task> _temp;

	Task t1float;
	Task t2deadline;
	Task t3normal;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, false, "comment");

	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);

	//taskList.remove(t1float);
	//EXPECT_EQ(0, taskList.getFloat().size());

	//taskList.remove(t2deadline);
	//EXPECT_EQ(0, taskList.getDeadline().size());

	//taskList.remove(t3normal);
	//EXPECT_EQ(0, taskList.getNormal().size());

}


TEST(TaskListTest, CheckSearch)
{
	TaskList taskList;

	vector<Task> _temp;

	Task t1float;
	Task t2deadline;
	Task t3normal;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, false, "comment");

	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);

	taskList.search("la lah" , _temp);
	EXPECT_EQ(0, _temp.size());

	taskList.search("hahaha boring..." , _temp);
	EXPECT_EQ(1, _temp.size());

	taskList.search("Try again later" , _temp);
	EXPECT_EQ(1, _temp.size());

	taskList.search("la la lah" , _temp);
	EXPECT_EQ(1, _temp.size());

}

//TEST(TaskListTest, CheckSearchKeywords)
//{
//	TaskList taskList;
//
//	vector<Task> _temp;
//
//	Task t1float;
//	Task t2deadline;
//	Task t3normal;
//
//	BasicDateTime bdtstart1(2013,8,13);
//	BasicDateTime bdtstart2(2013,8,17);
//	BasicDateTime bdtstart3(2013,8,19);
//
//	BasicDateTime bdtend1(2013,8,16);
//	BasicDateTime bdtend2(2013,8,18);
//	BasicDateTime bdtend3(2013,8,20);
//
//	t1float = Task("hahaha BoriNg...", bdtstart1, bdtend1, 0, false, "comment");
//	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
//	t3normal = Task("hahaha lah", bdtstart3, bdtend3, 2, false, "comment");
//
//	taskList.add(t1float, _temp);
//	taskList.add(t2deadline, _temp);
//	taskList.add(t3normal, _temp);
//
//	vector<string> keywords;
//	keywords.push_back("A");
//	keywords.push_back("A");
//
//	taskList.searchKeywords(keywords, _temp);
//	EXPECT_EQ(3, _temp.size());
//
//	keywords.clear();
//	keywords.push_back("Hahaha boring");
//	keywords.push_back("Hahaha");
//	keywords.push_back("boring");
//
//	taskList.searchKeywords(keywords, _temp);
//
//	EXPECT_EQ(2, _temp.size());
//	EXPECT_EQ("hahaha BoriNg..." , _temp[0].getTitle());
//	EXPECT_EQ("hahaha lah" , _temp[1].getTitle());
//
//}

//TEST(TaskListTest, CheckSearchtoLowerString){
//
//	TaskList taskList;
//
//	string data = "HAHAHA";
//
//	taskList.stringToLower(data);
//
//	EXPECT_EQ("hahaha", data);
//}

//TEST(TaskListTest, CheckSearchKeywordsWithRange)
//{
//	TaskList taskList;
//
//	vector<Task> _temp;
//
//	Task t1float;
//	Task t2deadline;
//	Task t3normal;
//
//	BasicDateTime dummystart(2013, 5, 10);
//	BasicDateTime dummyend(2013, 5, 12);
//
//	BasicDateTime bdtstart1(2013,8,13);
//	BasicDateTime bdtstart2(2013,8,17);
//	BasicDateTime bdtstart3(2013,8,19);
//
//	BasicDateTime bdtend1(2013,8,16);
//	BasicDateTime bdtend2(2013,8,18);
//	BasicDateTime bdtend3(2013,8,20);
//
//	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
//	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
//	t3normal = Task("hahaha lah", bdtstart3, bdtend3, 2, false, "comment");
//
//	taskList.add(t1float, _temp);
//	taskList.add(t2deadline, _temp);
//	taskList.add(t3normal, _temp);
//
//	vector<string> keywords;
//	keywords.push_back("haha Try");
//	keywords.push_back("haha");
//	keywords.push_back("Try");
//
//	taskList.searchKeywordsInRange(keywords, dummystart, dummyend, _temp);
//	EXPECT_EQ(0, _temp.size());
//
//	taskList.searchKeywordsInRange(keywords, dummystart, bdtend3, _temp);
//	EXPECT_EQ(2, _temp.size());
//
//	EXPECT_EQ("hahaha lah", _temp[0].getTitle());
//	EXPECT_EQ("Try again later", _temp[1].getTitle());
//}

TEST(TaskListTest, CheckDisplayAll){

	TaskList taskList;

	vector<Task> _temp;

	Task t1float;
	Task t2deadline;
	Task t3normal;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, false, "comment");

	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);

	taskList.displayAll(_temp);

	EXPECT_EQ(3, _temp.size());
}

TEST(TaskListTest, CheckDisplayStatusFalse){

	TaskList taskList;

	vector<Task> _temp;

	Task t1float;
	Task t2deadline;
	Task t3normal;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, false, "comment");

	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);

	taskList.displayStatus(false, _temp);

	EXPECT_EQ(3, _temp.size());
}

TEST(TaskListTest, CheckDisplayStatusTrue){

	TaskList taskList;

	vector<Task> _temp;

	Task t1float;
	Task t2deadline;
	Task t3normal;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, true, "comment");
	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, true, "comment");
	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, true, "comment");

	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);

	taskList.displayStatus(true, _temp);

	EXPECT_EQ(3, _temp.size());
}
//
//TEST(TaskListTest, CheckDisplayInRange){
//
//	TaskList taskList;
//
//	vector<Task> _temp;
//
//	Task t1float;
//	Task t2deadline;
//	Task t3normal;
//
//	BasicDateTime bdtstart1(2013,8,13);
//	BasicDateTime bdtstart2(2013,8,17);
//	BasicDateTime bdtstart3(2013,8,19);
//
//	BasicDateTime bdtend1(2013,8,16);
//	BasicDateTime bdtend2(2013,8,18);
//	BasicDateTime bdtend3(2013,8,20);
//
//	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
//	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
//	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, false, "comment");
//
//	taskList.add(t1float, _temp);
//	taskList.add(t2deadline, _temp);
//	taskList.add(t3normal, _temp);
//
//	taskList.searchInRange(bdtstart1, bdtend3, _temp);
//
//	EXPECT_EQ(2, _temp.size());
//
//	taskList.searchInRange(bdtstart1, bdtstart2, _temp);
//
//	EXPECT_EQ(0, _temp.size());
//}

//TEST(TaskListTest, CheckDisplayStatusInRange){
//
//	TaskList taskList;
//
//	vector<Task> _temp;
//
//	Task t1float;
//	Task t2deadline;
//	Task t3normal;
//
//	BasicDateTime bdtstart1(2013,8,13);
//	BasicDateTime bdtstart2(2013,8,17);
//	BasicDateTime bdtstart3(2013,8,19);
//
//	BasicDateTime bdtend1(2013,8,16);
//	BasicDateTime bdtend2(2013,8,18);
//	BasicDateTime bdtend3(2013,8,20);
//
//	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
//	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
//	t3normal = Task("la la lah", bdtstart3, bdtend3, 2, false, "comment");
//
//	taskList.add(t1float, _temp);
//	taskList.add(t2deadline, _temp);
//	taskList.add(t3normal, _temp);
//
//	taskList.searchStatusInRange(false, bdtstart1, bdtend3, _temp);
//
//	EXPECT_EQ(2, _temp.size());
//
//	taskList.searchStatusInRange(true, bdtstart1, bdtend3, _temp);
//
//	EXPECT_EQ(0, _temp.size());
//}

TEST(TaskListTest, CheckUpdate){

	TaskList taskList;

	vector<Task> _temp;

	Task t1float;
	Task t2deadline;
	Task t3normal;
	Task t4new;
	Task t5new;
	Task t6new;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
	t3normal = Task("la la lah", bdtstart2, bdtend3, 2, false, "comment");
	t4new = Task("burp", bdtstart3, bdtend3, 1, false, "comment");
	t5new = Task("burp burp", bdtstart3, bdtend3, 2, false, "comment");
	t6new = Task("burp burp bureppp", bdtstart3, bdtend3, 0, false, "comment");

	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);

	taskList.update(t1float, t4new, _temp);
	taskList.update(t2deadline, t5new, _temp);

	EXPECT_EQ(1, _temp.size());
	EXPECT_EQ("la la lah", _temp[0].getTitle());

	taskList.update(t3normal, t6new, _temp);
	EXPECT_EQ(0, _temp.size());

	taskList.displayAll(_temp);
	EXPECT_EQ(3, _temp.size());
	EXPECT_EQ("burp burp", _temp[0].getTitle());
	EXPECT_EQ("burp", _temp[1].getTitle());
	EXPECT_EQ("burp burp bureppp", _temp[2].getTitle());
}

TEST(TaskListTest, CheckMark){

	TaskList taskList;

	vector<Task> _temp;

	Task t1float;
	Task t2deadline;
	Task t3normal;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,17);
	BasicDateTime bdtstart3(2013,8,19);

	BasicDateTime bdtend1(2013,8,16);
	BasicDateTime bdtend2(2013,8,18);
	BasicDateTime bdtend3(2013,8,20);

	t1float = Task("hahaha boring...", bdtstart1, bdtend1, 0, false, "comment");
	t2deadline = Task("Try again later", bdtstart2, bdtend2, 1, false, "comment");
	t3normal = Task("la la lah", bdtstart2, bdtend3, 2, false, "comment");

	taskList.add(t1float, _temp);
	taskList.add(t2deadline, _temp);
	taskList.add(t3normal, _temp);

	taskList.mark(true, t1float);
	taskList.mark(true, t2deadline);
	taskList.mark(true, t3normal);

	taskList.displayStatus(false, _temp);
	EXPECT_EQ(0, _temp.size());

	taskList.displayStatus(true, _temp);
	EXPECT_EQ(3, _temp.size());

}

//TEST(TaskListTest, CheckSort){
//
//	TaskList taskList;
//
//	vector<Task> _temp;
//
//	Task t1;
//	Task t2;
//	Task t3;
//
//	BasicDateTime bdtstart1(2013,8,13);
//	BasicDateTime bdtstart2(2013,8,13);
//	BasicDateTime bdtstart3(2013,8,14);
//
//	BasicDateTime bdtend1(2013,8,16);
//	BasicDateTime bdtend2(2013,8,18);
//	BasicDateTime bdtend3(2013,8,20);
//
//	t1 = Task("t1", bdtstart1, bdtend1, 2, false, "comment");
//	t2 = Task("t2", bdtstart2, bdtend2, 2, false, "comment");
//	t3 = Task("t3", bdtstart3, bdtend3, 2, false, "comment");
//
//	taskList.add(t3, _temp);
//	taskList.add(t2, _temp);
//	taskList.add(t1, _temp);
//
//	taskList.sortNormal(_temp);
//
//	EXPECT_EQ("t2", _temp[0].getTitle());
//	EXPECT_EQ("t1", _temp[1].getTitle());
//	EXPECT_EQ("t3", _temp[2].getTitle());
//}

TEST(TaskListTest, CheckEmptySlots){

	TaskList taskList;

	vector<Task> _temp;
	vector<BasicDateTime> _tempTime;

	Task t1;
	Task t2;
	Task t3;

	BasicDateTime bdtstart1(2013,8,13);
	BasicDateTime bdtstart2(2013,8,16);
	BasicDateTime bdtstart3(2013,8,18);

	BasicDateTime bdtend1(2013,8,14);
	BasicDateTime bdtend2(2013,8,19);
	BasicDateTime bdtend3(2013,8,20);

	t1 = Task("t1", bdtstart1, bdtend1, 2, false, "comment");
	t2 = Task("t2", bdtstart2, bdtend2, 2, false, "comment");
	t3 = Task("t3", bdtstart3, bdtend3, 2, false, "comment");

	taskList.add(t3, _temp);
	taskList.add(t2, _temp);
	taskList.add(t1, _temp);

	BasicDateTime rangeStart(2013,8,10);
	BasicDateTime rangeEnd(2013,8,21);

	taskList.searchEmptySlots(rangeStart, rangeEnd, _tempTime);

	BasicDateTime expectStart(2013,8,10);
	BasicDateTime expectEnd(2013,8,13);

	EXPECT_EQ(6, _tempTime.size());

	cout << _tempTime[0].getDateTimeString() << endl;
	cout << _tempTime[1].getDateTimeString() << endl;
	cout << _tempTime[2].getDateTimeString() << endl;
	cout << _tempTime[3].getDateTimeString() << endl;
	cout << _tempTime[4].getDateTimeString() << endl;
	cout << _tempTime[5].getDateTimeString() << endl;

	/*cout << _tempTime[0].getDateTimeString();
	cout << _tempTime.size[1].getDateTimeString();*/

}