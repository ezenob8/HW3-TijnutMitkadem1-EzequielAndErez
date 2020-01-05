//
// Created by erez on 05/11/2019.
//

#ifndef EX1_CPP_VALUE_H
#define EX1_CPP_VALUE_H

#include "Expression.h"

class Value : public Expression {
private:
    double num;
public:
    Value(double val);

    double calculate() override;

    ~Value() override ;
};


#endif //EX1_CPP_VALUE_H
