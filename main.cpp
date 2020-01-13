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

using namespace std;
int main()
{
    // insert first student
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

    // read both students
    USER stu3;
    ifstream in("models/students.dat", ios::binary);
    while(in >> stu3)
    {
        cout << stu3.getUid() << " " << stu3.getName() << " " << stu3.getIndex() << "\n";
    }
    in.close();

    in.close();
    return 0;
}
