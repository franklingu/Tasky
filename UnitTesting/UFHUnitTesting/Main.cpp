//@author A0099016B
#include "UI.h"
#include "testHistory.h"
#include "testFileProcessing.h"

int main()
{
	testHistory testHist;
	testHist.testHistoryClass();

	testFileProcessing testFP;
	testFP.testFileProcessingClass();

	UI uiTest;
	uiTest.UI_interface();
	system("pause");

	return 0;
}


