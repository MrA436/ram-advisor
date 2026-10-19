
#include "DecisionNode.h"

DecisionNode::DecisionNode(conditionType condition, float Threshold) //The first is type, second DecisionNode is the constructor's name.
{
    // this->condition means: The condition belonging to this particular object.
    this->condition=condition; // Put the constructor's condition value into the object's condition.
    this->Threshold=Threshold;
    
    // When we initially create a node, it doesn't have children yet.
    yes = nullptr;// nullptr means the pointer currently points to nothing.
    no = nullptr;

    // there isn't a final answer yet.
    result = INSUFFICIENT_DATA;// This isn't a leaf/result node
    isLeaf = false;
}


// This is for a leaf node.
DecisionNode::DecisionNode(RiskLevel result)    
{
    this -> condition = avgUsage;
    this -> Threshold = 0;

    // yes and no begin as nullptr, meaning no children have been attached yet.
    yes = nullptr;
    no = nullptr;

    this -> result = result;
    isLeaf = true;
}