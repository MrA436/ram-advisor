// CircularQueue.h
// TCS302 Unit 2: Queue, circular queue (fixed-size rolling history)
// TCS307 Unit 5: Function templates
#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <vector>
#include <stdexcept>

template <typename T>
class CircularQueue {
private:
    std::vector<T> buffer;
    int capacity;
    int front, rear, count;

public:
    explicit CircularQueue(int cap)
        : buffer(cap), capacity(cap), front(0), rear(-1), count(0) {}

    bool isFull() const { return count == capacity; }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }

    // Enqueue: when full, the oldest reading is overwritten (rolling window behaviour)
    void enqueue(const T& value) {
        if (isFull()) {
            front = (front + 1) % capacity;   // drop the oldest reading
            count--;
        }
        rear = (rear + 1) % capacity;
        buffer[rear] = value;
        count++;
    }

    T dequeue() {
        if (isEmpty()) throw std::underflow_error("CircularQueue is empty");
        T value = buffer[front];
        front = (front + 1) % capacity;
        count--;
        return value;
    }

    // Return all current elements oldest -> newest, for computing statistics
    std::vector<T> toVector() const {
        std::vector<T> out;
        for (int i = 0; i < count; ++i)
            out.push_back(buffer[(front + i) % capacity]);
        return out;
    }
};

#endif
