#include "graph.h"

Vertex::Vertex() : vertexColor(-1) {
	
}

color Vertex::getColor() {
	return vertexColor;
}

void Vertex::setColor(color newColor) {
	vertexColor = newColor;
}

Graph::Graph() : boostDeleg() {
	
}

vertex Graph::addVertex() {
	return boost::add_vertex(boostDeleg);
}

Vertex& Graph::getVertex(vertex v) {
	return boostDeleg[v];
}

void Graph::addEdge(vertex source,
			vertex target) {
	boost::add_edge(source, target, boostDeleg);
}
