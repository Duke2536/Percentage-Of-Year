#include "filesaver.h"

#include <iostream>
#include <fstream>

ofstream outfile;
ifstream infile;

const string file_name = "times_saved.txt";

int input_count = 0; //Documents lines for file input

bool file_enabled = true;
bool need_update = true;

//Gets count on how many inputs have already been recorded in file
void get_input_count()
{
    infile.open(file_name);
    while (true)
    {
        string line;
        getline(infile, line);

        if (infile.fail()) break;

        if(line.size() > 0 && line.at(0) == '#') //Each # represents a new documentary of user input
        {
            input_count++; //Number corresponding the input number (i.e. 4th documented data)
        }
    }
    infile.close();
}

//Runs for each input if file is enabled
void add_data(string input, string leap, string percentage, string days_complete, string days_overall)
{
    if(need_update) //If this is the first call, numbers the inputs to properly store the current
    {
        get_input_count();
        need_update = false;
    }

    if(file_enabled) //Runs if user has not disabled saving
    {
        input_count++;
        outfile.open(file_name, ios_base::app);

        outfile << "#" << input_count << " " << input << "\n";
        outfile << "Is Leap Year: " << leap << "\n\n";
        outfile << "Percentage of Year Completed: " << percentage.substr(0, 5) << "\n";
        outfile << "Current Days Out of Year: " << days_complete << "\n";
        outfile << "Current Days in Year Total: " << days_overall << "\n\n";

        outfile.close();
    }
}

void run_file_cmd(string user_input) //Equivalent of main() for filesaver.cpp , all commands and actions run inside here
{
    cout << "\nFILE SYSTEM:\n";

    infile.open(file_name);
    if(infile.fail())
    {
        outfile.open(file_name);    //If the file has been either deleted, or never added, a new recovery file is made
        cout << "New recovery file created!\n";
        outfile.close();
    }
    infile.close();

    cout << "Input a number for the corresponding action:\n";
    cout << "1) Print out file data \n2) Enable/Disable file saving \n3) Clear file\n";
    getline(cin, user_input);   //All possible commands for files^

    while (true)
    {
        if(user_input == "1")
        {
            print_file();
        }
        else if(user_input == "2") //Disables file saving
        {
            file_enabled = !file_enabled;
            string notification_text = (file_enabled) ? "enabled" : "disabled";
            cout << "File saving has been " << notification_text << ", to revert action recall command #2\n\n";
        }
        else if(user_input == "3") //Clears file
        {
            string line;
            getline(infile, line);

            infile.open(file_name);
            outfile.open(file_name);

            if(infile.fail())
            {       //UNEXPECTION BEHAVIOR / INPUT means it can either be a big error, or the user tried clearing an empty file
                throw invalid_argument("[UNEXPECTED BEHAVIOR / INPUT] <- Interchangeable; Are you sure this file isn't already cleared?");
            }
            else if(line == "")
            {
                cout << "\nFile successfully cleared!\n";
            }
            else
            {       //This line should NEVER run
                throw invalid_argument("File did not clear -> ? [UNEXPECTED BEHAVIOR] CRITICAL issue, check files");
            }
            infile.close();
            outfile.close();
        }
        else if(user_input == "EXIT")
        {
            cout << "Exitting file system\n";
            return;
        }
        else
        {
            cout << "Invalid input, returning to menu: \n";
            return;
        }
        cout << "Input next command (type EXIT to exit): ";
        getline(cin, user_input);
    }
}

void print_file()
{
    infile.open(file_name);

    cout << "\nPrinting file data:\n\n";
    int line_number = 1;

    while (true)
    {
        string line;
        getline(infile, line);

        if (infile.fail()) break;

        cout << line_number << ". " << line << "\n"; //Numbers lines as such -> 1. (text)
        line_number++;
    }
    if(line_number == 1) cout << "(File is empty)\n";
    infile.close();

    return;
}