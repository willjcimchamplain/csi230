/*
@file finals.cpp
@brief Formats temperature information from a txt file into an html file to work with google charts api
@author Will Im
@credit https://www.youtube.com/watch?v=yv_WdDWEr90
@credit boost.timer: https://theboostcpplibraries.com/boost.timer
@assignment Final
@date 12/14/2020
*/

#include "final.h"

/*
@brief Places information from the input file into the proper vectors to be referenced later on in the program
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fin - the txt file
@param x, y - Vectors that we are writing our information to, they will be referenced later on
*/
bool inputFile(ifstream&fin, vector<string> &x, vector<double> &y){
    string tmpStr;
    double tmpDouble;

    if(fin){
        while(!fin.eof()){
            getline(fin, tmpStr, '\t');
            fin >> tmpDouble;
            x.push_back(tmpStr);
            y.push_back(tmpDouble);
        }
        return true;
    }
    else{
        return false;
    }
}

/*
@brief Formats the data into an html file that displays all of the data across all years and months in the file
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fout - total.html
@param x, y - Vectors that we are recieving information from 
*/
bool outputFileFull(ofstream&fout, vector<string>&x, vector<double> &y){
    if (fout){
        // Outputs the header information for the html file
        for (int i = 0; i < HEADER_SIZE; i++){
            fout << HEADER[i];
        }

        // Continues header info specific to the graph type
        fout << "\t\t\t\t\tvar wrapper = new google.visualization.ChartWrapper({\n";
        fout << "\t\t\t\t\t\tchartType: 'LineChart',\n";
        fout << "\t\t\t\t\t\tdataTable: [\n";
        fout << "\t\t\t\t\t\t\t['Date', 'Temp (Celcius)'],\n";

        for (int i = 0; i < x.size(); i++){ // Outputs all of the information from the vectors, formatted properly
            if (i == 0){
                fout << "['" << x[i].substr(0,7) << "', " << y[i] << "]," << endl;
            }
            else{
                fout << "['" << x[i].substr(2,7) << "', " << y[i] << "]," << endl;
            }
        }
        // Outputs footer info specific to the graph type
        fout << "\t\t\t\t\t\t], options: {'title': 'Temperatures by month since 1950'},\n";
        fout << "\t\t\t\t\t\t containerId: 'visualization_div'\n";
        fout << "\t\t\t\t\t});\n";
        fout << "\t\t\t\t\twrapper.draw();\n";
        fout << "\t\t\t\t}\n";

        // Outputs footer information
        for (int i = 0; i < FOOTER_SIZE; i++){
            fout << FOOTER[i];
        }

        return true;
    }
    else{
        return false;
    }
}

