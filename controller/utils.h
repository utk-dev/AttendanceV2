
#ifndef __STRINGS__
#define __STRINGS__
#include <string>
#include <string.h>
#endif

#ifndef __TYPE__
#define __TYPE__
#include "../models/utype.h"
#endif // __DAY__

#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include <fstream>
#endif


int getRnoByUid(std::string);
USER getUserByUid(std::string);
TYPE getTypeByUid(std::string);
void showMainMenu();


//this function is open aprropriate file with given userType
std::ifstream* openReadfileByType(TYPE);
std::ofstream* openWritefileByType(TYPE);
