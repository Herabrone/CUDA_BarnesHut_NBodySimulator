#include <vector>
#include <random>
#include <iostream>

#include "Body.h"
#include "Vec3.h"
#include "barneshut/BarnesHutTree.h"
#include "barneshut/GraphvizDump.h"

int main() {
    constexpr int N = 100;
    std::vector<Body> bodies;
    bodies.reserve(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    // Generate random bodies
    for (int i = 0; i < N; ++i) {
        Body b;
        b.pos = Vec3(dist(gen), dist(gen), dist(gen));
        b.mass = 1.0;
        bodies.push_back(b);
    }

    // Build Barnes–Hut tree
    BarnesHutTree tree;
    tree.buildTree(bodies);
    std::cout << "Built tree with " << tree.getNodeCount() << " nodes" << std::endl;

    // Dump to Graphviz DOT
    dumpTreeToDot("tree.dot", tree.getNodePool());
    std::cout << "Dumped tree to tree.dot" << std::endl;

    return 0;
}
