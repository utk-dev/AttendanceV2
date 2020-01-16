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

#ifndef __UTILS__
#define __UTILS__
#include "utils.h"
#endif // __UTILS__

#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include <fstream>
#endif


USER* logIn(){
    std::string user_id,password="";
    char ch;
    std::cout<<"\n\tLog in\n\n";
    std::cout<<"\nUser Id : ";
    std::cin>>user_id;
    std::cout<<"\nPassword: ";
    std::cin>>password;
    
    std::string uidPrefix = user_id.substr(0,2);
    if(!(uidPrefix == "ST" || uidPrefix == "TC" || uidPrefix == "MD")){
        return nullptr;
    }

    TYPE utype=getTypeByUid(user_id);      



    if(getRnoByUid(user_id) < getRnoByUid(getNewUid(utype))){
        std::ifstream file;
        switch(utype){
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
        
    }
}

