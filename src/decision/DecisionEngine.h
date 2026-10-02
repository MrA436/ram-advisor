// DecisionNode is one piece of the tree.
// DecisionEngine is the thing that owns and operates the whole tree.
#pragma once
#include "DecisionNode.h"

struct SystemData // input
{
    int installedRAM;
    float averageUsage;
    float peakUsage;
};

class DecisionEngine
{
private:
    DecisionNode* root; // root = starting point/node
    Recommendation traverse(DecisionNode* node, const SystemData& data);

public:
    DecisionEngine(); // constructor
    ~DecisionEngine();// destructor

    // other modules will call evaluate() 
    // & means we're passing a reference instead of copying the entire structure.
    // const means that it will read data, but won't modify it. 
    Recommendation evaluate(const SystemData& data); // this can safely analyze systemData without changing it, because of const
};