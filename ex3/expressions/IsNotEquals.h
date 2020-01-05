//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#ifndef EX3_ISNOTEQUALS_H
#define EX3_ISNOTEQUALS_H


#include "Expression.h"
#include "BooleanOperator.h"

class IsNotEquals: public BooleanOperator {

    double calculate() override;

    ~IsNotEquals() override;

public:
    IsNotEquals(Expression *expression1, Expression *expression2);
};


#endif //EX3_ISNOTEQUALS_H
