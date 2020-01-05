//
// Created by erez on 06/11/2019.
//

#ifndef EX1_CPP_UMINUS_H
#define EX1_CPP_UMINUS_H


#include "UnaryExpression.h"

class UMinus : public UnaryExpression {
public:
    UMinus(Expression *expression1);

    double calculate() override;

    ~UMinus() override;
};


#endif //EX1_CPP_UMINUS_H
