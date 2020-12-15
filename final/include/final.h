/*
@file finals.h
@brief Header file for final.cpp and stubb.cpp
@author Will Im
@credit https://www.youtube.com/watch?v=yv_WdDWEr90
@credit boost.timer: https://theboostcpplibraries.com/boost.timer
@assignment Final
@date 12/14/2020
*/
#ifndef EARTH_UTILS_H
#define EARTH_UTILS_H
#include <string> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>
#include <cmath>

using namespace std;

// Constant variables
const string HTML_FILE_FULL = "total.html";
const string HTML_FILE_AVG = "avg.html";
const string HTML_FILE_HIGH = "high.html";
const string HTML_FILE_LOW = "low.html";
const string MONTHS[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// Constant variables for file formatting
const int HEADER_SIZE = 8;
const int FOOTER_SIZE = 6;
const string HEADER[HEADER_SIZE] = {"<html>\n", "\t<head>\n", "\t\t<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\">\n", "\t\t</script>\n", "\t\t<script type=\"text/javascript\">\n", "\t\t\tgoogle.load('visualization', '1');\n", "\t\t\tgoogle.setOnLoadCallback(drawVisualization);\n", "\t\t\tfunction drawVisualization(){\n" };
const string FOOTER[FOOTER_SIZE] = {"\t\t</script>\n", "\t</head>\n", "\t<body>\n", "\t\t<div id=\"visualization_div\" style=\"width:100%; height:100%;\"></div>", "\t</body>\n", "</html>\n"};

/*
@brief Places information from the input file into the proper vectors to be referenced later on in the program
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fin - the txt file
@param x, y - Vectors that we are writing our information to, they will be referenced later on
*/
bool inputFile(ifstream&fin, vector<string> &x, vector<double> &y);

/*
@brief Formats the data into an html file that displays all of the data across all years and months in the file
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fout - total.html
@param x, y - Vectors that we are recieving information from 
*/
bool outputFileFull(ofstream&fout, vector<string>&x, vector<double> &y);

/*
@brief Formats the data into an html file that displays average data per month, tracked since 1950
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fout - avg.html
@param x, y - Vectors that we are recieving information from 
*/
bool outputFileAvg(ofstream&fout, vector<string>&x, vector<double> &y);

/*
@brief Formats the data into an html file that displays highest temperature data per month since 1950
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fout - high.html
@param x, y - Vectors that we are recieving information from 
*/
bool outputFileHigh(ofstream&fout, vector<string>&x, vector<double> &y);

/*
@brief Formats the data into an html file that displays lowest temperature data per month since 1950
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fout - low.html
@param x, y - Vectors that we are recieving information from 
*/
bool outputFileLow(ofstream&fout, vector<string>&x, vector<double> &y);

#endif