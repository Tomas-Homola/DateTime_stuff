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
	DateTime(int year, int month, int day, int hours, int minutes, int seconds);
	DateTime(std::string dateTime, std::string delimiterDate, std::string delimiterDateTime, std::string delimiterTime);

	void printDateTime();

};

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

	//std::cout << date << "///" << std::endl;
	//std::cout << time << "///" << std::endl;

	while (position = date.find(delimiterDate) != -1)
	{
		//std::cout << "Najdene na: " << position << std::endl;
		tempString = date.substr(0, position + 1);
		date.erase(0, position + 2);
		//std::cout << tempString << "///" << std::endl;
		temp[i] = std::stoi(tempString);
		i++;
	}

	this->day = temp[0];
	this->month = temp[1];
	this->year = std::stoi(date);

	i = 0;

	while (position = time.find(delimiterTime) != -1)
	{
		//std::cout << "Najdene na: " << position << std::endl;
		tempString = time.substr(0, position + 1);
		time.erase(0, position + 2);
		//std::cout << tempString << "///" << std::endl;
		temp[i] = std::stoi(tempString, nullptr);
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

int main()
{
	//DateTime datum1(2020, 10, 24, 14, 55, 23);
	//datum1.printDateTime();
	
	std::string test = "0123456";

	/*std::cout << test.substr(0, test.find("3")) << std::endl;
	test.erase(0, test.find("3") + 1);
	std::cout << test << std::endl;*/

	DateTime datum2("24.10.2020 14:55:23", ".", " ", ":");
	datum2.printDateTime();



	return 0;
}
