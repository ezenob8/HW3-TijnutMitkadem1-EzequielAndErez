//
// Created by erez on 07/11/2019.
//

#ifndef EX1_CPP_MINUS_H
#define EX1_CPP_MINUS_H


#include "Expression.h"
#include "BinaryOperator.h"

class Minus : public BinaryOperator {
public:
    Minus(Expression *expression1, Expression *expression2);

    double calculate() override;

    ~Minus() override;
};


#endif //EX1_CPP_MINUS_H
