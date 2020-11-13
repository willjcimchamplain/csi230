/*
@file earth_utils.cpp
@brief Formats information from a csv file into a kml file
@author Will Im
@credit Devin Paden
@assignment Lab 10.2
@date 11/12/2020
*/

#include "earth_utils.h"

/*
@brief Parses the CSV file
@date 11/12/2020
@return int records - the amount of records in the csv file
@param inFile - the csv file
@param kmlFileName - The name of the kml file we are writing to 
*/
int processCSV(ifstream& inFile, string kmlFileName){
    
    int records = 0;
    string strCountry, strCapital, strLat, strLong, strLine;

    if(inFile){
        ofstream fout;
        fout.open(kmlFileName);
        if(fout.is_open()){
            getline(inFile, strLine);
            fout << KML_HEADER1 << endl;
            fout << KML_HEADER2 << endl;
            fout << KML_DOC_START << endl;
            while(getline(inFile, strLine)){
                stringstream ss;
                ss << strLine;
                getline(ss, strCountry, ',');
                getline(ss, strCapital, ',');
                getline(ss, strLat, ',');
                getline(ss, strLong, ',');
                cout << strCountry << "~" << strCapital << "~" << strLat << "~" << strLong << endl;
                writePlacemark(fout, strCapital + ", " + strCountry, strLong, strLat);
                records++;
            }
            fout << KML_DOC_END << endl;
            fout << KML_FOOTER << endl;
            return records;
        }
        else{
            cout << "Could not open " << kmlFileName << endl;
            return 0;
        }
        fout.close();
    }
    else{
        return 0;
    }
}

/*
@brief Outputs to kml file
@date 11/12/2020
@param kmlFile - output to the kml file
@param string name - capital, country
@param string latitude - the latitude of the city
@param string longitude - the longitude of the city
@param string elevation - the elevation of the city
*/
void writePlacemark(ofstream& kmlFile, string name, string latitude, string longitude){
    kmlFile << "<Placemark>\n";
    kmlFile << "<name>" << name << "</name>" << endl;
    kmlFile << "<Point><coordinates>" << latitude << "," << longitude << "</coordinates></Point>\n";
    kmlFile << "</Placemark>\n";
}