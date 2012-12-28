#ifndef MOVE_H
#define MOVE_H

#include "../graph/graph.h"

class ColoringMove {
public:
	ColoringMove(vertex v, color c);
	color getColor();
	vertex getVertex();
	void play(Graph& graph);
	void undo(Graph& graph);
private:
	color c;
	vertex v;
};

ColoringMove makeEmptyMove();

#endif
