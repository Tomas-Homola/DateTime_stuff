#include <iostream>
#include <string>

class DateTime
{
private:
	int year;
	int month;
	int day;
	int hours;
	int minutes;
	int seconds;
public:
	DateTime();
	DateTime(int year, int month, int day, int hours, int minutes, int seconds);
	DateTime(std::string dateTime, std::string delimiterDate, std::string delimiterDateTime, std::string delimiterTime);

	int getSeconds() { return seconds; }
	int getMinutes() { return minutes; }
	int getHours() { return hours; }
	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }

	void printDateTime();

	DateTime& operator ++(); // ++i najprv zvysi a potom vrati na vypocet
	DateTime& operator --(); // --i
	DateTime operator ++(int); // i++ najprv vrati na vypocet a potom zvysi
	DateTime operator --(int); // i--
	DateTime operator +(int addSeconds);
	DateTime operator -(int subtractSeconds);
	bool operator ==(const DateTime& dateTime); // dateTime == this->dateTime
	bool operator !=(const DateTime& dateTime); // dateTime != this->dateTime
	bool operator >(const DateTime& dateTime);
	bool operator <(const DateTime& dateTime);
	friend std::istream& operator <<(std::istream& input, DateTime& dateTime);
	int operator [](int index);
	int operator -(const DateTime& dateTime);


};

DateTime::DateTime()
{
	this->year = -1;
	this->month = -1;
	this->day = -1;
	this->hours = -1;
	this->minutes = -1;
	this->seconds = -1;
}

DateTime::DateTime(int year, int month, int day, int hours, int minutes, int seconds)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

DateTime::DateTime(std::string dateTime, std::string delimiterDate, std::string delimiterDateTime, std::string delimiterTime)
{
	std::string date;
	std::string time;
	std::string tempString;
	size_t position = 0;
	int temp[2] = { 0,0 };
	int i = 0;

	position = dateTime.find(delimiterDateTime);
	if (position == -1)
	{
		"Zle zadany datum a cas";
		exit(-1);
	}

	date = dateTime.substr(0, position);
	dateTime.erase(0, position + delimiterDateTime.length());
	time = dateTime;

	while (position = date.find(delimiterDate) != std::string::npos)
	{
		tempString = date.substr(0, position + delimiterDate.length());
		date.erase(0, position + 2 * delimiterDate.length());
		temp[i] = std::stoi(tempString);
		i++;
	}

	this->day = temp[0];
	this->month = temp[1];
	this->year = std::stoi(date);

	i = 0;

	while (position = time.find(delimiterTime) != std::string::npos)
	{
		tempString = time.substr(0, position + delimiterTime.length());
		time.erase(0, position + 2 * delimiterTime.length());
		temp[i] = std::stoi(tempString);
		i++;
	}
	
	this->hours = temp[0];
	this->minutes = temp[1];
	this->seconds = std::stoi(time);
}

void DateTime::printDateTime()
{
	std::cout << day << "." << month << "." << year << " " << hours << ":" << minutes << ":" << seconds << std::endl;
}

DateTime& DateTime::operator++() // ++i
{
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	seconds++;

	if (seconds == 60)
	{
		seconds = 0;
		minutes++;

		if (minutes == 60)
		{
			minutes = 0;
			hours++;

			if (hours == 24)
			{
				hours = 0;
				day++;

				if (day == daysInMonth[month - 1] + 1)
				{
					day = 1;
					month++;

					if (month == 13)
					{
						month = 1;
						year++;
					}
				}
			}
		}
	}

	return *this;
}

DateTime& DateTime::operator--()
{
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	seconds--;

	if (seconds == -1)
	{
		seconds = 59;
		minutes--;

		if (minutes == -1)
		{
			minutes = 59;
			hours--;

			if (hours == -1)
			{
				hours = 23;
				day--;

				if (day == 0)
				{
					if (month == 1) // ak by bol mesiac = 1 -> januar, tak sa zmeni den na 31, mesiac na 12 -> decemebr a znizi sa 1 rok
					{
						day = 31;
						month = 12;
						year--;
					}
					else
					{
						day = daysInMonth[month - 2];
						month--;
					}
				}
			}
		}
	}

	return *this;
}

