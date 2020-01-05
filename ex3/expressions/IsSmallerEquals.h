//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#ifndef EX3_ISSMALLEREQUALS_H
#define EX3_ISSMALLEREQUALS_H


#include "BooleanOperator.h"

class IsSmallerEquals : public BooleanOperator {

    double calculate() override;

    ~IsSmallerEquals() override;

public:
    IsSmallerEquals(Expression *expression1, Expression *expression2);
};


#endif //EX3_ISSMALLEREQUALS_H
