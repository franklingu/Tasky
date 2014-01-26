#ifndef _BASICDATETIME_H_
#define _BASICDATETIME_H_

#include <iostream>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "Essential.h"

using namespace System;
using namespace msclr::interop;

///wrap date and time into a simple class

class BasicDateTime
{
private:
	int _year;
	int _month;
	int _day;
	int _hour;
	int _minute;
	int _sec;

public:	
	///default constructor
	BasicDateTime();
	///year, month, day
	BasicDateTime(int year, int month, int day);
	///year, month, day, hour, minute
	BasicDateTime(int year, int month, int day, int hour, int minute);
	///year, month, day, hour, minute, sec
	BasicDateTime(int, int, int, int, int, int);
	///destructor
	~BasicDateTime();
	///setter 1
	void setDateTime(int year, int month, int day);
	///setter 2
	void setDateTime(int year, int month, int day, int hour, int minute);
	///setter 3
	void setDateTime(int year, int month, int day, int hour, int minute, int sec);
	///getter for year
	int getYear();
	///setter for year
	void setYear(int year);
	///getter for month
	int getMonth();
	///setter for month
	void setMonth(int month);
	///getter for day
	int getDay();
	///setter for day
	void setDay(int day);
	///getter for hour
	int getHour();
	///setter for hour
	void setHour(int hour);
	///getter for minute
	int getMinute();
	///setter for minute
	void setMinute(int minute);
	///getter for sec
	int getSec();
	///setter for sec
	void setSec(int sec);
	///translate the datetime into string
	string getDateTimeString();
	///compare to another BasicDateTime object
	int compareTo(BasicDateTime another);
};

#endif
