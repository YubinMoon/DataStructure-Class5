#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

class CircularQueue {
public:
    explicit CircularQueue(int capacity);
    ~CircularQueue();

    bool empty() const;
    bool full() const;
    int size() const;
    int capacity() const;

    bool enqueue(char value);
    bool dequeue(char& value);
    bool front(char& value) const;
    void clear();

private:
    char* _data; // 데이터 저장
    int _capacity; // Queue 크기
    int _front;
    int _rear;
};

#endif
