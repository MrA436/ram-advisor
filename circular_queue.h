#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "usage_snapshot.h"

// Maximum number of snapshots preserved in rolling telemetry history
const int QUEUE_CAPACITY = 8;

/**
 * ============================================================================
 * DATA STRUCTURE: Circular Queue (Array-based)
 * ============================================================================
 * Solves the "False Overflow" problem of linear queues.
 * Once elements are dequeued in a linear queue, freed indices at the front
 * cannot be reused without shifting elements (O(N) cost).
 * The Circular Queue wraps around using modulo arithmetic (%) in O(1) time.
 * ============================================================================
 */
class CircularQueue {
private:
    ram buffer[QUEUE_CAPACITY];
    int front;
    int rear;
    int count;

public:
    CircularQueue();

    bool isFull() const;
    bool isEmpty() const;
    int size() const;
    int capacity() const;

    // Enqueues a new snapshot; if queue is full, overwrites the oldest snapshot (rolling window)
    void enqueue(int timeStep, int usedMB, int totalMB);

    // Removes and returns the oldest snapshot
    bool dequeue(ram& outSnapshot);

    // Returns the latest snapshot without removing it
    bool peekLatest(ram& outSnapshot) const;

    // Displays the full telemetry history from oldest to newest
    void displayHistory() const;
};

#endif // CIRCULAR_QUEUE_H
