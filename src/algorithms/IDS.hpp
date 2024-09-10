#pragma once

#include "../utils.h"
#include <deque>
#include <map>

namespace IDS {
    struct tuple {
        Node * node;
        int cost;
        int depth;
    };
    int IDS(Node & n, Node & goal, std::list<Node *> * path = nullptr) {
        if (path != nullptr) { path->clear(); }
        int currentDepthLimit = 0;
        while (true) {
            std::deque< tuple > q { {&n, 0, currentDepthLimit} };
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
                    // std::cout << "child: " << child->name << " cost: " << cost << std::endl;
                    if (parents.find(child) == parents.end()) {
                        q.push_back( {child, currentCost+cost, nodeDepth-1} );
                        parents[child] = current;
                    }
                }
            }
            // return -1;
            currentDepthLimit++;
        }
    }
}