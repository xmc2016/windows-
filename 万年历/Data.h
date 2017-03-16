#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
class Date
{
public:
	Date(int year = 1600, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		
		return *this;
	}
	~Date()
	{

	}

public:
	bool operator == (const Date& d);
	bool operator<(const Date& d);
	bool operator>(const Date& d);
	bool operator>=(const Date& d);
	bool operator<=(const Date& d);
	// 日期类计算器
	Date operator +(int day);
	Date& operator += (int day);
	Date operator-(int day);
	//Date& operator-=(int day);
	Date& operator++();//前置++
	Date operator++(int);//后置++
	Date& operator--();
	Date operator--(int);
	int operator-(const Date& d); //计算两个日期之间相隔的天数
	void Print();
private:
	bool IsLeap(int year);//判断闰年
	int DayofMonth(int& year, int &month);//计算当月的天数
	void GetRightDate(int day);//计算出正确的日期  
	int MonthOfoneDay(int year, int month);
	void PrintCalendar(int year, int month);//打印日历
private:
	int _year;
	int _month;
	int _day;
};
void PrintCalendar(int year ,int month);//打印日历