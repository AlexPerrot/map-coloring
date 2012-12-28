#include <cstdlib>
#include <iostream>
#include <vector>

#include "game.h"

/****** MapGame ******/

MapGame::MapGame(Graph& g, int maxColors)
 : graph(g), maxColors(maxColors), firstUnusedColor(0) {

 }

Graph& MapGame::getGraph() {
	return graph;
}

color MapGame::getFirstUnusedColor() {
	color max = -1;
	VertexIterator vertices = graph.getVertices();
	while(vertices.hasNext()) {
		vertex curr = vertices.getCurrent();
		color c = graph.getVertexProperties(curr).getColor();
		if (c>max)
			max = c;
		vertices.moveNext();
	}
	return max+1;
}

int MapGame::getMaxColors() {
	return maxColors;
}

bool MapGame::isFinished() {
	VertexIterator it = graph.getVertices();
	while(it.hasNext()) {
		vertex curr = it.getCurrent();
		if (!graph.getVertexProperties(curr).isColored())
			return false;
		it.moveNext();
	}
	return true;
}

bool* MapGame::getVisibleColors(vertex v) {
	bool * existingColors = new bool[maxColors];
	
	//parcours des voisins
	AdjacencyIterator neigh = graph.getNeighbours(v);
	while(neigh.hasNext()) {
		color c = graph.getVertexProperties(neigh.getCurrent()).getColor();
		//ajout des couleurs existantes
		if (c>=0)
			existingColors[c] = true;
		neigh.moveNext();
	}

	return existingColors;
}

bool MapGame::seesEveryColor(vertex v) {
	//tableau d'existence des couleurs dans le voisinage
	bool* existingColors = getVisibleColors(v);


	//verification du nombre de couleurs
	bool seesEveryColor = true;
	for (int i=0 ; i<maxColors ; i++)
		seesEveryColor &= existingColors[i];

	//le sommet a toutes les couleurs voisines
	if (seesEveryColor) {
		delete[] existingColors;
		return true;
	}

	delete[] existingColors;
	return false;
}

bool MapGame::canContinue() {

	//parcours de tous les sommets du graphe
	VertexIterator it = graph.getVertices();
	while (it.hasNext()) {
		vertex curr = it.getCurrent();

		if(seesEveryColor(curr))
			return false;		

		it.moveNext();
	}

	return true;
} 

bool MapGame::play(Player& alice, Player& bob) {
	while (!isFinished() && canContinue()) {
		alice.play(graph);
		if (!isFinished() && canContinue())
			bob.play(graph);
	}
	return isFinished();
}

void MapGame::reset() {
	VertexIterator it = graph.getVertices();
	while (it.hasNext()) {
		vertex curr = it.getCurrent();
		graph.getVertexProperties(curr).uncolor();
		it.moveNext();
	}
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
	bool * existingColors = game.getVisibleColors(v);
	color max = game.getFirstUnusedColor()+1;
	if (max>game.getMaxColors())
		max = game.getMaxColors();
	color c = rand()%max;
	while(existingColors[c])
		c = rand()%max;
	delete[] existingColors;
	return c;
}

ColoringMove SelectionAlgorithm::selectMove() {
	vertex v = selectVertex();
	color c = selectColor(v);
	return ColoringMove(v, c);
}

/****** Player ******/
Player::Player(SelectionAlgorithm& algo)
	: algo(algo) {

}

void Player::play(Graph& graph) {
	ColoringMove move = algo.selectMove();
	
	// std::cout << "coloring vertex " << move.getVertex() <<
	//  " with color " << move.getColor() << std::endl;

	 move.play(graph);
}

std::vector<ColoringMove*> getPossibleMoves(MapGame* game) {
	std::vector<ColoringMove*> moves;
	Graph& g = game->getGraph();
	color fuc = game->getFirstUnusedColor();
	VertexIterator vertices = g.getVertices();
	while(vertices.hasNext()) {
		vertex curr = vertices.getCurrent();

		if(!g.getVertexProperties(curr).isColored()) {
			bool* colors = game->getVisibleColors(curr);
			for(int i=0 ; i<fuc ; ++i) {
				if (!colors[i]) {
					moves.push_back(new ColoringMove(curr, i));
				}
			}
			delete[] colors;
		}
		if (fuc < game->getMaxColors())
			moves.push_back(new ColoringMove(curr, fuc));

		vertices.moveNext();
	}
	return moves;
}
