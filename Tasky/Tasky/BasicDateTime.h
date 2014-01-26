#ifndef BASICDATETIME_H
#define BASICDATETIME_H

#include <iostream>
#include <string>
#include <ctime>
#include "Essential.h"

//@author A0099016B
/**
* Tasky's version of storing date and time 
* 1. able to set based on date, month, year ,  hour , min , sec
* 2. able to compare to another BasicDateTime object based on contained DateTime object
* 3. format the date and time to be inclusive of 0s
*/

class BasicDateTime
{
private:
	int _year;
	int _month;
	int _day;
	int _hour;
	int _minute;
	int _sec;

private:
	static const string DASH;
	static const string SPACE;
	static const string COLON;
	static const string ZERO_STRING;
	static const int ZERO=0;

public:
	BasicDateTime();
	BasicDateTime(int year, int month, int day);
	BasicDateTime(int year, int month, int day, int hour, int minute);
	BasicDateTime(int year,int month,int day,int hour,int minute,int sec);
	~BasicDateTime();
	void setDateTime(int year, int month, int day);
	void setDateTime(int year, int month, int day, int hour, int minute);
	void setDateTime(int year, int month, int day, int hour, int minute, int sec);
	void setYear(int year);	
	void setMonth(int month);	
	void setDay(int day);	
	void setHour(int hour);	
	void setMinute(int minute);	
	void setSec(int sec);
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	int getSec();
	string getDateTimeString();
	/**
	 * compare to another BasicDateTime object based on internal DateTime object comparison
	 * @param another BasicDateTime Object to be compared to
	 * @return value of comparision(compareTo)
	 */
	int compareTo(BasicDateTime another);

private:
	string addZeroFromFront(string str);
	string dayOfWeek();
	string mapDayOfWeekToString(int dayOfWeek);
};

#endif
