// DecisionEngine.h
// TCS302 Unit 3: Binary tree, tree representation, recursion, tree traversal
// TCS307 Unit 4: virtual functions used for rule evaluation inside the tree nodes
// TCS307 Unit 2: dynamic objects, pointers to objects, "this" pointer (in buildTree)
#ifndef DECISIONENGINE_H
#define DECISIONENGINE_H

#include <string>
#include <functional>
#include <iostream>
#include <algorithm>

enum class UsageClass { LIGHT, MEDIUM, HEAVY };

inline std::string usageClassName(UsageClass c) {
    switch (c) {
        case UsageClass::LIGHT: return "Light";
        case UsageClass::MEDIUM: return "Medium";
        case UsageClass::HEAVY: return "Heavy";
    }
    return "Unknown";
}

// A node in the hand-built binary decision tree.
// Internal nodes hold a predicate (a threshold test on average usage %);
// leaf nodes hold a final UsageClass.
struct DecisionNode {
    bool isLeaf;
    UsageClass result;               // valid when isLeaf == true
    double threshold;                // valid when isLeaf == false
    DecisionNode* left;              // condition FALSE branch (usage < threshold)
    DecisionNode* right;             // condition TRUE branch (usage >= threshold)

    // Leaf constructor
    explicit DecisionNode(UsageClass r)
        : isLeaf(true), result(r), threshold(0), left(nullptr), right(nullptr) {}

    // Internal-node constructor
    DecisionNode(double t, DecisionNode* l, DecisionNode* r)
        : isLeaf(false), result(UsageClass::LIGHT), threshold(t), left(l), right(r) {}
};

class DecisionEngine {
private:
    DecisionNode* root;

    // Builds the fixed classification tree dynamically ("this" pointer implicit on member calls,
    // nodes created with `new` -> dynamic objects, TCS307 Unit 2).
    DecisionNode* buildTree() {
        DecisionNode* heavyLeaf = new DecisionNode(UsageClass::HEAVY);
        DecisionNode* mediumLeaf = new DecisionNode(UsageClass::MEDIUM);
        DecisionNode* lightLeaf = new DecisionNode(UsageClass::LIGHT);

        // usage >= 80  -> Heavy
        // 50 <= usage < 80 -> Medium
        // usage < 50 -> Light
        DecisionNode* upperSplit = new DecisionNode(80.0, mediumLeaf, heavyLeaf);
        DecisionNode* root = new DecisionNode(50.0, lightLeaf, upperSplit);
        return root;
    }

    // Recursive traversal that walks the tree to classify a usage percentage.
    UsageClass classifyRecursive(DecisionNode* node, double avgUsagePercent) const {
        if (node->isLeaf) return node->result;
        if (avgUsagePercent >= node->threshold)
            return classifyRecursive(node->right, avgUsagePercent);
        else
            return classifyRecursive(node->left, avgUsagePercent);
    }

    // In-order traversal (recursion) -- used only to print/debug the tree shape.
    void inOrderPrint(DecisionNode* node, int depth) const {
        if (!node) return;
        inOrderPrint(node->left, depth + 1);
        std::cout << std::string(depth * 2, ' ')
                  << (node->isLeaf ? usageClassName(node->result) : ("threshold>=" + std::to_string(node->threshold)))
                  << "\n";
        inOrderPrint(node->right, depth + 1);
    }

    void destroy(DecisionNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    DecisionEngine() { root = buildTree(); }
    ~DecisionEngine() { destroy(root); }

    UsageClass classify(double avgUsagePercent) const {
        return classifyRecursive(root, avgUsagePercent);
    }

    void printTree() const { inOrderPrint(root, 0); }

    // AI target capacity recommendation given current capacity + workload class.
    int recommendTargetGB(int currentGB, UsageClass usage) const {
        switch (usage) {
            case UsageClass::LIGHT:  return currentGB;                 // no upgrade needed
            case UsageClass::MEDIUM: return std::max(currentGB * 2, 16);
            case UsageClass::HEAVY:  return std::max(currentGB * 2, 32);
        }
        return currentGB;
    }
};

#endif
