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
	for (int i=0 ; i< 6 ; i++)
		g.addVertex();
	VertexIterator allVertices = g.getVertices();
	while (allVertices.hasNext()) {
		vertex curr = allVertices.getCurrent();
		std::cout << g.getVertexProperties(curr).getColor() << std::endl;
		allVertices.moveNext();
	}
}
