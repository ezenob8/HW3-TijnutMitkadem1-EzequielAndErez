//
// Created by erez on 07/11/2019.
//

#include "Plus.h"

Plus::Plus(Expression *expression1, Expression *expression2) : BinaryOperator(expression1, expression2) {

}

double Plus::calculate() {
    return this->left->calculate() + this->right->calculate();
}

Plus::~Plus() {
    delete this->right;
    delete this->left;
}
