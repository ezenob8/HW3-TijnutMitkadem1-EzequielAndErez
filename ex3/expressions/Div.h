//
// Created by erez on 07/11/2019.
//

#ifndef EX1_CPP_DIV_H
#define EX1_CPP_DIV_H


#include "BinaryOperator.h"

class Div : public BinaryOperator {
public:
    Div(Expression *expression1, Expression *expression2);
    double calculate() override;
    ~Div() override;
};


#endif //EX1_CPP_DIV_H
