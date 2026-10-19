
#include "DecisionEngine.h"

DecisionEngine::DecisionEngine()
{
    // Leaf nodes
    // "new" dynamically creates an object in memory.
    DecisionNode* low = new DecisionNode(LOW_RISK);
    DecisionNode* moderate1 = new DecisionNode(MODERATE_RISK);
    DecisionNode* moderate2 = new DecisionNode(MODERATE_RISK);
    DecisionNode* high = new DecisionNode(HIGH_RISK);

    // Decision nodes
    DecisionNode* peakNode = new DecisionNode(peakUsage, 90);
    DecisionNode* averageNode = new DecisionNode(avgUsage, 60);
    DecisionNode* rootNode = new DecisionNode(avgUsage, 80);

    // Connect root
    rootNode->yes = peakNode;
    rootNode->no = averageNode;

    // Connect root's YES branch
    peakNode->yes = high;
    peakNode->no = moderate1;

    // Connect root's NO branch
    averageNode->yes = moderate2;
    averageNode->no = low;

    root = rootNode;
}

RiskLevel DecisionEngine::traverse(
    DecisionNode* node, const SystemData& data)
{
    if (node->isLeaf)
        return node->result;

    bool conditionResult = false;

    if (node->condition == avgUsage)
        conditionResult = data.averageUsage > node->Threshold;
    else if (node->condition == peakUsage)
        conditionResult = data.peakUsage > node->Threshold;

    if (conditionResult)
        return traverse(node->yes, data);

    return traverse(node->no, data);
}

RiskAssessment DecisionEngine::evaluate(const SystemData& data)
{
    // Do not assess risk when the required measurements are unavailable.
    if (!data.usageDataAvailable)
    {
        return {
            INSUFFICIENT_DATA,
            "System RAM usage data is unavailable."
        };
    }

    RiskLevel risk = traverse(root, data);

    // Initial risk adjustment based on additional system indicators.
    if (data.persistentHighUsage && data.pagingDetected)
        risk = HIGH_RISK;
    else if (data.persistentHighUsage &&
             risk == LOW_RISK)
        risk = MODERATE_RISK;

    const char* explanation = "RAM risk assessment completed.";

    if (risk == HIGH_RISK)
        explanation = "Potential high risk of RAM-related problems.";
    else if (risk == MODERATE_RISK)
        explanation = "Potential moderate risk of RAM-related problems.";
    else
        explanation = "No significant risk identified by current rules.";

    return {risk, explanation};
}

DecisionEngine::~DecisionEngine()
{
    delete root->yes->yes;
    delete root->yes->no;
    delete root->yes;

    delete root->no->yes;
    delete root->no->no;
    delete root->no;

    delete root;
}
