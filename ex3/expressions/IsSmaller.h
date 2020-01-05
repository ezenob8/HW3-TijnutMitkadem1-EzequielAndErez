//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#ifndef EX3_ISSMALLER_H
#define EX3_ISSMALLER_H


#include "BooleanOperator.h"

class IsSmaller : public BooleanOperator {

    double calculate() override;

    ~IsSmaller() override;

public:
    IsSmaller(Expression *expression1, Expression *expression2);
};


#endif //EX3_ISSMALLER_H
