#ifndef STACK_H
#define STACK_H

class Stack {
public:
    explicit Stack(int capacity);
    ~Stack();

    bool empty() const;
    bool full() const;
    bool push(char value);
    bool pop(char& value);
    bool top(char& value) const;

private:
    char* _data;
    int _capacity;
    int _top;
};

#endif
