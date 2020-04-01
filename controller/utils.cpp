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

#ifndef __INVALIDEXCEPTION__
#define __INVALIDEXCEPTION__
#include <stdexcept>
#endif // __INVALIDEXCEPTION__

/** returns integer part of the given user ID
*   @param uid - USER ID
*   @return integer part of the user ID
*/
int getRnoByUid(std::string uid){
        return std::stoi(uid.substr(2));
}

/** returns USERTYPE of the given user ID
*   @param uid - USER ID
*   @return usertype in the form of enumeration TYPE
*/
TYPE getTypeByUid(std::string uid){
    std::string prefix = uid.substr(0, 2);
    if(prefix == "ST")
        return TYPE::STUDENT;
    else if(prefix == "TC")
        return TYPE::TEACHER;
    else
        return TYPE::MODERATOR;
}

/** Opens read-only file of the specified TYPE
*   @param type - TYPE of the users whose file is to be openend
*   @param file - stream to which the 'read' access is given
*/
void openReadfileByType(TYPE type, std::ifstream& file){
    switch(type){
        case TYPE::STUDENT:
            file.open("models/students.dat",std::ios::binary);
            break;
        case TYPE::TEACHER:
            file.open("models/teachers.dat",std::ios::binary);
            break;
        case TYPE::MODERATOR:
            file.open("models/moderators.dat",std::ios::binary);
    }
}

/** Opens write-only file of the specified TYPE
*   @param type - TYPE of the users whose file is to be openend
*   @param file - stream to which the 'write' access is given
*/
void openWritefileByType(TYPE type, std::ofstream& file){
    switch(type){
        case TYPE::STUDENT:
            file.open("models/students.dat",std::ios::binary | std::ios::app);
            break;
        case TYPE::TEACHER:
            file.open("models/teachers.dat",std::ios::binary | std::ios::app);
            break;
        case TYPE::MODERATOR:
            file.open("models/moderators.dat",std::ios::binary | std::ios::app);
    }
}

