#include "monte_carlo_algo.h"

static int nb_simu = 1000;

void setNumberOfSimulations(int nb) {
  nb_simu = nb;
}

MonteCarloSelection::MonteCarloSelection(MapGame& game, bool minimize)
	: SelectionAlgorithm(game), tree(0), minimize(minimize) {
	MapGame* tmp = new MapGame(game);
	tree = new MonteCarloNode(tmp);
}

ColoringMove MonteCarloSelection::selectMove() {
	//synchro avec le vrai graphe
	//recuperation du coup de l'adversaire
	vertex v;
	color c=-1;
	bool found;
	VertexIterator it = game.getGraph().getVertices();
	while(it.hasNext()) {
		if(game.getGraph().getVertexProperties(it.getCurrent()).getColor() !=
		   tree->getGame()->getGraph().getVertexProperties(it.getCurrent()).getColor()) {
			v = it.getCurrent();
			c = game.getGraph().getVertexProperties(v).getColor();
			found = true;
			break;
		}
		it.moveNext();
	}
	
	if(found) {
		//synchro de l'arbre
		std::vector<MonteCarloNode*> children = tree->getChildren();
		for(std::vector<MonteCarloNode*>::iterator it=children.begin() ;
		    it != children.end() ; ++it) {
			ColoringMove* move = (*it)->getMove();
			if(move->getVertex()==v && move->getColor()==c) {
				(*it)->playMove();
				tree=(*it);
				tree->deleteParent();
				break;
			}
		}
	}

	//simulations
	simulate(tree, nb_simu, minimize, UCB1);

	//selection du coup
	std::vector<MonteCarloNode*> children = tree->getChildren();
	MonteCarloNode* best(children.at(0));
	int nbWon = best->gamesWon;
	for(std::vector<MonteCarloNode*>::iterator it=children.begin() ;
	    it != children.end() ; ++it) {
		switch(minimize) {
		case false:
			if((*it)->gamesWon > nbWon) {
				nbWon = (*it)->gamesWon;
				best = (*it);
			}
			break;
		case true:
			if((*it)->gamesWon < nbWon) {
				nbWon = (*it)->gamesWon;
				best = (*it);
			}
			break;
		}
	}
	
	best->playMove();
	tree = best;
	tree->deleteParent();

	return *(tree->getMove());

}

void MonteCarloSelection::reset() {
	delete tree->getGame();
	tree->deleteChildren();
	delete tree;
	MapGame* tmp = new MapGame(game);
	tree = new MonteCarloNode(tmp);
}
