# AttendanceV2
 Attendance management application
 
 _Note: This application is a **code::blocks** project._

Project Authors: [Utkarsh Gupta](https://www.github.com/utk-dev), [Ronit Chopada](https://www.github.com/ronit9586), [Arnav Dixit](https://github.com/arnav127)

## Introduction

Attendance management system is a terminal based application software for assisting in the process of roll calls in various institutions. It automates certain aspects of managing attendance and exposes a friendly interface to it's various users. The software maintains students' records in the form of binary files, which are called 'Registers' throughout this project's documentation. This project compiles on both Linux's `g++` and Windows `minGW` that comes bundled with **Code::Blocks 17.12**. 


## Assumptions

Certain assumptions have been made to simplify the application:

1. There is only one class of students.
2. All teachers registered in this application teach that class.
3. Each teacher teaches only one subject and has a Register associated with it.
4. Only moderators can add new students.
5. Password is stored in plain text i.e. there is no encryption.


## How to use

Linux executable is available [here](https://github.com/utk-dev/AttendanceV2/releases/tag/v0.1-alpha) (with instructions).
Windows binary is available [here](https://github.com/utk-dev/AttendanceV2/releases/tag/v0.2-alpha) (with instructions).

You can also compile this project yourself. It requires you to enable C++11 flag in your compiler (Currently only g++ and minGW have been tested). Curses library is used to securely take password inputs and it needs to be installed if compiling the code from source.


## Contribute

We welcome all kinds of pull requests and issues filed within the scope of the assumptions made for this project. We will try to reply to all kinds of queries as promptly as possible. If you are interested in improving the documentation of the project, please fork our repository into your own account and file a pull request.
