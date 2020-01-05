//
// Created by erez on 07/11/2019.
//

#include "Mul.h"

Mul::Mul(Expression *expression1, Expression *expression2) : BinaryOperator(expression1, expression2) {

}

double Mul::calculate() {
    return this->left->calculate() * this->right->calculate();
}


Mul::~Mul() {
    delete this->left;
    delete this->right;
}
