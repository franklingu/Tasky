//@author A0099016B
#include "testHistory.h"

void testHistory::testHistoryClass(){

	History hT;
	//--------DEFAULT-----------------
	BasicDateTime DoldBDTStart(0,0,0);
	BasicDateTime DoldBDTEnd(0,0,0);
	Task DoldTask("DoldTask1",DoldBDTStart,DoldBDTEnd,2,false,"");

	BasicDateTime DnewBDTStart(0,0,0);
	BasicDateTime DnewBDTEnd(0,0,0);
	Task DnewTask("DnewTask1",DnewBDTStart,DnewBDTEnd,2,false,"");

	HistoryCommand DhCommand(COMMAND_TYPES::ADD,DoldTask,DnewTask);

	//---------END OF DEFAULT----------

	cout<< DhCommand.getOld().getTitle() <<endl;
	cout<< DhCommand.getNew().getTitle() <<endl;
	cout<< endl;


	BasicDateTime oldBDTStart(2012,10,10);
	BasicDateTime oldBDTEnd(2012,11,11);
	Task oldTask("oldTask1",oldBDTStart,oldBDTEnd,2,false,"");

	BasicDateTime newBDTStart(2013,10,10);
	BasicDateTime newBDTEnd(2013,12,12);
	Task newTask("newTask1",newBDTStart,newBDTEnd,2,false,"");

	HistoryCommand hCommand(COMMAND_TYPES::ADD,oldTask,newTask);

	BasicDateTime oldBDTStart2(2012,10,10);
	BasicDateTime oldBDTEnd2(2012,11,11);
	Task oldTask2("oldTask2",oldBDTStart2,oldBDTEnd2,2,false,"");

	BasicDateTime newBDTStart2(2013,10,10);
	BasicDateTime newBDTEnd2(2013,12,12);
	Task newTask2("newTask2",newBDTStart2,newBDTEnd2,2,false,"");

	HistoryCommand hCommand2(COMMAND_TYPES::ADD,oldTask2,newTask2);


	hT.record(hCommand);
	hT.record(hCommand2);
	hT.undo(DhCommand);
	//hT.redo(DhCommand);
	hT.undo(DhCommand);
	
	cout<< DhCommand.getOld().getTitle() <<endl;
	cout<< DhCommand.getNew().getTitle() <<endl;
	
}