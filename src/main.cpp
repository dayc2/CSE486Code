#include <iostream>
#include "utils.h"
#include "algorithms/BFS.hpp"
#include "algorithms/DFS.hpp"
#include "algorithms/UCS.hpp"
#include "algorithms/DLS.hpp"
#include "algorithms/IDS.hpp"
#include "algorithms/AStar.hpp"

int main() {

    Node S('S'), A('A'), B('B'), C('C'), D('D'), E('E'), G('G');
    S.addChild(& A, 1);
    S.addChild(& B, 5);
    S.addChild(& C, 8);

    A.addChild(& D, 3);
    A.addChild(& E, 7);
    A.addChild(& G, 9);
    B.addChild(& G, 4);
    C.addChild(& G, 5);

    std::list<Node *> path;
    int cost;

    cost = BFS::BFS(S, G, &path);
    std::cout << "BFS: " << std::endl;
    std::cout << "cost: " << cost << std::endl;
    std::cout << "path: " << path << std::endl << std::endl;

    cost = UCS::UCS(S, G, &path);
    std::cout << "UCS: " << std::endl;
    std::cout << "cost: " << cost << std::endl;
    std::cout << "path: " << path << std::endl << std::endl;

    cost = DFS::DFS(S, G, &path);
    std::cout << "DFS: " << std::endl;
    std::cout << "cost: " << cost << std::endl;
    std::cout << "path: " << path << std::endl << std::endl;

    cost = DLS::DLS(S, G, 2, &path);
    std::cout << "DLS: " << std::endl;
    std::cout << "cost: " << cost << std::endl;
    std::cout << "path: " << path << std::endl << std::endl;

    cost = IDS::IDS(S, G, &path);
    std::cout << "IDS: " << std::endl;
    std::cout << "cost: " << cost << std::endl;
    std::cout << "path: " << path << std::endl << std::endl;

    // HeuristicNode hS(8, 'S'), hA(8, 'A'), hB(4, 'B'), hC(3, 'C'), hD(INT_MAX, 'D'), hE(INT_MAX, 'E'), hG(0, 'G');
    // hS.addChild(& hA, 1);
    // hS.addChild(& hB, 5);
    // hS.addChild(& hC, 8);

    // hA.addChild(& hD, 3);
    // hA.addChild(& hE, 7);
    // hA.addChild(& hG, 9);
    // hB.addChild(& hG, 4);
    // hC.addChild(& hG, 5);
    HeuristicNode hS(6, 'S'), hA(0, 'A'), hB(2, 'B'), hC(4, 'C'), hD(1, 'D'), hE(10, 'E'), hG(0, 'G');
    hS.addChild(& hA, 2);
    hS.addChild(& hB, 1);
    hS.addChild(& hG, 9);

    hA.addChild(& hC, 2);
    hA.addChild(& hD, 3);
    hB.addChild(& hD, 2);
    hB.addChild(& hE, 4);
    hC.addChild(& hG, 4);
    hD.addChild(& hG, 4);

    std::list<HeuristicNode *> hPath;

    cost = AStar::AStar(hS, hG, &hPath);
    std::cout << "A*: " << std::endl;
    std::cout << "cost: " << cost << std::endl;
    std::cout << "path: " << hPath << std::endl << std::endl;


    return 0;
}