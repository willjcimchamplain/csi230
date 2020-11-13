/*
@file logger.cpp
@brief header information for logger.cpp
@author Devin Paden
@editor Will Im
@assignment Lab 10.2
@date 11/12/2020
*/

#pragma once

#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <string>
#include <fstream>
#ifndef LOGGER_H
#define LOGGER_H

using namespace std;

/*
@brief Error checks the program and runs necessary functions given a lack of errors
@date 11/12/2020
@return either true or false bool 
@param string msg - message to go with the log
@param logFile - output to the file we are logging to 
@param string strProgramName - the name of our current program (found in main)
*/
bool log(string msg, ofstream& logFile, string strProgramName);
#endif