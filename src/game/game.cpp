#include "game.h"

MapGame::MapGame(Graph& g, int maxColors)
 : graph(g), maxColors(maxColors), firstUnusedColor(0) {

 }

Graph& MapGame::getGraph() {
	return graph;
}

color MapGame::getFirstUnusedColor() {
	return firstUnusedColor++;;
}

int MapGame::getMaxColors() {
	return maxColors;
}