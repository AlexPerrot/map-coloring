#include <boost/graph/copy.hpp>

#include "graph.h"


/****** VertexProperties Implementation ******/

VertexProperties::VertexProperties() : vertexColor(-1), colored(false) {
	
}

VertexProperties::VertexProperties(const VertexProperties& vp)
	: vertexColor(vp.vertexColor), colored(vp.colored) {

}

VertexProperties& VertexProperties::operator=(const VertexProperties& vp) {
	vertexColor = vp.vertexColor;
	colored = vp.colored;
	return *this;
}


color VertexProperties::getColor() {
	return vertexColor;
}

void VertexProperties::setColor(color newColor) {
	vertexColor = newColor;
	colored = true;
}

void VertexProperties::uncolor() {
	vertexColor = -1;
	colored = false;
}

bool VertexProperties::isColored() {
	return colored;
}


/****** Graph Implementation ******/

Graph::Graph() : boostDeleg() {
	
}

Graph::Graph(const Graph& g) : boostDeleg() {
	boost::copy_graph(g.boostDeleg, boostDeleg);
}

vertex Graph::addVertex() {
	return boost::add_vertex(boostDeleg);
}

vertex Graph::getVertex(int n) {
	return boost::vertex(n, boostDeleg);
}

int Graph::getNbVertices() {
	return boost::num_vertices(boostDeleg);
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

// Easy to use but raises an exception if the dot input file has information the graph can't handle.
void Graph::getGraphFromDot(const std::string& filename)
{
	this->in = std::ifstream(filename.c_str());
	dp.property("node_id", boost::get(&VertexProperties::name, this->boostDeleg));
	boost::read_graphviz(in, this->boostDeleg, dp, "node_id");
}

void Graph::printGraph()
{
	boost::write_graphviz_dp(std::cout, this->boostDeleg, this->dp, std::string("node_id"));
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
