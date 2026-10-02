#pragma once

enum conditionType
{
    avgUsage,
    peakUsage
};

enum Recommendation {
    LIGHT,
    MEDIUM,
    HEAVY,
    NO_RECOMMENDATION
};

struct DecisionNode
{
    conditionType condition;
    float Threshold;

    DecisionNode* yes;
    DecisionNode* no;

    Recommendation result;

    DecisionNode(conditionType condition,float Threshold);
    DecisionNode(Recommendation result);
};


