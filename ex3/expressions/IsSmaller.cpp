//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#include "IsSmaller.h"
IsSmaller::IsSmaller(Expression *expression1, Expression *expression2) : BooleanOperator(expression1, expression2) {

}

double IsSmaller::calculate() {
    if(this->left->calculate() < this->right->calculate()){
        return 1;
    }
    return 0;
}

IsSmaller::~IsSmaller() {
    delete this->left;
    delete this->right;
}