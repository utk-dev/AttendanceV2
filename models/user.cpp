#ifndef __IOSTREAM__
#define __IOSTREAM__
#include <iostream>
#endif

#ifndef __USERGUARD__
#define __USERGUARD__
#include "user.h"
#endif

#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include <fstream>
#endif

#ifndef __STRINGS__
#define __STRINGS__
#include <string>
#include <string.h>
#endif

/** pad the given number with required number of zeros to make the string
 *  3 charaters long.
 *
 * @param num - {int} the number to be padded
 * @return std::string padded form of the number
 */
std::string padZeros(int num)
{
    std::string ret = std::to_string(num);
    while(ret.size() != 3)
        ret = "0" + ret;
    return ret;
}

/** Get a new uid of given TYPE x
 * @param x - {TYPE} Type of the new uid to be generated
 * @return std::string new uid
*/
std::string getNewUid(TYPE x)
{
    std::ifstream file;
    std::string newUid;
    switch (x)
    {
    case TYPE::STUDENT:
        file.open("models/students.dat", std::ios::binary);
        newUid = "ST";
        break;
    case TYPE::TEACHER:
        file.open("models/teachers.dat", std::ios::binary);
        newUid = "TC";
        break;
    case TYPE::MODERATOR:
        file.open("models/moderators.dat", std::ios::binary);
        newUid = "MD";
        break;
    }
    int ct = 0;
    int isOpen = file.is_open();
    if(isOpen)
    {
        file.seekg(0, file.end);
        ct = (int)(file.tellg())/(int)(sizeof(USER));
        file.close();
    }
    return newUid + padZeros(ct);
}

/** Set the name of the user
 * @param n - {std::string} name of the user
 * @return Boolean value denoting if the name was set successfully
*/
bool USER::setName(std::string n)
{
    if(n.size() < 100)
    {
        strcpy(name, n.c_str());
        return true;
    }
    return false;
}

/** Set the uid of the user
 * @param n - {std::string} uid of the user
 * @return Boolean value denoting if the uid was set successfully
*/
bool USER::setUid(std::string n)
{
    if(n.size() < 10)
    {
        strcpy(uid, n.c_str());
        return true;
    }
    return false;
}

/** Set the TYPE(usertype) of the user
 * @param t - {TYPE} type of the user [STUDENT/TEACHER/MODERATOR]
*/
void USER::setUsertype(TYPE t)
{
    usertype = t;
}

/** Change the password of the user
 * @param p - {std::string} new password
 * @return - Boolean value denoting if password was changed successfully
*/
bool USER::changePassword(std::string p)
{
    if(p.size() < 100)
    {
        strcpy(password, p.c_str());
        return true;
    }
    return false;
}

/** USER Constructor - Empty user object
 * for use by stream extraction operator
*/
USER::USER() {}

/** USER Constructor - Sets Uid automatically
 * @param Utype - TYPE of the user
 * @param Name - std::string name
 * @param Pwd - std::string password
*/
USER::USER(TYPE Utype, std::string Name, std::string Pwd)
{
    // [TODO]: need to check of everything is valid here

    setUsertype(Utype);
    setName(Name);
    setUid(getNewUid(Utype));
    changePassword(Pwd);
}

/** name of the user
 * @return  - {std::string} name of the user
*/
std::string USER::getName()
{
    return std::string(name);
}

/** uid of the user
 * @return  - {std::string} uid of the user
*/
std::string USER::getUid()
{
    return std::string(uid);
}

/** type of the user
 * @return  - {TYPE} type of the user
*/
TYPE USER::getUserType()
{
    return usertype;
}

/** index of the user
 * @return  - {int} integer part of the uid
*/
int USER::getIndex()
{
    return std::stoi(getUid().substr(2));
}

std::string USER::getPassword(){
    return std::string(password);
}

/** Writes a USER object to a file output stream
 * The file needs to be opened in ios::binary mode
*/
std::ofstream& operator<<(std::ofstream& out, const USER& u)
{
    out.write((char *)&u, sizeof(USER));
    return out;
}

/** Reads a USER object from a file input stream
 * The file needs to be opened in ios::binary mode
*/
std::ifstream& operator>>(std::ifstream& in, USER& u)
{
    in.read((char *)&u, sizeof(USER));
    return in;
}


