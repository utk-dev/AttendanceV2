#ifndef __IOSTREAM__
#define __IOSTREAM__
#include <iostream>
#endif

#ifndef __TYPE__
#define __TYPE__
#include "models/utype.h"
#endif // __TYPE__

#ifndef __USERGUARD__
#define __USERGUARD__
#include "models/user.h"
#endif

#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include <fstream>
#endif

#ifndef __STRINGS__
#define __STRINGS__
#include <string>
#include <string.h>
#endif

#ifndef __UTILS__
#define __UTILS__
#include "controller/utils.h"
#endif

#ifndef __VIEW__
#define __VIEW__
#include "controller/view.h"
#endif

using namespace std;

void addDummyData()
{
    USER stu1(TYPE::STUDENT, "Utkarsh Gupta", "Windows@10");
    ofstream out("models/students.dat", ios::binary | ios::trunc);
    out << stu1;
    out.close();

    // insert second student
    USER stu2(TYPE::STUDENT, "Akash Kumar", "WhistleMistle");
    out.open("models/students.dat", ios::binary | ios::app);
    out << stu2;
    out.close();

    // insert second student
    USER stu5(TYPE::STUDENT, "Ankit Mishra", "WhistleMania");
    out.open("models/students.dat", ios::binary | ios::app);
    out << stu5;
    out.close();

    USER tea1(TYPE::TEACHER, "Amit Bhagat", "Windows@10");
    out.open("models/teachers.dat", ios::binary | ios::trunc);
    out << tea1;
    out.close();

    USER tea2(TYPE::TEACHER, "Sanjay Sharma", "Windows@10");
    out.open("models/teachers.dat", ios::binary | ios::app);
    out << tea2;
    out.close();

    USER mod1(TYPE::MODERATOR, "Raghu Baba", "Windows@10");
    out.open("models/moderators.dat", ios::binary | ios::trunc);
    out << mod1;
    out.close();
}

int main()
{
    //addDummyData();
    bool loggedIn = false;
    while(!loggedIn)
    {
        USER curr;
        int ch1 = showLoginMenu();
        if(ch1 == 1)
        {
            loggedIn = logIn(curr);
            if(loggedIn)
            {
                while(loggedIn)
                {
                    int ch2 = showMainMenu(curr);
                    TYPE t = curr.getUserType();
                    switch(ch2)
                    {
                    case 0:
                        loggedIn = false;
                        break;
                    case 1:
                        if(t != TYPE::TEACHER) cout << "\n## Unauthorised Access ##\n";
                        else takeAttendance(curr);
                        break;
                    case 2:
                        if(t != TYPE::STUDENT) cout << "\n## Unauthorised Access ##\n";
                        else generateIndividualReportPercentage(curr);
                        break;
                    case 3:
                        if(t != TYPE::MODERATOR) cout << "\n## Unauthorised Access ##\n";
                        else
                        {
                            bool s = createUser();
                            if(s) cout << "\nUser Creation Successful!\n";
                            else cout << "\nUser Creation Failed!\n";
                        }
                        break;
                    case 4:
                        if(t != TYPE::MODERATOR && t != TYPE::TEACHER)
                            cout << "\n## Unauthorised Access ##\n";
                        else generateClassReportPercentage(curr);
                        break;
                    case 5:
                        bool y = changePassword(curr);
                        if(y) cout << "\nPassword Change Successful!\n";
                        if(y) cout << "\nPassword Change Failed!\n";
                        break;
                    }
                }
            }
            else
            {
                cout << "\n## Authentication Failed. Try Again. ##\n";
            }
        }
        else if(ch1 == 2)
        {
            cout << "\n## Exiting Program ##\n";
            return 0;
        }
    }
    return 0;
}
