#include "graph.h"

VertexProperties::VertexProperties() : vertexColor(-1) {
	
}

color VertexProperties::getColor() {
	return vertexColor;
}

void VertexProperties::setColor(color newColor) {
	vertexColor = newColor;
}

Graph::Graph() : boostDeleg() {
	
}

vertex Graph::addVertex() {
	return boost::add_vertex(boostDeleg);
}

VertexProperties& Graph::getVertexProperties(vertex v) {
	return boostDeleg[v];
}

void Graph::addEdge(vertex source,
			vertex target) {
	boost::add_edge(source, target, boostDeleg);
}

VertexIterator::VertexIterator(vertexIterator begin, vertexIterator end)
 : current(begin), end(end) {
	
}

VertexIterator::VertexIterator(std::pair<vertexIterator,vertexIterator> iterPair)
 : current(iterPair.first), end(iterPair.second) {
	 
 }

bool VertexIterator::hasNext() {
	return current < end;
}

void VertexIterator::moveNext() {
	if (this->hasNext())
		current++;
}

vertex VertexIterator::getCurrent() {
	return *current;
}
