#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include <fstream>
#endif // __FILEHANDLER__

struct Date{
    int day,month,year;
};

class Day{
    private:
        Date today;
        bool setToday();
    public:
        char attendance[200];
        Day();
        Date getToday();
};

std::ifstream& operator>>(std::ifstream&, Day&);
std::ofstream& operator<<(std::ofstream&, const Day&);

