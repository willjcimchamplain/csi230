/*
@file logger.cpp
@brief contains functions for logging each run of the program to mylogfile.txt
@author Devin Paden
@editor Will Im
@assignment Lab 10.2
@date 11/12/2020
*/

#include "logger.h"

/*
@brief Error checks the program and runs necessary functions given a lack of errors
@date 11/12/2020
@return either true or false bool 
@param string msg - message to go with the log
@param logFile - output to the file we are logging to 
@param string strProgramName - the name of our current program (found in main)
*/
bool log(string msg, ofstream& logFile, string strProgramName){
    string strTime;

    // Gets time
    time_t logTime = time(0);
    strTime = ctime(&logTime);

    // Time off the newline
    int timeSize = strTime.size();
    if(timeSize){
        strTime[timeSize - 1] = ' ';
    }
    
    // Gets pid
    pid_t pid = getpid();

    // Gets host name
    char hostname[HOST_NAME_MAX];
    string strHostName;
    strHostName = gethostname(hostname, HOST_NAME_MAX);
    
    if(logFile){
        logFile << strTime << strHostName << " " << strProgramName << "[" << pid << "]" << ": " << msg << endl;
        return true;
    }
    else{
        return false;
    }
}