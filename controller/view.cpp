#ifndef __USERGUARD__
#define __USERGUARD__
#include "../models/user.h"
#endif

#ifndef __IOSTREAM__
#define __IOSTREAM__
#include <iostream>
#endif // __IOSTREAM__


#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include <fstream>
#endif

#ifndef __STRINGS__
#define __STRINGS__
#include <string>
#include <string.h>
#endif

#ifndef __VECTOR__
#define __VECTOR__
#include <vector>
#endif // __VECTOR__

#ifndef __UTILS__
#define __UTILS__
#include "utils.h"
#endif // __UTILS__

#ifndef __DAY__
#define __DAY__
#include "../models/day.h"
#endif // __DAY__

#ifndef __IOMANIP__
#define __IOMANIP__
#include <iomanip>
#endif // __IOMANIP__

#ifndef __NCURSES__
#define __NCURSES__
#include <ncurses.h>
#endif // __NCURSES__

std::string getpass(const char *prompt)     //using the ncurses library
{
  printw(prompt);
  noecho();  // disable character echoing

  char buff[32];
  getnstr(buff,sizeof(buff));

  echo(); // enable character echoing again
  return buff;
}


// #include <unistd.h> -- won't work on windows
void generateClassReportByModerator();

bool logIn(USER& succ)
{
    std::string user_id;
    std::cout << "\n#### Log in ####\n";
    std::cout << "User Id: ";
    std::cin >> user_id;
    //char *pa = getpass("Password: ");
    //std::string password(pa);
    std::string password = "";
    std::cout << "Password: ";
    std::cin >> password;

    std::string uidPrefix = user_id.substr(0,2);

    if(!(uidPrefix == "ST" || uidPrefix == "TC" || uidPrefix == "MD"))
    {
        return false;
    }

    TYPE utype = getTypeByUid(user_id);
    try
    {

        if(getRnoByUid(user_id) < getRnoByUid(getNewUid(utype)))
        {

            std::ifstream file;
            openReadfileByType(utype, file);

            file.seekg(sizeof(USER)*getRnoByUid(user_id), std::ios::beg);
            file >> succ;
            file.close();
            return password == succ.getPassword();
        }
    }
    catch(const std::invalid_argument& arge)
    {
        std::cout << "Inside catch\n\n\n";
        return false;   // if format of UID is wrong
    }
    std::cout << "Outside here";
    return false;       // if format of UID is valid but there is no record
}

bool createUser()
{
    std::string name, password;
    TYPE type;
    int type_no;

    std::cout<<"\n\tCreate New User\n";
    std::cout<<"\nEnter Name :";
    std::cin>>name;
    std::cout<<"\nEnter Password :";
    std::cin>>password;

    std::cout<<"\nSelect type of user\n0 for STUDENT\n1 For Teacher\n2 For MODERTAOR :\n\nEnter Choice : ";
    std::cin>>type_no;

    switch(type_no)
    {
    case 0:
        type=TYPE::STUDENT;
        break;
    case 1:
        type=TYPE::TEACHER;
        break;
    case 2:
        type=TYPE::MODERATOR;
        break;
    default:
        std::cout<<"\nWrong choice of User Type..";
        return false;
    }

    USER user(type, name, password);
    std::ofstream file;
    openWritefileByType(type, file);

    if(file.is_open())
    {
        file << user;
        file.close();
        if(user.getUserType() == TYPE::TEACHER)
        {
            std::string registerName = "models/registers/" + user.getUid() + ".dat";
            std::ofstream Register(registerName);
            Register.close();
        }
        return true;
    }
    return false;
}

bool changePassword(USER& user)
{
    std::string password, c_password;
    std::cout<<"\n\tChange Password";

    std::cout<<"\nNew Password : ";
    std::cin>>password;
    std::cout<<"\nConfirm New Password : ";
    std::cin>>c_password;

    if(password != c_password)
    {
        return false;
    }

    user.changePassword(password);
    std::fstream file;
    std::string fname = "models/";

    switch(user.getUserType())
    {
    case TYPE::STUDENT:
        fname += "students.dat";
        break;
    case TYPE::TEACHER:
        fname += "teachers.dat";
        break;
    case TYPE::MODERATOR:
        fname += "moderators.dat";
    }

    file.open(fname);
    file.seekp(sizeof(USER)*getRnoByUid(user.getUid()), std::ios::beg);
    file.write((char *)&user,sizeof(user));

    file.close();
    return true;
}

