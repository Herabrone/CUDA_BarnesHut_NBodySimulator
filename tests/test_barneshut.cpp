// Unit tests for BarnesHutTree
// Uses Catch2 (header-only) for simplicity
// To add: download catch.hpp to tests/ or use your preferred test framework

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Body.h"
#include "barneshut/BarnesHutTree.h"
#include <vector>

TEST_CASE("BarnesHutTree builds a single node for one body", "[tree]") {
    std::vector<Body> bodies(1);
    bodies[0].pos = Vec3(1.0, 2.0, 3.0);
    bodies[0].mass = 2.0;
    BarnesHutTree tree;
    tree.buildTree(bodies);
    REQUIRE(tree.getNodeCount() >= 1);
    auto& pool = tree.getNodePool();
    // Root node should have correct COM and mass
    REQUIRE(pool.data()[0].COM.x == Approx(1.0));
    REQUIRE(pool.data()[0].COM.y == Approx(2.0));
    REQUIRE(pool.data()[0].COM.z == Approx(3.0));
    REQUIRE(pool.data()[0].totalMass == Approx(2.0));
}

TEST_CASE("BarnesHutTree buckets two bodies into different children", "[tree]") {
    std::vector<Body> bodies(2);
    bodies[0].pos = Vec3(-1.0, -1.0, -1.0);
    bodies[1].pos = Vec3(1.0, 1.0, 1.0);
    BarnesHutTree tree;
    tree.buildTree(bodies);
    REQUIRE(tree.getNodeCount() >= 3); // root + 2 children
    auto& pool = tree.getNodePool();
    // Root should have two children, each with a body
    int childCount = 0;
    for (int i = 0; i < 8; ++i) {
        int32_t c = pool.data()[0].children[i];
        if (c != -1) {
            ++childCount;
            REQUIRE(pool.data()[c].bodyIndex >= 0);
        }
    }
    REQUIRE(childCount == 2);
}

TEST_CASE("BarnesHutTree handles empty input", "[tree]") {
    std::vector<Body> bodies;
    BarnesHutTree tree;
    tree.buildTree(bodies);
    REQUIRE(tree.getNodeCount() == 1); // Only root node
}
