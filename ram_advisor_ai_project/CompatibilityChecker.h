// CompatibilityChecker.h
// TCS307 Unit 4: polymorphic evaluation via base-class pointers/references
// TCS307 Unit 5: throwing InfeasibleUpgradeException on hard-constraint failure
// TCS302 Unit 4: (feeds into) searching/sorting of resulting feasible options
#ifndef COMPATIBILITYCHECKER_H
#define COMPATIBILITYCHECKER_H

#include "CompatibilityRule.h"
#include "Exceptions.h"
#include <vector>
#include <memory>
#include <string>

struct FeasibilityResult {
    bool feasible;
    std::string reason;
};

class CompatibilityChecker {
private:
    std::vector<std::unique_ptr<CompatibilityRule>> rules;   // polymorphic collection

public:
    CompatibilityChecker() {
        rules.push_back(std::make_unique<CapacityRule>());
        rules.push_back(std::make_unique<SlotRule>());
        rules.push_back(std::make_unique<SpeedRule>());
    }

    // Step 4-6 of the feasibility logic in the project brief.
    // Throws InfeasibleUpgradeException when a hard constraint fails.
    FeasibilityResult check(const SystemProfile& profile, const RAMModule& proposed, int addedGB) const {
        for (const auto& rule : rules) {
            if (!rule->evaluate(profile, proposed, addedGB)) {
                std::string reason = "Failed " + rule->ruleName() + ": ";
                if (rule->ruleName() == "CapacityRule")
                    reason += "resulting capacity (" + std::to_string(profile.installedCapacityGB + addedGB) +
                              "GB) would exceed supported limit (" + std::to_string(profile.supportedMaxGB) + "GB)";
                else if (rule->ruleName() == "SlotRule")
                    reason += "no free physical slots available";
                else
                    reason += "RAM type mismatch (" + proposed.getType() + " vs " + profile.ramType + ")";

                throw InfeasibleUpgradeException(reason);
            }
        }
        return {true, "All compatibility rules satisfied"};
    }
};

#endif
