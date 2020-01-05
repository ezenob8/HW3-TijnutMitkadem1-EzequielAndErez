//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#ifndef EX3_BOOLEANOPERATOR_H
#define EX3_BOOLEANOPERATOR_H

#include "Expression.h"

class BooleanOperator: public Expression  {
protected:
    Expression *left;
    Expression *right;
public:
    BooleanOperator(Expression* expression1, Expression* expression2);
    virtual ~BooleanOperator() override {} ;

};


#endif //EX3_BOOLEANOPERATOR_H
