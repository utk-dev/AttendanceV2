// MVC

// MODEL
TYPE: ENUM {
  STUDENT,
  TEACHER,
  MODERATOR
}

USER {
  PUBLIC CONST USERTYPE: TYPE
  PUBLIC CONST NAME: STRING
  PUBLIC CONST UID: STRING (
    STUDENT - STxxx(ST000, ST001, ST002...)
    TEACHER - TCxxx
    MODERATOR - MDxxx
  )
  PRIVATE PASSWORD: STRING
  PUBLIC CHANGE_PASSWORD()
  PUBLIC INT GETrno(USER) "ST000" -> 0, "ST123" -> 123
}

allSTUDENTs: FILE {
   // contains info about students' attendance
   all users with USERTYPE: STUDENT
}

allTEACHERs: FILE {
  // contains info about all teachers
}

allMODERATORs: FILE {
  // contains info about all moderators
}

REGISTER : FILE
  SHEET[]: DAY;

DAY {
  DATE: DATE
  ATTENDANCE[]: (P/A, LENGTH=NO_OF_STUDENTS)
}

// VIEW
1.
LOGIN(): ALL {
  UID: _________
  PASSWORD: __________
  1. FIND TYPE
  2. CHECK IF VALID UID 
      (USING getRnoByUid(UID) < getNewRollNo(TYPE))
  3. OPEN TYPE FILE
  4. CURR = getUserbyUid(UID);
  5. if(CURR.password == PASSWORD):
        return CURR
     else 
        return nullptr
}

2.
CREATE_USER() : MODERATOR {
  1. take input
  2. generate new roll no
  3. save to all_students/all_teacher
  4. if(type = teacher) {
     1. create a new REGISTER with T_ID = UID
  }
}

3.
CHANGE_PASSWORD() : ALL {
  this.CHANGEpassword();
}

4.
TAKE_ATTENDANCE() : TEACHER {
  1. find out todays date: DT
  2. create new object of DAY {
    DATE: DT
    ATTENDANCE[]: take input from the teacher (p/a)
    ( \\multiple ways\\ )
  }
  3. open the correct Register -> store the DAY in it.
}

5.
GENERATE_CLASS_REPORT_perc() : TEACHER {
  1. open the correct Register with TID
  2. array[] { %age of each students attendance }
  3. DISPLAY WITH STUDENT DETAILS (OPEN allStudentsFile)
}

6.
GENERATE_INDIVIDUAL_REPORT_perc() : STUDENT {
  1. OPEN allTEACHERS file
  2. LOOP THROUGH ALL REGISTERS(TID):
        OPEN REGISTER X
        FIND %age of this student for REGISTER X
        print this %
        CLOSE  REGISTER X
}

// utility functions
1. getNewRollNo(TYPE) {
  generate user ID
  return rno
}

2. INT getRnoByUid(Uid) {
  return Rno:INT from given UID
}

3. USER getUserByUid(Uid) {
   1. DETERMINE TYPE OF THE USER
   2. OPEN THAT TYPE FILE(ALLSTUDENTS/ALLTEACHERS ETC.)
   3. GET the pos = getRnoByUid(Uid)
   4. RETURN THE NTH USER (sizeof(USER)*pos)
}

4. TYPE getTypeByUid(Uid) {
  return TYPE:ENUM from given UID
}

5. ShowMainMenu() {
   Welcome CURR.name
   if(CURR.USERTYPE = TYPE.TEACHER) {
    PRINT(1. TAKE ATTENDANCE)
    PRINT(2. GENERATE REPORT)
   }
   if(CURR.USERTYPE = TYPE.STUDENT) {
    PRINT(3. GENERATE_INDIVIDUAL_REPORT_perc)
   }
   if(CURR.USERTYPE = TYPE.MODERATOR) {
    PRINT(4. CREATE_USER)
   }
   PRINT(5. CHANGE_PASSWORD)
   PRINT(6. LOGOUT)
}


// MAIN FUNCTION
0. USER CURR_USER, BOOL LOGGEDIN;
do {
1. SHOW LOGIN SCREEN;
2. CURR = LOGIN();
3. LOGGEDIN = (CURR != nullptr)
} while(!LOGGEDIN);

do {
  INT CH;
  ShowMainMenu();
  Take CH from user;
  switch(CH) {
    case 1:
      if(CURR.USERTYPE != TYPE.TEACHER) {
        "wrong choice nigga"
      } else {
        TAKE_ATTENDANCE(CURR);
      }
      break;
    case 2:
      if(CURR.USERTYPE != TYPE.TEACHER) {
        "wrong choice"
      } else {
        GENERATE_CLASS_REPORT_perc(CURR);
      }
      break;
    case 3:
      if(CURR.USERTYPE != TYPE.STUDENT)
      {
        "wrong choice"
      }else{
        GENERATE_INDIVIDUAL_REPORT_perc(CURR);
      }
    case 4:
      if(CURR.USERTYPE != TYPE.MODERATER)
      {
        "wrong choice"
      }else{
        CREATE_USER(CURR);
      }
    case 5:
      CHANGE_PASSWORD(CURR)
    case 6:
      LOGGEDIN=FALSE;
    default: "wrong choice"
  }

} while(LOGGEDIN)








