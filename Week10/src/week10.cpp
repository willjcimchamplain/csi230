/**
@file week10.cpp
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

main(){
    // Initializes and populates a string vector
    vector <string> vectorStr;
    vectorStr.push_back("String One");
    vectorStr.push_back("String Two");
    vectorStr.push_back("String Three");
    vectorStr.push_back("String Four");
    vectorStr.push_back("String Five");

    cout << "Vector String Elements:\n";
    for (int i = 0; i < MAX; i++){ // Outputs the strings in the vector
        cout << vectorStr[i] << endl;
    }

    cout << "A random element in this vector is: " << randomElement(vectorStr) << endl;

    cout << "Vector Double Elements:\n";
    
    // Initializes and populates a double vector
    vector <double> vectorDoub;
    for (double i = 0; i < MAX; i++){
        vectorDoub.push_back(i + i/10);
        cout << vectorDoub[i] << " ";
    }

    cout << "\nThe sum of these doubles is: " << sum(vectorDoub) << endl;
    cout << "The average of these doubles is: " << avg(vectorDoub) << endl;
    cout << "The lowest of these doubles is: " << lowest(vectorDoub) << endl;

    // Initializes a multi word string
    string str = "A little bird with a yellow bill";

    cout << "A multi word string is: " << str << endl;
    cout << "This string in camel case is: " << camelCase(str) << endl;

    return 0;
}
