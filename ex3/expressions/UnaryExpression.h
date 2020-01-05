//
// Created by erez on 06/11/2019.
//

#ifndef EX1_CPP_UNARYEXPRESSION_H
#define EX1_CPP_UNARYEXPRESSION_H


#include "Expression.h"
#include "Variable.h"

class UnaryExpression : public Expression {
protected:
    Expression *expression;
public:
    UnaryExpression(Expression *expression1);

    virtual ~UnaryExpression() override {}
};

#endif //EX1_CPP_UNARYEXPRESSION_H
