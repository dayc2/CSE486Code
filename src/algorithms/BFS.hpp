#pragma once

#include "../utils.h"
#include <deque>
#include <map>

namespace BFS {
    int BFS(Node & n, Node & goal, std::list<Node *> * path = nullptr) {
        if (path != nullptr) { path->clear(); }
        std::deque< std::pair<Node *, int> > q { {&n, 0} };
        std::map< Node *, Node * > parents;
        parents [&n] = nullptr;
        while (!q.empty()) {
            //get the current node and cost
            auto [current, currentCost] = q.front();
            q.pop_front();
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
                    q.push_back( {child, currentCost+cost} );
                    parents[child] = current;
                }
            }
        }
        return -1;
    }
}