//@author A0099016B
#include "testFileProcessing.h"

void testFileProcessing::testFileProcessingClass(){
	normalTestCase();
	lessDataTestCase();
	moreDataTestCase();
}

/*normal test case, expected to return all correct values*/
void testFileProcessing::normalTestCase(){
	vector<string> testData;
	testData.push_back("data line 1");
	testData.push_back("data line 2");
	testData.push_back("data line 3");
	testData.push_back("data line 4");
	testData.push_back("data line 5");
	testData.push_back("data line 6");

	testData.push_back("data line 7");
	testData.push_back("data line 8");
	testData.push_back("data line 9");
	testData.push_back("data line 10");
	testData.push_back("data line 11");
	testData.push_back("data line 12");


	FileProcessing fP;
	int result;

	result = fP.save(testData);
	if (result != SUCCESS_SAVE) {
		cout << result;
		cout << "Not a successful save" << endl;
	}

	vector<string> output;
	result = fP.load(output);
	if (result != SUCCESS_LOAD && result != WARNING_LOAD_EMPTY_FILE){
		cout << result;
		cout << "Not a successful load"<< endl;
	}

	int count = 0;
	for(string str:output){
		cout << str << endl;
		count++;
		if (count == 6) {
			cout<<endl;
			count = 0;
		}
	}
}

/*boundary case for more data lines not in multiple of 6*/
void testFileProcessing::moreDataTestCase(){
	vector<string> testData;
	
	testData.push_back("data line 1");
	testData.push_back("data line 2");
	testData.push_back("data line 3");
	testData.push_back("data line 4");
	testData.push_back("data line 5");
	testData.push_back("data line 6");

	testData.push_back("data line 7");

	FileProcessing fP;
	int result;

	result = fP.save(testData);
	if (result != SUCCESS_SAVE) {
		cout << result;
		cout << "Not a successful save" << endl;
	}

	vector<string> output;
	result = fP.load(output);
	if (result != SUCCESS_LOAD && result != WARNING_LOAD_EMPTY_FILE){
		cout << result;
		cout << "Not a successful load"<< endl;
	}
}

/*boundary case for less data lines not in multiple of 6*/
void testFileProcessing::lessDataTestCase(){
	vector<string> testData;
	
	testData.push_back("data line 1");
	testData.push_back("data line 2");
	testData.push_back("data line 3");
	testData.push_back("data line 4");
	testData.push_back("data line 5");

	FileProcessing fP;
	int result;

	result = fP.save(testData);
	if (result != SUCCESS_SAVE) {
		cout << result;
		cout << "Not a successful save" << endl;
	}

	vector<string> output;
	result = fP.load(output);
	if (result != SUCCESS_LOAD && result != WARNING_LOAD_EMPTY_FILE){
		cout << result;
		cout << "Not a successful load"<< endl;
	}
}
