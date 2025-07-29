#ifndef NODEPOOL_H
#define NODEPOOL_H

// NodePool.h - manages allocation of octree nodes in a pre-allocated pool

#include <vector>
#include <atomic>
#include <cassert>
#include "Tree.h"

class NodePool {
public:
    // Reserve capacity for up to reserveCount nodes
    explicit NodePool(size_t reserveCount = 100000000) {
        nodes.reserve(reserveCount);
        nodeCount.store(0);
    }

    // Atomically allocate a new node, return its index
    int32_t allocateNode() {
        int32_t idx = nodeCount.fetch_add(1);
        assert(idx < static_cast<int32_t>(nodes.capacity()));
        nodes.emplace_back();
        return idx;
    }

    // Access node by index
    Tree::Node& operator[](int32_t idx) {
        return nodes[idx];
    }

    // Current number of allocated nodes
    int32_t size() const {
        return nodeCount.load();
    }

    // Get raw node container (for dumps)
    const std::vector<Tree::Node>& data() const {
        return nodes;
    }

private:
    std::vector<Tree::Node> nodes;
    std::atomic<int32_t> nodeCount;
};

#endif // NODEPOOL_H
