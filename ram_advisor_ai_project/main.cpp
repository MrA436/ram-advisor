// main.cpp
// RAM Advisor AI -- Final PBL Project
// Mapped to TCS302 (Data Structures with C) and TCS307 (OOP with C++)
//
// Pipeline (matches the project's data-flow diagram):
//   System Boot -> Scan (hash lookup) -> Usage Monitor (circular queue) ->
//   Compatibility Check (polymorphic rules + exceptions) -> Decision Tree (recursion) ->
//   Target capacity -> Graph shortest-path optimizer (Dijkstra) -> Final report (file I/O)

#include <iostream>
#include <vector>
#include "RAMModule.h"
#include "SystemScanner.h"
#include "UsageMonitor.h"
#include "CompatibilityChecker.h"
#include "DecisionEngine.h"
#include "CatalogBST.h"
#include "UpgradeGraph.h"
#include "ReportGenerator.h"
#include "Exceptions.h"

int main() {
    std::cout << "=====================================\n";
    std::cout << "        RAM ADVISOR AI  (PBL)         \n";
    std::cout << "=====================================\n\n";

    // ---------- Stage 1: System Scanner ----------
    Motherboard mb("MainBoard", "Gigabyte B450M", 32, /*totalSlots*/ 4, /*usedSlots*/ 1, "DDR4");
    SystemScanner scanner;
    SystemProfile profile = scanner.scan(mb);
    std::cout << profile << "\n";

    // ---------- Stage 2: Usage Monitor (circular queue) ----------
    UsageMonitor monitor(10);
    std::srand(42);
    for (int i = 0; i < 12; ++i) monitor.readUsage();      // simulated sensor readings
    monitor.readUsage(78.0);                                // one real external reading
    double avgUsage = monitor.averageUsage();
    std::cout << "Rolling average usage: " << avgUsage << "%\n\n";

    // ---------- Stage 3: AI Decision Engine (binary tree + recursion) ----------
    DecisionEngine engine;
    UsageClass usageClass = engine.classify(avgUsage);
    int targetGB = engine.recommendTargetGB(profile.installedCapacityGB, usageClass);
    std::cout << "Workload classified as: " << usageClassName(usageClass) << "\n";
    std::cout << "AI recommended target capacity: " << targetGB << " GB\n";
    std::cout << "\nDecision tree structure:\n";
    engine.printTree();
    std::cout << "\n";

    // ---------- Candidate catalog (AVL/BST) ----------
    CatalogBST catalog;
    catalog.insert(RAMModule("Kingston Fury 8GB", 8, "DDR4", 3200, 25.0));
    catalog.insert(RAMModule("Corsair Vengeance 16GB", 16, "DDR4", 3200, 45.0));
    catalog.insert(RAMModule("Crucial 32GB", 32, "DDR4", 3200, 95.0));
    std::cout << "Catalog (AVL-balanced) height: " << catalog.treeHeight() << "\n\n";

    // ---------- Stage 4: Compatibility & Feasibility ----------
    CompatibilityChecker checker;
    int proposedAddGB = 32;   // user requests adding 32GB, as in the brief's example
    RAMModule proposedModule("Requested 32GB Kit", proposedAddGB, "DDR4", 3200, 95.0);

    bool feasible = true;
    std::string reason;
    try {
        FeasibilityResult fr = checker.check(profile, proposedModule, proposedAddGB);
        reason = fr.reason;
    } catch (const InfeasibleUpgradeException& ex) {
        feasible = false;
        reason = ex.what();
        std::cout << "[Exception caught] InfeasibleUpgradeException: " << ex.what() << "\n\n";
    }

    // ---------- Stage 5: Upgrade Path Optimizer (Graph + Dijkstra) ----------
    UpgradeGraph graph;
    std::vector<std::pair<int, double>> candidateSteps = {
        {8, 25.0},    // add 8GB for $25
        {16, 45.0},   // add 16GB for $45
        {32, 95.0}    // add 32GB for $95 (may be infeasible per slot/capacity rule above)
    };
    graph.buildFromCandidates(profile.installedCapacityGB, candidateSteps);
    UpgradeGraph::PathResult path = graph.dijkstra(profile.installedCapacityGB, targetGB);

    // ---------- Stage 6: Final Report ----------
    FinalReport report;
    report.profile = profile;
    report.avgUsagePercent = avgUsage;
    report.usageClass = usageClass;
    report.aiTargetGB = targetGB;
    report.feasible = feasible;
    report.feasibilityReason = reason;
    report.optimizerPath = path;

    ReportGenerator reporter;
    std::cout << "===== FINAL RECOMMENDATION REPORT =====\n";
    reporter.printToConsole(report);
    reporter.exportToFile(report, "ram_advisor_report.txt");
    std::cout << "\n(Report also exported to ram_advisor_report.txt)\n";

    std::cout << "\nTotal Component objects created this run: " << Component::getTotalComponents() << "\n";

    return 0;
}
