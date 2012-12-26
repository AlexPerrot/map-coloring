#ifndef GAME_H
#define GAME_H

#include "../graph/graph.h"

class Player;

class MapGame {
	public:
		MapGame(Graph& g, int maxColors);
		Graph& getGraph();
		color getFirstUnusedColor();
		int getMaxColors();
		bool isFinished();
		bool canContinue();
		bool play(Player& alice, Player& bob);
		void reset();
		bool* getVisibleColors(vertex v);
	private:
		Graph& graph;
		int maxColors;
		color firstUnusedColor;
		bool seesEveryColor(vertex v);
};

class SelectionAlgorithm {
public:
	SelectionAlgorithm(MapGame& game);
	virtual vertex selectVertex();
	virtual color selectColor(vertex v);
private:
	MapGame& game;
};

class Player {
public:
	Player(SelectionAlgorithm& algo, MapGame& game);
	void play();
private:
	SelectionAlgorithm& algo;
	MapGame& game;
};

#endif