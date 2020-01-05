//
// Created by erez on 07/11/2019.
//

#include "Minus.h"

Minus::Minus(Expression *expression1, Expression *expression2) : BinaryOperator(expression1, expression2) {

}

double Minus::calculate() {
    return this->left->calculate() - this->right->calculate();
}


Minus::~Minus() {
    delete this->right;
    delete this->left;
}