#include <cstdlib>
#include <iostream>

#include "game.h"

/****** MapGame ******/

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

bool MapGame::isFinished() {
	VertexIterator it = graph.getVertices();
	while(it.hasNext()) {
		vertex curr = it.getCurrent();
		if (graph.getVertexProperties(curr).getColor() == -1)
			return false;
		it.moveNext();
	}
	return true;
}

bool MapGame::canContinue() {
	return !isFinished();
}

void MapGame::play(Player& alice, Player& bob) {
	while (!isFinished() && canContinue()) {
		alice.play();
		bob.play();
	}
	if (isFinished())
		std::cout << "alice a gagné" << std::endl;
	else
		std::cout << "bob a gagné" << std::endl;
}

/****** SelectionAlgorithm ******/
SelectionAlgorithm::SelectionAlgorithm(MapGame& game)
	: game(game) {

}

vertex SelectionAlgorithm::selectVertex() {
	int nbVertices = game.getGraph().getNbVertices();
	int r = rand() % nbVertices;
	return game.getGraph().getVertex(r);
}

color SelectionAlgorithm::selectColor(vertex v) {
	return game.getFirstUnusedColor();
}

/****** Player ******/
Player::Player(SelectionAlgorithm& algo, MapGame& game)
	: algo(algo), game(game) {

}

void Player::play() {
	vertex v = algo.selectVertex();
	color c = algo.selectColor(v);
	game.getGraph().getVertexProperties(v).setColor(c);
	std::cout << "coloring vertex " << v << " with color " << c << std::endl;
}