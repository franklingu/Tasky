#include "UI.h"


void UI::UI_interface(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	string command;
	bool statusFlag = false;
	while (!statusFlag) {
		displayCommandMessage(command, hConsole);
		displayProcessorMessage(command, hConsole, statusFlag);
	}
	system("pause");
}


void UI::displayWelcomeMessage(HANDLE hConsole){
	cout << MESSAGE_WELCOME <<endl;
	bool alwaysFalse = false;
	displayProcessorMessage(COMMAND_DISPLAY_TASK_PENDING,hConsole,alwaysFalse);
}


void UI::displayCommandMessage(string& command, HANDLE hConsole){
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE |FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << MESSAGE_COMMAND;
	getline(cin, command);
}


void UI::displayProcessorMessage(string command, HANDLE hConsole, bool& statusFlag){
	string message;
	vector<string> feedback;
	int output = _processor.UImainProcessor(command, message, feedback);
	switch(output){
	case STATUS_CODE_SET_OVERALL::OVERALL_ERROR:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case STATUS_CODE_SET_OVERALL::OVERALL_SUCCESS:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case STATUS_CODE_SET_OVERALL::OVERALL_WARNING:
	case STATUS_CODE_SET_OVERALL::OVERALL_PROMPT:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN |FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case STATUS_CODE_SET_OVERALL::OVERALL_EXIT:
		statusFlag = true;
		break;
	}

	assert(!message.empty());
	cout << endl;
	cout << message << endl;

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE |FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	for (string str:feedback){
		cout << str << endl;
		cout << endl;
	}
	cout << endl;


}

