#ifndef __STRINGS__
#define __STRINGS__
#include <string>
#include <string.h>
#endif

#ifndef __USERGUARD__
#define __USERGUARD__
#include "../models/user.h"
#endif

#ifndef __TYPE__
#define __TYPE__
#include "../models/utype.h"
#endif // __DAY__

#ifndef __UTILS__
#define __UTILS__
#include "utils.h"
#endif


int getRnoByUid(std::string uid){
    return std::stoi(uid.substr(2));
}

TYPE getTypeByUid(std::string uid){
    std::string prefix = uid.substr(0, 2);
    if(prefix == "ST")
        return TYPE::STUDENT;
    else if(prefix == "TC")
        return TYPE::TEACHER;
    else
        return TYPE::MODERATOR;
}

std::ifstream* openReadfileByType(TYPE type){
    std::ifstream *file=new std::ifstream;
    switch(type){
        case TYPE::STUDENT:
            file->open("./models/students.dat",std::ios::binary);
            break;
        case TYPE::TEACHER:
            file->open("./models/teachers.dat",std::ios::binary);
            break;
        case TYPE::MODERATOR:
            file->open("./models/moderators.dat",std::ios::binary);
            break;
    }

    return file;
}
std::ofstream* openWritefileByType(TYPE type){
    std::ofstream *file=new std::ofstream;
    switch(type){
        case TYPE::STUDENT:
            file->open("./models/students.dat",std::ios::binary | std::ios::app);
            break;
        case TYPE::TEACHER:
            file->open("./models/teachers.dat",std::ios::binary | std::ios::app);
            break;
        case TYPE::MODERATOR:
            file->open("./models/moderators.dat",std::ios::binary | std::ios::app);
            break;
    }
    return file;
}
std::fstream* openReadWritefileByType(TYPE type){
    std::fstream *file=new std::fstream;
    switch(type){
        case TYPE::STUDENT:
            file->open("./models/students.dat",std::ios::binary | std::ios::app);
            break;
        case TYPE::TEACHER:
            file->open("./models/teachers.dat",std::ios::binary | std::ios::app);
            break;
        case TYPE::MODERATOR:
            file->open("./models/moderators.dat",std::ios::binary | std::ios::app);
            break;
    }
    return file;
}
