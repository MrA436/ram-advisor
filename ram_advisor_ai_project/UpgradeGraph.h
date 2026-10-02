// UpgradeGraph.h
// TCS302 Unit 5: Graph representation, Dijkstra's shortest path algorithm
// TCS302 Unit 4: sorting candidate options before they're added as edges
#ifndef UPGRADEGRAPH_H
#define UPGRADEGRAPH_H

#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <string>
#include <algorithm>
#include "Utils.h"

// Each node is a reachable RAM capacity (in GB), e.g. 8 -> 16 -> 32 -> 64.
// Edge weight = cost (here: price) of moving from one capacity tier to the next.
class UpgradeGraph {
private:
    // adjacency list: capacityGB -> list of (neighbourCapacityGB, cost)
    std::map<int, std::vector<std::pair<int, double>>> adj;

public:
    void addNode(int capacityGB) {
        if (adj.find(capacityGB) == adj.end())
            adj[capacityGB] = {};
    }

    void addEdge(int fromGB, int toGB, double cost) {
        addNode(fromGB);
        addNode(toGB);
        adj[fromGB].push_back({toGB, cost});
    }

    // Build the graph from a list of feasible candidate modules, after sorting
    // them by price-per-GB (TCS302 Unit 4: sorting) so cheaper upgrade steps are tried first.
    void buildFromCandidates(int startGB, std::vector<std::pair<int, double>> candidates) {
        // candidates: (capacityToAdd, cost)
        quickSort(candidates, [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
            return (a.second / a.first) < (b.second / b.first);   // price-per-GB ascending
        });

        addNode(startGB);
        int current = startGB;
        for (const auto& c : candidates) {
            int next = current + c.first;
            addEdge(current, next, c.second);
            current = next;   // chain tiers: 8 -> 16 -> 32 ...
        }
    }

    // Dijkstra's algorithm: least-cost path from startGB to (>=) targetGB
    struct PathResult {
        bool reachable;
        double totalCost;
        std::vector<int> path;
    };

    PathResult dijkstra(int startGB, int targetGB) const {
        std::map<int, double> dist;
        std::map<int, int> prev;
        for (const auto& kv : adj) dist[kv.first] = std::numeric_limits<double>::infinity();
        if (dist.find(startGB) == dist.end()) dist[startGB] = std::numeric_limits<double>::infinity();
        dist[startGB] = 0.0;

        using PQItem = std::pair<double, int>;   // (distance, node)
        std::priority_queue<PQItem, std::vector<PQItem>, std::greater<PQItem>> pq;
        pq.push({0.0, startGB});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;

            auto it = adj.find(u);
            if (it == adj.end()) continue;
            for (const auto& [v, weight] : it->second) {
                double nd = d + weight;
                if (dist.find(v) == dist.end() || nd < dist[v]) {
                    dist[v] = nd;
                    prev[v] = u;
                    pq.push({nd, v});
                }
            }
        }

        // Find the cheapest reachable node that satisfies capacity >= targetGB
        int bestNode = -1;
        double bestDist = std::numeric_limits<double>::infinity();
        for (const auto& kv : dist) {
            if (kv.first >= targetGB && kv.second < bestDist) {
                bestDist = kv.second;
                bestNode = kv.first;
            }
        }

        PathResult result;
        if (bestNode == -1) {
            result.reachable = false;
            result.totalCost = 0;
            return result;
        }

        result.reachable = true;
        result.totalCost = bestDist;
        std::vector<int> path;
        int cur = bestNode;
        path.push_back(cur);
        while (prev.find(cur) != prev.end()) {
            cur = prev[cur];
            path.push_back(cur);
        }
        std::reverse(path.begin(), path.end());
        result.path = path;
        return result;
    }
};

#endif
