/*
@file stubb.cpp
@brief main function for the program 
@author Will Im
@assignment Final Project
@date 12/14/2020
*/

#include "logger.h"
#include "final.h"

/*
@brief Error checks the program and runs necessary functions given a lack of errors
@date 12/14/2020
@return either success or error bool
@param int argc - the character indicating which argument is being called
@param char** argv - the argument passed with function call
@param char* env[] - information from the linux environment we are in 
*/
int main(int argc, char** argv, char* env[]){
    // Initializes necessary variables
    int opt;
    bool checkTxt = false;
    bool checkLog = false;
    bool checkError = true;
    string txtFile;
    string logFile;

    // Gets file names from the user
    while ((opt = getopt(argc, argv, "t:l:")) != EOF){
        switch(opt){
            case 't':
                checkTxt = true;
                txtFile = optarg; 
                break;
            case 'l':
                checkLog = true;
                logFile = optarg;
                break;
            default:
                checkError = true;
                break;
        }
    }

    if (checkTxt && checkLog){
        cout << "Flags set\n";
        if (txtFile.empty() || logFile.empty()){
            checkError = true;
            cout << "Input error: Empty files!\n";
        }
        else{
            // Opens logging file
            ofstream foutLog;
            foutLog.open(logFile, ios_base::app);
            if(foutLog){
                // Logs data
                string programName = basename(argv[0]);
                string msg = "Txt File: " + txtFile + " Log File: " + logFile;
                log(msg, foutLog, programName);
                checkError = false;
                
                // Initializes vectors
                vector<string> x;
                vector<double> y;

                // Recieves input from the txt file into the vectors
                ifstream fin;
                fin.open(txtFile);
                if(fin){
                    bool checkInput = inputFile(fin, x, y);
                    fin.close();
                    if(checkInput){
                        checkError = false; 
                    }
                    else{
                        checkError = true;
                    }
                    
                    // Timer function to keep track of time it takes to create the various files
                    boost::timer::cpu_timer timer;
                    msg = "Beginning Processing Files: " + timer.format();
                    log(msg, foutLog, programName);

                    boost::timer::cpu_timer timer_high;
                    msg = "Beginning Processing High File: " + timer_high.format();
                    log(msg, foutLog, programName);

                    // Opens a new file output stream
                    ofstream foutHigh;
                    foutHigh.open(HTML_FILE_HIGH, ios_base::app);
                    if(foutHigh){
                        bool checkOutputHigh = outputFileHigh(foutHigh, x, y);
                        if(checkOutputHigh){
                            checkError = false;
                        }
                        else{
                            checkError = true;
                        }
                    }
                    foutHigh.close();

                    timer_high.stop();
                    msg = "Finished Processing High File: " + timer_high.format();
                    log(msg, foutLog, programName);

                    boost::timer::cpu_timer timer_low;
                    msg = "Beginning Processing Low File: " + timer_low.format();
                    log(msg, foutLog, programName);

                    ofstream foutLow;
                    foutLow.open(HTML_FILE_LOW, ios_base::app);
                    if(foutLow){
                        bool checkOutputLow = outputFileLow(foutLow, x, y);
                        if(checkOutputLow){
                            checkError = false;
                        }
                        else{
                            checkError = true;
                        }
                    }
                    foutLow.close();

                    timer_low.stop();
                    msg = "Finished Processing Low File: " + timer_low.format();
                    log(msg, foutLog, programName);

                    boost::timer::cpu_timer timer_full;
                    msg = "Beginning Processing Full Data File: " + timer_full.format();
                    log(msg, foutLog, programName);

                    ofstream foutFull;
                    foutFull.open(HTML_FILE_FULL, ios_base::app);
                    if (foutFull){
                        bool checkOutputFull = outputFileFull(foutFull, x, y);
                        if (checkOutputFull){
                            checkError = false;
                        }
                        else{
                            checkError = true;
                        }
                    }
                    foutFull.close();

                    timer_full.stop();
                    msg = "Finished Processing Full Data File: " + timer_full.format();
                    log(msg, foutLog, programName);

                    boost::timer::cpu_timer timer_avg;
                    msg = "Beginning Processing Full Avg File: " + timer_avg.format();
                    log(msg, foutLog, programName);

                    ofstream foutAvg;
                    foutAvg.open(HTML_FILE_AVG, ios_base::app);
                    if(foutAvg){
                        bool checkOutputAvg = outputFileFull(foutFull, x, y);
                        if(checkOutputAvg){
                            checkError = false;
                        }
                        else{
                            checkError = true;
                        }
                    }
                    
                    foutAvg.close();

                    timer_full.stop();
                    msg = "Finished Processing Avg File: " + timer_avg.format();
                    log(msg, foutLog, programName);
                    
                    timer.stop();
                    msg = "Finished Processing Files: " + timer.format();
                    log(msg, foutLog, programName);
                    
                }
                else{
                    checkError = true;
                }
                foutLog.close();
            }
            else{
                cout << "Could not open: " << logFile << endl;
                checkError = true;
            }
        }
    }
    else{
        cout << "Error - Flags are not set\n";
        checkError = true;
    }

    if (checkError){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}