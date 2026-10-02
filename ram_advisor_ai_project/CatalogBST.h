// CatalogBST.h
// TCS302 Unit 3: Binary Search Tree, path length, (height-balancing noted -> AVL-style rotation)
// Keeps candidate RAM modules keyed by price so lookups stay O(log n) as the catalog grows.
#ifndef CATALOGBST_H
#define CATALOGBST_H

#include "RAMModule.h"
#include <vector>
#include <algorithm>

struct BSTNode {
    RAMModule module;
    BSTNode* left;
    BSTNode* right;
    int height;   // used for AVL-style balancing

    explicit BSTNode(const RAMModule& m) : module(m), left(nullptr), right(nullptr), height(1) {}
};

class CatalogBST {
private:
    BSTNode* root = nullptr;

    int height(BSTNode* n) const { return n ? n->height : 0; }
    int balanceFactor(BSTNode* n) const { return n ? height(n->left) - height(n->right) : 0; }

    BSTNode* rotateRight(BSTNode* y) {
        BSTNode* x = y->left;
        BSTNode* t2 = x->right;
        x->right = y;
        y->left = t2;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

    BSTNode* rotateLeft(BSTNode* x) {
        BSTNode* y = x->right;
        BSTNode* t2 = y->left;
        y->left = x;
        x->right = t2;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        return y;
    }

    // AVL-balanced insert keyed by price-per-module (TCS302 Unit 3: AVL trees)
    BSTNode* insertRec(BSTNode* node, const RAMModule& m) {
        if (!node) return new BSTNode(m);

        if (m.getPrice() < node->module.getPrice())
            node->left = insertRec(node->left, m);
        else
            node->right = insertRec(node->right, m);

        node->height = 1 + std::max(height(node->left), height(node->right));
        int bf = balanceFactor(node);

        // Left-Left
        if (bf > 1 && m.getPrice() < node->left->module.getPrice()) return rotateRight(node);
        // Right-Right
        if (bf < -1 && m.getPrice() >= node->right->module.getPrice()) return rotateLeft(node);
        // Left-Right
        if (bf > 1 && m.getPrice() >= node->left->module.getPrice()) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Left
        if (bf < -1 && m.getPrice() < node->right->module.getPrice()) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    void inOrderCollect(BSTNode* node, std::vector<RAMModule>& out) const {
        if (!node) return;
        inOrderCollect(node->left, out);
        out.push_back(node->module);
        inOrderCollect(node->right, out);
    }

    BSTNode* findByCapacityRec(BSTNode* node, int capacityGB) const {
        if (!node) return nullptr;
        if (node->module.getCapacity() == capacityGB) return node;
        BSTNode* l = findByCapacityRec(node->left, capacityGB);
        if (l) return l;
        return findByCapacityRec(node->right, capacityGB);
    }

public:
    void insert(const RAMModule& m) { root = insertRec(root, m); }

    std::vector<RAMModule> inOrder() const {
        std::vector<RAMModule> out;
        inOrderCollect(root, out);
        return out;
    }

    // Simple recursive search by capacity (not by the BST's own key, so it's O(n) worst case;
    // demonstrates a plain BST/tree search alongside the AVL-balanced insert above).
    bool findByCapacity(int capacityGB, RAMModule& result) const {
        BSTNode* found = findByCapacityRec(root, capacityGB);
        if (!found) return false;
        result = found->module;
        return true;
    }

    int treeHeight() const { return height(root); }
};

#endif
