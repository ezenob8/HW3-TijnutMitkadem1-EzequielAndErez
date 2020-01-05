//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#ifndef EX3_ISBIGGER_H
#define EX3_ISBIGGER_H


#include "BooleanOperator.h"

class IsBigger : public BooleanOperator {

    double calculate() override;

    ~IsBigger() override;

public:
    IsBigger(Expression *expression1, Expression *expression2);
};

#endif //EX3_ISBIGGER_H
