#include "Stack.h"

Stack::Stack(int capacity)
    : _data(0), _capacity(capacity), _top(-1) {
    if (_capacity <= 0) {
        _capacity = 1;
    }

    _data = new char[_capacity];
}

Stack::~Stack() {
    delete[] _data;
}

bool Stack::empty() const {
    return _top == -1;
}

bool Stack::full() const {
    return _top == _capacity - 1;
}

bool Stack::push(char value) {
    if (full()) {
        return false;
    }

    ++_top;
    _data[_top] = value;
    return true;
}

bool Stack::pop(char& value) {
    if (empty()) {
        return false;
    }

    value = _data[_top];
    --_top;
    return true;
}

bool Stack::top(char& value) const {
    if (empty()) {
        return false;
    }

    value = _data[_top];
    return true;
}
