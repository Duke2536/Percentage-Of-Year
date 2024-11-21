#include <iostream>
#include <vector>
#include <utility>
#include <ctime>
#include <cmath>
#include <cstdio>

#include "filesaver.h" //Custom header

/* DEVELOPER NOTES:
* [UNEXPECTED INPUT] = User input a date incorrecly
* [UNEXPECTED BEHAVIOR] = Critical bug in code, unintentional
* All function prototypes are functions intended to provide readability
*/

const std::vector <std::string> month_list = //Vector to convert numerical value of months into string
{"January", "February", "March", "April", "May", "June", 
"July", "August", "September", "October", "November", "December"};

std::vector <std::pair<int, int> > month_and_dates = //Numerical pair of month and it's greatest date (using a 365 day calendar)
{ {1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31},  {6, 30},
{7, 31}, {8, 31}, {9, 30}, {10, 31}, {11, 30}, {12, 31}};

std::string get_month(int month)
{
    if(month <= 11 && month >= 0)
    {
        return month_list.at(month);
    }
    else    //Throws error in event month is out of range (states month number given in exception)
    {
        throw std::invalid_argument("Month outside of range -> ? [UNEXPECTED INPUT] month given: (" + std::to_string(month) + ")\n");
    }
}

bool get_leap_year(int year)
{
    if(year % 4 == 0 && !(year % 1000 == 0))
    {
        return true;
    }
    else if(year % 1000 == 0 && year % 400 == 0) //Checks for end-of-century years (i.e. 1900, 2000...)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int days_total (bool isleap, int month, int date, int year) //Calculates how many days have passed given the users date INCLUSSIVE OF THE DAY
{                                                           //i.e. (1/1/24 = 1) , (1/2/24 = 2) ...
    int days_completed = 0;

    month_and_dates.at(1).second = 28; //Assures previous leap years are reverted
    if(isleap) month_and_dates.at(1).second = 29; //In the event it is a leap year, it updates the month_and_dates

    for(int i = 0; i < month_and_dates.size(); i++)
    {
        if(month_and_dates.at(i).first < month) //If this month is before the one inputted by the user, add all the days to days_completed
        {
            days_completed += month_and_dates.at(i).second;
        }
        else if(month_and_dates.at(i).first == month) //In the case it is the exact month, it will add the dates input
        {
            if(date > month_and_dates.at(i).second) //Throws an error if date is greater than month (i.e. February 30th)
            {
                throw std::invalid_argument
                    ("Date outside of range -> [UNENXPECTED INPUT] date given: (" + std::to_string(date) + ") in month: (" 
                    + std::to_string(month_and_dates.at(i).first) + ")");
            }
            days_completed += date;
            return days_completed;
        }
    }
    throw std::invalid_argument("function \"days_total\" met end [UNEXPECTED BEHAVIOR]; check function call");
}

//Intended to convert the date given into their designated variables
void update_date_variables(int &month, int &date, int &year, std::string &user_input);


//MAIN
int main() {
   std::string user_input; 

   const time_t now = time(NULL);
   const tm *thistime = localtime(&now); //Grabs time on computer

   std::string current_month = get_month(thistime -> tm_mon); //Converts numerical value month into string
   int current_day = thistime -> tm_mday; //Stores date of month into variable for accessibility

   int current_year = (thistime -> tm_year) + 1900; //tm_year grabs the distance from the current year to 1900, by adding 1900 we get the current year
   std::string is_leap_year = (get_leap_year(current_year)) ? "True" : "False";

   int days_completed = thistime -> tm_yday; //Grabs the number of how many days have been completed through the year
   int days_overall = (get_leap_year(current_year)) ? 366 : 365;

   double percentage = std::round( ((days_completed + 0.0) / (0.0 + days_overall)) * 100 * 100 ) / 100 ; //Grabs percentage with first 2 decimals included

   //Prints out all values we've calculated / collected 
   std::cout << "Percentage of year calculator:\n\n";
   std::cout << "Date (MM :: DD :: YY): "<<  current_month << " " << current_day << ", " << current_year << "\n";

   std::cout << "Is Leap Year: " << is_leap_year << "\n\n";

                                            //Assures that the 2nd decimal is printed incase it's 0
   std::cout << "Percentage of Year Completed: ";       printf("%.2f", percentage);     std::cout << "%\n";
   std::cout << "Current Day Out of Year: " << days_completed <<"\n";
   std::cout << "Current Days in Year Total: " << days_overall << "\n";

   while (true) //Intended to constantly loop until program ends
   {
        std::cout << "\nTo exit type \"EXIT\", to see all commands type \"COMMAND\" \n"; 
        std::cout << "Enter date you want to calculate (MM :: DD :: YYYY): "; //Month should be compatible with int only
        std::getline(std::cin, user_input);

        if(user_input == "EXIT") break;
        if(user_input.size() < 4) throw std::invalid_argument("Not enough characters for any command, did you mean \"EXIT\"?");

        if(user_input == "COMMAND") //Prints all available commands, might add onto commands later
        {
            std::cout << "\nCOMMAND LIST: \n-FILE \n-EXIT";
            continue;
        }
        if(user_input == "FILE") //Opens all file commands -> originates within filesaver.h and filesaver.cpp
        {
            run_file_cmd(user_input);
            continue;
        }

        int user_month;
        int user_date;
        int user_year;

        update_date_variables(user_month, user_date, user_year, user_input); //Refer to prototype call

        is_leap_year = (get_leap_year(user_year)) ? "True" : "False";
        std::cout << "Is Leap Year: " << is_leap_year << "\n";

        days_overall = get_leap_year(user_year) ? 366 : 365;
        
        days_completed = 0;
        days_completed = days_total(get_leap_year(user_year), user_month, user_date, user_year); //Refer to function call

        percentage = std::round( (days_completed + 0.0) / (0.0 + days_overall) * 100 * 100 ) / 100; //Grabs percentage with first 2 decimals included

                                                    //Assures that the 2nd decimal is printed incase it's 0
        std::cout << "Percentage of Year Completed: ";       printf("%.2f", percentage);     std::cout << "%\n";
        std::cout << "Current Day out of Year: " << days_completed << "\n";
        std::cout << "Current Days in Year Total: " << days_overall << "\n";

        add_data(user_input, is_leap_year, std::to_string(percentage), std::to_string(days_completed), std::to_string(days_overall));
   }        //Function call from filesaver.h, refer to filesaver.h for more info

   return 0;
}


//VOID FUNCTION(S)
void update_date_variables(int &month, int &date, int &year, std::string &user_input)
{
   int space_count = 0; //Variable referring to how many times a space or / was detected
   for(int i = 0; i < user_input.size(); i++)
   {
        if((user_input.at(i) == ' ' || user_input.at(i) == '/') && space_count == 0) //Checks on 1st instance of a space or /
        {
            space_count++;
            try
            {
                month = std::stoi(user_input.substr(0, i)); //Attempts to convert formatted like (01/#/#)
            }
            catch(std::invalid_argument)
            {
                month = std::stoi(user_input.substr(0, i-1)); //If try fails, converts to format (1/#/#)
            }
        }
        else if((user_input.at(i) == ' ' || user_input.at(i) == '/') && space_count == 1) //Checks on 2nd instance of a space or /
        {
            space_count++;
            try
            {
                date = std::stoi(user_input.substr(i-2, i-1)); //Attempts to convert formatted like (#/01/#)
            }
            catch(std::invalid_argument)
            {
                date = std::stoi(user_input.substr(i-1, i-1)); //If try fails, converts to format (#/1/#)
            }
        }
        else if(i == user_input.size()-1) //Grabs last 2 or 4 digits (varries on if year is formatted like 2024 or 24)
        {
            bool check = false;
            for(char c : user_input.substr(i-3, i))
            {
                if (c == '/' || c == ' ')
                {
                    year = std::stoi(user_input.substr(i-1, i)); //In the case a space or / is found in 4 number range, refers to 2 number range
                    check = true;
                }
            }
            if( !check ) //Accounts for case where no space or / was uncovered in 4 number range
            {
                year = std::stoi(user_input.substr(i-3, i));
            }
        }
   }
   if(year <= 99) //Intends to print with regular format (2024) for 2 numbered years
   {
        std::cout << "Calculating percentage for date: (" << get_month(month-1) <<  " " << date << ", 20" << year << ")\n\n";
   }
   else //Regular print of date
   {
        std::cout << "Calculating percentage for date: (" << get_month(month-1) <<  " " << date << ", " << year << ")\n\n";
   }
    return;
}