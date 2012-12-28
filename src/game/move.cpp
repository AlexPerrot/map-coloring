#include "move.h"

/****** ColoringMove ******/
ColoringMove::ColoringMove(vertex v, color c)
: c(c), v(v) {

}

color ColoringMove::getColor() {
	return c;
}

vertex ColoringMove::getVertex() {
	return v;
}

void ColoringMove::play(Graph& graph) {
	graph.getVertexProperties(v).setColor(c);
}

void ColoringMove::undo(Graph& graph) {
	graph.getVertexProperties(v).uncolor();
}

ColoringMove makeEmptyMove() {
	vertex v = 0;
	color c = -1;
	return ColoringMove(v, c);
}
