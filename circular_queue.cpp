#include "circular_queue.h"
#include <iostream>
#include <iomanip>

using namespace std;

CircularQueue::CircularQueue() {
    front = -1;
    rear = -1;
    count = 0;
}

bool CircularQueue::isFull() const {
    return count == QUEUE_CAPACITY;
}

bool CircularQueue::isEmpty() const {
    return count == 0;
}

int CircularQueue::size() const {
    return count;
}

int CircularQueue::capacity() const {
    return QUEUE_CAPACITY;
}

void CircularQueue::enqueue(int timeStep, int usedMB, int totalMB) {
    ram snap;
    snap.timestamp = timeStep;
    snap.usedRAM_MB = usedMB;
    snap.totalRAM_MB = totalMB;
    snap.usagePercent = (totalMB > 0) ? ((float)usedMB / totalMB * 100.0f) : 0.0f;

    if (isEmpty()) {
        front = 0;
        rear = 0;
        buffer[rear] = snap;
        count = 1;
    } else if (isFull()) {
        // Rolling Window: Overwrite the oldest element
        // Advance both front and rear circularly using modulo
        front = (front + 1) % QUEUE_CAPACITY;
        rear = (rear + 1) % QUEUE_CAPACITY;
        buffer[rear] = snap;
    } else {
        // Standard enqueue
        rear = (rear + 1) % QUEUE_CAPACITY;
        buffer[rear] = snap;
        count++;
    }
}

bool CircularQueue::dequeue(ram& outSnapshot) {
    if (isEmpty()) {
        return false;
    }

    outSnapshot = buffer[front];

    if (front == rear) {
        // Queue becomes empty after removing the only element
        front = -1;
        rear = -1;
        count = 0;
    } else {
        front = (front + 1) % QUEUE_CAPACITY;
        count--;
    }

    return true;
}

bool CircularQueue::peekLatest(ram& outSnapshot) const {
    if (isEmpty()) {
        return false;
    }
    outSnapshot = buffer[rear];
    return true;
}

void CircularQueue::displayHistory() const {
    if (isEmpty()) {
        cout << "  [!] Circular Queue is empty. No snapshots recorded yet.\n";
        return;
    }

    cout << "\n  --- TELEMETRY SNAPSHOT HISTORY (Circular Queue: " 
         << count << "/" << QUEUE_CAPACITY << ") ---\n";
    cout << "  " << left << setw(10) << "Time"
         << setw(16) << "Used (MB)"
         << setw(16) << "Total (MB)"
         << setw(12) << "Usage %"
         << "Visual Gauge\n";
    cout << "  --------------------------------------------------------------------\n";

    int idx = front;
    for (int i = 0; i < count; i++) {
        const ram& s = buffer[idx];
        cout << "  t = " << left << setw(6) << s.timestamp
             << setw(16) << s.usedRAM_MB
             << setw(16) << s.totalRAM_MB
             << fixed << setprecision(1) << setw(10) << s.usagePercent << "%  ";

        // Visual mini-bar (up to 15 blocks)
        int barLength = (int)(s.usagePercent / 6.66f);
        cout << "[";
        for (int b = 0; b < 15; b++) {
            if (b < barLength) cout << "#";
            else cout << "-";
        }
        cout << "]\n";

        idx = (idx + 1) % QUEUE_CAPACITY;
    }
}
