#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

const int MAX_PROCESSES = 15;

/**
 * Structure representing an operating system process.
 */
struct Process {
    int pid;             // Process ID
    char name[32];       // Process executable name
    int memoryMB;        // Allocated memory in Megabytes
    bool isActive;       // Active state flag
};

/**
 * ============================================================================
 * DATA STRUCTURE: Process Table (Array-based Directory)
 * ============================================================================
 * Maintains active running processes, assigns unique PIDs, and calculates
 * cumulative memory consumption across all active processes.
 * ============================================================================
 */
class ProcessTable {
private:
    Process table[MAX_PROCESSES];
    int count;
    int nextPID;

public:
    ProcessTable();

    int addProcess(const char* name, int memoryMB);
    bool removeProcess(int pid, char* outName, int& outFreedMB);
    int getTotalMemoryUsed() const;
    int getProcessCount() const;
    void displayTable() const;
};

#endif // PROCESS_TABLE_H
