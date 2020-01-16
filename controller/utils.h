
#ifndef __STRINGS__
#define __STRINGS__
#include <string>
#include <string.h>
#endif

#ifndef __UTYPE__
#define __UTYPE__
#include "../models/utype.h"
#endif // __DAY__

int getRnoByUid(std::string);
USER getUserByUid(std::string);
TYPE getTypeByUid(std::string);
void showMainMenu();