/*
@brief Formats the data into an html file that displays average data per month, tracked since 1950
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fout - avg.html
@param x, y - Vectors that we are recieving information from 
*/
bool outputFileAvg(ofstream&fout, vector<string>&x, vector<double> &y){
    double arr[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    string tmp;

    if (fout){
        for (int i = 0; i < x.size(); i++){ // Sorts the data by month
            tmp = x[i].substr(7,2);

            if (tmp == "01"){
                arr[0] = arr[0] + y[i];
            }
            else if(tmp == "02"){
                arr[1] = arr[1] + y[i];
            }
            else if(tmp == "03"){
                arr[2] = arr[2] + y[i];
            }
            else if(tmp == "04"){
                arr[3] = arr[3] + y[i];
            }
            else if (tmp == "05"){
                arr[4] = arr[4] + y[i];
            }
            else if (tmp == "06"){
                arr[5] = arr[5] + y[i];
            }
            else if (tmp == "07"){
                arr[6] = arr[6] + y[i];
            }
            else if (tmp == "08"){
                arr[7] = arr[7] + y[i];
            }
            else if (tmp == "09"){
                arr[8] = arr[8] + y[i];
            }
            else if (tmp == "10"){
                arr[9] = arr[9] + y[i];
            }
            else if (tmp == "11"){
                arr[10] = arr[10] + y[i];
            }
            else if (tmp == "12"){
                arr[11] = arr[11] + y[i];
            }
            else{
                cout << "Invalid Date\n";
            }
        }
        
        int divisor = x.size() / 12;

        for (int i = 0; i < 12; i++){ // Gets the average for each month
            arr[i] = arr[i] / divisor;
        } 

        // Header info
        for (int i = 0; i < HEADER_SIZE; i++){
            fout << HEADER[i];
        }
        fout << "\t\t\t\t\tvar wrapper = new google.visualization.ChartWrapper({\n";
        fout << "\t\t\t\t\t\tchartType: 'ColumnChart',\n";
        fout << "\t\t\t\t\t\tdataTable: [\n";
        fout << "\t\t\t\t\t\t\t['Month', 'Temp (Celcius)'],\n";

        // Outputs data 
        for (int i = 0; i < 12; i++){
            fout << "['" << MONTHS[i] << "', " << arr[i] << "]," << endl;
        }   

        // Footer info
        fout << "\t\t\t\t\t\t], options: {'title': 'Average Temperatures by Month'},\n";
        fout << "\t\t\t\t\t\t containerId: 'visualization_div'\n";
        fout << "\t\t\t\t\t});\n";
        fout << "\t\t\t\t\twrapper.draw();\n";
        fout << "\t\t\t\t}\n";
        for (int i = 0; i < FOOTER_SIZE; i++){
            fout << FOOTER[i];
        }

        fout << endl;
        return true;
    }
    else{
        return false;
    }
}

/*
@brief Formats the data into an html file that displays highest temperature data per month since 1950
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fout - high.html
@param x, y - Vectors that we are recieving information from 
*/
bool outputFileHigh(ofstream&fout, vector<string>&x, vector<double> &y){
    string tmp;
    double arr[12] = {-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100}; // Initializes array low so that we don't get stuck on a certain degree

    for (int i = 0; i < x.size(); i++){ // Sorts data by month
        tmp = x[i].substr(7,2);
        
        if (tmp == "01"){
            if (arr[0] < y[i]){
                arr[0] = y[i];
            }
        }
        else if(tmp == "02"){
            if (arr[1] < y[i]){
                arr[1] = y[i];
            }
        }
        else if(tmp == "03"){
            if (arr[2] < y[i]){
                arr[2] = y[i];
            }
        }
        else if(tmp == "04"){
            if (arr[3] < y[i]){
                arr[3] = y[i];
            }
        }
        else if (tmp == "05"){
            if (arr[4] < y[i]){
                arr[4] = y[i];
            }
        }
        else if (tmp == "06"){
            if (arr[5] < y[i]){
                arr[5] = y[i];
            }
        }
        else if (tmp == "07"){
            if (arr[6] < y[i]){
                arr[6] = y[i];
            }
        }
        else if (tmp == "08"){
            if (arr[7] < y[i]){
                arr[7] = y[i];
            }
        }
        else if (tmp == "09"){
            if (arr[8] < y[i]){
                arr[8] = y[i];
            }
        }
        else if (tmp == "10"){
            if (arr[9] < y[i]){
                arr[9] = y[i];
            }
        }
        else if (tmp == "11"){
            if (arr[10] < y[i]){
                arr[10] = y[i];
            }
        }
        else if (tmp == "12"){
            if (arr[11] < y[i]){
                arr[11] = y[i];
            }
        }
        else{
            cout << "Invalid Date\n";
        }
    }

    if (fout){
        // Header information
        for (int i = 0; i < HEADER_SIZE; i++){
            fout << HEADER[i];
        }
        fout << "\t\t\t\t\tvar wrapper = new google.visualization.ChartWrapper({\n";
        fout << "\t\t\t\t\t\tchartType: 'ColumnChart',\n";
        fout << "\t\t\t\t\t\tdataTable: [\n";
        fout << "\t\t\t\t\t\t\t['Month', 'Temp (Celcius)'],\n";

        // Outputs data
        for (int i = 0; i < 12; i++){
            fout << "\t\t\t\t\t\t\t['" << MONTHS[i] << "', " << arr[i] << "],\n";
        }
        
        // Footer information
        fout << "\t\t\t\t\t\t], options: {'title': 'Highest Temperatures by Month'},\n";
        fout << "\t\t\t\t\t\t containerId: 'visualization_div'\n";
        fout << "\t\t\t\t\t});\n";
        fout << "\t\t\t\t\twrapper.draw();\n";
        fout << "\t\t\t\t}\n";
        for (int i = 0; i < FOOTER_SIZE; i++){
            fout << FOOTER[i];
        }

        fout << endl;

        return true;
    }
    else{
        return false;
    }
}

/*
@brief Formats the data into an html file that displays lowest temperature data per month since 1950
@date 12/14/2020
@return boolean of true or false based on success of the function
@param fout - low.html
@param x, y - Vectors that we are recieving information from 
*/
bool outputFileLow(ofstream&fout, vector<string>&x, vector<double> &y){
    string tmp;
    double arr[12] = {100,100,100,100,100,100,100,100,100,100,100,100}; // Initializes the array high so we don't get stuck

    for (int i = 0; i < x.size(); i++){ // Sorts the data by months
        tmp = x[i].substr(7,2);
        

        if (tmp == "01"){
            if (arr[0] > y[i]){
                arr[0] = y[i];
            }
        }
        else if(tmp == "02"){
            if (arr[1] > y[i]){
                arr[1] = y[i];
            }
        }
        else if(tmp == "03"){
            if (arr[2] > y[i]){
                arr[2] = y[i];
            }
        }
        else if(tmp == "04"){
            if (arr[3] > y[i]){
                arr[3] = y[i];
            }
        }
        else if (tmp == "05"){
            if (arr[4] > y[i]){
                arr[4] = y[i];
            }
        }
        else if (tmp == "06"){
            if (arr[5] > y[i]){
                arr[5] = y[i];
            }
        }
        else if (tmp == "07"){
            if (arr[6] > y[i]){
                arr[6] = y[i];
            }
        }
        else if (tmp == "08"){
            if (arr[7] > y[i]){
                arr[7] = y[i];
            }
        }
        else if (tmp == "09"){
            if (arr[8] > y[i]){
                arr[8] = y[i];
            }
        }
        else if (tmp == "10"){
            if (arr[9] > y[i]){
                arr[9] = y[i];
            }
        }
        else if (tmp == "11"){
            if (arr[10] > y[i]){
                arr[10] = y[i];
            }
        }
        else if (tmp == "12"){
            if (arr[11] > y[i]){
                arr[11] = y[i];
            }
        }
        else{
            cout << "Invalid Date\n";
        }
    }

    if (fout){
        // Header 
        for (int i = 0; i < HEADER_SIZE; i++){
            fout << HEADER[i];
        }
        fout << "\t\t\t\t\tvar wrapper = new google.visualization.ChartWrapper({\n";
        fout << "\t\t\t\t\t\tchartType: 'ColumnChart',\n";
        fout << "\t\t\t\t\t\tdataTable: [\n";
        fout << "\t\t\t\t\t\t\t['Month', 'Temp (Celcius)'],\n";

        // Outputs data
        for (int i = 0; i < 12; i++){
            fout << "['" << MONTHS[i] << "', " << arr[i] << "],\n";
        }

        // Footer
        fout << "\t\t\t\t\t\t], options: {'title': 'Lowest Temperatures by Month'},\n";
        fout << "\t\t\t\t\t\tcontainerId: 'visualization_div'\n";
        fout << "\t\t\t\t\t});\n";
        fout << "\t\t\t\t\twrapper.draw();\n";
        fout << "\t\t\t\t}\n";
        for (int i = 0; i < FOOTER_SIZE; i++){
            fout << FOOTER[i];
        }

        fout << endl;

        return true;
    }
    else{
        return false;
    }
}