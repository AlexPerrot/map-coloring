#include "graph.h"


/****** VertexProperties Implementation ******/

VertexProperties::VertexProperties() : vertexColor(-1) {
	
}

color VertexProperties::getColor() {
	return vertexColor;
}

void VertexProperties::setColor(color newColor) {
	vertexColor = newColor;
}


/****** Graph Implementation ******/

Graph::Graph() : boostDeleg() {
	
}

vertex Graph::addVertex() {
	return boost::add_vertex(boostDeleg);
}

vertex Graph::getVertex(int n) {
	return boost::vertex(n, boostDeleg);
}

VertexProperties& Graph::getVertexProperties(vertex v) {
	return boostDeleg[v];
}

void Graph::addEdge(vertex source,
			vertex target) {
	boost::add_edge(source, target, boostDeleg);
}

VertexIterator Graph::getVertices() {
	return VertexIterator(boost::vertices(boostDeleg));
}

AdjacencyIterator Graph::getNeighbours(vertex v) {
	return AdjacencyIterator(boost::adjacent_vertices(v, boostDeleg));
}


/****** VertexIterator Implementation ******/

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

/****** AjacencyIterator Implementation ******/

AdjacencyIterator::AdjacencyIterator(adjIterator begin, adjIterator end)
 : current(begin), end(end) {

}

AdjacencyIterator::AdjacencyIterator(std::pair<adjIterator,adjIterator> iterPair)
 : current(iterPair.first), end(iterPair.second) {
	 
}

bool AdjacencyIterator::hasNext() {
	return current < end;
}

void AdjacencyIterator::moveNext() {
	if (this->hasNext())
		current++;
}

vertex AdjacencyIterator::getCurrent() {
	return *current;
}
