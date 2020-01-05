//
// Created by erez on 05/11/2019.
//

#include "Value.h"

Value::Value(double val) : num(val) {}

double Value::calculate() {
    return this->num;
}

Value::~Value() {

}
