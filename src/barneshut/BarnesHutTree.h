#ifndef BARNESHUTTREE_H
#define BARNESHUTTREE_H

// BarnesHutTree.h - CPU-side Barnes–Hut octree builder

#include "Body.h"
#include "Tree.h"
#include "ThreadPool.h"
#include "NodePool.h"
#include <vector>

class BarnesHutTree {
public:
    // Construct with optional reserve for node pool
    BarnesHutTree(size_t reserveNodes = 100000000);

    // Build the octree from input bodies
    void buildTree(const std::vector<Body>& bodies);

    // Access built node pool
    const NodePool& getNodePool() const;
    int32_t getNodeCount() const;

private:
    // Recursive subtree construction for a bucket of bodies
    void buildSubtree(int32_t nodeIdx, const std::vector<int>& bucket);
    // Insert a single body into subtree
    void insertNode(int32_t nodeIdx, int bodyIdx);

    NodePool nodePool;
    ThreadPool threadPool;
    const std::vector<Body>* bodiesPtr;
    int32_t rootIndex;
};

#endif // BARNESHUTTREE_H
