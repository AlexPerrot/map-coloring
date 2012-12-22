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
	//tableau d'existence des couleurs dans le voisinage
	bool * existingColors = new bool[maxColors];

	//parcours de tous les sommets du graphe
	VertexIterator it = graph.getVertices();
	while (it.hasNext()) {
		vertex curr = it.getCurrent();

		//remise à zero des couleurs
		for (int i=0 ; i<maxColors ; i++)
			existingColors[i] = false;

		//parcours des voisins
		AdjacencyIterator neigh = graph.getNeighbours(curr);
		while(neigh.hasNext()) {
			color c = graph.getVertexProperties(neigh.getCurrent()).getColor();
			//ajout des couleurs existantes
			if (c>=0)
				existingColors[c] = true;
			neigh.moveNext();
		}

		//verification du nombre de couleurs
		bool seesEveryColor = true;
		for (int i=0 ; i<maxColors ; i++)
			seesEveryColor &= existingColors[i];

		//le sommet a toutes les couleurs voisines
		if (seesEveryColor) {
			delete[] existingColors;
			return false;
		}

		it.moveNext();
	}

	delete[] existingColors;
	return true;
}

void MapGame::play(Player& alice, Player& bob) {
	while (!isFinished() && canContinue()) {
		alice.play();
		if (!isFinished() && canContinue())
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
	vertex v;
	do {
		int nbVertices = game.getGraph().getNbVertices();
		int r = rand() % nbVertices;
		v = game.getGraph().getVertex(r);
	} while (game.getGraph().getVertexProperties(v).isColored());
	return v;
}

color SelectionAlgorithm::selectColor(vertex v) {
	int maxColors = game.getMaxColors();
	bool * existingColors = new bool[maxColors];
	for (int i=0 ; i<maxColors ; i++)
			existingColors[i] = false;

	AdjacencyIterator neigh = game.getGraph().getNeighbours(v);
	while(neigh.hasNext()) {
			color c = game.getGraph().getVertexProperties(neigh.getCurrent()).getColor();
			//ajout des couleurs existantes
			if (c>=0)
				existingColors[c] = true;
			neigh.moveNext();
	}
	color c = game.getFirstUnusedColor();
	if (c>=game.getMaxColors() )
		c = rand()%game.getMaxColors();
	while(existingColors[c])
		c = rand()%game.getMaxColors();
	delete[] existingColors;
	return c;
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