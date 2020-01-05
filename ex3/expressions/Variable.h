//
// Created by erez on 05/11/2019.
//
#ifndef EX1_CPP_VARIABLE_H
#define EX1_CPP_VARIABLE_H

#include <string>
#include "Expression.h"

using namespace std;

class Variable : public Expression{
private:
    string name;
    double value;
public:
    Variable(string theName, double theValue);
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double num1);
    Variable& operator-=(double num1);
    Variable& operator++(int num);
    Variable& operator--(int num);
    double calculate() override;
    ~Variable();
};


#endif //EX1_CPP_VARIABLE_H
