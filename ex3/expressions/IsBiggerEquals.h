//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#ifndef EX3_ISBIGGEREQUALS_H
#define EX3_ISBIGGEREQUALS_H


#include "BooleanOperator.h"

class IsBiggerEquals : public BooleanOperator {

    double calculate() override;

    ~IsBiggerEquals() override;

public:
    IsBiggerEquals(Expression *expression1, Expression *expression2);
};


#endif //EX3_ISBIGGEREQUALS_H
