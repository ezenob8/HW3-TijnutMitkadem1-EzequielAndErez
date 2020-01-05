//
// Created by erez on 07/11/2019.
//

#ifndef EX1_CPP_BINARYOPERATOR_H
#define EX1_CPP_BINARYOPERATOR_H


#include "Expression.h"

class BinaryOperator : public Expression {
protected:
    Expression *left;
    Expression *right;
public:
    BinaryOperator(Expression* expression1, Expression* expression2);

    virtual ~BinaryOperator() override {} ;
};


#endif //EX1_CPP_BINARYOPERATOR_H
