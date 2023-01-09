#include<iostream>
#include<fstream>
#include <string>

using namespace std;

int main()
{
    fstream calor;
    calor.open("jmeno.txt", ios::in); //open a file to perform read operation using file object
    if (calor.is_open()) {   //checking whether the file is open
        string tp;


        while (getline(calor, tp)) {  //read data from file object and put it into string.

        }
        calor.close();

    }
}

