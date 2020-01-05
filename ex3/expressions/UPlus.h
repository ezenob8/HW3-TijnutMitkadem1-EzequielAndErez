//
// Created by erez on 06/11/2019.
//

#ifndef EX1_CPP_UPLUS_H
#define EX1_CPP_UPLUS_H


#include "UnaryExpression.h"

class UPlus : public UnaryExpression {
public:
    UPlus(Expression *expression1);

    double calculate() override;

    ~UPlus() override;
};


#endif //EX1_CPP_UPLUS_H
