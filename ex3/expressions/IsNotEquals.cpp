//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#include "IsNotEquals.h"
#include "Expression.h"

IsNotEquals::IsNotEquals(Expression *expression1, Expression *expression2) : BooleanOperator(expression1, expression2) {

}

double IsNotEquals::calculate() {
    if(this->left->calculate() != this->right->calculate()){
        return 1;
    }
    return 0;
}


IsNotEquals::~IsNotEquals() {
    delete this->left;
    delete this->right;
}