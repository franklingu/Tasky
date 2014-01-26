#include "BasicDateTime.h"

BasicDateTime::BasicDateTime(){
	_year=0;
	_month=0;
	_day=0;
	_hour=0;
	_minute=0;
	_sec=0;
}

BasicDateTime::~BasicDateTime(){
}

BasicDateTime::BasicDateTime(int year, int month, int day){
	_year=year;
	_month=month;
	_day=day;
	_hour=23;
	_minute=59;
	_sec=59;
}

BasicDateTime::BasicDateTime(int year, int month, int day, int hour, int minute){
	_year = year;
	_month = month;
	_day = day;
	_hour = hour;
	_minute = minute;
	_sec=0;
}

BasicDateTime::BasicDateTime(int year, int month, int day, int hour, int minute, int sec){
	_year = year;
	_month = month;
	_day = day;
	_hour = hour;
	_minute = minute;
	_sec=sec;
}

void BasicDateTime::setDateTime(int year, int month, int day){
	_year = year;
	_month = month;
	_day = day;
	_hour = 23;
	_minute = 59;
	_sec=59;
}

void BasicDateTime::setDateTime(int year, int month, int day, int hour, int minute){
	_year = year;
	_month = month;
	_day = day;
	_hour = hour;
	_minute = minute;
	_sec=0;
}

void BasicDateTime::setDateTime(int year, int month, int day, int hour, int minute, int sec){
	_year = year;
	_month = month;
	_day = day;
	_hour = hour;
	_minute = minute;
	_sec=sec;
}

int BasicDateTime::getYear(){ 
	return _year;
}

void BasicDateTime::setYear(int year){
	_year=year;
}

int BasicDateTime::getMonth(){ 
	return _month;
}

void BasicDateTime::setMonth(int month){
	_month=month;
}

int BasicDateTime::getDay(){
	return _day;
}

void BasicDateTime::setDay(int day){
	_day=day;
}

int BasicDateTime::getHour(){ 
	return _hour;
}

void BasicDateTime::setHour(int hour){
	_hour=hour;
}

int BasicDateTime::getMinute(){
	return _minute;
}

void BasicDateTime::setMinute(int minute){
	_minute=minute;
}

int BasicDateTime::getSec(){
	return _sec;
}

void BasicDateTime::setSec(int sec){
	_sec=sec;
}

string BasicDateTime::getDateTimeString(){
	DateTime temp = DateTime(_year, _month, _day,  _hour, _minute, _sec);
	return marshal_as<std::string>(temp.ToString()); 
}

int BasicDateTime::compareTo(BasicDateTime another){
	DateTime temp = DateTime(another.getYear(),	another.getMonth(),	another.getDay(),
							another.getHour(), another.getMinute(),another.getSec());
	DateTime thisDateTime = DateTime( _year, _month, _day, _hour, _minute, _sec);
	return thisDateTime.CompareTo(temp);
}
