#pragma once

#include "../utils.h"
#include <queue>
#include <map>

namespace AStar {

    std::pair<HeuristicNode *, int> popMin(std::map< HeuristicNode *, int > & M) {
        if(M.empty()) return {nullptr, 0}; // Return a default value when the map is empty
        HeuristicNode * n;
        int minCost = INT_MAX;
        for (auto & [node, cost] : M) {
            if (cost + node->heuristic < minCost) {
                n = node;
                minCost = cost + node->heuristic;
            }
        }
        M.erase(n);
        return {n, minCost - n->heuristic};
    }

    int AStar(HeuristicNode & n, HeuristicNode & goal, std::list<HeuristicNode *> * path = nullptr) {
        if (path != nullptr) { path->clear(); }
        std::map< HeuristicNode *, int> m { {&n, 0} };
        std::map< HeuristicNode *, HeuristicNode * > parents { {&n, nullptr} };
        while (!m.empty()) {
            //get the current node and cost
            auto [current, currentCost] = popMin(m);
            if (current == &goal) {
                if (path != nullptr) {
                    HeuristicNode * current = &goal;
                    while (current != nullptr) {
                        path->push_front(current);
                        current = parents[current];
                    }
                }
                return currentCost;
            }
            // std::cout << "expanding: " << current->name << " cost: " << currentCost << " heuristic cost: " << currentCost+current->heuristic << std::endl;
            // expand node
            for (auto & [child, cost] : current->children) {
                // std::cout << "child: " << child->name << " cost: " << currentCost+cost << " heuristic cost: " << currentCost+cost+child->heuristic << std::endl;
                if (parents.find(child) == parents.end()) {
                    m[child] = currentCost + cost;
                    parents[child] = current;
                } else if (currentCost + cost < m[child]) {
                    // update better to cost and path
                    m[child] = currentCost + cost;
                    parents[child] = current;
                }
            }
        }
        return -1;
    }
}