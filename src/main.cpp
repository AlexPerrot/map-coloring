#include <iostream>
#include <cstdlib>
#include <time.h>

// For testing purpose
#include <chrono>
#include <thread>
// End for testing purpose

#include "graph/graph.h"
#include "game/game.h"

int main() {

	srand(time(0));

	Graph g;
	g.getGraphFromDot("graphviz_example.dot");
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
	MapGame game(g, 3);

	std::cout << "The graph has " << game.getGraph().getNbVertices()
		 << " vertices"  << std::endl;
	std::cout << (game.isFinished()?"finished":"not finished") << std::endl;

	SelectionAlgorithm algoAlice(game), algoBob(game);
	Player alice(algoAlice, game);
	Player bob(algoBob, game);
	game.play(alice, bob);

	// For testing purpose
	g.printGraph(); // Only works on graph generated from a dot file using getGraphFromDot
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	// End for testing purpose
}
