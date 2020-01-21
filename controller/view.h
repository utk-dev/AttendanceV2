#ifndef __USERGUARD__
#define __USERGUARD__
#include "user.h"
#endif
/**
*
*/
bool logIn(USER&);
bool createUser();
bool changePassword(USER&);
void takeAttendance(USER&);
void generateClassReportPercentage(USER&);
void generateIndividualReportPercentage(USER&);
int showMainMenu(USER&);
int showLoginMenu();
void generateClassReportByTeacher(USER&);



