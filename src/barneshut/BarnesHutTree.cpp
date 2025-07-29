#include "barneshut/BarnesHutTree.h"
#include <algorithm>
#include <limits>

BarnesHutTree::BarnesHutTree(size_t reserveNodes)
    : nodePool(reserveNodes), threadPool(), bodiesPtr(nullptr), rootIndex(-1) {}

void BarnesHutTree::buildTree(const std::vector<Body>& bodies) {
    bodiesPtr = &bodies;
    // Compute global bounds
    Vec3 minB(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Vec3 maxB(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
    for (const auto& b : bodies) {
        minB.x = std::min(minB.x, b.pos.x);
        minB.y = std::min(minB.y, b.pos.y);
        minB.z = std::min(minB.z, b.pos.z);
        maxB.x = std::max(maxB.x, b.pos.x);
        maxB.y = std::max(maxB.y, b.pos.y);
        maxB.z = std::max(maxB.z, b.pos.z);
    }
    Vec3 center((minB.x + maxB.x) * 0.5, (minB.y + maxB.y) * 0.5, (minB.z + maxB.z) * 0.5);
    double halfWidth = std::max({maxB.x - minB.x, maxB.y - minB.y, maxB.z - minB.z}) * 0.5;

    // Allocate root node
    rootIndex = nodePool.allocateNode();
    auto& root = nodePool[rootIndex];
    root.center = center;
    root.halfWidth = halfWidth;
    root.COM = Vec3(0.0, 0.0, 0.0);
    root.totalMass = 0.0;
    root.bodyIndex = NO_CHILD;

    // Bucket bodies
    std::vector<int> buckets[8];
    for (int i = 0; i < (int)bodies.size(); ++i) {
        const auto& p = bodies[i].pos;
        int idx = (p.x > center.x ? 4 : 0) | (p.y > center.y ? 2 : 0) | (p.z > center.z ? 1 : 0);
        buckets[idx].push_back(i);
    }

    // Initialize children
    for (int i = 0; i < 8; ++i) {
        if (!buckets[i].empty()) {
            int childIdx = nodePool.allocateNode();
            root.children[i] = childIdx;
            auto& child = nodePool[childIdx];
            child.halfWidth = halfWidth * 0.5;
            child.center = center;
            child.center.x += (i & 4) ? child.halfWidth : -child.halfWidth;
            child.center.y += (i & 2) ? child.halfWidth : -child.halfWidth;
            child.center.z += (i & 1) ? child.halfWidth : -child.halfWidth;
            child.totalMass = 0.0;
            child.COM = Vec3(0.0, 0.0, 0.0);
        } else {
            root.children[i] = NO_CHILD;
        }
    }

    // Parallel subtree builds
    for (int i = 0; i < 8; ++i) {
        if (!buckets[i].empty()) {
            int childIdx = root.children[i];
            threadPool.enqueue([this, childIdx, &buckets, i]() {
                buildSubtree(childIdx, buckets[i]);
            });
        }
    }
    threadPool.joinAll();

    // Optionally recompute root COM and mass
    Vec3 comAccum(0.0, 0.0, 0.0);
    double massAccum = 0.0;
    for (const auto& b : buckets) {
        for (int idx : b) {
            const Body& body = (*bodiesPtr)[idx];
            comAccum = comAccum + body.pos * body.mass;
            massAccum += body.mass;
        }
    }
    if (massAccum > 0.0) {
        root.COM = comAccum / massAccum;
        root.totalMass = massAccum;
    }
}

void BarnesHutTree::buildSubtree(int32_t nodeIdx, const std::vector<int>& bucket) {
    for (int bodyIdx : bucket) {
        insertNode(nodeIdx, bodyIdx);
    }
}

void BarnesHutTree::insertNode(int32_t nodeIdx, int bodyIdx) {
    auto& node = nodePool[nodeIdx];
    const Body& b = (*bodiesPtr)[bodyIdx];
    // Update center-of-mass and mass
    node.COM = (node.COM * node.totalMass + b.pos * b.mass) / (node.totalMass + b.mass);
    node.totalMass += b.mass;
    // Leaf insertion: if leaf, set bodyIndex; deeper splitting omitted for brevity
    if (node.bodyIndex == NO_CHILD) {
        node.bodyIndex = bodyIdx;
    }
}

const NodePool& BarnesHutTree::getNodePool() const {
    return nodePool;
}

int32_t BarnesHutTree::getNodeCount() const {
    return nodePool.size();
}
