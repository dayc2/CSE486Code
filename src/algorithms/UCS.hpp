#pragma once

#include "../utils.h"
#include <queue>
#include <map>

namespace UCS {

    std::pair<Node *, int> popMin(std::map< Node *, int > & M) {
        if(M.empty()) return {nullptr, 0};
        Node * n;
        int minCost = INT_MAX;
        for (auto & [node, cost] : M) {
            if (cost < minCost) {
                n = node;
                minCost = cost;
            }
        }
        M.erase(n);
        return {n, minCost};
    }

    int UCS(Node & n, Node & goal, std::list<Node *> * path = nullptr) {
        if (path != nullptr) { path->clear(); }
        std::map< Node *, int > m { {&n, 0} };
        std::map< Node *, Node * > parents { {&n, nullptr} };
        while (!m.empty()) {
            //get the current node and cost
            auto [current, currentCost] = popMin(m);
            if (current == &goal) {
                if (path != nullptr) {
                    Node * current = &goal;
                    while (current != nullptr) {
                        path->push_front(current);
                        current = parents[current];
                    }
                }
                return currentCost;
            }
            // expand node
            for (auto & [child, cost] : current->children) {
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