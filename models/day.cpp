#ifndef __TIME__
#define __TIME__
#include <ctime>
#endif // __TIME__

#ifndef __IOSTREAM__
#define __IOSTREAM__
#include <iostream>
#endif // __IOSTREAM__

#ifndef __DAY__
#define __DAY__
#include "day.h"
#endif // __DAY__


bool Day::setToday()
{
    time_t curr = time(nullptr);    // get current time as an integer
    tm *t = localtime(&curr);       // convert curr into a readable structure
    today.day = t->tm_mday;
    today.month = t->tm_mon;
    today.year = t->tm_year;
    //for checking whether current date is present or not...
    return true;
}

Day::Day()
{
    setToday();
}

Date Day::getToday()
{
    return today;
}

std::ifstream& operator>>(std::ifstream& f, Day& d)
{
    f.read((char *)&d, sizeof(Day));
    return f;
}

std::ofstream& operator<<(std::ofstream& f, const Day &d)
{
    f.write((char *)&d, sizeof(Day));
    return f;
}
