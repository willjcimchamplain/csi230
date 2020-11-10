#include "util.h"

string randomElement(vector <string> &vectStr){
    // Gets a random number in the range of our vector
    srand(time(0));
    int i = rand() % MAX;

    return vectStr[i];
}

string camelCase(string str){
    string camel = "";

    for (int i = 0; i < str.length(); i++){
        if (i == 0){
            camel += tolower(str[i]);
        }
        else if(str[i] == ' '){
            str[i + 1] = toupper(str[i + 1]);
        }
        else{
            camel += str[i];
        }
    }
    
    return camel;
}

double sum(vector <double> &vectDoub){
    double sum = 0;

    for (int i = 0; i < MAX; i++){
        sum = sum + vectDoub[i];
    }

    return sum;
}

double avg(vector <double> &vectDoub){
    double avg = sum(vectDoub) / MAX;

    return avg;
}

double lowest(vector <double> &vectDoub){
    double lowest = vectDoub[0];

    for (int i = 0; i < MAX; i++){
        if (vectDoub[i] < lowest){
            lowest = vectDoub[i];
        }
    }

    return lowest;
}