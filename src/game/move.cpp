#include "move.h"

/****** ColoringMove ******/
ColoringMove::ColoringMove(Graph& graph, vertex v, color c)
: c(c), v(v), g(graph) {

}

color ColoringMove::getColor() {
	return c;
}

vertex ColoringMove::getVertex() {
	return v;
}

Graph& ColoringMove::getGraph() {
	return g;
}

void ColoringMove::play() {
	g.getVertexProperties(v).setColor(c);
}

void ColoringMove::undo() {
	g.getVertexProperties(v).uncolor();
}
