#ifndef _filesaver_h
#define _filesaver_h

#include <iostream>

using namespace std;

void run_file_cmd(string user_input); //Main call of filesaver.cpp, allows file modifications, refer to filesaver.cpp for more info

void add_data(string input, string leap, string percentage, string days_complete, string days_overall); //Adds data to txt file from input year

void print_file(); //Prints file, function accessed through run_file_cmd, check filesaver.cpp for more info

#endif