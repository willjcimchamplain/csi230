/*
@file lab10-2.cpp
@brief main function for the program 
@author Devin Paden
@editor Will Im
@assignment Lab 10.2
@date 11/12/2020
*/

#include "logger.h"
#include "earth_utils.h"

/*
@brief Error checks the program and runs necessary functions given a lack of errors
@date 11/12/2020
@return either success or error bool
@param int argc - the character indicating which argument is being called
@param char** argv - the argument passed with function call
@param char* env[] - information from the linux environment we are in 
*/
int main(int argc, char** argv, char* env[]){
    int opt{};
    bool kmlFlag{false};
    bool logFlag{false};
    string kmlValue;
    string logValue;
    bool optErr = true;

    while ((opt = getopt(argc, argv, "k:l:")) != EOF){
        switch(opt){
            case 'k':
                kmlFlag = true;
                kmlValue = optarg; 
                break;
            case 'l':
                logFlag = true;
                logValue = optarg;
                break;
            default:
                optErr = true;
                break;
        }
    }

    cout << "Count Flag: " << kmlFlag << endl;
    cout << "Log Flag: " << logFlag << endl;

    if (kmlFlag && logFlag){
        cout << "Flags set\n";
        if (logValue.empty() || kmlValue.empty()){
            optErr = true;
            cout << "Option arguments are not set\n";
        }
        else{
            ofstream flog;
            flog.open(logValue, ios_base::app);
            if(flog){
                string programName = basename(argv[0]);
                string msg = "The KML File is: " + kmlValue + " and the Log File is: " + logValue;
                log(msg, flog, programName);
                optErr = false;
                flog.close();

                ifstream inFile;
                inFile.open(kmlValue);
                if(inFile){
                    int recordCount = processCSV(inFile, kmlValue + ".kml");
                    inFile.close();
                    if(recordCount){
                        cout << recordCount << " records processed" << endl;
                        optErr = false;
                    }
                    else{
                        optErr = true;
                    }
                }
                else{
                    optErr = true;
                }
                
            }
            else{
                cout << "Could not open: " << logValue << endl;
                optErr = true;
            }
        }
    }
    else{
        cout << "Error - Flags are not set\n";
        optErr = true;
    }

    if (optErr){
        return EXIT_FAILURE;
    }
    
    cout << "KML File: " << kmlValue << endl;
    cout << "Log File: " << logValue << endl;
    cout << "Error: " << optErr << endl;
    return EXIT_SUCCESS;
}