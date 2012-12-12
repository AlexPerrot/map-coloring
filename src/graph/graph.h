#include <boost/graph/adjacency_list.hpp>

/*
 * Ces classes sont une surcouche aux graphes boost
 * Les fonctionnalités attendues sont :
 *  - creation de graphe
 * 	- ajout de sommet
 * 	- coloration de sommet
 * (hésitez pas à en rajouter)
 */
 
 typedef int color;
 
 class Vertex {
	public:
		Vertex();
		color getColor();
		void setColor(color newColor);
	private:
		color vertexColor;
 };
 
typedef boost::adjacency_list<
				boost::vecS,
				boost::vecS,
				boost::undirectedS,
				Vertex,
				boost::no_property
			> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex;

class Graph {
	public:
		Graph();
		vertex addVertex();
		void addEdge(vertex source, vertex target);
		Vertex& getVertex(vertex v);
	private:
		graph boostDeleg;
};
