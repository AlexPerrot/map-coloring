#include "graph.h"

Vertex::Vertex() : vertexColor(-1) {
	
}

color Vertex::getColor() {
	return vertexColor;
}

void Vertex::setColor(color newColor) {
	vertexColor = newColor;
}

Graph::Graph() {
	
}

Vertex* Graph::addVertex() {
	return new Vertex();
}
