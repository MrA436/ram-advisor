#include "process_table.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

ProcessTable::ProcessTable() {
    count = 0;
    nextPID = 101; // Start PID numbering at 101
    for (int i = 0; i < MAX_PROCESSES; i++) {
        table[i].pid = -1;
        table[i].name[0] = '\0';
        table[i].memoryMB = 0;
        table[i].isActive = false;
    }
}

int ProcessTable::addProcess(const char* name, int memoryMB) {
    if (count >= MAX_PROCESSES) {
        return -1; // Table full
    }

    int pid = nextPID++;
    table[count].pid = pid;
    strncpy(table[count].name, name, sizeof(table[count].name) - 1);
    table[count].name[sizeof(table[count].name) - 1] = '\0';
    table[count].memoryMB = memoryMB;
    table[count].isActive = true;
    count++;

    return pid;
}

bool ProcessTable::removeProcess(int pid, char* outName, int& outFreedMB) {
    for (int i = 0; i < count; i++) {
        if (table[i].isActive && table[i].pid == pid) {
            table[i].isActive = false;
            strncpy(outName, table[i].name, 31);
            outName[31] = '\0';
            outFreedMB = table[i].memoryMB;

            // Shift array elements left to maintain compact storage
            for (int j = i; j < count - 1; j++) {
                table[j] = table[j + 1];
            }
            count--;
            return true;
        }
    }
    return false;
}

int ProcessTable::getTotalMemoryUsed() const {
    int total = 0;
    for (int i = 0; i < count; i++) {
        if (table[i].isActive) {
            total += table[i].memoryMB;
        }
    }
    return total;
}

int ProcessTable::getProcessCount() const {
    return count;
}

void ProcessTable::displayTable() const {
    if (count == 0) {
        cout << "  [!] Process Table is empty. No active processes running.\n";
        return;
    }

    cout << "\n  --- ACTIVE PROCESS TABLE (" << count << "/" << MAX_PROCESSES << ") ---\n";
    cout << "  " << left << setw(8) << "Index"
         << setw(10) << "PID"
         << setw(26) << "Process Name"
         << setw(16) << "Memory (MB)"
         << "Status\n";
    cout << "  --------------------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << "  [" << left << setw(5) << (i + 1) << "]"
             << setw(10) << table[i].pid
             << setw(26) << table[i].name
             << setw(16) << table[i].memoryMB
             << "[RUNNING]\n";
    }
    cout << "  --------------------------------------------------------------------\n";
    cout << "  Total Process Memory Consumed: " << getTotalMemoryUsed() << " MB\n";
}