void takeAttendance(USER& teacher)
{
    std::ifstream fin("models/students.dat");
    if(fin.is_open())
    {
        Day d;
        USER curr;
        std::cout << "\n\nATTENDANCE for " << d.getToday().day << "-" << 1+d.getToday().month << "-" << 1900+d.getToday().year << "\n\n";
        std::cout << "Mark P/A for each student\n";
        while(fin >> curr)
        {
            std::cout << curr.getUid() << "  " << curr.getName() << ": ";
            std::cin >> d.attendance[curr.getIndex()];
        }
        fin.close();

        std::string filePath = "models/registers/" + teacher.getUid() + ".dat";
        std::fstream file(filePath, std::ios::binary | std::ios::app);
        file << d;
        file.close();
    }
    else
    {
        std::cout << "No student data available.";
    }
}

// report generation not working
void generateClassReportPercentage(USER& usr)
{
    std::cout << std::fixed << std::setprecision(2);
    if(usr.getUserType() == TYPE::TEACHER)
    {

        std::ifstream fin;
        USER curr;
        openReadfileByType(TYPE::STUDENT, fin);
        fin.seekg(0,fin.end);
        int total_student=fin.tellg()/sizeof(USER);
        fin.seekg(0,fin.beg);

        std::string filePath = "models/registers/" + usr.getUid() + ".dat";
        std::ifstream Register(filePath);
        if(Register.is_open())
            std::cout << "Open";
        else
        {
            std::cout<<"Not Open"<<Register.exceptions();
        }
        int totalCount[200];
        Register.seekg(0, Register.end);
        int totalDays = Register.tellg() / sizeof(Day);
        for(int i = 0; i < total_student; i++)
            totalCount[i] = 0;

        Day d;
        Register.seekg(0, Register.beg);
        while(Register >> d)
        {
            for(int j=0; j<total_student; j++)
            {
                totalCount[j] += (d.attendance[j] == 'P' ? 1 : 0);
            }
        }
        Register.close();

        std::cout << "\n  Uid  |  Attendance  ";
        while(fin >> curr)
        {
            std::cout << "\n " << curr.getUid() << " |  " << totalCount[curr.getIndex()]*100.00/totalDays << "%";
        }
        fin.close();
    }
    else
    {
        generateClassReportByModerator();
    }
    std::cout << "\n\n";
}

void generateClassReportByModerator()
{
    std::ifstream teachers, students;
    openReadfileByType(TYPE::TEACHER, teachers);
    USER teacher;
    std::cout << "\n  UID  ";
    while(teachers >> teacher)
    {
        generateClassReportPercentage(teacher);
    }
    teachers.close();
}


void generateIndividualReportPercentage(USER& student)
{
    std::cout << std::fixed << std::setprecision(2);
    std::ifstream file;
    openReadfileByType(TYPE::TEACHER, file);
    USER teacher;
    std::cout << "\n\nReport for " << student.getName() << "\n";
    std::cout << "\n Subject | Attendance\n";
    while(file >> teacher)
    {
        std::string filePath = "models/registers/" + teacher.getUid() + ".dat";
        std::ifstream Register(filePath);

        int total = 0;
        Day d;
        while(Register >> d)
        {
            total += (d.attendance[student.getIndex()] == 'P' ? 1 : 0);
        }
        Register.seekg(0, Register.end);
        int totalDays = Register.tellg() / sizeof(Day);
        Register.close();

        std::cout << "  " << teacher.getUid() << "  | " << total*100.00/totalDays << "%\n";
    }
}

int showMainMenu(USER& curr)
{
    int choice;
    TYPE t = curr.getUserType();
    std::cout << "------------------------\n";
    do
    {
        if(t == TYPE::TEACHER)
        {
            std::cout << "1. Take Attendance\n";
        }
        if(t == TYPE::STUDENT)
        {
            std::cout << "2. Generate Report\n";
        }
        if(t == TYPE::MODERATOR)
        {
            std::cout << "3. Create New User\n";
        }
        if(t == TYPE::MODERATOR || t == TYPE::TEACHER)
        {
            std::cout << "4. Generate Class Report\n";
        }
        std::cout << "5. Change Password\n";
        std::cout << "0. Log Out\n";
        std::cout << "------------------------\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
    }
    while(choice < 0 || choice > 5);
    return choice;
}

int showLoginMenu()
{
    std::cout << "::ATTENDANCE MANAGEMENET SYSTEM::\n";
    int choice;
    do
    {
        std::cout << "---------------------------------\n";
        std::cout << "  1. Login\n";
        std::cout << "  2. Exit\n";
        std::cout << "---------------------------------\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
    }
    while(choice < 1 || choice > 2);
    return choice;
}



