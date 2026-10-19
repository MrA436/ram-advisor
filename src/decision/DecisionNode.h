#pragma once

enum conditionType
{
    avgUsage,
    peakUsage
};

enum RiskLevel
{
    LOW_RISK,
    MODERATE_RISK,
    HIGH_RISK,
    INSUFFICIENT_DATA
};

struct DecisionNode
{
    conditionType condition;
    float Threshold;

    DecisionNode* yes;
    DecisionNode* no;

    RiskLevel result;
    bool isLeaf;

    DecisionNode(conditionType condition, float Threshold);
    DecisionNode(RiskLevel result);
};
