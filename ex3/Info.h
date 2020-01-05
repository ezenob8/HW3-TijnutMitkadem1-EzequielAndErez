//
// Created by Erez Rigevsky and Ezequiel Glocer on 16/12/2019.
//

#ifndef EX3_INFO_H
#define EX3_INFO_H

#include "string"

using namespace std;

//includes all the information of a variable in variable command
class Info {
private:
    double value;
    string sim; //variable in the simulator
public:
    //default constructor
    Info() {

    }
    //constructor
    Info(const string &s) {
        this->sim=s;
    }

    //set the value
    void setValue(double v) {
        this->value=v;
    }

    //set the sim variabe
    void setSim(const string& v) {
        this->sim=v;
    }

    //return the value
    double getValue() {
        return this->value;
    }

    //return the sim variable
    string getSim() {
        return this->sim;
    }
};

#endif //EX3_INFO_H
