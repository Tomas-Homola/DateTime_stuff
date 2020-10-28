#include <iostream>
#include <iomanip>
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

	void addDay() { day += 1; }

	void printDateTime();

	DateTime& operator ++(); // ++i najprv zvysi a potom vrati na vypocet
	DateTime& operator --(); // --i
	DateTime operator ++(int); // i++ najprv vrati na vypocet a potom zvysi
	DateTime operator --(int); // i--
	DateTime operator +(int addSeconds); // + "n" sekund
	DateTime operator -(int subtractSeconds); // - "n" sekund
	bool operator ==(const DateTime& dateTime); // dateTime == this->dateTime
	bool operator !=(const DateTime& dateTime); // dateTime != this->dateTime
	bool operator >(const DateTime& dateTime);
	bool operator <(const DateTime& dateTime);
	friend std::ostream& operator <<(std::ostream& output, const DateTime& dateTime);
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
	std::cout << std::setfill('0') << std::setw(2) << day << "." << std::setfill('0') << std::setw(2) << month << "." << year << " " << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds << std::endl;
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

	return DateTime(year, month, day, hours, minutes, seconds);
}

DateTime DateTime::operator-(int subtractSeconds)
{
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	seconds -= subtractSeconds; // < sec -> v pohode, == sec -> v pohode, > sec -> odcitavame z minut
	if (seconds < 0)
	{
		minutes += subtractSeconds / 60; // pripocitavane "zaporne" sekundy, cize odpocitavame
		seconds = 60 + (seconds % 60);

		if (minutes < 0)
		{
			hours += minutes / 60;
			minutes = 60 + (minutes % 60);

			if (hours < 0)
			{
				day += hours / 24;
				hours = 24 + (hours % 24);

				if (day < 1)
				{
					do // toto este dorobit
					{
						if (month == 1)
						{
							day += daysInMonth[11];
							month = 12;
							year--;
						}
						else
						{
							day += daysInMonth[month - 2];
							month--;
						}

					} while (day / daysInMonth[month - 1] != 0);
				}

			}
		}
	}

	return DateTime(year, month, day, hours, minutes, seconds);
}

bool DateTime::operator==(const DateTime& dateTime)
{
	if (year == dateTime.year && month == dateTime.month && day == dateTime.day && hours == dateTime.hours && minutes == dateTime.minutes && seconds == dateTime.seconds)
		return true;
	else
		return false;
}

bool DateTime::operator!=(const DateTime& dateTime)
{
	if (year == dateTime.year && month == dateTime.month && day == dateTime.day && hours == dateTime.hours && minutes == dateTime.minutes && seconds == dateTime.seconds)
		return false;
	else
		return true;
}

bool DateTime::operator>(const DateTime& dateTime)
{
	if (year > dateTime.year)
	{
		return true;
	}
	else if (year < dateTime.year)
	{
		return false;
	}
	else
	{
		if (month > dateTime.month)
		{
			return true;
		}
		else if (month < dateTime.month)
		{
			return false;
		}
		else
		{
			if (day > dateTime.day)
			{
				return true;
			}
			else if (day < dateTime.day)
			{
				return false;
			}
			else
			{
				if (hours > dateTime.hours)
				{
					return true;
				}
				else if (hours < dateTime.hours)
				{
					return false;
				}
				else
				{
					if (minutes > dateTime.minutes)
					{
						return true;
					}
					else if (minutes < dateTime.minutes)
					{
						return false;
					}
					else
					{
						if (seconds > dateTime.seconds)
						{
							return true;
						}
						else if (seconds < dateTime.seconds)
						{
							return false;
						}
						else if (seconds == dateTime.seconds)
						{
							return false;
						}
					}
				}
			}
		}
	}
}

bool DateTime::operator<(const DateTime& dateTime)
{
	if (year > dateTime.year)
	{
		return false;
	}
	else if (year < dateTime.year)
	{
		return true;
	}
	else
	{
		if (month > dateTime.month)
		{
			return false;
		}
		else if (month < dateTime.month)
		{
			return true;
		}
		else
		{
			if (day > dateTime.day)
			{
				return false;
			}
			else if (day < dateTime.day)
			{
				return true;
			}
			else
			{
				if (hours > dateTime.hours)
				{
					return false;
				}
				else if (hours < dateTime.hours)
				{
					return true;
				}
				else
				{
					if (minutes > dateTime.minutes)
					{
						return false;
					}
					else if (minutes < dateTime.minutes)
					{
						return true;
					}
					else
					{
						if (seconds > dateTime.seconds)
						{
							return false;
						}
						else if (seconds < dateTime.seconds)
						{
							return true;
						}
						else if (seconds == dateTime.seconds)
						{
							return false;
						}
					}
				}
			}
		}
	}
}

int DateTime::operator[](int index)
{
	if (index == 0)
		return seconds;
	else if (index == 1)
		return minutes;
	else if (index == 2)
		return hours;
	else if (index == 3)
		return day;
	else if (index == 4)
		return month;
	else if (index == 5)
		return year;
	else
		return -1; // ked sa zada chybny index, vrati -1
}

int DateTime::operator-(const DateTime& dateTime)
{
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int diffSeconds = 3, diffYears = 0, diffMonths = 0, diffDays = 0;
	DateTime tempDT(dateTime.year, dateTime.month, dateTime.day, dateTime.hours, dateTime.minutes, dateTime.seconds); // kind of kopia toho, co je ako referencia v argumente funkcie, aby sa dali menit hodnoty, kedze argument je ako const

	if (*this == tempDT)
		return 0;

	if (year > tempDT.year)
	{	
		year++;

		diffYears = year - tempDT.year;
		diffMonths = month - tempDT.month;

		if (diffMonths < 0)
			diffYears--;

		diffDays += (daysInMonth[tempDT.month - 1] - tempDT.day);
		tempDT.month++;
		if (tempDT.month == 13) // zmena mesiaca na januar
			tempDT.month = 1;

		while (month != tempDT.month)
		{
			diffDays += daysInMonth[tempDT.month - 1];
			tempDT.month++;
		};

		diffDays += day;

	}
	else if (year < dateTime.year)
	{
		
	}
	else if (year == dateTime.year)
	{

	}



	return diffSeconds;
}

std::ostream& operator<<(std::ostream& output, const DateTime& dateTime)
{
	output << std::setfill('0') << std::setw(2) << dateTime.day << "." << std::setfill('0') << std::setw(2) << dateTime.month << "." << dateTime.year << " " << std::setfill('0') << std::setw(2) << dateTime.hours << ":" << std::setfill('0') << std::setw(2) << dateTime.minutes << ":" << std::setfill('0') << std::setw(2) << dateTime.seconds << std::endl;
	
	return output;
}

int main()
{
	DateTime d1(2020, 10, 27, 20, 52, 23);
	DateTime d2(2020, 10, 27, 20, 52, 23);

	std::cout << "Rozdiel d1 - d2 (d1 > d2): " << d1 - d2 << std::endl;

	std::cout << "Rozdiel d2 - d1 (d1 > d2): " << d2 - d1 << std::endl;

	return 0;
}


