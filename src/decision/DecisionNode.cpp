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
    result = NO_RECOMMENDATION;// This isn't a leaf/result node
}


// This is for a leaf node.
DecisionNode::DecisionNode(Recommendation result)
{
    this -> condition = avgUsage;
    this -> Threshold = 0;

    yes = nullptr;
    no = nullptr;

    this -> result = result;
}