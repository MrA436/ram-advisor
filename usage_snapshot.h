#ifndef USAGE_SNAPSHOT_H
#define USAGE_SNAPSHOT_H

/**
 * Structure representing a point-in-time snapshot of system memory usage.
 * Used as the data element stored in the Circular Queue.
 */
struct ram {
    int timestamp;       // Relative time tick (e.g. t = 1, 2, 3...)
    int usedRAM_MB;      // Currently consumed RAM in Megabytes
    int totalRAM_MB;     // Total available system RAM in Megabytes
    float usagePercent;  // Calculated usage percentage (0.0% to 100.0%)
};

#endif // USAGE_SNAPSHOT_H
