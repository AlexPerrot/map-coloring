#ifndef MOVE_H
#define MOVE_H

#include "../graph/graph.h"

class ColoringMove {
public:
	ColoringMove(Graph& graph, vertex v, color c);
	color getColor();
	vertex getVertex();
	Graph& getGraph();
	void play();
	void undo();
private:
	color c;
	vertex v;
	Graph& g;
};

#endif
