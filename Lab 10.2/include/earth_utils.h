/*
@file earth_utils.h
@brief Header information for earth_utils.cpp
@author Will Im
@credit Devin Paden
@assignment Lab 10.2
@date 11/12/2020
*/

#ifndef EARTH_UTILS_H
#define EARTH_UTILS_H
#include <string> 
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const string KML_HEADER1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
const string KML_HEADER2 = "<kml xmlns=\"http://www.opengis.net/kml/2.2\">";
const string KML_FOOTER = "</kml>";
const string KML_DOC_START = "<Document>";
const string KML_DOC_END = "</Document>";

/*
@brief Parses the CSV file
@date 11/12/2020
@return int records - the amount of records in the csv file
@param inFile - the csv file
@param kmlFileName - The name of the kml file we are writing to 
*/
int processCSV(ifstream& inFile, string kmlFileName);

/*
@brief Outputs to kml file
@date 11/12/2020
@param kmlFile - output to the kml file
@param string name - capital, country
@param string latitude - the latitude of the city
@param string longitude - the longitude of the city
@param string elevation - the elevation of the city
*/
void writePlacemark(ofstream& kmlFile, string name, string latitude, string longitude);

#endif