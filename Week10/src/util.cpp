/**
@file util.cpp
@brief Week 10, C++ Review and Warmup 
@author Will Im
@assignment Lab 10.1
@date Nov 9, 2020
@credits
    Devin Paden
    https://dev.to/talhabalaj/setup-visual-studio-code-for-multi-file-c-projects-1jpi
    https://stackoverflow.com/questions/16931770/makefile4-missing-separator-stop
/*

#include "util.h"

//Pre: recieves a double vector
//Post: returns the average of all the doubles in the vector
//Purpose: finds the average of all the doubles in the vector
double avg(vector <double> &vectDoub){
    double avg = sum(vectDoub) / MAX;

    return avg;
}

//Pre: recieves a multi word string
//Post: returns the string in camel case
//Purpose: converts a multi word string to camel case
string camelCase(string str){
    string camel = "";

    for (int i = 0; i < str.length(); i++){ // Runs through every character in the string
        if (i == 0){ // If set the first character to lower case
            camel += tolower(str[i]);
        }
        else if(str[i] == ' '){ // If the current character is a space, don't add to the camel string, but make the next element upper case
            str[i + 1] = toupper(str[i + 1]);
        }
        else{
            camel += str[i];
        }
    }
    
    return camel;
}

//Pre: recieves a double vector
//Post: returns the lowest double in the vector
//Purpose: finds the lowest of all the doubles in the vector
double lowest(vector <double> &vectDoub){
    double lowest = vectDoub[0];

    for (int i = 0; i < MAX; i++){
        if (vectDoub[i] < lowest){
            lowest = vectDoub[i];
        }
    }

    return lowest;
}

//Pre: recieves a populated string vector
//Post: returns a random element in that vector
//Purpose: to isolate a random element in a string vector
string randomElement(vector <string> &vectStr){
    // Gets a random number in the range of our vector
    srand(time(0));
    int i = rand() % MAX;

    return vectStr[i];
}

//Pre: recieves a double vector
//Post: returns the sum of all the doubles in the vector
//Purpose: adds all of the doubles in a double vector
double sum(vector <double> &vectDoub){
    double sum = 0;

    for (int i = 0; i < MAX; i++){
        sum = sum + vectDoub[i];
    }

    return sum;
}
