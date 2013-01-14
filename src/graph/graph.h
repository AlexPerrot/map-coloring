#ifndef GRAPH_H
#define GRAPH_H

#include <boost/regex.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <string>
#include <fstream>

/*
 * Ces classes sont une surcouche aux graphes boost
 * Les fonctionnalités attendues sont :
 *  - creation de graphe
 * 	- ajout de sommet
 * 	- coloration de sommet
 * (hésitez pas à en rajouter)
 */
 
 typedef int color;
 
 class VertexProperties {
	public:
		VertexProperties();
		VertexProperties(const VertexProperties& vp);
		VertexProperties& operator=(const VertexProperties& vp);
		color getColor();
		void setColor(color newColor);
		void uncolor();
		bool isColored();
		std::string name;
	private:
		color vertexColor;
		bool colored;
 };
 
typedef boost::adjacency_list<
				boost::vecS,
				boost::vecS,
				boost::undirectedS,
				VertexProperties,
				boost::no_property
			> graph;
			
typedef boost::graph_traits<graph>::vertex_descriptor vertex;
typedef boost::graph_traits<graph>::vertex_iterator vertexIterator;
typedef boost::graph_traits<graph>::adjacency_iterator adjIterator;

class Iterator {
	public:
		virtual bool hasNext()=0;
		virtual vertex getCurrent()=0;
		virtual void moveNext()=0;
};

class VertexIterator : public Iterator {
	public:
		VertexIterator(vertexIterator begin, vertexIterator end);
		VertexIterator(std::pair<vertexIterator, vertexIterator> iterPair);
		bool hasNext();
		vertex getCurrent();
		void moveNext();
	private:
		vertexIterator current;
		vertexIterator end;
};

class AdjacencyIterator : public Iterator {
	public:
		AdjacencyIterator(adjIterator begin, adjIterator end);
		AdjacencyIterator(std::pair<adjIterator, adjIterator> iterPair);
		bool hasNext();
		vertex getCurrent();
		void moveNext();
	private:
		adjIterator current;
		adjIterator end;
};

class Graph {
	public:
		Graph();
		Graph(const Graph& g);
		vertex addVertex();
		void addEdge(vertex source, vertex target);
		vertex getVertex(int n);
		int getNbVertices();
		VertexProperties& getVertexProperties(vertex v);
		VertexIterator getVertices();
		AdjacencyIterator getNeighbours(vertex v);
		void getGraphFromDot(const std::string& filename);
		void printGraph();
private:
		graph boostDeleg;
		std::ifstream* in;
		boost::dynamic_properties dp;
};

#endif
