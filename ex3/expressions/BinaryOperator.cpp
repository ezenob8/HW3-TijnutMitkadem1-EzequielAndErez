//
// Created by erez on 07/11/2019.
//

#include "BinaryOperator.h"

BinaryOperator::BinaryOperator(Expression* expression1, Expression* expression2) {
    this->left=expression1;
    this->right=expression2;
}
