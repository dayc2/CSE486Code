#pragma once

#include "../utils.h"
#include <deque>
#include <map>

namespace DLS {
    struct tuple {
        Node * node;
        int cost;
        int depth;
    };
    int DLS(Node & n, Node & goal, int depth, std::list<Node *> * path = nullptr) {
        if (path != nullptr) { path->clear(); }
        std::deque< tuple > q { {&n, 0, depth} };
        std::map< Node *, Node * > parents;
        parents [&n] = nullptr;
        while (!q.empty()) {
            //get the current node and cost
            auto [current, currentCost, nodeDepth] = q.back();
            q.pop_back();
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
            if (nodeDepth < 0) continue;
            // expand node
            for (auto & [child, cost] : current->children) {
                if (parents.find(child) == parents.end()) {
                    q.push_back( {child, currentCost+cost, nodeDepth-1} );
                    parents[child] = current;
                }
            }
        }
        return -1;
    }
}