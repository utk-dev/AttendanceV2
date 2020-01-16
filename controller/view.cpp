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
        std::fstream *file=openfileByType(utype);
       
        USER *user;
         
        file->seekg(sizeof(USER)*getRnoByUid(user_id));
        file->read((char *)user,sizeof(USER));
        file->close();

        if(strcasecmp(password.c_str(),user->getPassword()) == 0){
            return user;
        }else{
            return nullptr;
        }

    }
}

bool createUser(){
    std::string name,password;
    TYPE type;
    int type_no;

    std::cout<<"\n\tCreate New User\n";
    std::cout<<"\nEnter Name :";
    std::cin>>name;
    std::cout<<"\nEnter Password :";
    std::cin>>password;


    //label for validate right User type choice.....
    user_type_lb:

    std::cout<<"\nSelect type of user\n1 for STUDENT\n2 For Teacher\n3 For MODERTAOR :";
    std::cin>>type_no;

    switch(type_no){
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
                goto user_type_lb;
                break;
    }
     
    USER user(type,name,password);
    std::fstream *file=openfileByType(type);
    file->write((char *)&user,sizeof(USER));
    file->close();

    return true;
}

bool changePassword(){


}

