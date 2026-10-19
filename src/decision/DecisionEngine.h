#pragma once
#include "DecisionNode.h"

// Input received from the system-monitoring module.
struct SystemData
{
    int installedRAM;
    float averageUsage;
    float peakUsage;

    // Additional risk indicators (provided by another module).
    bool usageDataAvailable;
    bool persistentHighUsage;
    bool pagingDetected;
};

// Output returned by the Decision Engine.
struct RiskAssessment
{
    RiskLevel risk;
    const char* explanation;
};

class DecisionEngine
{
private:
    DecisionNode* root;

    // Traverses the binary tree to determine the risk level.
    RiskLevel traverse(DecisionNode* node, const SystemData& data);

public:
    DecisionEngine(); // constructor 
    ~DecisionEngine(); // destructor

    RiskAssessment evaluate(const SystemData& data);
};
