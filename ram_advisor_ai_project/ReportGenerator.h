// ReportGenerator.h
// TCS307 Unit 5: File streams (fstream), file handling operations, STL (vector, map)
// TCS307 Unit 2: operator<< overloading used when printing the report
#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "SystemScanner.h"
#include "DecisionEngine.h"
#include "UpgradeGraph.h"

struct FinalReport {
    SystemProfile profile;
    double avgUsagePercent;
    UsageClass usageClass;
    int aiTargetGB;
    bool feasible;
    std::string feasibilityReason;
    UpgradeGraph::PathResult optimizerPath;

    friend std::ostream& operator<<(std::ostream& os, const FinalReport& r) {
        os << r.profile;
        os << "Usage Profile    : avg " << r.avgUsagePercent << "% -> " << usageClassName(r.usageClass) << "\n";
        os << "AI Target        : " << r.aiTargetGB << " GB\n";
        os << "Feasibility      : " << (r.feasible ? "Supported" : "Unsupported") << " -- " << r.feasibilityReason << "\n";
        if (r.feasible && r.optimizerPath.reachable) {
            os << "Optimizer Path   : ";
            for (size_t i = 0; i < r.optimizerPath.path.size(); ++i) {
                os << r.optimizerPath.path[i];
                if (i + 1 < r.optimizerPath.path.size()) os << " -> ";
            }
            os << "  (total cost $" << r.optimizerPath.totalCost << ")\n";
        } else if (r.feasible) {
            os << "Optimizer Path   : no reachable path within slot/budget constraints\n";
        }
        return os;
    }
};

class ReportGenerator {
public:
    void printToConsole(const FinalReport& report) const {
        std::cout << report;
    }

    // File I/O: export the recommendation report as a text file (TCS307 Unit 5: fstream)
    void exportToFile(const FinalReport& report, const std::string& filename) const {
        std::ofstream out(filename);
        if (!out.is_open()) {
            std::cerr << "Could not open file for writing: " << filename << "\n";
            return;
        }
        out << report;
        out.close();
    }
};

#endif
