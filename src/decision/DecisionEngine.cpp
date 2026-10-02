#include "DecisionEngine.h"

DecisionEngine::DecisionEngine() //constructor: builds entire decision tree in memory
{
    // Leaf nodes: Leaf nodes in a binary tree are nodes that have no children (both left and right pointers are null). 
    DecisionNode* light = new DecisionNode(LIGHT);
    DecisionNode* medium1 = new DecisionNode(MEDIUM);
    DecisionNode* medium2 = new DecisionNode(MEDIUM);
    DecisionNode* heavy = new DecisionNode(HEAVY);

    // Decision nodes
    DecisionNode* peakNode = new DecisionNode(peakUsage, 90);
    DecisionNode* averageNode = new DecisionNode(avgUsage, 60);
    DecisionNode* rootNode = new DecisionNode(avgUsage, 80);

    // Connect root
    rootNode->yes = peakNode;
    rootNode->no = averageNode;

    // Connect root's YES branch
    peakNode->yes = heavy;
    peakNode->no = medium1;

    // Connect root's NO branch
    averageNode->yes = medium2;
    averageNode->no = light;

    root = rootNode;
}


// evaluate() starts at root → traverse() checks each node →
// if leaf, return result; otherwise check condition and recurse YES/NO.
Recommendation DecisionEngine::evaluate(const SystemData& data)
{
    return traverse(root, data);
}


Recommendation DecisionEngine::traverse(DecisionNode* node, const SystemData& data)
{
    if (node->result != NO_RECOMMENDATION)
        return node->result;

    bool conditionResult = false;

    if (node->condition == avgUsage)
    {
        conditionResult = data.averageUsage > node->Threshold;
    }
    else if (node->condition == peakUsage)
    {
        conditionResult = data.peakUsage > node->Threshold;
    }

    if (conditionResult)
        return traverse(node->yes, data);
    else
        return traverse(node->no, data);
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