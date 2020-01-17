#ifndef __TYPE__
#define __TYPE__
#include "utype.h"
#endif // __TYPE__

#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include <fstream>
#endif

#ifndef __STRINGS__
#define __STRINGS__
#include <string>
#include <string.h>
#endif

std::string padZeros(int);
std::string getNewUid(TYPE);

class USER
{
private:
    TYPE usertype;
    char name[100];
    char uid[10];
    char password[100];
    bool setName(std::string);
    bool setUid(std::string);
    void setUsertype(TYPE);
public:
    USER();
    USER(TYPE, std::string, std::string);
    bool changePassword(std::string);
    std::string getName();
    std::string getUid();
    TYPE getUserType();
    int getIndex();
    char* getPassword();
};

std::ofstream& operator<<(std::ofstream&, const USER&);
std::ifstream& operator>>(std::ifstream&, USER&);

