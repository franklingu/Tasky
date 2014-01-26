//@author A0099016B
#include "FileProcessing.h"


int FileProcessing::load(vector<string>& data){
	try{
		ifstream input(_LOGNAME);
		if(!input.is_open()) 
			return STATUS_CODE_SET_ERROR::ERROR_LOAD_OPENFILE;
		if (!input.good()){
			LogLibrary::Log::writeLog(LogLibrary::STATUS_CODE_SET_LOG::LOG_ERROR, "Error in opening file","FileProcessingLog");
			return STATUS_CODE_SET_ERROR::ERROR_LOAD_OPENFILE;
		}
		if (emptyFile()){
			input.close();
			LogLibrary::Log::writeLog(LogLibrary::STATUS_CODE_SET_LOG::LOG_WARNING,"Empty file","FileProcessingLog");
			return STATUS_CODE_SET_WARNING::WARNING_LOAD_EMPTY_FILE;	
		}
		readLines(input,data);
		input.close();
		if (data.size() % TASKLINES != 0) {
			LogLibrary::Log::writeLog(LogLibrary::STATUS_CODE_SET_LOG::LOG_ERROR, "Corrupted data while loading file","FileProcessingLog");
			return STATUS_CODE_SET_ERROR::ERROR_LOAD_CORRUPTED_DATA;
		}
		return STATUS_CODE_SET_SUCCESS::SUCCESS_LOAD;
	}catch(exception e) {
		LogLibrary::Log::writeLog(LogLibrary::STATUS_CODE_SET_LOG::LOG_ERROR,"Error in opening file","FileProcessingLog");
		return STATUS_CODE_SET_ERROR::ERROR_LOAD_OPENFILE;
	}
}

void FileProcessing::readLines(ifstream& input, vector<string>& data){
	data.clear();
	while(input) {
		string line;
		getline(input, line);
		if (line != "\n" && line != ""){
			data.push_back(line);
		}
	}
}


int FileProcessing::save(vector<string>& data){
	try{
		ofstream output(_LOGNAME);
		if (!output.is_open()) {
			output.clear();
			output.open(_LOGNAME, ofstream::out|ofstream::trunc);
		}
		if (!output.good()){
			output.close();
			LogLibrary::Log::writeLog(LogLibrary::STATUS_CODE_SET_LOG::LOG_ERROR,"Error in saving file","FileProcessingLog");
			return STATUS_CODE_SET_ERROR::ERROR_SAVE_SAVEFILE;
		}
		writeLines(output,data);

		output.close();
		return STATUS_CODE_SET_SUCCESS::SUCCESS_SAVE;
	}catch(exception e){
		LogLibrary::Log::writeLog(LogLibrary::STATUS_CODE_SET_LOG::LOG_ERROR,"Error in saving file","FileProcessingLog");
		return STATUS_CODE_SET_ERROR::ERROR_SAVE_SAVEFILE;
	}
}

void FileProcessing::writeLines(ofstream& output, vector<string>& data){
	int countLine = 0;
	for(string s:data) {
		output << s << endl;
		countLine++;
		if (countLine >= TASKLINES){
			output << endl;
			countLine = 0;
		}
	}
}


bool FileProcessing::emptyFile() {
	bool isEmpty = false;
	ifstream inf;
	inf.open(_LOGNAME);
	if(inf.peek() == ifstream::traits_type::eof())
		isEmpty = true;
	inf.close();
	return isEmpty;
}
