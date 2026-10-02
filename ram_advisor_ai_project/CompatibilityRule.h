// CompatibilityRule.h
// TCS307 Unit 4: virtual functions, pure virtual functions, abstract classes,
//                run-time polymorphism, function overriding
#ifndef COMPATIBILITYRULE_H
#define COMPATIBILITYRULE_H

#include "RAMModule.h"
#include "SystemScanner.h"
#include <string>

// Abstract base -- an interface every concrete rule must implement.
class CompatibilityRule {
public:
    virtual bool evaluate(const SystemProfile& profile, const RAMModule& proposed, int addedGB) const = 0;
    virtual std::string ruleName() const = 0;
    virtual ~CompatibilityRule() {}
};

// Concrete rule 1: resulting capacity must not exceed the motherboard's supported max
class CapacityRule : public CompatibilityRule {
public:
    bool evaluate(const SystemProfile& profile, const RAMModule& proposed, int addedGB) const override {
        return (profile.installedCapacityGB + addedGB) <= profile.supportedMaxGB;
    }
    std::string ruleName() const override { return "CapacityRule"; }
};

// Concrete rule 2: enough free physical slots must exist
class SlotRule : public CompatibilityRule {
public:
    bool evaluate(const SystemProfile& profile, const RAMModule& proposed, int addedGB) const override {
        int freeSlots = profile.totalSlots - profile.usedSlots;
        return freeSlots >= 1;
    }
    std::string ruleName() const override { return "SlotRule"; }
};

// Concrete rule 3: RAM type must match what the motherboard supports (e.g. DDR4 vs DDR5)
class SpeedRule : public CompatibilityRule {
public:
    bool evaluate(const SystemProfile& profile, const RAMModule& proposed, int addedGB) const override {
        return proposed.getType() == profile.ramType;
    }
    std::string ruleName() const override { return "SpeedRule"; }
};

#endif
