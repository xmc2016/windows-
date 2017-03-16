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
	// �����������
	Date operator +(int day);
	Date& operator += (int day);
	Date operator-(int day);
	//Date& operator-=(int day);
	Date& operator++();//ǰ��++
	Date operator++(int);//����++
	Date& operator--();
	Date operator--(int);
	int operator-(const Date& d); //������������֮�����������
	void Print();
private:
	bool IsLeap(int year);//�ж�����
	int DayofMonth(int& year, int &month);//���㵱�µ�����
	void GetRightDate(int day);//�������ȷ������  
	int MonthOfoneDay(int year, int month);
	void PrintCalendar(int year, int month);//��ӡ����
private:
	int _year;
	int _month;
	int _day;
};
void PrintCalendar(int year ,int month);//��ӡ����