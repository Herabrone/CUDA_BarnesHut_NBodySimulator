#ifndef GRAPHVIZDUMP_H
#define GRAPHVIZDUMP_H

// GraphvizDump.h - utility to dump octree as Graphviz DOT

#include <string>
#include "NodePool.h"

// Write the octree nodes and edges to a DOT file at the given path
void dumpTreeToDot(const std::string& path, const NodePool& pool);

#endif // GRAPHVIZDUMP_H
