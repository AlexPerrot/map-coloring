#include "monte_carlo_algo.h"

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
	simulate(tree, 1000, minimize, UCB1);

	//selection du coup
	int nbPlayed = 0;
	MonteCarloNode* best(0);
	std::vector<MonteCarloNode*> children = tree->getChildren();
	for(std::vector<MonteCarloNode*>::iterator it=children.begin() ;
	    it != children.end() ; ++it) {
		if((*it)->gamesPlayed > nbPlayed) {
			nbPlayed = (*it)->gamesPlayed;
			best = (*it);
		}
	}
	
	best->playMove();
	tree = best;
	tree->deleteParent();

	return *(tree->getMove());

}