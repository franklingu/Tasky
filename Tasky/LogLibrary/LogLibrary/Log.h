
#include <string>
#include <fstream>
#include <vector>

namespace LogLibrary{	

	enum STATUS_CODE_SET_LOG{
		LOG_INFO,
		LOG_DEBUG,
		LOG_WARNING,
		LOG_ERROR
	};

	class Log {
	private :
		static bool emptyFile(std::string logName);
	public:
		/**
		* Purpose: writes a log 
		*
		* @param type to be logged down(see STATUS_CODE_SET_LOG)
		* @param data the things to be logged down
		* @param logName the name you want your file to be
		*/
		static void writeLog(int logType, std::string data, std::string logName);

	};
}