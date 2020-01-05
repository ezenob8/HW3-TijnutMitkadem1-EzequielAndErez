//
// Created by erez on 07/11/2019.
//

#ifndef EX1_CPP_PLUS_H
#define EX1_CPP_PLUS_H


#include "BinaryOperator.h"

class Plus : public BinaryOperator {
public:
    Plus(Expression *expression1, Expression *expression2);

    double calculate() override;

    ~Plus() override;
};


#endif //EX1_CPP_PLUS_H
