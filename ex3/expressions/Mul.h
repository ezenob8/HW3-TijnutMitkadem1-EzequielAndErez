//
// Created by erez on 07/11/2019.
//

#ifndef EX1_CPP_MUL_H
#define EX1_CPP_MUL_H


#include "BinaryOperator.h"

class Mul: public BinaryOperator {
public:
    Mul(Expression* expression1, Expression* expression2);
    double calculate() override;
    ~Mul() override;
};


#endif //EX1_CPP_MUL_H
