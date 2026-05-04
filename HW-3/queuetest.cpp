#include "Queue/CircularQueue.h"

#include <iostream>
#include <string>

bool check(bool condition, const char* message) {
    if (!condition) {
        std::cout << "FAIL: " << message << '\n';
        return false;
    }

    std::cout << "PASS: " << message << '\n';
    return true;
}

std::string messageWithChar(const char* message, char value) {
    std::string result = message;
    result += ' ';
    result += value;
    return result;
}

int main() {
    CircularQueue queue(20);
    char value = '\0';
    bool passed = true;

    passed = check(queue.empty(), "new queue is empty") && passed;
    passed = check(queue.size() == 0, "new queue size is 0") && passed;
    passed = check(queue.capacity() == 20, "queue capacity is 20") && passed;

    for (char ch = 'A'; ch <= 'J'; ++ch) {
        std::string message = messageWithChar("enqueue", ch);
        passed = check(queue.enqueue(ch), message.c_str()) && passed;
    }

    passed = check(queue.front(value) && value == 'A', "front is A") && passed;
    passed = check(queue.dequeue(value) && value == 'A', "dequeue A") && passed;
    passed = check(queue.dequeue(value) && value == 'B', "dequeue B") && passed;

    for (char ch = 'K'; ch <= 'V'; ++ch) {
        std::string message = messageWithChar("enqueue", ch);
        passed = check(queue.enqueue(ch), message.c_str()) && passed;
    }

    passed = check(queue.size() == 20, "queue size is 20") && passed;
    passed = check(queue.full(), "queue is full with 20 alphabets") && passed;
    passed = check(!queue.enqueue('W'), "enqueue fails when queue is full") && passed;

    for (char ch = 'C'; ch <= 'V'; ++ch) {
        std::string message = messageWithChar("dequeue", ch);
        passed = check(queue.dequeue(value) && value == ch, message.c_str()) && passed;
    }

    passed = check(queue.empty(), "queue is empty after dequeue all") && passed;
    passed = check(!queue.dequeue(value), "dequeue fails when queue is empty") && passed;

    queue.enqueue('Z');
    queue.clear();
    passed = check(queue.empty(), "clear makes queue empty") && passed;

    if (passed) {
        std::cout << "All queue tests passed.\n";
        return 0;
    }

    std::cout << "Some queue tests failed.\n";
    return 1;
}
