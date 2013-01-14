#include <iostream>
#include <cstdlib>
#include <time.h>

// For testing purpose
// #include <chrono>
// #include <thread>
// End for testing purpose

#include "graph/graph.h"
#include "game/game.h"
#include "monte_carlo/monte_carlo.h"
#include "monte_carlo/monte_carlo_algo.h"

void usage(std::ostream& stream) {
  stream << "usage: map_coloring graph.dot nb_colors [nb_games]" << std::endl;
  exit(0);
}

int main(int argc, char* argv[]) {

  if (argc < 3)
    usage(std::cout);

  int nb_colors = atoi(argv[2]);
	srand(time(0));

	int nbParties = 10;
	if (argc > 3)
		nbParties = atoi(argv[3]);

	Graph g;
	g.getGraphFromDot(argv[1]);
	/*for(int i=0 ; i<6 ; i++)
		g.addVertex();
	g.addEdge(g.getVertex(1), g.getVertex(2));
	g.addEdge(g.getVertex(1), g.getVertex(5));
	g.addEdge(g.getVertex(2), g.getVertex(3));
	g.addEdge(g.getVertex(2), g.getVertex(5));
	g.addEdge(g.getVertex(3), g.getVertex(4));
	g.addEdge(g.getVertex(4), g.getVertex(5));
	g.addEdge(g.getVertex(0), g.getVertex(5));
	*/
	MapGame game(g, nb_colors);

	std::cout << "The graph has " << game.getGraph().getNbVertices()
		 << " vertices"  << std::endl;
	std::cout << (game.isFinished()?"finished":"not finished") << std::endl;

	MonteCarloSelection algoAlice(game, false), algoBob(game, true);
	Player alice(algoAlice);
	Player bob(algoBob);
	int nbGagnees = 0;
	for (int i = 0; i < nbParties; ++i)
	{
		if (game.play(alice, bob))
			++nbGagnees;
		game.reset();
		algoAlice.reset();
		algoBob.reset();
	}

	std::cout << "alice a gagne " << nbGagnees << "/" << nbParties << " parties" << std::endl;

	// MonteCarloNode* mcTree = new MonteCarloNode(&game);
	// int nbWon = simulate(mcTree, nbParties, false, UCB1);
	// std::cout << "Monte-Carlo a gagne " << nbWon << "/" << nbParties << " parties" << std::endl;

	// mcTree->deleteChildren();
	// delete mcTree;

	// For testing purpose
	// g.printGraph(); // Only works on graph generated from a dot file using getGraphFromDot
	// std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	// End for testing purpose
}
