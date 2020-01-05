//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#include "BooleanOperator.h"

BooleanOperator::BooleanOperator(Expression *expression1, Expression *expression2) {
    this->left=expression1;
    this->right=expression2;
}
