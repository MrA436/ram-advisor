// RAMModule.h
// TCS307 Unit 3: single inheritance (Component -> RAMModule), multiple inheritance (+ Loggable)
// TCS307 Unit 2: constructors (parameterized, copy), operator overloading, friend functions
#ifndef RAMMODULE_H
#define RAMMODULE_H

#include "Component.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// RAMModule represents one installed/candidate RAM stick.
// Inherits from Component (single inheritance) and Loggable (multiple inheritance).
class RAMModule : public Component, public Loggable {
private:
    int capacityGB;
    std::string type;      // "DDR4", "DDR5" ...
    int speedMHz;
    double pricePerModule; // used for cost/optimizer ranking

public:
    // Parameterized constructor
    RAMModule(const std::string& n, int cap, const std::string& t, int speed, double price)
        : Component(n), capacityGB(cap), type(t), speedMHz(speed), pricePerModule(price) {}

    // Copy constructor (TCS307 Unit 2)
    RAMModule(const RAMModule& other)
        : Component(other.name), capacityGB(other.capacityGB), type(other.type),
          speedMHz(other.speedMHz), pricePerModule(other.pricePerModule) {}

    int getCapacity() const { return capacityGB; }
    std::string getType() const { return type; }
    int getSpeed() const { return speedMHz; }
    double getPrice() const { return pricePerModule; }

    void describe() const override {
        std::cout << "RAMModule[" << name << "] " << capacityGB << "GB " << type
                  << " @" << speedMHz << "MHz  $" << pricePerModule << "\n";
    }

    std::string logTag() const override { return "[RAM:" + name + "]"; }

    // ---- Operator overloading (TCS307 Unit 2), via friend functions ----
    // + merges two modules' capacity into a hypothetical combined module (used by usage-history windows too)
    friend RAMModule operator+(const RAMModule& a, const RAMModule& b);

    // ++ (prefix) : bump the module to the "next" standard capacity tier (8->16->32->64)
    RAMModule& operator++() {
        if (capacityGB < 64) {
            static const int tiers[] = {8, 16, 32, 64};
            for (int i = 0; i < 3; ++i)
                if (capacityGB <= tiers[i]) { capacityGB = tiers[i + 1]; break; }
        }
        return *this;
    }

    // << overload to print a module nicely (friend, TCS307 Unit 2)
    friend std::ostream& operator<<(std::ostream& os, const RAMModule& m);
};

inline RAMModule operator+(const RAMModule& a, const RAMModule& b) {
    return RAMModule(a.name + "+" + b.name, a.capacityGB + b.capacityGB,
                      a.type, std::min(a.speedMHz, b.speedMHz),
                      a.pricePerModule + b.pricePerModule);
}

inline std::ostream& operator<<(std::ostream& os, const RAMModule& m) {
    os << m.capacityGB << "GB " << m.type << " @" << m.speedMHz << "MHz ($" << m.pricePerModule << ")";
    return os;
}

// ---- Motherboard: another Component subclass (single inheritance) ----
class Motherboard : public Component {
private:
    std::string model;
    int maxSupportedGB;
    int totalSlots;
    int usedSlots;
    std::string supportedType;

public:
    Motherboard(const std::string& n, const std::string& mdl, int maxGB,
                int slots, int used, const std::string& ramType)
        : Component(n), model(mdl), maxSupportedGB(maxGB),
          totalSlots(slots), usedSlots(used), supportedType(ramType) {}

    std::string getModel() const { return model; }
    int getMaxSupportedGB() const { return maxSupportedGB; }
    int getTotalSlots() const { return totalSlots; }
    int getUsedSlots() const { return usedSlots; }
    int getFreeSlots() const { return totalSlots - usedSlots; }
    std::string getSupportedType() const { return supportedType; }

    void describe() const override {
        std::cout << "Motherboard[" << model << "] max=" << maxSupportedGB
                  << "GB slots=" << usedSlots << "/" << totalSlots
                  << " type=" << supportedType << "\n";
    }
};

#endif
