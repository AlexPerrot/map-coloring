#include <iostream>

#include "graph/graph.h"

int main() {
	Graph g;
	vertex v = g.addVertex();
	VertexProperties& v1 = g.getVertexProperties(v);
	std::cout << "Vertex color : " << v1.getColor() << std::endl;
	v1.setColor(1);
	std::cout << "Vertex color : " << v1.getColor() << std::endl;
	std::cout << "Color from graph : " << g.getVertexProperties(v).getColor() << std::endl;
}
