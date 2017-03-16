#define _CRT_SECURE_NO_WARNINGS 1
#include"Data.h"
void Date::GetRightDate(int day)//计算出正确的日期  
{
	if (day > 0)
	{
		while (day > DayofMonth(_year, _month))
		{
			day -= DayofMonth(_year, _month);
			_month++;
			if (_month > 12)
			{
				_year++;
				_month=1;
			}
		}

		if (day > DayofMonth(_year, _month) -_day)
		{
			day =day-( DayofMonth(_year, _month) - _day);
			_month++;
			if (_month > 12)
			{
				_year++;
				_month = 1;
			}
			_day = 0; 
		}

	   if (day <= DayofMonth(_year, _month) - _day)
		{
			_day += day;
			day = 0;
		}
	}
	else if (day < 0)
	{
		while (day < -(DayofMonth(_year, _month)))
		{
			day =  day+DayofMonth(_year, _month);
			_month--;
			if (_month < 1)
			{
				_year--;
				_month = 12;
			}
		}

		if (day < -_day)
		{
			day += _day;
			_month--;
			if (_month < 1)
			{
				_year--;
				_month = 12;
			}
			_day = DayofMonth(_year,_month);
		}
		if (day>=- _day )
		{
			_day += day;
			day = 0;
		}
	}

}
bool  Date:: operator == (const Date& d)
{
	return (this->_year == d._year)
		&&(this->_month = d._month)
		&&  (this->_day = d._day);
}
bool  Date::operator>(const Date& d)
{
	if (this->_year>d._year)
	{
		return true;
	}
	else if (this->_year==d._year&&this->_month>d._month)
	{
		return true;
	}
	else if ((this->_year == d._year)&&(this->_month = d._month)&&(this->_day > d._day))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Date::operator<(const Date& d)
{
	if (_year < d._year)
	{
		return true;
	}
	else if (_year == d._year&&_month < d._month)
	{
		return true;
	}
	else if (_year == d._day&&_month == d._month&&_day < d._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Date::operator>=(const Date& d)
{
	return operator>(d) || operator==(d);
}

bool Date::operator<=(const Date& d)
{
	return operator<(d) || operator==(d);
}

// 日期类计算器
Date Date::operator +(int day) //日期加天数
{
	GetRightDate( day);
	return *this;
}
Date& Date::operator += (int day)
{
	GetRightDate(day);
	return *this;
}
Date Date::operator-(int day)
{
	GetRightDate(-day);
	return *this;

}
//Date&  Date:: operator-=(int day)
//{
//
//}
Date& Date::operator++()//前置++
{
	_day++;
	if (_day > DayofMonth(_year, _month))
	{
		_month++;
		if (_month > 12)
		{
			_year++;
			_month = 1;
			_day = 1;
		}
	}
	return *this;
}
Date  Date::operator++(int)//后置++
{
	 Date tmp( *this);
	 _day++;
	 if (_day > DayofMonth(_year, _month))
	 {
		 _month++;
		 if (_month > 12)
		 {
			 _year++;
			 _month = 1;
			 _day = 1;
		 }
	 }
	 return  tmp;
}
Date&  Date::operator--()
{
	_day--;
	if (_day == 0)
	{
		_month--;
		if (_month == 0)
		{
			_year--;
			_month = 12;
			_day = 31;
		}
	}
	return *this;
    
}
Date Date::operator--(int)
{
	Date tmp(*this);
	_day--;
	if (_day == 0)
	{
		_month--;
		if (_month == 0)
		{
			_year--;
			_month = 12;
			_day = 31;
		}
	}
	return tmp;
}
int  Date::operator-(const Date& d) //计算两个日期之间相隔的天数
{
	int day =0;
	Date small = d;
	Date big(*this);
	if (*this < d)
	{
		small = *this;
		big = d;
	} 
	while (small._year < big._year)
	{
		if (IsLeap(small._year))
		{
			day += 366;
		}
		else
		{
			day += 365;
		}
		small._year++;
	}

	while(small._month > big._month)
	{
		small._month--;
		day -= DayofMonth(small._year, small._month);
	}
	while (small._month < big._month)	
	{
		day += DayofMonth(small._year, small._month);
		small._month++;
		
	}
	if(small._day<big._day)
	{
		day +=big._day-small._day;
	}
	else
	{
		day -= small._day - big._day;
	}
	return day;
}

bool  Date::IsLeap(int year)//判断闰年
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int  Date::DayofMonth(int& year,int &month)//计算当月的天数
{
	int days[13] = {0, 31 ,28,31,30,31,30,31,31,30,31,30,31};
	if (IsLeap(year))
	{
		days[2] = 29;
	}
	return days[month];
}

int Date::MonthOfoneDay(int year, int month) //计算当月第一天为星期几
{
	if (year >= 1600 && month >= 1)
	{
		int week = 6; //1600.1.1为星期六
		int day = 0;
		Date d1(1600, 1, 1);
		Date d2(year, month, 1);
		day = d2 - d1;
		week = day % 7 + week;
		if (week >= 7)
		{
			week -= 7;
		}
		return week;
	}
}
void Date::PrintCalendar(int year, int month)//打印日历
{
	printf("%d年%d月\n", year, month);
	printf("日 一 二 三 四 五  六\n");
	int week = MonthOfoneDay(year, month);
	Date d(year, month, 1);
	int day = 1;
	int i = 0;
	for (i = 0; i < week; i++)
	{
		printf("   ");
	}
	for (int j = 0; j< 6; j++)
	{
		for (; i < 7; i++)
		{
			if (day <= DayofMonth(year, month))
			{
				printf("%2d ", day);
				day++;
			}
			else
			{
				break;
			}
		}
		i = 0;
		printf("\n");
		

	}
	printf("\n");

}


void Date::Print()
{
	printf("%d:%d:%d\n", _year, _month, _day);
	PrintCalendar(_year, _month);
}