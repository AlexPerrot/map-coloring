#include <iostream>

#include "graph/graph.h"

int main() {
	Graph g;
	Vertex* v = g.addVertex();
	std::cout << "Vertex color : " << v->getColor() << std::endl;
	v->setColor(1);
	std::cout << "Vertex color : " << v->getColor() << std::endl;
}
