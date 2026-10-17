/*
 * Data Structures & Algorithms Mini Project
 * Title: RAM Usage Monitor
 * Description: Simulates OS memory tracking using a Circular Queue
 *              for historical snapshots and an array for the Process Table.
 */

#include <iostream>
#include <iomanip>
#include "circular_queue.h"
#include "process_table.h"

using namespace std;

// System total RAM: 4096 MB (4 GB)
const int TOTAL_RAM = 4096;

// Function to print a visual progress bar of RAM usage
void printRAMBar(float percent) {
    int barWidth = 25;
    int filled = (int)((percent / 100.0f) * barWidth);
    if (filled > barWidth) filled = barWidth;

    cout << "[";
    for (int i = 0; i < barWidth; i++) {
        if (i < filled) cout << "#";
        else cout << "-";
    }
    cout << "] " << fixed << setprecision(1) << percent << "% ";

    if (percent >= 85.0f) cout << "(CRITICAL)";
    else if (percent >= 70.0f) cout << "(WARNING)";
    else cout << "(NORMAL)";
    cout << "\n";
}

int main() {
    CircularQueue queue;
    ProcessTable procTable;
    int timeStep = 1;

    // Add some default system processes at startup
    procTable.addProcess("init_daemon", 256);
    procTable.addProcess("window_server", 512);
    procTable.addProcess("file_system", 384);

    // Save initial snapshot
    int initialUsed = procTable.getTotalMemoryUsed();
    queue.enqueue(timeStep++, initialUsed, TOTAL_RAM);

    int choice = 0;
    while (true) {
        int currentUsed = procTable.getTotalMemoryUsed();
        float usagePercent = (float)currentUsed / TOTAL_RAM * 100.0f;

        cout << "\n========================================\n";
        cout << "           RAM USAGE MONITOR            \n";
        cout << "========================================\n";
        cout << "RAM: " << currentUsed << " MB / " << TOTAL_RAM << " MB  ";
        printRAMBar(usagePercent);
        cout << "----------------------------------------\n";
        cout << "1. View Active Process Table\n";
        cout << "2. Add New Process\n";
        cout << "3. Terminate Process (by PID)\n";
        cout << "4. Take Memory Snapshot\n";
        cout << "5. View Snapshot History (Circular Queue)\n";
        cout << "6. View DSA Concepts Used\n";
        cout << "7. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter your choice (1-7): ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                procTable.displayTable();
                break;
            }

            case 2: {
                char name[32];
                int mem = 0;

                cout << "\n--- Add New Process ---\n";
                cout << "Enter process name: ";
                cin >> name;
                cout << "Enter memory required (in MB): ";
                if (!(cin >> mem) || mem <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Error: Invalid memory size entered.\n";
                    break;
                }

                // Check if enough RAM is available
                if (currentUsed + mem > TOTAL_RAM) {
                    cout << "Error: Not enough free RAM available!\n";
                    break;
                }

                int newPid = procTable.addProcess(name, mem);
                if (newPid != -1) {
                    cout << "Process '" << name << "' started with PID " << newPid 
                         << " (" << mem << " MB).\n";
                    // Automatically record a snapshot after adding
                    queue.enqueue(timeStep++, procTable.getTotalMemoryUsed(), TOTAL_RAM);
                } else {
                    cout << "Error: Process table is full!\n";
                }
                break;
            }

            case 3: {
                int targetPid;
                cout << "\n--- Terminate Process ---\n";
                cout << "Enter PID to terminate: ";
                if (!(cin >> targetPid)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Error: Invalid PID entered.\n";
                    break;
                }

                char termName[32];
                int freedMem = 0;
                if (procTable.removeProcess(targetPid, termName, freedMem)) {
                    cout << "Process PID " << targetPid << " ('" << termName 
                         << "') terminated. Freed " << freedMem << " MB.\n";
                    // Automatically record snapshot after terminating
                    queue.enqueue(timeStep++, procTable.getTotalMemoryUsed(), TOTAL_RAM);
                } else {
                    cout << "Error: Process with PID " << targetPid << " not found.\n";
                }
                break;
            }

            case 4: {
                queue.enqueue(timeStep++, procTable.getTotalMemoryUsed(), TOTAL_RAM);
                cout << "Snapshot saved for time t = " << (timeStep - 1) << ".\n";
                break;
            }

            case 5: {
                queue.displayHistory();
                break;
            }

            case 6: {
                cout << "\n========================================\n";
                cout << "           DSA CONCEPTS USED            \n";
                cout << "========================================\n";
                cout << "1. Circular Queue (Array-based):\n";
                cout << "   - Uses front and rear pointers with modulo arithmetic:\n";
                cout << "     rear = (rear + 1) % CAPACITY\n";
                cout << "   - Solves the 'False Overflow' issue of simple linear queues.\n";
                cout << "   - Runs enqueue and dequeue in O(1) time.\n";
                cout << "   - When full, overwrites the oldest snapshot (sliding window).\n\n";
                cout << "2. Process Table:\n";
                cout << "   - Array of Process structs storing PID, name, and memory.\n";
                cout << "   - Computes total memory currently consumed by active processes.\n";
                cout << "========================================\n";
                break;
            }

            case 7: {
                cout << "\nExiting RAM Usage Monitor. Goodbye!\n\n";
                return 0;
            }

            default:
                cout << "Invalid choice! Please select an option between 1 and 7.\n";
                break;
        }
    }

    return 0;
}
