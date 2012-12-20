#ifndef GAME_H
#define GAME_H value

#include "../graph/graph.h"

class MapGame {
	public:
		MapGame(Graph& g, int maxColors);
		Graph& getGraph();
		color getFirstUnusedColor();
		int getMaxColors();
		bool isFinished();
		bool canContinue();
	private:
		Graph& graph;
		int maxColors;
		color firstUnusedColor;
};

#endif