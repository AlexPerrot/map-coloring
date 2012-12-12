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
 : _current(begin), _end(end) {
	
}

VertexIterator::VertexIterator(std::pair<vertexIterator,vertexIterator> iterPair)
 : _current(iterPair.first), _end(iterPair.second) {
	 
 }

bool VertexIterator::hasNext() {
	return _current < _end;
}

void VertexIterator::moveNext() {
	if (this->hasNext())
		_current++;
}

vertex VertexIterator::current() {
	return *_current;
}
