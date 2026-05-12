#include "CircularQueue.h"

#include <stdexcept>

CircularQueue::CircularQueue(int capacity)
    : _data(0), _capacity(capacity), _front(0), _rear(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("capacity must be greater than 0");
    }

    _data = new char[_capacity + 1];
}

CircularQueue::~CircularQueue() {
    delete[] _data;
}

bool CircularQueue::empty() const {
    return _front == _rear;
}

bool CircularQueue::full() const {
    return (_rear + 1) % (_capacity + 1) == _front;
}

int CircularQueue::size() const {
    return (_rear - _front + _capacity + 1) % (_capacity + 1);
}

int CircularQueue::capacity() const {
    return _capacity;
}

bool CircularQueue::enqueue(char value) {
    if (full()) {
        return false;
    }

    _data[_rear] = value;
    _rear = (_rear + 1) % (_capacity + 1);
    return true;
}

bool CircularQueue::dequeue(char& value) {
    if (empty()) {
        return false;
    }

    value = _data[_front];
    _front = (_front + 1) % (_capacity + 1);
    return true;
}

bool CircularQueue::front(char& value) const {
    if (empty()) {
        return false;
    }

    value = _data[_front];
    return true;
}

void CircularQueue::clear() {
    _front = 0;
    _rear = 0;
}
