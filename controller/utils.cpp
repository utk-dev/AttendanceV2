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

std::fstream* openfileByType(TYPE type){
    std::fstream file;
    switch(type){
        case TYPE::STUDENT:
            file.open("../models/students.dat",std::ios::binary);
            break;
        case TYPE::TEACHER:
            file.open("../models/teachers.dat",std::ios::binary);
            break;
        case TYPE::MODERATOR:
            file.open("../models/moderators.dat",std::ios::binary);
            break;
    }
    return &file;
}