DateTime DateTime::operator++(int)
{
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int oldSeconds = seconds, oldMinutes = minutes, oldHours = hours, oldDay = day, oldMonth = month, oldYear = year;

	seconds++;

	if (seconds == 60)
	{
		seconds = 0;
		minutes++;

		if (minutes == 60)
		{
			minutes = 0;
			hours++;

			if (hours == 24)
			{
				hours = 0;
				day++;

				if (day == daysInMonth[month - 1] + 1)
				{
					day = 1;
					month++;

					if (month == 13)
					{
						month = 1;
						year++;
					}
				}
			}
		}
	}
	
	return DateTime(oldYear, oldMonth, oldDay, oldHours, oldMinutes, oldSeconds);
}

DateTime DateTime::operator--(int)
{
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int oldSeconds = seconds, oldMinutes = minutes, oldHours = hours, oldDay = day, oldMonth = month, oldYear = year;
	
	seconds--;

	if (seconds == -1)
	{
		seconds = 59;
		minutes--;

		if (minutes == -1)
		{
			minutes = 59;
			hours--;

			if (hours == -1)
			{
				hours = 23;
				day--;

				if (day == 0)
				{
					if (month == 1) // ak by bol mesiac = 1 -> januar, tak sa zmeni den na 31, mesiac na 12 -> decemebr a znizi sa 1 rok
					{
						day = 31;
						month = 12;
						year--;
					}
					else
					{
						day = daysInMonth[month - 2];
						month--;
					}
				}
			}
		}
	}
	
	return DateTime(oldYear, oldMonth, oldDay, oldHours, oldMinutes, oldSeconds);
}

DateTime DateTime::operator+(int addSeconds)
{
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	seconds += addSeconds;

	if (seconds >= 60)
	{
		minutes += seconds / 60;
		seconds = seconds % 60;

		if (minutes >= 60)
		{
			hours += minutes / 60;
			minutes = minutes % 60;

			if (hours >= 24)
			{
				day += hours / 24;
				hours = hours % 24;

				if (day > daysInMonth[month - 1])
				{
					while (day / daysInMonth[month - 1] != 0)
					{
						day -= daysInMonth[month - 1];
						month++;

						if (month > 12)
						{
							month = 1;
							year++;
						}
					}
				}
			}
		}
	}
	
	return DateTime();
}

DateTime DateTime::operator-(int subtractSeconds)
{
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	seconds -= subtractSeconds; // < sec -> v pohode, == sec -> v pohode, > sec -> odcitavame z minut
	//12:45:43 - 647 sec
	if (seconds < 0)
	{
		minutes -= subtractSeconds / 60;
		seconds = 60 + (seconds * 60);

		if (minutes < 0)
		{
			hours += minutes / 60;
			minutes = 60 + (minutes % 60);
		}
	}
	
	
	
	return DateTime();
}

bool DateTime::operator==(const DateTime& dateTime)
{
	return false;
}

bool DateTime::operator!=(const DateTime& dateTime)
{
	return false;
}

bool DateTime::operator>(const DateTime& dateTime)
{
	return false;
}

bool DateTime::operator<(const DateTime& dateTime)
{
	return false;
}

int DateTime::operator[](int index)
{
	return 0;
}

int DateTime::operator-(const DateTime& dateTime)
{
	return 0;
}

int main()
{
	DateTime datum1(2020, 10, 24, 14, 55, 23);
	datum1.printDateTime();

	DateTime datum2("24.10.2020 14:55:23", ".", " ", ":");
	datum2.printDateTime();



	return 0;
}

std::istream& operator<<(std::istream& input, DateTime& dateTime)
{
	// TODO: insert return statement here
}
