# 📊 RAM Usage Monitor & Memory Telemetry System (C++)

![C++](https://img.shields.io/badge/Language-C%2B%2B11%20%7C%20C%2B%2B14%20%7C%20C%2B%2B17-blue.svg)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)
![Milestone](https://img.shields.io/badge/Milestone-Phase%201%20(40%25%20Completed)-orange.svg)
![DSA](https://img.shields.io/badge/DSA-Circular%20Queue%20%7C%20Array%20Table-purple.svg)

A modular, terminal-based **RAM Usage Monitor and Telemetry System** built in pure C++ demonstrating foundational Data Structures and Algorithms (DSA) without external dependencies or STL containers.

---

## 📌 Project Overview

This project simulates how an operating system monitors and tracks memory consumption across multiple active processes over time. The system employs a custom **Array-based Circular Queue** to store a rolling history of memory usage snapshots and a **Process Table** to manage process lifecycles.

---

## 🚀 Milestone 1 (40% Submission Checklist)

- [x] **Custom Array-based Circular Queue** (`circular_queue.h` / `circular_queue.cpp`)
  - Modulo arithmetic `(rear + 1) % QUEUE_CAPACITY` preventing linear queue false overflow.
  - Automatic rolling window overwrite when capacity is saturated.
  - $O(1)$ Enqueue and Dequeue operations.
- [x] **Point-in-Time Snapshot Model** (`usage_snapshot.h`)
  - Tracks timestamp, utilized MB, baseline RAM, and percentage metrics.
- [x] **Process Table Management** (`process_table.h` / `process_table.cpp`)
  - Process creation, memory quota assignment, and termination.
  - Real-time cumulative memory aggregation.
- [x] **Interactive Command-Line Interface** (`main.cpp`)
  - Menu-driven controller with real-time ASCII visual progress gauge.
- [x] **Build System** (`Makefile`)
  - Automated compilation flags (`-Wall -Wextra -std=c++11`).

---

## 🧠 Data Structures & Algorithmic Design

### 1. The Circular Queue (Rolling History Buffer)
In a conventional linear queue, dequeuing elements leaves unutilized memory at the front of the array that cannot be reused without shifting elements ($O(N)$ overhead).

Our circular queue eliminates this limitation using modular arithmetic:

```
           [0]       [1]       [2]
        ┌─────────┬─────────┬─────────┐
        │ Snapshot│ Snapshot│ Snapshot│
        │  t = 1  │  t = 2  │  t = 3  │
        └─────────┴─────────┴─────────┘
             ▲                   ▲
             │                   │
           Front                Rear
                 (Wraps Around)
```

* **Enqueue Time Complexity:** $\mathcal{O}(1)$
* **Dequeue Time Complexity:** $\mathcal{O}(1)$
* **Space Complexity:** $\mathcal{O}(K)$ where $K = 8$ (fixed buffer size)

---

## 🛠️ Build and Execution Instructions

### Prerequisites
* A standard C++ compiler (`g++`, `clang++`, or MinGW) supporting C++11 or higher.
* `make` utility.

### 1. Compile the Project
```bash
make
```

### 2. Run the Program
```bash
make run
# or directly:
./ram_monitor
```

### 3. Clean Build Artifacts
```bash
make clean
```

---

## 🗺️ Project Roadmap

- [x] **Phase 1 (40%):** Core DSA, Circular Queue telemetry, Process Table, and basic CLI.
- [ ] **Phase 2 (70%):** Dynamic Memory Partitions via **Singly Linked List**, First-Fit allocation, and **Coalescing** (adjacent block merging) to resolve external fragmentation.
- [ ] **Phase 3 (100%):** OS Hardware system bindings (`sysctl`), custom **Bubble Sort** for process ranking, and complete threshold alert engine.

---

## 👤 Author
* **College Course:** Data Structures & Algorithms / Operating Systems (2nd Year)
* **Language:** C++
