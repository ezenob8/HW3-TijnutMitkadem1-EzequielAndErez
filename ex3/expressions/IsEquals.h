//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#ifndef EX3_ISEQUALS_H
#define EX3_ISEQUALS_H


#include "BooleanOperator.h"

class IsEquals: public BooleanOperator {

    double calculate() override;

    ~IsEquals() override;

public:
    IsEquals(Expression *expression1, Expression *expression2);
};


#endif //EX3_ISEQUALS_H
