#include "GraphvizDump.h"
#include <fstream>
#include <iomanip>

void dumpTreeToDot(const std::string& path, const NodePool& pool) {
    const auto& nodes = pool.data();
    std::ofstream ofs(path);
    if (!ofs.is_open()) return;

    ofs << "digraph BarnesHut {" << std::endl;
    ofs << "  node [shape=box];" << std::endl;

    // Emit node definitions
    for (size_t i = 0; i < nodes.size(); ++i) {
        const auto& node = nodes[i];
        std::ostringstream label;
        label << i << "\n";
        label << "mass=" << node.totalMass << "\n";
        label << "center=(" << std::fixed << std::setprecision(2)
              << node.center.x << "," << node.center.y << "," << node.center.z << ")";
        ofs << "  node_" << i << " [label=\"" << label.str() << "\"];" << std::endl;
    }

    // Emit edges
    for (size_t i = 0; i < nodes.size(); ++i) {
        const auto& node = nodes[i];
        for (int c = 0; c < 8; ++c) {
            int32_t child = node.children[c];
            if (child != NO_CHILD) {
                ofs << "  node_" << i << " -> node_" << child << ";" << std::endl;
            }
        }
    }

    ofs << "}" << std::endl;
}
