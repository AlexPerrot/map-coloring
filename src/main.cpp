#include <iostream>
#include <cstdlib>

#include "graph/graph.h"
#include "game/game.h"

int main(int argc, char* argv[]) {

	srand(time(0));

	int nbParties = 10;
	if (argc > 1)
		nbParties = atoi(argv[1]);

	Graph g;
	for(int i=0 ; i<6 ; i++)
		g.addVertex();
	g.addEdge(g.getVertex(1), g.getVertex(2));
	g.addEdge(g.getVertex(1), g.getVertex(5));
	g.addEdge(g.getVertex(2), g.getVertex(3));
	g.addEdge(g.getVertex(2), g.getVertex(5));
	g.addEdge(g.getVertex(3), g.getVertex(4));
	g.addEdge(g.getVertex(4), g.getVertex(5));
	g.addEdge(g.getVertex(0), g.getVertex(5));

	MapGame game(g, 3);

	std::cout << "The graph has " << game.getGraph().getNbVertices()
		 << " vertices"  << std::endl;
	std::cout << (game.isFinished()?"finished":"not finished") << std::endl;

	SelectionAlgorithm algoAlice(game), algoBob(game);
	Player alice(algoAlice, game);
	Player bob(algoBob, game);
	int nbGagnees = 0;
	for (int i = 0; i < nbParties; ++i)
	{
		if (game.play(alice, bob))
			++nbGagnees;
		game.reset();
	}

	std::cout << "alice a gagne " << nbGagnees << "/" << nbParties << " parties" << std::endl;
}
