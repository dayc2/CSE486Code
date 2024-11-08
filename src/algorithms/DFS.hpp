#pragma once

#include "../utils.h"
#include <deque>
#include <map>

namespace DFS {
    int DFS(Node & n, Node & goal, std::list<Node *> * path = nullptr) {
        if (path != nullptr) { path->clear(); }
        std::deque< std::pair<Node *, int> > q { {&n, 0} };
        std::map< Node *, Node * > parents;
        parents [&n] = nullptr;
        while (!q.empty()) {
            //get the current node and cost
            auto [current, currentCost] = q.back();
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
            // expand node

            // sort the children in alphabetical order
            std::vector< std::pair<Node *, int> > children = current->children;
            std::sort(children.begin(), children.end(), [](std::pair<Node *, int> a, std::pair<Node *, int> b) {
                return a.first->name > b.first->name;
            });

            for (auto & [child, cost] : children) {
                if (parents.find(child) == parents.end()) {
                    q.push_back( {child, currentCost+cost} );
                    parents[child] = current;
                }
            }
        }
        return -1;
    }
}