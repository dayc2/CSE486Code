#pragma once

#include <vector>
#include <list>
#include <iostream>

using std::vector;

struct Node {
    char name;
    vector<std::pair<Node*, int> > children;

    Node(char name = '_') : name(name) {}

    void addChild(Node * node) {
        children.push_back({node, 0});
    }

    void addChild(Node * node, int cost) {
        children.push_back({node, cost});
    }
};

struct HeuristicNode : Node{
    int heuristic;
    vector<std::pair<HeuristicNode*, int> > children;

    HeuristicNode(int heuristic, char name = '_') : Node(name), heuristic(heuristic) {}
    HeuristicNode(char name) = delete;

    void addChild(HeuristicNode * node, int cost) {
        children.push_back({node, cost});
    }
    void addChild(HeuristicNode * node) {
        children.push_back({node, 0});
    }
};

std::ostream & operator<<(std::ostream & os, const std::list<Node *> & path) {
    os << "[";
    for (auto it = path.begin(); it != path.end(); it++) {
        os << (*it)->name;
        if (it != --path.end()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

std::ostream & operator<<(std::ostream & os, const std::list<HeuristicNode *> & path) {
    os << "[";
    for (auto it = path.begin(); it != path.end(); it++) {
        os << (*it)->name;
        if (it != --path.end()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}