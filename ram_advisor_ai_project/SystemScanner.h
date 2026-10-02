// SystemScanner.h
// TCS302 Unit 4: Hash table, hash functions, collision resolution (motherboard -> max RAM lookup)
// TCS307 Unit 1: structs via classes, pointers
// TCS307 Unit 2: operator<< overloading for report printing
#ifndef SYSTEMSCANNER_H
#define SYSTEMSCANNER_H

#include "RAMModule.h"
#include <unordered_map>
#include <list>
#include <vector>
#include <iostream>

// A snapshot of the whole system's current RAM configuration.
struct SystemProfile {
    std::string motherboardModel;
    int installedCapacityGB;
    std::string ramType;
    int speedMHz;
    int totalSlots;
    int usedSlots;
    int supportedMaxGB;

    friend std::ostream& operator<<(std::ostream& os, const SystemProfile& p) {
        os << "--- System Profile ---\n"
           << "Motherboard      : " << p.motherboardModel << "\n"
           << "Installed RAM    : " << p.installedCapacityGB << " GB (" << p.ramType << " @" << p.speedMHz << "MHz)\n"
           << "Slots            : " << p.usedSlots << "/" << p.totalSlots << " used\n"
           << "Supported Max    : " << p.supportedMaxGB << " GB\n";
        return os;
    }
};

// ---- Hand-built hash table: motherboard model -> max supported RAM (GB) ----
// Implemented on top of std::unordered_map, which itself uses separate
// chaining (std::list buckets) for collision resolution -- we demonstrate
// the concept explicitly with our own bucket array below as well.
class MotherboardLimitTable {
private:
    static const int BUCKET_COUNT = 16;
    std::vector<std::list<std::pair<std::string, int>>> buckets;   // separate chaining

    int hashFunction(const std::string& key) const {
        unsigned long h = 0;
        for (char c : key) h = h * 31 + static_cast<unsigned char>(c);
        return static_cast<int>(h % BUCKET_COUNT);
    }

public:
    MotherboardLimitTable() : buckets(BUCKET_COUNT) {}

    void insert(const std::string& model, int maxGB) {
        int idx = hashFunction(model);
        for (auto& kv : buckets[idx]) {
            if (kv.first == model) { kv.second = maxGB; return; }   // update
        }
        buckets[idx].push_back({model, maxGB});   // collision -> chained in same bucket
    }

    // O(1) average-case lookup
    int lookup(const std::string& model) const {
        int idx = hashFunction(model);
        for (const auto& kv : buckets[idx])
            if (kv.first == model) return kv.second;
        return -1;   // unknown motherboard
    }
};

// ---- Scans / builds the system's RAM + motherboard picture ----
class SystemScanner {
private:
    MotherboardLimitTable limitTable;

public:
    SystemScanner() {
        // Seed the hash table with a small catalog of known motherboards
        limitTable.insert("Gigabyte B450M", 32);
        limitTable.insert("ASUS ROG STRIX Z690", 128);
        limitTable.insert("MSI B550 TOMAHAWK", 128);
        limitTable.insert("ASRock A320M", 32);
        limitTable.insert("ASUS TUF X570", 64);
    }

    // Pass by const reference (TCS307 Unit 1: argument passing by reference, avoids copies)
    SystemProfile scan(const Motherboard& mb) const {
        SystemProfile profile;
        profile.motherboardModel = mb.getModel();
        profile.installedCapacityGB = mb.getUsedSlots() * 8;   // simplified: assume 8GB sticks installed
        profile.ramType = mb.getSupportedType();
        profile.speedMHz = 3200;
        profile.totalSlots = mb.getTotalSlots();
        profile.usedSlots = mb.getUsedSlots();

        int max = limitTable.lookup(mb.getModel());
        profile.supportedMaxGB = (max == -1) ? mb.getMaxSupportedGB() : max;
        return profile;
    }
};

#endif
